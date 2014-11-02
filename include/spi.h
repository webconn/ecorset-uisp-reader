#ifndef INCLUDE_SPI_H
#define INCLUDE_SPI_H

void spi_init(void);
uint8_t spi_write(const uint8_t *buf, uint8_t len);
uint8_t spi_read(uint8_t *buf, uint8_t len);

#endif
