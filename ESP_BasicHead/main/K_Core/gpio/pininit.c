#include "pininit.h"
#include "configure.h"

void Init_GPIO(void)
{	
	gpio_set_direction(PIN_POWER_ON, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_POWER_ON, 1); //blink the backlight
	gpio_set_direction(PIN_HEARTBEAT, GPIO_MODE_OUTPUT);
//	gpio_set_level(LED_BL, 1); //blink the backlight
}

void gpio_output_enable(int pin, bool enable) {
	volatile uint32_t *r = GPIO_ENABLE_REG;
	if (pin > 31) pin -= 31, r = GPIO_ENABLE1_REG;
	r[0] &= ~BIT(pin);
	r[0] |= (enable ? 1U : 0U) << pin;
}

void gpio_output(int pin) {
	GPIO_FUNC_OUT_SEL_CFG_REG[pin] = 256; // Simple output, TRM 4.3.3
	gpio_output_enable(pin, 1);
}

void gpio_write(int pin, bool value) {
	volatile uint32_t *r = GPIO_OUT_REG;
	if (pin > 31) pin -= 31, r = GPIO_OUT1_REG;
	r[0] &= ~BIT(pin); // Clear first
	r[0] |= (value ? 1U : 0U) << pin; // Then set
}

void gpio_toggle(int pin) {
	volatile uint32_t *r = GPIO_OUT_REG;
	if (pin > 31) pin -= 31, r = GPIO_OUT1_REG;
	r[0] ^= BIT(pin);
}

void gpio_input(int pin) {
	// Index lookup table for IO_MUX_GPIOx_REG, TRM 4.12
	unsigned char map[40] = { 
		17,34,16,33,18,27,24,25,26,21, // 0-9
	    22,23,13,14,12,15,19,20,28,29, // 10-19
	    30,31,32,35,36,9, 10,11,0, 0, // 20-29
	    0,0,7,8, 5, 6, 1, 2, 3, 4 
	}; // 30-39
	volatile uint32_t *mux = REG(0X3ff49000);
	if (pin < 0 || pin > (int) sizeof(map) || map[pin] == 0) return;
	gpio_output_enable(pin, 0); // Disable output
	mux[map[pin]] |= BIT(9); // Enable input
}

bool gpio_read(int pin) {
	volatile uint32_t *r = GPIO_IN_REG;
	if (pin > 31) pin -= 31, r = GPIO_IN1_REG;
	return r[0] & BIT(pin) ? 1 : 0;
}
