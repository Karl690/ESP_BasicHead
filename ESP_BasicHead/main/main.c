#include <stdio.h>
#include "main.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "spi/spi.h"
#include "adc/adc.h"
#include "tle5012/tle5012.h"

uint32_t DisplayIndex = 0;
uint32_t ForegroundIndex = 0;

void app_main(void)
{
	Init_GPIO();
	Init_RCC();
	Init_GUI();
	Init_Display();
	//InitTle5012();
	Init_ADC();
	while (1)
	{
		switch (DisplayIndex)
		{
		//case 0:UpdateScreen(SecsStringTable); break;
		case 0:UpdateScreen(LcdVarsTable); break;
		case 1:UpdateScreen(UsbGcodeArguments); break;
		case 2:UpdateScreen(CMDQueValues); break;
		case 3:UpdateScreen(TaskTimeTable1); break;
		case 4:UpdateScreen(ADCValueTable); break;
		case 5:UpdateScreen(BarValueTable); break;
		case 6:UpdateScreen(FaultValueTable); break;
		}
		vTaskDelay(10);		
		ForegroundIndex++;
		/////////////
	}
}
