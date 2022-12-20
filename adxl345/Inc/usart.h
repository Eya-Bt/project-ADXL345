/*
 * uart.h
 *
 *  Created on: 16 déc. 2022
 *      Author: 21624
 */

#ifndef USART_H_
#define USART_H_

#include<stdint.h>
#include "stm32f4xx.h"

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphCLK, uint32_t BaudRate);
void uart2_RXtx_init(void);
void uart2_write(int ch);
#endif /* USART_H_ */
