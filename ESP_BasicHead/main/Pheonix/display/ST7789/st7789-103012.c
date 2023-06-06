#include "configure.h"
#ifdef BOARD_103012
#include "main.h"
#include "../lcdspi.h"
#include "../colortables.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_heap_caps.h"


#include "st7789-103012.h"

#if 0
#ifdef CONFIG_IDF_TARGET_ESP32
#define LCD_HOST HSPI_HOST
#elif defined CONFIG_IDF_TARGET_ESP32S2
#define LCD_HOST SPI2_HOST
#elif defined CONFIG_IDF_TARGET_ESP32S3
#define LCD_HOST SPI2_HOST
#elif defined CONFIG_IDF_TARGET_ESP32C3
#define LCD_HOST SPI2_HOST
#endif
#endif
//#if CONFIG_SPI2_HOST
//#define HOST_ID SPI2_HOST
//#elif CONFIG_SPI3_HOST
//#define HOST_ID SPI3_HOST
//#endif

void ST7789_write_command(uint8_t cmd)
{
	LCD_CS_CLR;
	LCD_RS_CLR; // gpio_set_level(dev->_dc, SPI_Command_Mode);	
	lcd_write_byte(LCD_HANLDE, &cmd, 1);
	LCD_CS_SET;
}

void ST7789_write_data_byte(uint8_t data)
{
	
	LCD_CS_CLR;
	LCD_RS_SET;
	lcd_write_byte(LCD_HANLDE, &data, 1);
	LCD_CS_SET;
}

void ST7789_write_data_bytes(uint8_t* data, uint32_t size)
{
	LCD_RS_SET; // gpio_set_level(dev->_dc, SPI_Data_Mode);
	lcd_write_byte(LCD_HANLDE, data, size);
	LCD_CS_SET;
}


void ST7789_write_data_word(uint16_t data)
{
	static uint8_t Byte[2];
	Byte[0] = (data >> 8) & 0xFF;
	Byte[1] = data & 0xFF;
	LCD_CS_CLR;
	LCD_RS_SET;
	lcd_write_byte(LCD_HANLDE, Byte, 2);
	LCD_CS_SET;
	
}

void ST7789_write_addr(uint16_t addr1, uint16_t addr2)
{
	static uint8_t Byte[4];
	Byte[0] = (addr1 >> 8) & 0xFF;
	Byte[1] = addr1 & 0xFF;
	Byte[2] = (addr2 >> 8) & 0xFF;
	Byte[3] = addr2 & 0xFF;
	LCD_CS_CLR;
	LCD_RS_SET; // gpio_set_level(dev->_dc, SPI_Data_Mode);
	lcd_write_byte(LCD_HANLDE, Byte, 4);
	LCD_CS_SET;
}

void ST7789_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	ST7789_write_command(0x2a); //
	ST7789_write_data_word(x1 + LCDHandler.xOffset);
	//ST7789_write_data_word(x2 + LCDHandler.xOffset);

	ST7789_write_command(0x2b); //
	ST7789_write_data_word(y1 + LCDHandler.yOffset);
	//ST7789_write_data_word(y2 + LCDHandler.yOffset);

	ST7789_write_command(0x2c); //
}
	

void ST7789_DisplayOn(void)
{
	/* Display ON command */
	ST7789_write_command(ST7789_DISPON);

	/* Sleep Out command */
	ST7789_write_command(ST7789_SLPOUT) ;
}
void ST7789_SetRotation(uint8_t rotation) {
	uint8_t madctl = 0;
	
//	switch (rotation) {
//	case 0:
//		madctl = ST7789_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_RGB;
//		break;
//	case 1:
//		madctl = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
//		break;
//	case 2:
//		madctl = ST77XX_MADCTL_RGB;
//		break;
//	case 3:
//		madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
//		break;
//	}
//	ST7789_write_command(ST77XX_MADCTL);
//	ST7789_write_data_byte(madctl);
}

