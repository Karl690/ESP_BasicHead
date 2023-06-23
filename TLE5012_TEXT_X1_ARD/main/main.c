#include <stdio.h>
#include "TLE5012/TLE5012.h"
#include "esp_log.h"
#define LED8  GPIO_NUM_2 // LCD RS

static uint8_t ledState = 0;
unsigned int rawAngle = 0;    
float scaleAngle = 0;
unsigned char ssc_delay = 10; // SSC clock frequency adjust, 0 = fastest, 255 = slowest
//TLE5012 enc(39, 38, 36, ssc_delay); // enc (cs, data, sck, delay)
void app_main(void)
{
	ESP_LOGI("TLE5012", "Start app_main");
	//Init_TLE5012(PIN_TLE5012_CSQ, PIN_TLE5012_DATA, PIN_TLE5012_SCK, ssc_delay);
	
	gpio_set_direction(LED8, GPIO_MODE_OUTPUT);
	TLE5012_Start();
	ESP_LOGI("TLE5012", "Start TLE5012");
	
	while (true)
	{
		rawAngle = TLE5012_ReadAngle();
		if (rawAngle == TLE5012_INVALIDANGLE)
		{
			//Serial.println("Invalid angle");
			//return;
		}
		scaleAngle = rawAngle / 32764.0f * 360;
		//Serial.print("Angle: ");
		//Serial.println(scaledAngle);
		
		ledState = !ledState;
		gpio_set_level(LED8, ledState); //blink LED.
		ESP_LOGI("lib_name", "Message for print");
	}
}
