/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    freertos.c
  * @brief   This file contains the code that the program consists of,
  * divided into tasks that will be run by the FreeRTOS scheduler.
  * @author William Asp
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
#include "adc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

#include "stdio.h"
#include "display.h"
#include "error.h"
#include "uart.h"
#include "clock.h"
#include "red.h"
#include "potentiometer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define POT_MAX 4066
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
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for backlightTask */
osThreadId_t backlightTaskHandle;
const osThreadAttr_t backlightTask_attributes = {
  .name = "backlightTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for clockTask */
osThreadId_t clockTaskHandle;
const osThreadAttr_t clockTask_attributes = {
  .name = "clockTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void startBacklightTask(void *argument);
void startClockTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of backlightTask */
  backlightTaskHandle = osThreadNew(startBacklightTask, NULL, &backlightTask_attributes);

  /* creation of clockTask */
  clockTaskHandle = osThreadNew(startClockTask, NULL, &clockTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

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
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_startBacklightTask */
/**
* @brief Function implementing the backlightTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startBacklightTask */
void startBacklightTask(void *argument)
{
  /* USER CODE BEGIN startBacklightTask */
    TickType_t lastWakeTime;
    const TickType_t period = pdMS_TO_TICKS(100);
    lastWakeTime = xTaskGetTickCount();

    uint32_t pot;

  /* Infinite loop */
  for(;;)
  {
    pot = get_potentiometer_value();
    set_brightness((double)pot/POT_MAX);

    vTaskDelayUntil(&lastWakeTime, period);
  }
  /* USER CODE END startBacklightTask */
}

/* USER CODE BEGIN Header_startClockTask */
/**
* @brief Function implementing the clockTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startClockTask */
void startClockTask(void *argument)
{
  /* USER CODE BEGIN startClockTask */
    TickType_t lastWakeTime;
    const TickType_t period = pdMS_TO_TICKS(1000);
    lastWakeTime = xTaskGetTickCount();

    RTC_TimeTypeDef time;
    uint8_t buf_len = 8;
    char buf[buf_len];

  /* Infinite loop */
  for(;;)
  {
    get_time(&time);
    sprintf(buf, "%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
    uart_println(buf);
    display_write_row(buf, buf_len, 0);

    vTaskDelayUntil(&lastWakeTime, period);
  }
  /* USER CODE END startClockTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
