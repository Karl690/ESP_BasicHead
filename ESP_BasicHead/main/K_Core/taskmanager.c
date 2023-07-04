#include "global.h"
#include "configure.h"
#include "taskmanager.h"
#include "tle5012/tle5012.h"
#include "adc/adc.h"
uint16_t SliceCnt = 0; // current slice being processed
uint16_t SliceOffset = 0;
uint32_t HeartBeat = 0;
float Tle5012Angle = 0;
const PFUNC F1000HZ[NUM_1000HZ] =
{
	Spare, // keep as last call in this array
	Spare, //canProcessTxQueueNoReturn,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
};

const PFUNC F100HZ[NUM_100HZ] =
{
	Spare,
	ProcessGetAdcRawData,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
};

const PFUNC F10HZ[NUM_10HZ] =
{
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
};

const PFUNC F1HZ[NUM_1HZ] =
{
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	Spare,
	BlinkHeartBeat,
};

/*
 * to make the slice scedular more effecient, we are going to use a binary counter, not base 10
 *
 */
//void TaskManager()
void func_SystickCallback(void* arg)
{

	SliceCnt++;
	SliceOffset = SliceCnt & 0x0007; //precalculate the slice index into the jump table
	if (SliceOffset)
	{
		F1000HZ[SliceOffset](); //run the task
		
		return;//toggle pin so we can see on Oscillosclope and exit
	}
	if (SliceCnt & 0x0038)
	{
		SliceOffset = (SliceCnt >> 3) & 0x0007;
		F100HZ[SliceOffset]();
		SliceOffset += 8;
		return;//toggle pin so we can see on Oscillosclope and exit
	}

	if (SliceCnt & 0x01C0)
	{
		SliceOffset = (SliceCnt >> 6)  & 0x0007;
		F10HZ[SliceOffset]();
		SliceOffset += 16;
		return;//toggle pin so we can see on Oscillosclope and exit
	}

	SliceOffset = (SliceCnt >> 9)  & 0x0007;
	F1HZ[SliceOffset]();
	SliceOffset += 24;
	
	return;//toggle pin so we can see on Oscillosclope and exit

}

void Spare(void)
{
	// placeholder call for empty slice
}
void BlinkHeartBeat(void)
{
	
	HeartBeat++;
	if (HeartBeat & 1) {
		HEARTBEAT_SET;
	}else {
		HEARTBEAT_CLR;
	}
}

void ReadTle5012()
{
	uint16_t data = Tle5012_ReadAngle();
	Tle5012Angle = (data / 32764.f) * 360;
}