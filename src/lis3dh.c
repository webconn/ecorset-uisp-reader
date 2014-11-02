#include "lis3dh.h"
#include "spi.h"

void lis3dh_init(void)
{
        spi_init();
}

uint8_t lis3dh_read(uint8_t addr, uint8_t len, uint8_t *buf)
{
        uint8_t rq = 0xC0 | addr; /* 0xC0 = 0xb110000000 <- read + increment */
        spi_write(&rq, 1);
        uint8_t ret = spi_read(buf, len);
        return ret;
}

uint8_t lis3dh_write(uint8_t addr, uint8_t len, const uint8_t *buf)
{
        uint8_t rq = 0x40 | addr; /* 0x40 = 0xb01000000 <- write + increment */
        spi_write(&rq, 1);
        uint8_t ret = spi_write(buf, len);
        return ret;
}


uint16_t lis3dh_read_u16(uint8_t addr)
{
        uint16_t ret = 0;
        lis3dh_read(addr, 2, (uint8_t *) &ret);
        return ret;
}

uint8_t lis3dh_read_u8(uint8_t addr)
{
        uint8_t ret = 0;
        lis3dh_read(addr, 1, (uint8_t *) &ret);
        return ret;
}

void lis3dh_write_u16(uint8_t addr, uint16_t val)
{
        lis3dh_write(addr, 2, (const uint8_t *) &val);
}

void lis3dh_write_u8(uint8_t addr, uint8_t val)
{
        lis3dh_write(addr, 1, (const uint8_t *) &val);
}
