#include "app.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "string.h"
#include "cmsis_os.h"
#include "can.h"
#include "kst_servo_canopen.h"

extern osMessageQId CAN_SERVO_SEND_MSGHandle;
extern osMessageQId CAN_SERVO_RECV_MSGHandle;
extern osEventFlagsId_t CanSyncEventHandle;


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan_t)
{
	canopen_cmd_t cmd = {0};
	CAN_RxHeaderTypeDef CanRxHeader = {0};
	if(HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &CanRxHeader, cmd.Data) == HAL_OK)
	{
		cmd.ID =   CanRxHeader.ExtId;
		cmd.Length  = CanRxHeader.DLC;
		osMessageQueuePut(CAN_SERVO_RECV_MSGHandle, &cmd, 0, 0);
	}
}


void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	printf("HAL_CAN_ErrorCallback\n");
}



int canMessageSend(canopen_cmd_t* cmd)
{
	uint32_t txMailBox = 0;
	CAN_TxHeaderTypeDef CanTxHeader;
	// 配置发送  头
	CanTxHeader.StdId              = 0x0000;                  // 发送设备标准ID
	CanTxHeader.IDE                = CAN_ID_EXT;              // can标准ID模式
	CanTxHeader.RTR                = CAN_RTR_DATA;            // 数据帧
	CanTxHeader.ExtId              = cmd->ID;                 // 扩展ID
	CanTxHeader.DLC                = cmd->Length;             // 传输长度8
	CanTxHeader.TransmitGlobalTime = DISABLE;                 // 时间戳 不使能
	// 发送数据到邮箱并判断状态
	if(HAL_CAN_AddTxMessage(&hcan, &CanTxHeader, cmd->Data, &txMailBox) != HAL_OK)
	{
		osEventFlagsSet(CanSyncEventHandle, EVENT_CAN_MSG_STATUS_SYNC);
		printf("can mail [%d] add msg failed! 0x%08X\n", txMailBox, HAL_CAN_GetError(&hcan));
		return -(__LINE__);
	}
	else{
		osEventFlagsClear(CanSyncEventHandle, EVENT_CAN_MSG_STATUS_SYNC);
	}
	
	uint16_t timeout = 1000;
	uint32_t flag = 0;

	switch(txMailBox){
		case 0x01: flag = CAN_TSR_TXOK0; break;
		case 0x02: flag = CAN_TSR_TXOK1; break;
		case 0x04: flag = CAN_TSR_TXOK2; break;
		default:
			return -(__LINE__);
	}
	while(timeout--){
		osDelay(1);
		uint32_t tsrflags = READ_REG(hcan.Instance->TSR);
		if ((tsrflags & flag) != 0U){
			break;
		}	
	}
	if(timeout == 0){	
		printf("can mail [%d] msg push failed! 0x%08X\n", txMailBox, HAL_CAN_GetError(&hcan));
		return -(__LINE__);	
	}
	return 0;
}


int CanFilter_Init(void)
{
	CAN_FilterTypeDef CAN_FilterStructure;
	// 配置过滤器
	CAN_FilterStructure.FilterIdHigh         = 0x00;                 // 过滤器需要过滤高ID
	CAN_FilterStructure.FilterIdLow          = 0x00;                 // 过滤器需要过滤低ID
	CAN_FilterStructure.FilterMaskIdHigh     = 0x00;                 // 过滤器掩码 '0'位不限制 
	CAN_FilterStructure.FilterMaskIdLow      = 0x00;                 // 过滤器掩码 '0'位不限制
	CAN_FilterStructure.FilterFIFOAssignment = CAN_FILTER_FIFO0;     // 挂在过滤器FIFO0
	CAN_FilterStructure.FilterBank           = 0;                    // 过滤器0
	CAN_FilterStructure.FilterMode           = CAN_FILTERMODE_IDMASK; // ID掩码模式
	CAN_FilterStructure.FilterScale          = CAN_FILTERSCALE_32BIT; // 16位过滤器
	CAN_FilterStructure.FilterActivation     = CAN_FILTER_ENABLE;     // 激活过滤器
	CAN_FilterStructure.SlaveStartFilterBank = 14;                  

	// 配置过滤器
	if (HAL_CAN_ConfigFilter(&hcan, &CAN_FilterStructure) != HAL_OK)
	{
		printf("err:%d\n",__LINE__);
		return -1;
	}

	// 使能FIFO接收到一个新报文中断
	if(HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		printf("err:%d\n",__LINE__);
		return -2;
	}

	if(HAL_CAN_Start(&hcan) != HAL_OK)
	{
		printf("err:%d\n",__LINE__);
		return -3;	
	}
	printf("can init success\n");
	return 0;
}  

void userAPP_MainTask(void)
{
	canopen_cmd_t cmd;
	CanFilter_Init();
	for(;;)
	{
		if(osMessageQueueGet(CAN_SERVO_SEND_MSGHandle, &cmd, 0, osWaitForever) != osOK){
			continue;
		}
		if(canMessageSend(&cmd) != 0)
		{
			
		}
	}
}

