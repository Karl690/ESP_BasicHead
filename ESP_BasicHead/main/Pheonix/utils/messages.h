/*
 * messages.h
 *
 *  Created on: May 13, 2022
 *      Author: hyrel
 */
#include <stdint.h>
#include "../display/display.h"
#include "../display/DisplayList.h"

typedef struct {
	char String[10];
}ASCiiFormatString;


extern uint32_t HeartBeat;
extern uint32_t Percent;
extern uint32_t DevicePosition;
extern uint32_t BootStateStep;
extern uint32_t WatchdogCounterMs;
extern uint32_t WatchdogMs;
extern uint32_t CanRxCount;
extern uint32_t CanTxCount;
extern uint32_t LastCanRxMsgId;
extern uint32_t LastCanTxMsgId;



extern ASCiiFormatString BootStepStrings[];
extern ASCiiFormatString CanEventStrings[];
extern LcdVariableInfo LcdVarsTable[];
extern LcdVariableInfo UsbGcodeArguments[];
extern LcdVariableInfo UsbUrgentGcodeArguments[];
extern LcdVariableInfo CMDQueValues[];