void ST7789_Fill_Color(uint16_t color)
{
	uint16_t i;
	ST7789_SetAddress(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

	uint16_t j;
	for (i = 0; i < LCD_WIDTH; i++)
		for (j = 0; j < LCD_HEIGHT; j++) {
			uint8_t data[] = { color >> 8, color & 0xFF };
			ST7789_write_data_word(color);
		}

}

void ST7789_Init()
{
	
	ST7789_write_command(ST7789_SLPOUT); // Sleep out
	vTaskDelay(120);

	ST7789_write_command(ST7789_NORON); // Normal display mode on

	//------------------------------display and color format setting--------------------------------//
	ST7789_write_command(ST7789_MADCTL);
	//writedata(0x00);
	ST7789_write_data_byte(0);

	// JLX240 display datasheet
	ST7789_write_command(0xB6);
	ST7789_write_data_byte(0x0A);
	ST7789_write_data_byte(0x82);

	ST7789_write_command(ST7789_RAMCTRL);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0xE0); // 5 to 6 bit conversion: r0 = r5, b0 = b5

	ST7789_write_command(ST7789_COLMOD);
	ST7789_write_data_byte(0x55);
	vTaskDelay(10);

	//--------------------------------ST7789V Frame rate setting----------------------------------//
	ST7789_write_command(ST7789_PORCTRL);
	ST7789_write_data_byte(0x0c);
	ST7789_write_data_byte(0x0c);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x33);
	ST7789_write_data_byte(0x33);

	ST7789_write_command(ST7789_GCTRL); // Voltages: VGH / VGL
	ST7789_write_data_byte(0x35);

	//---------------------------------ST7789V Power setting--------------------------------------//
	ST7789_write_command(ST7789_VCOMS);
	ST7789_write_data_byte(0x28); // JLX240 display datasheet

	ST7789_write_command(ST7789_LCMCTRL);
	ST7789_write_data_byte(0x0C);

	ST7789_write_command(ST7789_VDVVRHEN);
	ST7789_write_data_byte(0x01);
	ST7789_write_data_byte(0xFF);

	ST7789_write_command(ST7789_VRHS); // voltage VRHS
	ST7789_write_data_byte(0x10);

	ST7789_write_command(ST7789_VDVSET);
	ST7789_write_data_byte(0x20);

	ST7789_write_command(ST7789_FRCTR2);
	ST7789_write_data_byte(0x0f);

	ST7789_write_command(ST7789_PWCTRL1);
	ST7789_write_data_byte(0xa4);
	ST7789_write_data_byte(0xa1);

	//--------------------------------ST7789V gamma setting---------------------------------------//
	ST7789_write_command(ST7789_PVGAMCTRL);
	ST7789_write_data_byte(0xd0);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x02);
	ST7789_write_data_byte(0x07);
	ST7789_write_data_byte(0x0a);
	ST7789_write_data_byte(0x28);
	ST7789_write_data_byte(0x32);
	ST7789_write_data_byte(0x44);
	ST7789_write_data_byte(0x42);
	ST7789_write_data_byte(0x06);
	ST7789_write_data_byte(0x0e);
	ST7789_write_data_byte(0x12);
	ST7789_write_data_byte(0x14);
	ST7789_write_data_byte(0x17);

	ST7789_write_command(ST7789_NVGAMCTRL);
	ST7789_write_data_byte(0xd0);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x02);
	ST7789_write_data_byte(0x07);
	ST7789_write_data_byte(0x0a);
	ST7789_write_data_byte(0x28);
	ST7789_write_data_byte(0x31);
	ST7789_write_data_byte(0x54);
	ST7789_write_data_byte(0x47);
	ST7789_write_data_byte(0x0e);
	ST7789_write_data_byte(0x1c);
	ST7789_write_data_byte(0x17);
	ST7789_write_data_byte(0x1b);
	ST7789_write_data_byte(0x1e);

	ST7789_write_command(ST7789_INVON);

	ST7789_write_command(ST7789_CASET); // Column address set
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0xEF); // 239

	ST7789_write_command(ST7789_RASET); // Row address set
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x00);
	ST7789_write_data_byte(0x01);
	ST7789_write_data_byte(0x3F); // 319

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	end_tft_write();
//	vTaskDelay(120);
//	begin_tft_write();

	ST7789_write_command(ST7789_DISPON); //Display on
	vTaskDelay(120);

	LCD_BL_SET;

}
void Init_Display()
{
	SetupMyLCD();
	ST7789_Init();
//	ST7789_SetRotation(2);
	//ST7789_Fill_Color(RED);
	LCDHandler.ColorTable = ColorInvertTable;	
}

void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf)
{
	uint16_t* pData = buf;
	int xx = x + w > LCD_WIDTH ? LCD_WIDTH - 1 : x + w;
	int yy = y + h > LCD_HEIGHT ? LCD_HEIGHT - 1 : y + h;
	w = xx - x;
	ST7789_SetAddress(x, y, xx, yy);
		
	for (uint16_t i = y; i < yy; i++) {
		ST7789_write_data_bytes(pData, w *2);
		pData += LCD_WIDTH;
	}
}
#endif //BOARD_103012
