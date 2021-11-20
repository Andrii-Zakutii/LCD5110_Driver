#ifndef MAIN_H
#define MAIN_H

#include "LCD5110.h"
#include "image.h"

#define EXAMPLE_SPI_PORT GPIOC 
#define EXAMPLE_CS GPIO_PIN_9
#define EXAMPLE_DIN GPIO_PIN_6 
#define EXAMPLE_DC GPIO_PIN_7
#define EXAMPLE_RST GPIO_PIN_8

#define EXAMPLE_CLK_PORT GPIOA
#define EXAMPLE_CLK GPIO_PIN_8

#define IMAGE_X 8
#define IMAGE_Y 84

LCD_Connection getExampleConnectionData(void);
int main(void);

#endif
