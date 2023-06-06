#pragma once
#include "configure.h"

#ifdef USE_LCD
//Display Orientation Type
#define PORTRAIT 				0
#define PORTRAIT_ROT180 		1
#define LANDSCAPE				2
#define LANDSCAPE_ROT180		3

//Display Controller Type
#define ST7789_T_DISPLAY_LCD	0
#define ST7789_103012_LCD		1
#define ILI9341_LCD 			1
#define ST7735_LCD				2

//#define AB
#ifdef ST7735
/*
 * lcd display definition section
 * controller type ST7735
 * Width
 * Height
 * Orientation
 *
 *
 */

#define LCD_LINESIZE		14
#define PADDING 1				//Top side dead zone, in pixels
#define LEFT_PADDING 5				//Left side dead zone, in pixels
#define RIGHT_PADDING 5				//Right side dead zone, in pixels
#define VALUE_POS      	80
#define GUI_FONT_SIZE 				12
//Define the LCD Controller Type
#define ST7735_128_128_LANDSCAPE
//Display Orientation Type
#define PORTRAIT 				0
#define PORTRAIT_ROT180 		1
#define LANDSCAPE				2
#define LANDSCAPE_ROT180		3


	#define MAX_LCD_SIZE 		(MYLCD_WIDTH > MYLCD_HEIGHT?MYLCD_WIDTH:MYLCD_HEIGHT)


#elif defined(ILI9341)
 //* controller type ST7735
	#define LCD_LINESIZE		16
	#define TOP_PADDING 		5				//Top side dead zone, in pixels
	#define LEFT_PADDING 		5				//Left side dead zone, in pixels
	#define RIGHT_PADDING 		5				//Right side dead zone, in pixels
	#define VALUE_POS      		80
//Define the LCD Controller Type
//#define ILI9341_320_240_LANDSCAPE
	#define ILI9341_320_240_PORTRAIT

	#ifdef ILI9341_320_240_LANDSCAPE
		#define   MYLCD_CONTROLLER 		ILI9341_LCD
		#define   MYLCD_XOFFSET			0
		#define   MYLCD_YOFFSET			0
		#define   MYLCD_WIDTH			320
		#define   MYLCD_HEIGHT			240
		#define   MYLCD_ORIENTATION		LANDSCAPE
	#endif

	#ifdef ILI9341_320_240_PORTRAIT
		#define   MYLCD_CONTROLLER 		ILI9341_LCD
		#define   MYLCD_XOFFSET			0
		#define   MYLCD_YOFFSET			0
		#define   MYLCD_WIDTH			240
		#define   MYLCD_HEIGHT			320
		#define   MYLCD_ORIENTATION		PORTRAIT
	#endif

	#define MAX_LCD_SIZE 		(MYLCD_WIDTH > MYLCD_HEIGHT?MYLCD_WIDTH:MYLCD_HEIGHT)

#elif defined(BOARD_T_DISPLAY)
 //* controller type 
	#define LCD_LINESIZE		18
	#define PADDING 			1				//Top and Bottom side dead zone, in pixels
	#define LEFT_PADDING 		5				//Left side dead zone, in pixels
	#define RIGHT_PADDING 		5				//Right side dead zone, in pixels
	#define VALUE_POS      		80
	#define GUI_FONT_SIZE 		16
	//Define the LCD Controller Type
	//#define ILI9341_320_240_LANDSCAPE
	//#define ST7789_240_320_PORTRAIT
	#define ST7789_T_DISPLAY_320_170_PORTRAIT

	#if defined(ST7789_240_320_PORTRAIT)
		#define   MYLCD_CONTROLLER 		ST7789_LCD
		#define   MYLCD_XOFFSET			0
		#define   MYLCD_YOFFSET			0
		#define   MYLCD_WIDTH			240
		#define   MYLCD_HEIGHT			320
		#define   MYLCD_ORIENTATION		PORTRAIT //PORTRAIT

	#elif defined(ST7789_320_240_PORTRAIT)
		#define   MYLCD_XOFFSET			0
		#define   MYLCD_YOFFSET			0
		#define   MYLCD_CONTROLLER 		ST7789_LCD
		#define   MYLCD_WIDTH			240
		#define   MYLCD_HEIGHT			280
		#define   MYLCD_ORIENTATION		PORTRAIT	
	#elif defined(ST7789_T_DISPLAY_320_170_PORTRAIT)
		#define   MYLCD_XOFFSET			0
		#define   MYLCD_YOFFSET			0
		#define   MYLCD_CONTROLLER 		ST7789_LCD
		#define   MYLCD_WIDTH			320
		#define   MYLCD_HEIGHT			170
		#define   MYLCD_ORIENTATION		LANDSCAPE
	#endif

	#define MAX_LCD_SIZE 		(MYLCD_WIDTH > MYLCD_HEIGHT?MYLCD_WIDTH:MYLCD_HEIGHT)


#elif defined(BOARD_103012)
 //* controller type 
#define LCD_LINESIZE		18
#define PADDING 			1				//Top and Bottom side dead zone, in pixels
#define LEFT_PADDING 		5				//Left side dead zone, in pixels
#define RIGHT_PADDING 		5				//Right side dead zone, in pixels
#define VALUE_POS      		80
#define GUI_FONT_SIZE 		16
	//Define the LCD Controller Type	
#define ST7789_240_320_PORTRAIT
//#define ST7789_240_320_LANDSCAPE

#if defined(ST7789_240_320_PORTRAIT)
#define   MYLCD_CONTROLLER 		ST7789_LCD
#define   MYLCD_XOFFSET			0
#define   MYLCD_YOFFSET			0
#define   MYLCD_WIDTH			240
#define   MYLCD_HEIGHT			320
#define   MYLCD_ORIENTATION		LANDSCAPE //PORTRAIT
#elif defined(ST7789_240_320_LANDSCAPE)
#define   MYLCD_CONTROLLER 		ST7789_LCD
#define   MYLCD_XOFFSET			0
#define   MYLCD_YOFFSET			0
#define   MYLCD_WIDTH			320
#define   MYLCD_HEIGHT			240
#define   MYLCD_ORIENTATION		LANDSCAPE //PORTRAIT
#endif

#define MAX_LCD_SIZE 		(MYLCD_WIDTH > MYLCD_HEIGHT?MYLCD_WIDTH:MYLCD_HEIGHT)

#endif


#define LCD_WIDTH 	MYLCD_WIDTH
#define LCD_HEIGHT 	MYLCD_HEIGHT

#endif //USE_LCD