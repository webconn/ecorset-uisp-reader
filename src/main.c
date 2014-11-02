#include <arch/antares.h>
#include <avr/boot.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <generated/usbconfig.h>
#include <arch/vusb/usbportability.h>
#include <arch/vusb/usbdrv.h>
#include <arch/delay.h>
#include <string.h>
#include <stdio.h>

#include "accel.h"
#include "inner_usb.h"
#include "lis3dh.h"

uchar   usbFunctionSetup(uchar data[8])
{
        PORTC |= (1<<2);
        usbRequest_t *rq = (void *) data;

        uint8_t size = 0;
        static struct accel_data b_full;
        static union {
                uint8_t byte;
                uint16_t word;
        } b_int;

        select_channel(rq->wIndex.bytes[1]);

        switch (rq->bRequest) {
                case VENDOR_RQ_WRITE_8B:
                        lis3dh_write_u8(rq->wIndex.bytes[0], rq->wValue.bytes[0]);
                        b_int.byte = rq->wValue.bytes[0];
                        usbMsgPtr = (unsigned char *) &b_int.byte;
                        size = sizeof (uint8_t);
                        break;
                case VENDOR_RQ_READ_8B:
                        b_int.byte = lis3dh_read_u8(rq->wIndex.bytes[0]);
                        usbMsgPtr = (unsigned char *) &b_int.byte;
                        size = sizeof (uint8_t);
                        break;
                case VENDOR_RQ_WRITE_16B:
                        lis3dh_write_u16(rq->wIndex.bytes[0], rq->wValue.word);
                        b_int.word = rq->wValue.word;
                        usbMsgPtr = (unsigned char *) &b_int.word;
                        size = sizeof (uint16_t);
                        break;
                case VENDOR_RQ_READ_16B:
                        b_int.word = lis3dh_read_u16(rq->wIndex.word);
                        usbMsgPtr = (unsigned char *) &b_int.word;
                        size = sizeof (uint16_t);
                        break;
                case VENDOR_RQ_READ_FULL:
                        b_full = read_acc(rq->bRequest);
                        usbMsgPtr = (unsigned char *) &b_full;
                        size = sizeof (b_full);
                        break;
        }

        reset_channels();

        PORTC &= ~(1<<2);

        return size;
}

uchar usbFunctionWrite(uchar *data, uchar len)
{
        return 0;
}

static inline void usbReconnect()
{
        DDRD |= (1<<2)|(1<<4);
	_delay_ms(150);
        DDRD &= ~((1<<2)|(1<<4));
}

ANTARES_INIT_LOW(io_init)
{
	DDRC |= (1<<2); /* init LED */
        PORTC &= ~(1<<2);
 	usbReconnect();
}


ANTARES_INIT_HIGH(uinit)
{
  	usbInit();
}

ANTARES_APP(usb_app)
{
	usbPoll();
}
