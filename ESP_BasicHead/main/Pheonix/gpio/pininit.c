#include "pininit.h"
#include "../configure.h"
#include "pinout.h"
void Init_GPIO(void)
{
	gpio_set_direction(PIN_HEARTBEAT, GPIO_MODE_OUTPUT);
//	gpio_set_level(LED_BL, 1); //blink the backlight
}
