/*
 * messages.c
 *
 *  Created on: May 13, 2022
 *      Author: hyrel
 */


#include "messages.h"

//#include "parser.h"
#include "taskmanager.h"
ASCiiFormatString BootStepStrings[] = {
		{"DevInit  \0"}, 		//BOOT_STAGE_DISPLAY_INIT 			= 0
		{"SetIOSafe\0"},		//BOOT_STAGE_SAFE_MODE 				= 1
		{"HWINIT   \0"},		//BOOT_STAGE_HW_INIT_COMPLETE		= 2
		{"CheckTbl \0"},		//BOOT_STAGE_CHECKED_TABLES			= 3
		{"StepConf \0"},		//BOOT_STAGE_LOADED_STEPPER_CONFIG	= 4
		{"DevKnown \0"},		//BOOT_STAGE_DEVICE_ID_KNOWN		= 5
		{"DevAnnoc \0"},		//BOOT_STAGE_SENT_ANNOUNCE			= 6
		{"InitCAN  \0"},		//BOOT_STATE_INIT_FROM_CAN			= 7
		{"RegOK    \0"},		//BOOT_STAGE_REGISTERED				= 8
		{"ErrorCmb \0"},		//BOOT_STAGE_INVALID_COMBO			= 9
		{"Stage    \0"}			//BOOT_STAGES						= 10
};

ASCiiFormatString CanEventStrings[] = {
		{"Dev Hello\0"}, 		//CAN_EVENT_DEVICE_ANNOUNCE         			= 0,
		{"BL Hello \0"},		//CAN_EVENT_BOOTLOADER_ANNOUNCE 				= 1
		{"Hartbeat \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_0					= 2
		{"ManZ Mov \0"},		//CAN_EVENT_MANUAL_Z_MOVE						= 3
		{"PrimeEnd \0"},		//CAN_EVENT_PRIME_COMPLETE						= 4
		{"Limit=1  \0"},		//CAN_EVENT_LIMIT_SWITCH_ON						= 5
		{"Limit=0  \0"},		//CAN_EVENT_LIMIT_SWITCH_OFF					= 6
		{"ProbeDat \0"},		//CAN_EVENT_PROBE_REPORT              			= 7,
		{"PNP Down \0"},		//CAN_EVENT_PNP_DOWN_REPORT           			= 8,
		{"PNP UP   \0"},		//CAN_EVENT_PNP_UP_REPORT             			= 9,
		{"Motor End\0"},		//CAN_EVENT_PNP_MOTION_COMPLETE       			= 10,
		{"PNPBlockd\0"},		//CAN_EVENT_PNP_MOTION_BLOCKED        			= 11,
		{"ProbArmd \0"},		//CAN_EVENT_PROBE_ARMED               			= 12,
		{"PROBCBMV \0"},		//CAN_EVENT_PROBE_CONTACT_BEFORE_MOVE 			= 13,
		{"CO2Wdog- \0"},		//CAN_EVENT_CO2_WATCHDOG_EXPIRED      			= 14,
		{"PrimeEND \0"},		//CAN_EVENT_CO2_PRIME_FINISHED_START_RUN 		= 15,
		{"Limit1^v \0"},		//CAN_EVENT_MOTION_LIMIT1_STATE_CHANGE			= 16,
		{"Limit2^v \0"},		//CAN_EVENT_MOTION_LIMIT2_STATE_CHANGE			= 17,
		{"Enc Pass \0"},		//CAN_EVENT_ENCODER_CALIBRATION_PASS			= 18,
		{"ENC Fail \0"},		//CAN_EVENT_ENCODER_CALIBRATION_FAIL			= 19,
		{"EncCFG=1 \0"},		//CAN_EVENT_ENCODER_CONFIG_SAVE_PASS			= 20,
		{"EncCFG=0 \0"},		//CAN_EVENT_ENCODER_CONFIG_SAVE_FAIL			= 21,
		{"EncCal=0 \0"},		//CAN_EVENT_ENCODER_BAD_CALIBRATION				= 22,
		{"CBrating \0"},		//CAN_EVENT_ENCODER_CALIBRATING					= 23,
		{"Homing   \0"},		//CAN_EVENT_MOTION_HOMING_IN_PROCESS  			= 24,
		{"Homed    \0"},		//CAN_EVENT_MOTION_HOMING_COMPLETE				= 25,
		{"Jogged   \0"},		//CAN_EVENT_MOTION_JOGGING_COMPLETE				= 26,
		{"Lathe=0  \0"},		//CAN_EVENT_MOTION_LATHE_COMPLETE				= 27,
		{"Hrtbeat1 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_1        			= 28,
		{"Hrtbeat2 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_2        			= 29,
		{"Hrtbeat3 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_3        			= 30,
		{"Hrtbeat4 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_4        			= 31,
		{"Hrtbeat5 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_5        			= 32,
		{"Hrtbeat6 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_6        			= 33,
		{"Hrtbeat7 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_7        			= 34,
		{"Hrtbeat8 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_8        			= 35,
		{"Hrtbeat9 \0"},		//CAN_EVENT_DEVICE_HEARTBEAT_9        			= 36,
		{"SetSaved \0"},		//CAN_EVENT_DEVICE_WIPE_SAVED_SETTINGS        	= 37,
		{"         \0"},		//NONE        									= 38,
};

//LcdVariableInfo LcdVarsTable[] = {
//	{(uint32_t)&HeartBeat,               				"HB      ", &Format_Int, 	RED,		CYAN, 		0},
//	{(uint32_t)&DevicePosition,     					"CAN Addr", &Format_Int, 	BLUE,		CYAN, 		0},
//	{(uint32_t)&BootStateStep,      					"BootStep", &Format_Ascii, 	GREEN,		CYAN, 		(uint32_t)BootStepStrings},
//	{(uint32_t)&WatchdogCounterMs,  					"WDogTmr#", &Format_Int, 	CYAN,		CYAN, 		0},// i do not now which one of these to use
//	{(uint32_t)&ParsedLineCounter,       				"Parse Ct", &Format_Int, 	MAGENTA,	CYAN, 		0},//
//	{(uint32_t)&MaxTaskTime[28],   						"HB_Time ", &Format_Int, 	WHITE,		CYAN, 		0},// //Percent must be 0 to 100.
//	{(uint32_t)&CanRxCount,         					"Can Rx# ", &Format_Int, 	YELLOW,		CYAN,		0},
//	{(uint32_t)&CanTxCount,         					"Can Tx# ", &Format_Int, 	YELLOW,		CYAN, 		0},
//	{(uint32_t)&LastCanRxMsgId,         				"RxCanID#", &Format_Ascii, 	YELLOW,		CYAN, 		(uint32_t)CanEventStrings},
//	{(uint32_t)&LastCanTxMsgId,         				"TxCanID#", &Format_Ascii, 	YELLOW,		CYAN, 		(uint32_t)CanEventStrings},
//	{0}
//};


