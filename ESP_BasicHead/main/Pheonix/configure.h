#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "global.h"
//driver includes
#include "driver/gpio.h"

///////////
#include "gpio/pininit.h"
#include "rcc/rcc.h"
#include "taskmanager.h"


#define USE_LCD
//#define BOARD_T_DISPLAY   //pick the hardware and pinassignments
#define BOARD_103012		//Hyrel smart head controller 103012 esp32-S3 based


#ifdef BOARD_T_DISPLAY
#include "gpio/pinout_T_display.h"	

#elif defined(BOARD_103012)
#include "gpio/pinout_103012.h"
#endif 

#ifdef USE_LCD
	#include "display/LcdDefinitions.h"	
	#ifdef BOARD_T_DISPLAY
		#include "display/ST7789/st7789-t-display.h"
	#elif defined(BOARD_103012)
		#include "display/ST7789/st7789-103012.h"
	#endif
	#include "display/display.h"
	#include "display/gui.h"
#endif