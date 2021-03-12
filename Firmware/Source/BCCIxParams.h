// -----------------------------------------
// Parameters of BCCI interface
// ----------------------------------------

#ifndef __BCCI_PARAMS_H
#define __BCCI_PARAMS_H

#include "xCCIParams.h"


// ����� ���� �������
//
#define CAN_FUNC_MASK				0x000003FF

// ������������ Slave
//
#define CAN_SLAVE_NID				11				// Node ID ����������
#define CAN_SLAVE_NID_MASK			0x0003FC00		// ����� Slave node ID
#define CAN_SLAVE_NID_MPY			10				// �������� ������ Slave

// ������������ Master
//
#define CAN_MASTER_NID				20				// Node ID ����������
#define CAN_MASTER_NID_MASK			0x03FC0000		// ����� Master node ID
#define CAN_MASTER_NID_MPY			18				// �������� ������ Master

// CAN ������
//
#define CAN_SLAVE_FILTER_ID			(CAN_SLAVE_NID << CAN_SLAVE_NID_MPY)
#define CAN_MASTER_FILTER_ID		(CAN_MASTER_NID << CAN_MASTER_NID_MPY)

#endif // __BCCI_PARAMS_H
