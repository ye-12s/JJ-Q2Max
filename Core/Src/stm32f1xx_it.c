/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "main.h"
#include <stdbool.h>          /* 20240511   */
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "globaldata.h"
#include "WS2812.h"
/*heartbeat*/
#include "job1.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */
bool mak_fft_start=false;
extern	 volatile uint32_t   spp_count;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern volatile uint32_t  fft_start_count;
extern DMA_HandleTypeDef hdma_tim4_ch2;
extern DMA_HandleTypeDef hdma_tim4_ch3;
extern DMA_HandleTypeDef hdma_tim5_ch1;
extern DMA_HandleTypeDef hdma_tim5_ch2;
extern DMA_HandleTypeDef hdma_tim5_ch3_up;
extern DMA_HandleTypeDef hdma_tim5_ch4_trig;
extern UART_HandleTypeDef huart1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
 // while (1)																		//20240517  DEL
 // {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
 // }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

	//环形灯击打点亮倒计时
	if(1 == g_Cycle_Light_Flag[0])
	{
		g_Cycle_Light_Count[0]++;
		if(g_Cycle_Light_Count[0] >= g_Cycle_Light_Time)
		{
			g_Cycle_Light_Count[0] = 0;
			g_Cycle_Light_Flag[0] = 2;
		}
	}
	if(1 == g_Cycle_Light_Flag[1])
	{
		g_Cycle_Light_Count[1]++;
		if(g_Cycle_Light_Count[1] >= g_Cycle_Light_Time)
		{
			g_Cycle_Light_Count[1] = 0;
			g_Cycle_Light_Flag[1] = 2;
		}
	}  
	if(1 == g_Cycle_Light_Flag[2])
	{
		g_Cycle_Light_Count[2]++;
		if(g_Cycle_Light_Count[2] >= g_Cycle_Light_Time)
		{
			g_Cycle_Light_Count[2] = 0;
			g_Cycle_Light_Flag[2] = 2;
		}
	}  
	if(1 == g_Cycle_Light_Flag[3])
	{
		g_Cycle_Light_Count[3]++;
		if(g_Cycle_Light_Count[3] >= g_Cycle_Light_Time)
		{
			g_Cycle_Light_Count[3] = 0;
			g_Cycle_Light_Flag[3] = 2;
		}
	}  
	if(1 == g_Cycle_Light_Flag[4])
	{
		g_Cycle_Light_Count[4]++;
		if(g_Cycle_Light_Count[4] >= g_Cycle_Light_Time)
		{
			g_Cycle_Light_Count[4] = 0;
			g_Cycle_Light_Flag[4] = 2;
		}
	}  
	if(1 == g_Cycle_Light_Flag[5])
	{
		g_Cycle_Light_Count[5]++;
		if(g_Cycle_Light_Count[5] >= g_Cycle_Light_Time)
		{
			g_Cycle_Light_Count[5] = 0;
			g_Cycle_Light_Flag[5] = 2;
		}
	} 
	
	//条形灯定时
	g_Line_Count++;
 	if(g_Line_Count >= g_Line_Period )
	{
		g_Line_Count = 0;
		g_Line_Flag = 1;
	}
	
	//环形灯定时
	g_Cycle_Count++;
	if(g_Cycle_Count >= g_Cycle_Period)
	{
		g_Cycle_Count = 0;
		g_Cycle_Flag = 1;
	}
	
	//2S定时
	g_2000ms_counter++;
	if(g_2000ms_counter >= 2200)
	{
		g_2000ms_counter = 200;
		g_2000ms_flag = 1;
//		fft_start_count++;

//		if(fft_start_count > 6)
//		{
//    			mak_fft_start = true;
//		}
	}
	
	//500ms定时
	g_500ms_counter++;
	if(g_500ms_counter >= 550)
	{
		g_500ms_counter = 50;
		g_500ms_flag = 1;
		fft_start_count++; 									//20240711
	}
	
//	if(Led_On_Mode0_Step2_flag == 1)			//20240604  ADD	20240606  DEL
//	{
//		g_Line_Color_R = 0x40;
//		g_Line_Color_G = 0xFF;
//		g_Line_Color_B = 0x40;
//		Led_On_Mode0_Step2_flag = 0;
//	}	
	//串口报文接收计时
	if(com1_timeout_count > 0)
	{
		com1_timeout_count--;
	}
	
	if((com1_timeout_count == 0) && (com1_recvbyte_count > 0))
	{
		com1_recvbyte_count_1 = com1_recvbyte_count;
		com1_recvbyte_count = 0;
		g_com1_frame_flag = 1;
	}
	
		//heartbeat																	//20240711
		//job_heartbeat_tim( );		
		job_press( );
///////////////////////////////////////////////////  20240517  ADD	
//		amplitude_cnt++;
//		if(amplitude_cnt>rgb_led_time)
//		{
//			pwm_index++;
//			
//			if(pwm_index > (30-1))
//			{
//				pwm_index=0;
//			}
////			amplitude_cnt=0;
////			rgb_led_time_flag=0;
//		}
//		else
//		{
//			rgb_led_time_flag=1;
//		}
/////////////////////////////////////////////////////////		
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel4 global interrupt.
  */
void DMA1_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel4_IRQn 0 */

  /* USER CODE END DMA1_Channel4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim4_ch2);
  /* USER CODE BEGIN DMA1_Channel4_IRQn 1 */

  /* USER CODE END DMA1_Channel4_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

  /* USER CODE END DMA1_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim4_ch3);
  /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

  /* USER CODE END DMA1_Channel5_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel1 global interrupt.
  */
void DMA2_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel1_IRQn 0 */

  /* USER CODE END DMA2_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim5_ch4_trig);
  /* USER CODE BEGIN DMA2_Channel1_IRQn 1 */

  /* USER CODE END DMA2_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel2 global interrupt.
  */
void DMA2_Channel2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel2_IRQn 0 */

  /* USER CODE END DMA2_Channel2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim5_ch3_up);
  /* USER CODE BEGIN DMA2_Channel2_IRQn 1 */

  /* USER CODE END DMA2_Channel2_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel4 and channel5 global interrupts.
  */
void DMA2_Channel4_5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel4_5_IRQn 0 */

  /* USER CODE END DMA2_Channel4_5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_tim5_ch2);
  HAL_DMA_IRQHandler(&hdma_tim5_ch1);
  /* USER CODE BEGIN DMA2_Channel4_5_IRQn 1 */

  /* USER CODE END DMA2_Channel4_5_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

