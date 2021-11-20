#ifndef LCD5110_H
#define LCD5110_H

#define ERROR_CODE -1
#define OK 0
#define DEFAULT_MODE 0
#define LINES 6
#include <stm32f4xx_hal_gpio.h>

typedef struct {
	GPIO_TypeDef *Port;
	uint16_t CS;
	uint16_t DIN;
	uint16_t DC;
	uint16_t RST;
} LCD_SPI;

typedef struct {
	GPIO_TypeDef *Port;
	uint16_t CLK;
} LCD_Clocking;

typedef struct {
	LCD_SPI SPI;
	LCD_Clocking Clocking;
} LCD_Connection;

int initializeDisplay(LCD_Connection connection);
void displayImage(LCD_Connection connection, const char image[], int x, int y);
void writeChar(LCD_Connection connection, unsigned char letter);
void clearDisplay(LCD_Connection connection);
void writeByte(LCD_Connection connection, unsigned char dat, unsigned char mode);

void setCS(LCD_Connection connection);
void setDIN(LCD_Connection connection);
void setDC(LCD_Connection connection);
void setRST(LCD_Connection connection);
void setCLK(LCD_Connection connection);

void resetCS(LCD_Connection connection);
void resetDIN(LCD_Connection connection);
void resetDC(LCD_Connection connection);
void resetRST(LCD_Connection connection);
void resetCLK(LCD_Connection connection);

#endif
