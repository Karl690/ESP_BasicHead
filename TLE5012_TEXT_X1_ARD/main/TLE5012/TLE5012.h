#pragma once

#include <stdint.h>
#include "driver/gpio.h"

#define TLE5012_INVALIDANGLE 0xffff

typedef struct{
    gpio_num_t csq_pin;
	gpio_num_t data_pin;
	gpio_num_t sck_pin;
    unsigned char ssc_delay;
    uint16_t invalidAngle; //=0xffff
  
} TLE5012;

extern TLE5012 TLE5012Handler;

uint8_t J1850CRC8_Calc(const uint8_t *buf, int len);

void Init_TLE5012(gpio_num_t _csq, gpio_num_t _data, gpio_num_t _sck, unsigned char _ssc_delay);
void TLE5012_Write(uint16_t x);
uint16_t TLE5012_Read();
void TLE5012_Select();
void TLE5012_Deselect();
uint16_t TLE5012_ReadAngle();
void TLE5012_Start();
void TLE5012_Stop();