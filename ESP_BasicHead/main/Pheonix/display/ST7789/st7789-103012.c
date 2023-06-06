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

bool ST7789_write_command(uint8_t cmd)
{
	static uint8_t Byte = 0;
	Byte = cmd;
	LCD_RS_CLR; // gpio_set_level(dev->_dc, SPI_Command_Mode);
	return lcd_write_byte(LCD_HANLDE, &Byte, 1);
}

bool ST7789_write_data_byte(uint8_t data)
{
	static uint8_t Byte = 0;
	Byte = data;
	LCD_RS_SET; // gpio_set_level(dev->_dc, SPI_Data_Mode);
	return lcd_write_byte(LCD_HANLDE, &Byte, 1);
}

bool ST7789_write_data_bytes(uint8_t* data, uint32_t size)
{
	LCD_RS_SET; // gpio_set_level(dev->_dc, SPI_Data_Mode);
	return lcd_write_byte(LCD_HANLDE, data, size);
}


bool ST7789_write_data_word(uint16_t data)
{
	static uint8_t Byte[2];
	Byte[0] = (data >> 8) & 0xFF;
	Byte[1] = data & 0xFF;
	LCD_RS_SET; //gpio_set_level(dev->_dc, SPI_Data_Mode);
	return lcd_write_byte(LCD_HANLDE, Byte, 2);
}

bool ST7789_write_addr(uint16_t addr1, uint16_t addr2)
{
	static uint8_t Byte[4];
	Byte[0] = (addr1 >> 8) & 0xFF;
	Byte[1] = addr1 & 0xFF;
	Byte[2] = (addr2 >> 8) & 0xFF;
	Byte[3] = addr2 & 0xFF;
	LCD_RS_SET; // gpio_set_level(dev->_dc, SPI_Data_Mode);
	return lcd_write_byte(LCD_HANLDE, Byte, 4);
}

void ST7789_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	ST7789_write_command(0x2a); //	列地址设置，即X坐标
	ST7789_write_data_word(x1 + LCDHandler.xOffset);
	ST7789_write_data_word(x2 + LCDHandler.xOffset);

	ST7789_write_command(0x2b); //	行地址设置，即Y坐标
	ST7789_write_data_word(y1 + LCDHandler.yOffset);
	ST7789_write_data_word(y2 + LCDHandler.yOffset);

	ST7789_write_command(0x2c); //	开始写入显存，即要显示的颜色数据
}
	

void ST7789_DisplayOn(void)
{
	/* Display ON command */
	ST7789_write_command(ST77XX_DISPLAY_ON);

	/* Sleep Out command */
	ST7789_write_command(ST77XX_SLEEP_OUT) ;
}
void ST7789_SetRotation(uint8_t rotation) {
	uint8_t madctl = 0;
	
	switch (rotation) {
	case 0:
		madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MY | ST77XX_MADCTL_RGB;
		break;
	case 1:
		madctl = ST77XX_MADCTL_MY | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
		break;
	case 2:
		madctl = ST77XX_MADCTL_RGB;
		break;
	case 3:
		madctl = ST77XX_MADCTL_MX | ST77XX_MADCTL_MV | ST77XX_MADCTL_RGB;
		break;
	}
	ST7789_write_command(ST77XX_MADCTL);
	ST7789_write_data_byte(madctl);
}

