#ifndef _JOB1_H
#define _JOB1_H

#include "stm32f1xx_hal.h"
#include "sys.h" 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define  HEARTBEAT_TIM_1     2500     //循环  2000ms
#define  HEARTBEAT_TIM_2     8000     //累积  2000ms
#define  HEARTBEAT_LON        9            //心跳包长度

void  job_heartbeat_tim(void) ;
void  job_heartbert_rest(void) ;
void  job_heartbert_send(void);

extern uint16_t   heartbeat_tim_1,heartbeat_tim_2;    //循环延时,累计延时

extern uint8_t  heartbert_val;
extern uint8_t     heartbeat_val_1,heartbeat_val_2;       //循环延时标志


void job_press(void);
void job_press_rest(void);

extern uint8_t  prsss_sta[6],press_num;

#define  PRESS_TIM_VAL_ENABLE     0       //按键算法 1：老版    0：新版

#endif
