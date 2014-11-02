#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void spi_init(void)
{
        DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB2);
        DDRB &= ~(1<<PB4);
        PORTB |= (1<<PB4); /* enable pull-up for MISO */
        PORTB |= (1<<PB2); /* force master mode */
        /* SPI setup: clock high when idle, fq = F_CPU / 16 */
        SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0);
}

uint8_t spi_write(const uint8_t *buf, uint8_t len)
{
        for (uint8_t i=0; i<len; i++) {
                SPDR = buf[i];
                while ( !(SPSR & (1<<SPIF)) );
        }
        return len;
}

uint8_t spi_read(uint8_t *buf, uint8_t len)
{
        for (uint8_t i=0; i<len; i++) {
                SPDR = 0;
                while ( !(SPSR & (1<<SPIF)) );
                buf[i] = SPDR;
        }
        return len;
}
