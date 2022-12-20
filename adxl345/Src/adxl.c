#include "adxl.h"


#define MULTI_BYTE_EN  0x40
#define READ_OPERATION 0x80

void adxl_read(uint8_t address, uint8_t * rxdata)
{
	uint8_t data[2];

	/*set read operation*/
	address |= READ_OPERATION;
	/*enable multi byte*/
	address |= MULTI_BYTE_EN;
	/*pull cs line low to enable slave*/
	cs_enable();
	/*send address*/
	spi1_transmit(&address,1);
	/*read 6 bytes*/
	spi1_receive(rxdata,6);
	/*pull cs line high to disable slave*/
	cs_disable();
}
void adxl_write(uint8_t address ,char value)
{
	uint8_t data[2];

	/*enable multi bite place adress into buffer*/
	data[0]=address|MULTI_BYTE_EN;
	/*PLACE DATA INTO BUFFER*/
	data[1]=value;
	/*pull cs line low to enable slave*/
	cs_enable();
	/*transmit data abd address*/
	spi1_transmit(data,2);
	/*pull cs line high to disable slave*/
	cs_disable();
}


void adxl_init(void)
{
	/*ENABLE SPI GPIO*/
	spi_gpio_init();

	/*config SPI*/
	spi_config();

	/*set data format range to +-4g*/
	adxl_write (DATA_FORMAT_R,FOUR_G);
	/*CONfIG POWER CONTROLE MEASURE BIT*/
	adxl_write (POWER_CTL_R,SET_MEASURE_B);
}


