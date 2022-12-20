#include "usart.h"
#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define CR1_TE (1U<<3)
#define CR1_RE (1U<<2)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)
#define SR_RXNE (1U<<5)
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ

#define UART_BAUDRATE 115200



void uart2_rxtx_init(void)
{
	/*CONGIG UART
	 * ENABLE CLOCK ACCESS TO GPIOA*/
	RCC-> AHB1ENR |= GPIOAEN;
	 /* SET PA2 TO ALTERNATE FUNCTION*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);
	/* SET PA2 TO UART TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);
	/*set PA3 MODE to alternate function*/
	GPIOA ->MODER &=~(1U<<6);
	GPIOA->MODER |=(1U<<7);
	/* SET PA3 TO UART TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);
	 /* CONFIG USART MODULE*/
	RCC->APB1ENR |= UART2EN;
	/* CONGIG BAUDE RATE*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	 /* CONFIG THE TRANSFER DIRECTION*/
	USART2->CR1 = (CR1_TE|CR1_RE);
	 /* ENABLE UART MODULE*/
	USART2->CR1 |= CR1_UE;

}
void uart2_read(void)
{
	/*Make sure the receive data register is empty*/
		while(!(USART2->SR & SR_RXNE)){};
	/*read data*/
		return USART2->DR;
}
void uart2_write(int ch)
{
	/*Make sure the transmit data register is empty*/
	while(!(USART2->SR & SR_TXE)){};
	/*write to transmit data register*/
	USART2->DR = (ch & 0xff);
}
 static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphCLK, uint32_t BaudRate)
 {
	 USARTx->BRR = compute_uart_bd(PeriphCLK, BaudRate);
 }
 static uint16_t compute_uart_bd(uint32_t PeriphCLK, uint32_t BaudRate)
 {
	 return ((PeriphCLK+(BaudRate/2U))/BaudRate);
 }
