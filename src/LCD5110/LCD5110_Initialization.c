#include "LCD5110.h"
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>
#include <cmsis_os.h>

#define DELAY 10

int configureGPIO(LCD_Connection connection);
int enableClocking(LCD_Connection connection);
int enablePortClocking(GPIO_TypeDef *port);
void configureSPIClockingPins(LCD_Clocking clockingData);
void configureSPITransmissionPins(LCD_SPI clockingData);

int initializeDisplay(LCD_Connection connection) {
	if (configureGPIO(connection) == ERROR_CODE) {
		return ERROR_CODE;
	}
	
	setDC(connection);
	setDIN(connection);
	setCLK(connection);
	setCS(connection);
	resetRST(connection);
	osDelay(DELAY);
	setRST(connection);
	writeByte(connection, 0x21,0);
	writeByte(connection, 0xc6,0);
	writeByte(connection, 0x06,0);
	writeByte(connection, 0x13,0);
	writeByte(connection, 0x20,0);
	clearDisplay(connection);
	writeByte(connection, 0x0c,0);
	
	return OK;
}

int configureGPIO(LCD_Connection connection) {
	if (enableClocking(connection) == ERROR_CODE) {
		return ERROR_CODE;
	}
	
	configureSPIClockingPins(connection.Clocking);
	configureSPITransmissionPins(connection.SPI);
	
	return OK;
}

void configureSPIClockingPins(LCD_Clocking clockingData) {
	GPIO_InitTypeDef GPIO_CLK;
	GPIO_CLK.Pin = clockingData.CLK;
	GPIO_CLK.Speed = GPIO_SPEED_MEDIUM;
	GPIO_CLK.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_CLK.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(clockingData.Port, &GPIO_CLK);
}

void configureSPITransmissionPins(LCD_SPI spi) {
	GPIO_InitTypeDef GPIO_SPI;
	GPIO_SPI.Pin = spi.CS | spi.DIN | spi.DC | spi.RST;
	GPIO_SPI.Speed = GPIO_SPEED_MEDIUM;
	GPIO_SPI.Pull= GPIO_NOPULL;
	GPIO_SPI.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(spi.Port,&GPIO_SPI);
}

int enableClocking(LCD_Connection connection){
	if (enablePortClocking(connection.SPI.Port) == ERROR_CODE){
		return ERROR_CODE;
	}
	
	if (enablePortClocking(connection.Clocking.Port) == ERROR_CODE) {
		return ERROR_CODE;
	}
	
	return OK;
}

int enablePortClocking(GPIO_TypeDef *port) {
	if (port == GPIOA) {
		__GPIOA_CLK_ENABLE();
	} 
	else if (port == GPIOB) {
		__GPIOB_CLK_ENABLE();
	} 
	else if (port == GPIOC) {
		__GPIOC_CLK_ENABLE();
	}
	else if (port == GPIOD) {
		__GPIOD_CLK_ENABLE();
	} 
	else 
		return ERROR_CODE;
	
	return OK;
}