void ST7789_Init()
{
	
	uint8_t   parameter[14];

	/* Initialize ST7789 low level bus layer ----------------------------------*/

	/* Sleep In Command */
	ST7789_write_command(ST77XX_SLEEP_IN);
	/* Wait for 10ms */
	vTaskDelay(10);

	/* SW Reset Command */
	ST7789_write_command(0x01);
	/* Wait for 200ms */
	vTaskDelay(200) ;

	/* Sleep Out Command */
	ST7789_write_command(ST77XX_SLEEP_OUT);
	/* Wait for 120ms */
	vTaskDelay(120);

	/* Normal display for Driver Down side */
	ST7789_write_command(ST77XX_NORMAL_DISPLAY);
	ST7789_write_data_byte(0x00);

	/* Color mode 16bits/pixel */
	parameter[0] = 0x05;
	ST7789_write_command(ST77XX_COLOR_MODE);
	ST7789_write_data_byte(0x05);
	
	/* Display inversion On */
	ST7789_write_command(ST77XX_DISPLAY_INVERSION);
	
	/* Set Column address CASET */
	parameter[0] = 0x00;
	parameter[1] = 0x00;
	parameter[2] = 0x00;
	parameter[3] = 0xEF;
	ST7789_write_command(ST77XX_CASET);
	ST7789_write_data_bytes(parameter, 4);
	/* Set Row address RASET */
	parameter[0] = 0x00;
	parameter[1] = 0x00;
	parameter[2] = 0x00;
	parameter[3] = 0xEF;
	ST7789_write_command(ST77XX_RASET);
	ST7789_write_data_bytes(parameter, 4);

	/*--------------- ST7789 Frame rate setting -------------------------------*/
	/* PORCH control setting */
	parameter[0] = 0x0C;
	parameter[1] = 0x0C;
	parameter[2] = 0x00;
	parameter[3] = 0x33;
	parameter[4] = 0x33;
	ST7789_write_command(ST77XX_PORCH_CTRL);
	ST7789_write_data_bytes(parameter, 5);
	/* GATE control setting */
	ST7789_write_command(ST77XX_GATE_CTRL);
	ST7789_write_data_byte(0x35);

	/*--------------- ST7789 Power setting ------------------------------------*/
	/* VCOM setting */
	ST7789_write_command(ST77XX_VCOM_SET);
	ST7789_write_data_byte(0x1F);

	/* LCM Control setting */
	ST7789_write_command(ST77XX_LCM_CTRL);
	ST7789_write_data_byte(0x2C);

	/* VDV and VRH Command Enable */
	parameter[0] = 0x01;
	parameter[1] = 0xC3;
	ST7789_write_command(ST77XX_VDV_VRH_EN);
	ST7789_write_data_bytes(parameter, 2);

	/* VDV Set */
	parameter[0] = 0x20;
	ST7789_write_command(ST77XX_VDV_SET);
	ST7789_write_data_bytes(parameter, 0x20);

	/* Frame Rate Control in normal mode */
	parameter[0] = 0x0F;
	ST7789_write_command(ST77XX_FR_CTRL);
	ST7789_write_data_byte(0x0F);

	/* Power Control */
	parameter[0] = 0xA4;
	parameter[1] = 0xA1;
	ST7789_write_command(ST77XX_POWER_CTRL);
	ST7789_write_data_bytes(parameter, 1);

	/*--------------- ST7789 Gamma setting ------------------------------------*/
	/* Positive Voltage Gamma Control */
	parameter[0] = 0xD0;
	parameter[1] = 0x08;
	parameter[2] = 0x11;
	parameter[3] = 0x08;
	parameter[4] = 0x0C;
	parameter[5] = 0x15;
	parameter[6] = 0x39;
	parameter[7] = 0x33;
	parameter[8] = 0x50;
	parameter[9] = 0x36;
	parameter[10] = 0x13;
	parameter[11] = 0x14;
	parameter[12] = 0x29;
	parameter[13] = 0x2D;
	ST7789_write_command(ST77XX_PV_GAMMA_CTRL);
	ST7789_write_data_bytes(parameter, 14);

	/* Negative Voltage Gamma Control */
	parameter[0] = 0xD0;
	parameter[1] = 0x08;
	parameter[2] = 0x10;
	parameter[3] = 0x08;
	parameter[4] = 0x06;
	parameter[5] = 0x06;
	parameter[6] = 0x39;
	parameter[7] = 0x44;
	parameter[8] = 0x51;
	parameter[9] = 0x0B;
	parameter[10] = 0x16;
	parameter[11] = 0x14;
	parameter[12] = 0x2F;
	parameter[13] = 0x31;
	ST7789_write_command(ST77XX_NV_GAMMA_CTRL);
	ST7789_write_data_bytes(parameter, 14);
	

	/* Display ON command */
	//ST7789_DisplayOn();

	/* Tearing Effect Line On: Option (00h:VSYNC Interface OFF, 01h:VSYNC Interface ON) */
	parameter[0] = 0x00;
	ST7789_write_command(ST77XX_TEARING_EFFECT);
	ST7789_write_data_byte(0);

	//ST7789_write_command(colorMode == COLOR_MODE_INVERT ? ST7789_COLOR_INVERT_ON : ST7789_COLOR_INVERT_OFF);
	
	LCD_BL_SET;
}
void Init_Display()
{
	SetupMyLCD();
	ST7789_Init();
//	ST7789_SetRotation(2);
	LCDHandler.ColorTable = ColorNormalTable;	
}

void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf)
{
	uint16_t* pData = buf;
	int xx = x + w > LCD_WIDTH ? LCD_WIDTH - 1 : x + w;
	int yy = y + h > LCD_HEIGHT ? LCD_HEIGHT - 1 : y + h;
	w = xx - x;
	ST7789_SetAddress(x, y, xx, yy);
		
	for (uint16_t i = y; i < yy; i++) {
		for (uint16_t j = x; j < xx; j++) {
			ST7789_write_data_word(buf[i * MAX_LCD_SIZE + j]);
		}
			
//		ST7789_write_data_bytes(pData, w *2);
//		pData += MAX_LCD_SIZE;
	}
}
#endif //BOARD_T_DISPLAY
