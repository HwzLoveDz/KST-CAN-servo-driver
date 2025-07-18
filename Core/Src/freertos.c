/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app.h"
#include "kst_servo_canopen.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CAN_Servo_Task */
osThreadId_t CAN_Servo_TaskHandle;
const osThreadAttr_t CAN_Servo_Task_attributes = {
  .name = "CAN_Servo_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Uart_Main */
osThreadId_t Uart_MainHandle;
const osThreadAttr_t Uart_Main_attributes = {
  .name = "Uart_Main",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CAN_SERVO_SEND_MSG */
osMessageQueueId_t CAN_SERVO_SEND_MSGHandle;
const osMessageQueueAttr_t CAN_SERVO_SEND_MSG_attributes = {
  .name = "CAN_SERVO_SEND_MSG"
};
/* Definitions for CAN_SERVO_RECV_MSG */
osMessageQueueId_t CAN_SERVO_RECV_MSGHandle;
const osMessageQueueAttr_t CAN_SERVO_RECV_MSG_attributes = {
  .name = "CAN_SERVO_RECV_MSG"
};
/* Definitions for UART_SEND_MSG */
osMessageQueueId_t UART_SEND_MSGHandle;
const osMessageQueueAttr_t UART_SEND_MSG_attributes = {
  .name = "UART_SEND_MSG"
};
/* Definitions for UART_RECV_MSG */
osMessageQueueId_t UART_RECV_MSGHandle;
const osMessageQueueAttr_t UART_RECV_MSG_attributes = {
  .name = "UART_RECV_MSG"
};
/* Definitions for CanSyncEvent */
osEventFlagsId_t CanSyncEventHandle;
const osEventFlagsAttr_t CanSyncEvent_attributes = {
  .name = "CanSyncEvent"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void USB_Reset(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
	osDelay(100);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
}
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void CAN_Servo_Main(void *argument);
void Uart_MainTask(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of CAN_SERVO_SEND_MSG */
  CAN_SERVO_SEND_MSGHandle = osMessageQueueNew (16, 14, &CAN_SERVO_SEND_MSG_attributes);

//  /* creation of CAN_SERVO_RECV_MSG */
  CAN_SERVO_RECV_MSGHandle = osMessageQueueNew (16, 14, &CAN_SERVO_RECV_MSG_attributes);

//  /* creation of UART_SEND_MSG */
//  UART_SEND_MSGHandle = osMessageQueueNew (4, 128, &UART_SEND_MSG_attributes);

//  /* creation of UART_RECV_MSG */
//  UART_RECV_MSGHandle = osMessageQueueNew (4, 128, &UART_RECV_MSG_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

//  /* creation of CAN_Servo_Task */
  CAN_Servo_TaskHandle = osThreadNew(CAN_Servo_Main, NULL, &CAN_Servo_Task_attributes);

//  /* creation of Uart_Main */
//  Uart_MainHandle = osThreadNew(Uart_MainTask, NULL, &Uart_Main_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of CanSyncEvent */
//  CanSyncEventHandle = osEventFlagsNew(&CanSyncEvent_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  //USB_Reset();
  //MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  userAPP_MainTask();
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_CAN_Servo_Main */
/**
* @brief Function implementing the CAN_Servo_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CAN_Servo_Main */
void CAN_Servo_Main(void *argument)
{
  /* USER CODE BEGIN CAN_Servo_Main */
  /* Infinite loop */
   CAN_Servo_MainTask();
  /* USER CODE END CAN_Servo_Main */
}

/* USER CODE BEGIN Header_Uart_MainTask */
/**
* @brief Function implementing the Uart_Main thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Uart_MainTask */
void Uart_MainTask(void *argument)
{
  /* USER CODE BEGIN Uart_MainTask */
  /* Infinite loop */


  for(;;)
  {
	osDelay(500);
	HAL_GPIO_TogglePin(BSP_LED_GPIO_Port, BSP_LED_Pin);
	//printf("Uart_MainTask\n");
  }
  /* USER CODE END Uart_MainTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

