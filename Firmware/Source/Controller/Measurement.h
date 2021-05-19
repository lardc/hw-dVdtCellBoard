#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"
#include "SysConfig.h"

// Variables
extern Int16U MEASURE_ADC_BatteryVoltageRaw[ADC_DMA_BUFF_SIZE];

// Functions
// Functions prototypes
float MEASURE_SingleSampleBatteryVoltage();
Int16U MEASURE_ConvertRawArray(Int16U* InputArray, Int16U ArraySize);
Int16U MEASURE_DMAExtractBatVolatge();
float MEASURE_ConvertADCtoV (Int16U Data);


#endif // __MEASUREMENT_H

