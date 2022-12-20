/*
 * adxl.h
 *
 *  Created on: 16 déc. 2022
 *      Author: 21624
 */

#ifndef ADXL_H_
#define ADXL_H_

#include "spi.h"
#include <stdint.h>

#define DATA_FORMAT_R (0x31)
#define POWER_CTL_R (0x2D)
#define DATA_START_ADDR (0x32)

#define FOUR_G (0x01)
#define SET_MEASURE_B (0x08)

void adxl_init(void);
void adxl_read(uint8_t address, uint8_t * rxdata);
void adxl_write(uint8_t reg ,char value);

#endif /* ADXL_H_ */
