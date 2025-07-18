#include "kst_servo_canopen.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

#define MAX_CMD_WAIT_TIME  1000

extern osMessageQId CAN_SERVO_SEND_MSGHandle;
extern osMessageQId CAN_SERVO_RECV_MSGHandle;
extern osEventFlagsId_t CanSyncEventHandle;


struct nodePara_struct{
	uint8_t nodeID;
	uint8_t comm_state;
	int set_angle; // 0.1°
	int cur_angle;
	int l_vol_alarm;
	int Temperture;
	int Pwr_current;
	int Pwr_voltage;
	struct nodePara_struct * Next;
};

typedef struct nodePara_struct  nodePara_t;


int addNodeToRootChain(nodePara_t** root, nodePara_t* cur)
{
	if(cur == NULL){
		return -(__LINE__);
	}
	if(*root == NULL){
		*root = (nodePara_t*)malloc(sizeof (nodePara_t));
		if(*root == NULL){
			return -(__LINE__);
		}
		else{
			memcpy(*root, cur, sizeof(nodePara_t));
			(*root)->Next = NULL;
			return 0;
		}
	}
	
	nodePara_t * p = *root;
	for(; p->Next != NULL; p = p->Next)
		;
	p->Next = (nodePara_t*)malloc(sizeof(nodePara_t));
	if(p->Next == NULL){
		return -(__LINE__);
	}
	memcpy(p->Next, cur, sizeof(nodePara_t));
	p->Next->Next = NULL;
	return 0;
}

int getNodeTotalCntOnRootChain(nodePara_t* root)
{
	if(root == NULL){
		return 0;
	}
	int total = 1;
	nodePara_t * p = root;
	for(; p->Next != NULL; p = p->Next){
		total++;
	}
	return total;	
}



#define VAR_BE_ZERO(X)  memset(&X, 0, sizeof(X));

int checkAllNodeID(nodePara_t** rootNode)
{
	osStatus_t sta = osOK;
	canopen_cmd_t cmd = CMD_READ_NODE_NUMBER(0, 0);  //广播获取所有的id
	if((sta = osMessageQueuePut(CAN_SERVO_SEND_MSGHandle, (void*)&cmd, 0, MAX_CMD_WAIT_TIME)) != osOK)
	{
		printf("errLine:%d, errCode:%d \n",__LINE__, sta);
		return -1;
	}
	
	uint8_t responseTimeout = 0;
	int totalID = 0;
	do{
		osDelay(1);
		uint32_t cnt = osMessageQueueGetCount(CAN_SERVO_RECV_MSGHandle);	
		if(cnt == 0){
			continue;
		}
		responseTimeout = 0;//有响应则清空等待计时
		while(cnt--){
			VAR_BE_ZERO(cmd);
			if((sta = osMessageQueueGet(CAN_SERVO_RECV_MSGHandle, &cmd, NULL, MAX_CMD_WAIT_TIME)) != osOK)
			{
				printf("errLine:%d, errCode:%d \n",__LINE__, sta);
				continue;
			}
			if(cmd.Length != 8 || ((cmd.ID & 0x580 ) < 0x580) || cmd.Data[0] != 0x4f || cmd.Data[2] != 0x30){
				continue;
			}
			nodePara_t node = {0};
			node.nodeID =  cmd.Data[4];
			node.comm_state = 1;
			
			if(addNodeToRootChain(rootNode, &node))
				return -(__LINE__);
	
			totalID++;
			printf("find nodeID: %d, total: %d\n",cmd.Data[4], totalID);
		}
	}while( ++responseTimeout < 100);//等待回复,可以根据节点数量适当调整
	return totalID;
}


