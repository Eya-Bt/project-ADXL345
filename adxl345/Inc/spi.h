/*
 * spi.h
 *
 *  Created on: 16 déc. 2022
 *      Author: 21624
 */

#ifndef SPI_H_
#define SPI_H_

#include<stdint.h>
#include "stm32f4xx.h"

void spi_gpio_init(void);
void spi_config(void);
void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive(uint8_t *dat,uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif /* SPI_H_ */
