#include <stdint.h>
#include "LcdDefinitions.h"
#define GUI_OK 		1
#define GUI_ERROR 	0



#define GUI_COLOR_BACKGROUND 		0x6101
#define GUI_COLOR_AXIS				0x2203
#define GUI_COLOR_GREEN				0xE707
#define GUI_COLOR_YELLOW			0xE0CF
#define GUI_COLOR_PINK				0x1FF8

#define GUI_COLOR_ADC_CHANNEL_01	GUI_COLOR_GREEN
#define GUI_COLOR_ADC_CHANNEL_02	GUI_COLOR_PINK


#define ABS(a) 		(a > 0? a: -a)
#define MAX(a,b) 		(a > b? a: b)
#define MIN(a,b) 		(a < b? a: b)
extern 	uint16_t* GUI_BUF;//[LCD_LINESIZE][MAX_LCD_SIZE];


void Init_GUI();
void ResetGuiBuffer(uint16_t color);
void DrawPixel(uint16_t X, uint16_t Y, uint16_t color);
void DrawHLine(uint16_t X1, uint16_t X2, uint16_t Y, uint16_t color);
void DrawVLine(uint16_t X, uint16_t Y1, uint16_t Y2, uint16_t color);
void DrawLine(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint16_t color);
void DrawRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
void FillRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
void DrawChar(uint16_t X, uint16_t Y, uint8_t chr, uint16_t color);
void DrawString(uint16_t X, uint16_t Y, char *str, uint16_t color);
