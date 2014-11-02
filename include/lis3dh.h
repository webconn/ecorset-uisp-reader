#ifndef INCLUDE_LIS3DH_H
#define INCLUDE_LIS3DH_H

/* Registers */
#include <avr/io.h>
#include <stdint.h>

#define STATUS_REG_AUX 0x07
#define OUT_ADC1_L 0x08
#define OUT_ADC1_H 0x09
#define OUT_ADC2_L 0x0A
#define OUT_ADC2_H 0x0B
#define OUT_ADC3_L 0x0C
#define OUT_ADC3_H 0x0D
#define INT_COUNTER_REG 0x0E
#define WHO_AM_I 0x0F

#define TEMP_CFG_REG 0x1F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25
#define REFERENCE 0x26
#define STATUS_REG2 0x27

#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SOURCE 0x31
#define INT1_THS 0x32
#define INT1_DURATION 0x33

#define CLICK_CFG 0x38
#define CLICK_SRC 0x39
#define CLICK_THS 0x3A
#define TIME_LIMIT 0x3B
#define TIME_LATENCY 0x3C
#define TIME_WINDOW 0x3D

void lis3dh_init(void);
uint8_t lis3dh_read(uint8_t addr, uint8_t len, uint8_t *buf);
uint8_t lis3dh_write(uint8_t addr, uint8_t len, const uint8_t *buf);

uint16_t lis3dh_read_u16(uint8_t addr);
uint8_t lis3dh_read_u8(uint8_t addr);

void lis3dh_write_u16(uint8_t addr, uint16_t val);
void lis3dh_write_u8(uint8_t addr, uint8_t val);

#endif
