#pragma once
#include "configure.h"
#ifdef BOARD_103012

#define PIN_POWER_ON                GPIO_NUM_15
#define PIN_HEARTBEAT				GPIO_NUM_38 //LCD_BL

#define HEARTBEAT_SET				gpio_set_level(PIN_HEARTBEAT, 1);
#define HEARTBEAT_CLR				gpio_set_level(PIN_HEARTBEAT, 0);

#define SPI2_LCD_RST			GPIO_NUM_46
#define SPI2_LCD_RS				GPIO_NUM_13
#define SPI2_LCD_CS				GPIO_NUM_10
#define SPI2_LCD_MOSI			GPIO_NUM_11
#define SPI2_LCD_SCK			GPIO_NUM_12

#define PIN_LCD_RST		SPI2_LCD_RST
#define PIN_LCD_RS		SPI2_LCD_RS
#define PIN_LCD_CS		SPI2_LCD_CS
#define PIN_LCD_MOSI	SPI2_LCD_MOSI
#define PIN_LCD_SCK		SPI2_LCD_SCK

#define LED1			GPIO_NUM_45 //Heater Status
#define LED2			GPIO_NUM_48 //Fan Status
#define LED3			GPIO_NUM_47 //Motor Dir
#define LED4			GPIO_NUM_21 //Motor Step
#define LED5			GPIO_NUM_15
#define LED6			GPIO_NUM_7
#define LED7			GPIO_NUM_14 //Connection Status
#define LED8			GPIO_NUM_13 // LCD RS
#define LED_BL			GPIO_NUM_38

#endif // BOARD_10312