// Include
//
#include "Controller.h"
//
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "DeviceProfile.h"
#include "LowLevel.h"
#include "PowerDriver.h"
#include "Board.h"

// Variables
//
volatile long CONTROL_TimeCounterTemp = 0;
volatile long CONTROL_TimeCounter = 0;
volatile DeviceState CONTROL_State = DS_None;
static volatile Boolean Locked = false;
static Boolean CycleActive = false;

// Forward functions
//
static void CONTROL_ApplyParameters();
static void CONTROL_SetDeviceState(DeviceState NewState);
static void CONTROL_FillDefault();
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U UserError);

// Functions
//
void CONTROL_Init()
{
	DT_Init();
	
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	CONTROL_FillDefault();
}
//-----------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	IWDG_Refresh();
}
//-----------------------------

void CONTROL_Cycle()
{
	DRIVER_ControlRoutine();
}
//-----------------------------

static void CONTROL_ApplyParameters()
{
	DRIVER_SW_RateChannel(DataTable[REG_DESIRED_GATE_V]);
	DRIVER_SetGateVoltage(DataTable[REG_DESIRED_GATE_V]);
	DRIVER_CacheVariables();
}
//-----------------------------

static void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//-----------------------------

static void CONTROL_FillDefault()
{
	DataTable[REG_DEV_STATE] = DS_None;
	DataTable[REG_FAULT_REASON] = FAULT_NONE;
	DataTable[REG_DISABLE_REASON] = DISABLE_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	
	DataTable[REG_DESIRED_VOLTAGE] = CAP_VOLTAGE_MIN;
	DataTable[REG_DESIRED_GATE_V] = 0;
	
	DataTable[REG_VOLTAGE_FINE_N] = (1 << CAP_VF_RSHIFT);
	
	DataTable[REG_ADC_VBAT_OFFSET] = 65534;
	DataTable[REG_ADC_VBAT_N] = 319;
	DataTable[REG_ADC_VBAT_D] = 1000;
}
//-----------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U UserError)
{
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			DataTable[REG_DESIRED_VOLTAGE] = CAP_VOLTAGE_MIN;
			DataTable[REG_DESIRED_GATE_V] = 0;
			CONTROL_ApplyParameters();
			CONTROL_SetDeviceState(DS_Powered);
			DRIVER_SetMode(true);
			break;
			
		case ACT_DISABLE_POWER:
			DRIVER_SetMode(false);
			CONTROL_SetDeviceState(DS_None);
			break;
			
		case ACT_DIAG_SET_PWM_FB:
			FlybackPWMSet(DataTable[REG_DIAG_PWM_FB]);
			break;
			
		case ACT_DIAG_SET_PWM_BRK:
			BrakePWMSet(DataTable[REG_DIAG_PWM_BRK]);
			break;
			
		case ACT_DIAG_UPDATE_PWM_FREQ:
			break;
			
		case ACT_DIAG_SET_GATE_V:
			DRIVER_SW_RateChannel(DataTable[REG_DESIRED_GATE_V]);
			DRIVER_SetGateVoltage(DataTable[REG_DESIRED_GATE_V]);
			break;
			
		case ACT_DIAG_SW_LOW_RATE:
			LL_VRateLow();
			break;
			
		case ACT_DIAG_SW_MID_RATE:
			LL_VRateMid();
			break;
			
		case ACT_DIAG_SW_HIGH_RATE:
			LL_VRateHigh();
			break;
			
		case ACT_DIAG_SW_OFF_RATE:
			LL_VRateNone();
			break;
			
		case ACT_CLR_FAULT:
			if(CONTROL_State == DS_Fault)
				CONTROL_SetDeviceState(DS_None);
			DataTable[REG_FAULT_REASON] = FAULT_NONE;
			break;
			
		case ACT_CLR_WARNING:
			DataTable[REG_WARNING] = WARNING_NONE;
			break;
			
		case ACT_APPLY_PARAMS:
			CONTROL_ApplyParameters();
			break;
			
		default:
			return false;
	}
	
	return true;
}
//-----------------------------
