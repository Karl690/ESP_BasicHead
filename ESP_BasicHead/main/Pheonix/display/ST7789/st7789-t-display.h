#pragma once
#include "configure.h"
#ifdef BOARD_T_DISPLAY

void ST7789_Init();
void Init_Display();
void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf);
#endif