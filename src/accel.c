#include "lis3dh.h"
#include "spi.h"
#include "accel.h"

#include <arch/antares.h>

void select_channel(uint8_t i) {
        PORTD |= (1<<3)|(1<<5)|(1<<6)|(1<<7);
        if (i == 0) PORTD &= ~(1<<3);
        else if (i == 1) PORTD &= ~(1<<5);
        else if (i == 2) PORTD &= ~(1<<6);
        else if (i == 3) PORTD &= ~(1<<7);
}

void reset_channels(void) {
        PORTD |= (1<<3)|(1<<5)|(1<<6)|(1<<7);
}

ANTARES_INIT_LOW(acc_init)
{
        /* init channel selectors */
        DDRD |= (1<<3)|(1<<5)|(1<<6)|(1<<7);
        reset_channels();

        /* init SPI and accelerometer itself */
        lis3dh_init();
#if 0
        for (uint8_t i=0; i<4; i++) {
                select_channel(i);
                lis3dh_write_u8(CTRL_REG1, 0x07); /* 50 Hz data rate, all axes */
                reset_channels();
        }
#endif
}

struct accel_data read_acc(uint8_t i)
{
        struct accel_data ret;

        select_channel(i);
        ret.whoami = lis3dh_read_u8(WHO_AM_I);
        reset_channels();
        select_channel(i);
        lis3dh_read(OUT_X_L, 6, (uint8_t *) &ret + 1);
        reset_channels();

        return ret;
}
