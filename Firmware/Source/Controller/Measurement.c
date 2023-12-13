﻿// Header
#include "Measurement.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "Board.h"

// Variables
Int16U MEASURE_ADC_BatteryVoltageRaw[ADC_DMA_BUFF_SIZE];

// Forward functions
float MEASURE_RawArrayAvg(pInt16U InputArray, Int16U ArraySize);
float MEASURE_GetRawAvgBatVolatge();
float MEASURE_ConvertADCtoV(float RawInput);

// Functions
float MEASURE_RawArrayAvg(pInt16U InputArray, Int16U ArraySize)
{
	float AverageData = 0;
	
	for(Int16U i = 0; i < ArraySize; i++)
		AverageData += InputArray[i];
	
	return AverageData / ArraySize;
}
//-----------------------------------------------

float MEASURE_GetRawAvgBatVolatge()
{
	return MEASURE_RawArrayAvg(&MEASURE_ADC_BatteryVoltageRaw[1], ADC_DMA_BUFF_SIZE - 1);
}
//-----------------------------------------------

float MEASURE_ConvertADCtoV(float RawInput)
{
	float Voltage = (RawInput / ADC_DAC_RESOLUTION * ANALOG_REF_MV) * CAP_V_CONV_K - CAP_V_CONV_OFFSET;
	return (Voltage > 0) ? Voltage : 0;
}
//-----------------------------------------------

float MEASURE_GetBatteryVoltage()
{
	DMA_TransferCompleteReset(DMA1, DMA_TRANSFER_COMPLETE);
	ADC_SamplingStart(ADC1);
	while(!DMA_IsTransferComplete(DMA1, DMA_TRANSFER_COMPLETE));
	
	return MEASURE_ConvertADCtoV(MEASURE_GetRawAvgBatVolatge());
}
//-----------------------------------------------
