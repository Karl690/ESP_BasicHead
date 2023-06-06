#include "pininit.h"
#include "configure.h"

void Init_GPIO(void)
{	
	gpio_set_direction(PIN_POWER_ON, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_POWER_ON, 1); //blink the backlight
	gpio_set_direction(PIN_HEARTBEAT, GPIO_MODE_OUTPUT);
//	gpio_set_level(LED_BL, 1); //blink the backlight
}
