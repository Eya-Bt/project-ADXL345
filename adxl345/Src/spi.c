#include "spi.h"

#define SPI1EN (1U<<12)
#define GPIOAEN (1U<<0)

#define SR_BSY (1U<<7)
#define SR_TXE (1U<<1)
#define SR_RXNE (1U<<0)

void spi_gpio_init(void)
{
	/*ENABLE CLOCK ACCESS TO GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*SET PA5,PA6,PA7 MODE TO ALTERNATE FUNCTION*/
	/*PA5*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |=(1U<<11);
	/*PA6*/
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |=(1U<<13);
	/*PA7*/
	GPIOA->MODER &=~(1U<<14);
	GPIOA->MODER |=(1U<<15);
	/*PA9 OUTPUT*/
	GPIOA->MODER &=~(1U<<19);
	GPIOA->MODER |=(1U<<18);

	/* SPI ALTERNATE FUNCTION TYPE FOR PA5,PA6 AND PA7*/
	/*PA5*/
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~ (1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &=~ (1U<<23);
	/*PA6*/
	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &=~ (1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &=~ (1U<<27);
	/*PA7*/
	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &=~ (1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &=~ (1U<<31);


}

void spi_config(void)
{
	/*ENABLE CLOCK ACCESS FOR SPI*/
	RCC->APB2ENR |= SPI1EN;
	/*SET CLOCK TO FPCLK/4 TO SET THE FREQUENCY TO 4MHz*/
	SPI1->CR1 |=(1U<<3);
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 &=~(1U<<5);
	/*SET CPOL TO 1 AND CPHA TO 1*/
	SPI1->CR1 |=(1U<<0);
	SPI1->CR1 |=(1U<<1);
	/* ENABLE FULL DUPLEX */
	SPI1->CR1 &=~(1U<<10);
	/*SET MSB FIRST*/
	SPI1->CR1 &=~(1U<<7);
	/*SET MODE TO MASTER*/
	SPI1->CR1 |=(1U<<2);
	/*SET 8 BITDATA MODE*/
	SPI1->CR1 &=~(1U<<11);
	/*SELECT SOFTARE SLAVE MANAGEMENT BY SETTING SSM=1 AND SSI=1*/
	SPI1->CR1 |=(1U<<8);
	SPI1->CR1 |=(1U<<9);
	/*ENABLE SPI MODULE*/
	SPI1->CR1 |=(1U<<6);
}

void spi1_transmit(uint8_t *data, uint32_t size)
{
	uint32_t i=0;
	uint8_t temp;
	while(i<size)
	{
		/*wait until TXE is set*/
		while(!(SPI1->SR & (SR_TXE))){}
		/*WRITE THE DATA REGISTER*/
		SPI1->DR = data[i];
		i++;
	}
	/*wait until TXE is set*/
	while(!(SPI1->SR & (SR_TXE))){}
	/*WAIT FOR BUSY FLAG TO RESET*/
	while((SPI1->SR & (SR_BSY))){}
	/*CLEAR OVER FLAG*/
	temp=SPI1->DR;
	temp=SPI1->SR;
}
void spi1_receive(uint8_t *data,uint32_t size)
{
	while(size)
	{
		/*send dummy data*/
		SPI1->DR =0;

		/*WAIT FOR RXNE FLAG TO BE SET*/
		while(!(SPI1->SR & (SR_RXNE))){}
		/*READ DATA FROM DATA REGISTER*/
		*data++ = (SPI1->DR);
		size--;
	}
}
void cs_enable(void)
{
	GPIOA->ODR &=~(1U<<9);
}
void cs_disable(void)
{
	GPIOA->ODR |=(1U<<9);
}
