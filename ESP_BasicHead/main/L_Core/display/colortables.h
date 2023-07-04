#pragma once
#include <stdint.h>
typedef enum {
	COLOR_MODE_NORMAL,
	COLOR_MODE_INVERT,
	COLOR_MODE_SWAP,
}color_mode_t;

typedef enum {
	COLOR_BLACK           = 0,
	COLOR_WHITE           = 1,
	COLOR_RED             = 2,
	COLOR_LIME            = 3,
	COLOR_BLUE            = 4,
	COLOR_YELLOW          = 5,
	COLOR_CYAN            = 6,
	COLOR_MAGENTA         = 7,
	COLOR_SILVER          = 8,
	COLOR_GRAY            = 9,
	COLOR_MAROON          = 10,
	COLOR_OLIVE           = 11,
	COLOR_GREEN           = 12,
	COLOR_PURPLE          = 13,
	COLOR_TEAL            = 14,
	COLOR_NAVY            = 15,
	COLOR_DARKRED         = 16,
	COLOR_TOMATO          = 17,
	COLOR_GOLD            = 18,
	COLOR_YELLOWGREEN     = 19,
	COLOR_FORESTGREEN     = 20,
	COLOR_SPRINGGREEN     = 21,
	COLOR_DARKCYAN        = 22,
	COLOR_PALETURQUOISE   = 23,
	COLOR_POWDERBLUE      = 24,
	COLOR_DEEPSKYBLUE     = 25,
	COLOR_LIGHTSKYBLUE    = 26,
	COLOR_DARKBLUE        = 27,
	COLOR_MEDINUSLATEBLUE = 28,
	COLOR_DARKVIOLET      = 29,
	COLOR_PLUM            = 30,
	COLOR_BEIGE           = 31,
	COLOR_INDEX_SIZE      = 32
}ColorIndex_t;

#define WHITE         	 (0xFFFF)
#define BLACK         	 (0x0000)
#define BLUE         	 (0x001F)
#define BRED             (0XF81F)
#define GRED 			 (0XFFE0)
#define GBLUE			 (0X07FF)
#define RED           	 (0xF800)
#define MAGENTA       	 (0xF81F)
#define GREEN         	 (0x07E0)
#define CYAN          	 (0x7FFF)
#define YELLOW        	 (0xFFE0)
#define BROWN 			 (0XBC40)
#define BRRED 			 (0XFC07)
#define GRAY  			 (0X8430)
#define DARKGRAY		 (0x3186)
#define DARKBLUE      	 (0X01CF)
#define LIGHTBLUE      	 (0X7D7C)
#define GRAYBLUE       	 (0X5458)

extern uint16_t ColorNormalTable[];
extern uint16_t ColorInvertTable[];
extern uint16_t ColorSwapTable[];
