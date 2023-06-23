#pragma once

#include <stdint.h>
#include "driver/gpio.h"

#define TLE5012_INVALIDANGLE 0xffff
#define PIN_TLE5012_CSQ		2 //GPIO_NUM_39
#define PIN_TLE5012_DATA	1 //GPIO_NUM_38
#define PIN_TLE5012_SCK		3 //GPIO_NUM_36


uint8_t J1850CRC8_Calc(const uint8_t *buf, int len);

//void Init_TLE5012(gpio_num_t _csq, gpio_num_t _data, gpio_num_t _sck, unsigned char _ssc_delay);
void TLE5012_Write(uint16_t x);
uint16_t TLE5012_Read();
void TLE5012_Select();
void TLE5012_Deselect();
uint16_t TLE5012_ReadAngle();
void TLE5012_Start();
void TLE5012_Stop();