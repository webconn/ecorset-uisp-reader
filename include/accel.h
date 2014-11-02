#ifndef INCLUDE_ACCEL_H
#define INCLUDE_ACCEL_H

#include <stdint.h>

struct accel_data {
        uint8_t whoami;
        uint16_t data_x;
        uint16_t data_y;
        uint16_t data_z;
};

struct accel_data read_acc(uint8_t i);
void select_channel(uint8_t i);
void reset_channels(void);

#endif
