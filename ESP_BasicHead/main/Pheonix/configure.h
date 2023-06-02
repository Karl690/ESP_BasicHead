#pragma once
#include "global.h"
#include "gpio/pininit.h"
#include "gpio/pinout.h"
#include "rcc/rcc.h"
#include "taskmanager.h"

#define USE_LCD
#define ST7789
#ifdef USE_LCD
	#include "display/LcdDefinitions.h"
	#ifdef ST7789
		#include "display/ST7789/st7789.h"
	#endif
	#include "display/display.h"
	#include "display/gui.h"
#endif