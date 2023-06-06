#include "configure.h"
#ifdef BOARD_T_DISPLAY
#include "main.h"
#include "../lcdspi.h"
#include "../colortables.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_heap_caps.h"
#include "st7789-t-display.h"



void ST7789_Init()
{
	
}



void Init_Display()
{
	SetupMyLCD();
	//ST7789_Init();
	LCDHandler.ColorTable = ColorSwapTable;
}

void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf)
{	
	esp_lcd_panel_draw_bitmap((esp_lcd_panel_handle_t)(LCDHandler.Handle), x, y, x + w, y + h, buf);
}
#endif //BOARD_T_DISPLAY