int readNodeState(uint8_t nodeID, int* pwr_cur, int* temp)
{	
	osStatus_t sta = osOK;
	canopen_cmd_t cmd = CMD_READ_STATUS(nodeID);
	if((sta = osMessageQueuePut(CAN_SERVO_SEND_MSGHandle, (void*)&cmd, 0, MAX_CMD_WAIT_TIME)) != osOK)
	{
		printf("errLine:%d, errCode:%d \n",__LINE__, sta);
		return -(__LINE__);
	}
	osDelay(100);   		//等待回复
	VAR_BE_ZERO(cmd);
	uint32_t cnt = osMessageQueueGetCount(CAN_SERVO_RECV_MSGHandle);	
	if(cnt == 0){
		return -(__LINE__);
	}
	while(cnt--){
		if((sta = osMessageQueueGet(CAN_SERVO_RECV_MSGHandle, &cmd, NULL, MAX_CMD_WAIT_TIME)) != osOK)
		{
			printf("errLine:%d, errCode:%d \n",__LINE__, sta);
			return -(__LINE__);
		}
		if(cmd.Length != 8 || (cmd.ID != (0x580 + nodeID)) || cmd.Data[0] != 0x43 || cmd.Data[1] != 0x05 || cmd.Data[2] != 0x60 ){
			continue;
		}
		*pwr_cur = ((cmd.Data[5] << 8) | cmd.Data[4]) * 10; //mA
		*temp = cmd.Data[6] > 0x78 ?  -(0xff - cmd.Data[6] + 1) : cmd.Data[6];
		printf("Node:[%d],PWR_CUR:[%d mA],Temp:[%d ℃]\n",nodeID, *pwr_cur, *temp);
		break;
	}
	return 0;
}

int setServoPosition(uint8_t nodeID, int angle)
{
	if(nodeID > 128)
		return -2;	
	osStatus_t sta = osOK;	
    if(angle > 1000)
	  angle = 1000;
    else if(angle < -1000)
	  angle = -1000;

	canopen_cmd_t cmd = CMD_SET_POSITION(nodeID, angle & 0xff, (uint8_t)((angle & 0xff00) >> 8));
	if((sta = osMessageQueuePut(CAN_SERVO_SEND_MSGHandle, (void*)&cmd, 0, MAX_CMD_WAIT_TIME)) != osOK)
	{
		printf("errLine:%d, errCode:%d \n",__LINE__, sta);
		return -2;
	}
	return 0;
}


int setAutoReportingState(uint8_t nodeID, int sta)
{
	if(nodeID > 128)
		return -2;
	canopen_cmd_t *cmd;
	if(sta){
		canopen_cmd_t ret = CMD_START_REPORTING(nodeID);
		cmd = &ret;
	}
	else{
		canopen_cmd_t ret = CMD_STOP_REPORTING(nodeID);
		cmd = &ret;		
	}
	if((sta = osMessageQueuePut(CAN_SERVO_SEND_MSGHandle, (void*)cmd, 0, MAX_CMD_WAIT_TIME)) != osOK)
	{
		printf("errLine:%d, errCode:%d \n",__LINE__, sta);
		return -1;
	}
	return 0;
}



void subNodeHandler(nodePara_t* node, void* arg)
{
//	if((osEventFlagsGet(CanSyncEventHandle) & EVENT_CAN_MSG_STATUS_SYNC) == 0)
//		return; //总线断开链接
	
	static  int dir = 0;
	if(dir){
		node->set_angle += 40;
		if(node->set_angle > 600){
			dir = 0;
		}
	}
	else{
		node->set_angle -= 40;
		if(node->set_angle < -600){
			dir = 1;
			readNodeState(node->nodeID, &node->Pwr_current, &node->Temperture);
		}
	}
	setServoPosition(node->nodeID, node->set_angle);
}


volatile int totalNodeID_Cnt ;
void CAN_Servo_MainTask(void)
{
	nodePara_t* rootNode = NULL;
	totalNodeID_Cnt = checkAllNodeID(&rootNode);		
	for(;;)
	{		
		for(nodePara_t* p = rootNode; p != NULL; p = p->Next){
			subNodeHandler(p, 0);
		}
		osDelay(10);
	}
}
