#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_rcc.h>
#include <cmsis_os.h>
#include "LCD5110.h"
#include "font.h"

void gotoPoint(LCD_Connection connection, unsigned char x,unsigned char y);
void setXY(LCD_Connection connection, unsigned char x,unsigned char y);

void writeByte(LCD_Connection connection, unsigned char data, unsigned char mode)
{
	unsigned char i;

	resetCS(connection);

	if (mode == DEFAULT_MODE)
		resetDC(connection);
	else
		setDC(connection);

	for (i = 0; i < 8; i++)
	{
		unsigned char r = data & 0x80;
		if (r == 1) 
			setDIN(connection);
		else
			resetDIN(connection);
		
		data <<= 1;
		
		resetCLK(connection);
		setCLK(connection);
	}
	
	setCS(connection);
}

void writeChar(LCD_Connection connection, unsigned char c)
{
	unsigned char line;
	unsigned char ch = 0;

	c = c - 32;

	for(line = 0; line < LINES; line++)
	{
		ch = font6_8[c][line];
		writeByte(connection, ch, 1);
	}
}

void setXY(LCD_Connection connection, unsigned char x, unsigned char y)
{
	unsigned char x1 = LINES * x;
	writeByte(connection, 0x40 | y, 0);
	writeByte(connection, 0x80 | x1, 0);
}

void clearDisplay(LCD_Connection connection)
{
	unsigned char i,j;
	
	for (i = 0; i < LINES; i++)
		for (j = 0; j < 84; j++)
			writeByte(connection, 0, 1);	
}

void displayImage(LCD_Connection connection, const char img[], int X, int Y)
{
	unsigned char x,y;
	
	for (y = 0; y < Y; y++)
	{
		gotoPoint(connection, 0, y);
		
		for (x = 0; x < X; x++) {
			writeByte(connection, img[y * X + x], 1);
		}
	}
}

void gotoPoint(LCD_Connection connection, unsigned char x,unsigned char y)
{
	writeByte(connection, 0x80 | x, 0);
	writeByte(connection, 0x40 | y, 0);
}

void setCS(LCD_Connection connection)
{
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.CS, GPIO_PIN_SET);
}

void setDIN(LCD_Connection connection)
{
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.DIN, GPIO_PIN_SET);
}

void setDC(LCD_Connection connection)
{
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.DC, GPIO_PIN_SET);
}

void setRST(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.RST, GPIO_PIN_SET);
}

void setCLK(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.Clocking.Port, connection.Clocking.CLK, GPIO_PIN_SET);
}

void resetCS(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.CS, GPIO_PIN_RESET);
}

void resetDIN(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.DIN, GPIO_PIN_RESET);
}

void resetDC(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.DC, GPIO_PIN_RESET);
}

void resetRST(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.SPI.Port, connection.SPI.RST, GPIO_PIN_RESET);
}

void resetCLK(LCD_Connection connection){
	HAL_GPIO_WritePin(connection.Clocking.Port, connection.Clocking.CLK, GPIO_PIN_RESET);
}
