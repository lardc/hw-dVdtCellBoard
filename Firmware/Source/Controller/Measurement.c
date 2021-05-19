// Header
#include "Measurement.h"

// Includes
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"
#include "ZwDMA.h"

// Variables
//
Int16U MEASURE_ADC_BatteryVoltageRaw[ADC_DMA_BUFF_SIZE];


Int16U MEASURE_ConvertRawArray(Int16U* InputArray, Int16U ArraySize)
{
	Int32U AverageData = 0;

	for(int i = 0; i < ArraySize; i++)
		AverageData += *(InputArray + i);

	return (Int16U)((float)AverageData / ArraySize);
}
//-----------------------------------------------

Int16U MEASURE_DMAExtractBatVolatge()
{
	return MEASURE_ConvertRawArray(&MEASURE_ADC_BatteryVoltageRaw[1], (ADC_DMA_BUFF_SIZE-1) );
}
//-----------------------------------------------

float MEASURE_ConvertADCtoV (Int16U Data)
{

	float K = (float)DataTable[REG_ADC_VBAT_N] / (float)DataTable[REG_ADC_VBAT_D];
	float Offset = (float)((int16_t)DataTable[REG_ADC_VBAT_OFFSET]);
	float result = ((float)Data*ANALOG_REF_MV / ADC_RESOLUTION + Offset) * K ;

	return (result > 0) ? result : 0;
}
//-----------------------------------------------

float MEASURE_SingleSampleBatteryVoltage()
{
	DMA_TransferCompleteReset(DMA1, DMA_TRANSFER_COMPLETE);
	ADC_SamplingStart(ADC1);
	while(!DMA_IsTransferComplete(DMA1, DMA_TRANSFER_COMPLETE)){}

	return MEASURE_ConvertADCtoV(MEASURE_DMAExtractBatVolatge());
}
