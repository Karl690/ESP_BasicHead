#pragma once
#include "K_Core/configure.h"
#if defined(BOARD_T_DISPLAY) || defined(BOARD_103012) 
#include <driver/spi_master.h>

typedef struct
{
	void*						Handle;
	uint32_t					SpiFrequency;
	//addit ional pin information to complete the lcd interface
	
	// SPI pin out
	gpio_num_t                   SCK_Pin;
	gpio_num_t                   MOSI_Pin;
	gpio_num_t                   RST_Pin;
	gpio_num_t                   CS_Pin;
	gpio_num_t                   RS_Pin;
	gpio_num_t                   BKLT_Pin;
	//lcd specific information
	uint16_t					 xOffset;
	uint16_t					 yOffset;
	uint16_t                   width;
	uint16_t                   height;
	uint16_t                   orientation; //landscape , portrait,degrees 0-360
	uint16_t                   InitState; //0=not initialized   1=ok and ready
	uint16_t*				 	ColorTable;
	
} SPI_LCD_HandleTypeDef;


extern SPI_LCD_HandleTypeDef LCDHandler;


#define LCD_RS_CLR    	gpio_set_level(LCDHandler.RS_Pin, 0)
#define LCD_RS_SET    	gpio_set_level(LCDHandler.RS_Pin, 1)
#define LCD_CS_CLR    	gpio_set_level(LCDHandler.CS_Pin, 0)
#define LCD_CS_SET    	gpio_set_level(LCDHandler.CS_Pin, 1)
#define LCD_BL_CLR		gpio_set_level(LCDHandler.BKLT_Pin, 0)
#define LCD_BL_SET		gpio_set_level(LCDHandler.BKLT_Pin, 1)

#define LCD_HANLDE 		(LCDHandler.Handle)

void SetupMyLCD();
bool lcd_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength);
#endif // USE_LCD