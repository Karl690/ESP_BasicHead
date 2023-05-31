#include "esp_timer.h"
#include "taskmanager.h"

esp_timer_handle_t systickTimer;
void Init_RCC(void)
{
	esp_timer_create_args_t systickTimerArgs;
	systickTimerArgs.callback = func_SystickCallback;
	systickTimerArgs.arg = NULL;
	esp_timer_create(&systickTimerArgs, &systickTimer); // Create the timer
	esp_timer_start_periodic(systickTimer, 125); // Start the timer in automatic reload mode with a period of 125 microseconds
}
