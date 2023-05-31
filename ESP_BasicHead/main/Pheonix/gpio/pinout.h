#include "driver/gpio.h"

#define PIN_HEARTBEAT GPIO_NUM_38 //LCD_BL

#define HEARTBEAT_SET gpio_set_level(PIN_HEARTBEAT, 1);
#define HEARTBEAT_CLR gpio_set_level(PIN_HEARTBEAT, 0);