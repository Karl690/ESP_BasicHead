#pragma once
#include "configure.h"
#ifdef BOARD_103012
#include "../lcdspi.h"

#define ST77XX_LCD_ID             0x04
#define ST77XX_SLEEP_IN           0x10
#define ST77XX_SLEEP_OUT          0x11
#define ST77XX_PARTIAL_DISPLAY    0x12
#define ST77XX_DISPLAY_INVERSION  0x21
#define ST77XX_DISPLAY_ON         0x29
#define ST77XX_WRITE_RAM          0x2C
#define ST77XX_READ_RAM           0x2E
#define ST77XX_CASET              0x2A
#define ST77XX_RASET              0x2B
#define ST77XX_VSCRDEF            0x33 /* Vertical Scroll Definition */
#define ST77XX_VSCSAD             0x37 /* Vertical Scroll Start Address of RAM */
#define ST77XX_TEARING_EFFECT     0x35
#define ST77XX_NORMAL_DISPLAY     0x36
#define ST77XX_IDLE_MODE_OFF      0x38
#define ST77XX_IDLE_MODE_ON       0x39
#define ST77XX_COLOR_MODE         0x3A
#define ST77XX_PORCH_CTRL         0xB2
#define ST77XX_GATE_CTRL          0xB7
#define ST77XX_VCOM_SET           0xBB
#define ST77XX_DISPLAY_OFF        0xBD
#define ST77XX_LCM_CTRL           0xC0
#define ST77XX_VDV_VRH_EN         0xC2
#define ST77XX_VDV_SET            0xC4
#define ST77XX_VCOMH_OFFSET_SET   0xC5
#define ST77XX_FR_CTRL            0xC6
#define ST77XX_POWER_CTRL         0xD0
#define ST77XX_PV_GAMMA_CTRL      0xE0
#define ST77XX_NV_GAMMA_CTRL      0xE1

#define ST77XX_MADCTL				0x36

#define ST77XX_MADCTL_MY			0x80
#define ST77XX_MADCTL_MX			0x40
#define ST77XX_MADCTL_MV			0x20
#define ST77XX_MADCTL_ML			0x10
#define ST77XX_MADCTL_RGB			0x00

#if defined(FK_407) || defined(CORE_407I)
#define ST77XX_COLOR_INVERT_ON			0x21
#define ST77XX_COLOR_INVERT_OFF			0x20
#else
#define ST77XX_COLOR_INVERT_ON			0x20
#define ST77XX_COLOR_INVERT_OFF			0x21
#endif


void ST7789_Init();
void Init_Display();
void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf);
#endif