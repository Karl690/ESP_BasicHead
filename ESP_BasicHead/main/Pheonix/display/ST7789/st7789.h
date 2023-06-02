#pragma once
#ifdef ST7789

typedef enum {
	COLOR_MODE_NORMAL,
	COLOR_MODE_INVERT,
	COLOR_MODE_SWAP,
}color_mode_t;

void Init_Display();
void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf);
#endif