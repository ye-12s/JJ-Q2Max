#ifndef _TIMER_H
#define _TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "sys.h"
#include "main.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F103������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/9/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern void Error_Handler(void);
	
extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

//void TIM3_Init(u16 arr,u16 psc);
void TIM3_Init(void);


void MX_TIM4_Init(void);
void MX_TIM5_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);


#ifdef __cplusplus
}
#endif


#endif

