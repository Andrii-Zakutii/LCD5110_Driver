#include "main.h"

int main(void) {
	LCD_Connection connectionData = getExampleConnectionData();
	
	if (initializeDisplay(connectionData) == ERROR_CODE) {
		return ERROR_CODE;
	}
	
	displayImage(connectionData, exampleImage, IMAGE_X, IMAGE_Y);
		
	while (1) {
	}
}

LCD_Connection getExampleConnectionData() {
	LCD_Connection data;
	data.SPI.Port = EXAMPLE_SPI_PORT;
	data.SPI.CS = EXAMPLE_CS;
	data.SPI.DC = EXAMPLE_DC;
	data.SPI.DIN = EXAMPLE_DIN;
	data.SPI.RST = EXAMPLE_RST;
	data.Clocking.Port = EXAMPLE_CLK_PORT;
	data.Clocking.CLK = EXAMPLE_CLK;
	return data;
}
