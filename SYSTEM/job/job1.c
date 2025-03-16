#include "APP.h"
#include <stdbool.h>
#include "globaldata.h"
#include "globalfunc.h"
#include "WS2812.h"
#include "Bluetooth.h"
#include <string.h>		//strstr

#include "job1.h"

uint16_t   heartbeat_tim_1,heartbeat_tim_2;    //循环延时,累计延时
uint8_t     heartbeat_val_1,heartbeat_val_2;       //循环延时标志

/**
  * 功能  ：循环1ms执行   运行在 stm32f1xx_it.c(333)
  * 参数  ：无
  * 返回值：无    
  */
void  job_heartbeat_tim(void)
{
	heartbeat_tim_1++;
	heartbeat_tim_2++;
	if( heartbeat_tim_1 > HEARTBEAT_TIM_1-1 ) 
	{
		heartbeat_tim_1=0;
		heartbeat_val_1=1;    //
	}
	if( heartbeat_tim_2 > HEARTBEAT_TIM_2-1  )
	{
		heartbeat_tim_2=0;
		heartbeat_val_2=1;    //
	}
}

/**
  * 功能  ：标志复位  运行在APP.C(543)  Proc_USART1_BDP
  * 参数  ：无
  * 返回值：无    
  */
void  job_heartbert_rest(void)
{
	heartbeat_tim_1 = 0 ;    heartbeat_val_1 = 0 ;  
	heartbeat_tim_2 = 0 ;    heartbeat_val_2 = 0 ;
}

/**
  * 功能  ：发送心跳包  ,运行在 main.c (285)
  * 参数  ：无
  * 返回值：无    
  */
	uint8_t    heartbert_tx[HEARTBEAT_LON] = { 0xFC, 0x55, 0x00, 0x20,0x00,0x00, 0x00, 0x00, 0x71 };
void  job_heartbert_send(void)
{
	if( heartbeat_val_1 )
	{
		heartbeat_val_1 = 0 ;
		HAL_Delay(15);	
		COM1_Send_BDP( heartbert_tx , HEARTBEAT_LON);
	}
}

/************************************************************************************************************************/
/**
  * 功能  ：循环10ms执行   运行在 stm32f1xx_it.c(333)
  * 参数  ：无
  * 返回值：无    
  */
uint8_t  heartbert_press_tim;
uint8_t  heartbert_val;
uint8_t  prsss_sta[6],press_num;

void job_press(void)
{
	heartbert_press_tim++ ;
	if( heartbert_press_tim >(2-1))
	{
		heartbert_press_tim = 0 ;
		
		prsss_sta[0] = (!(Press_AD1)) ||  prsss_sta[0] ;
		prsss_sta[1] = (!(Press_AD2)) ||  prsss_sta[1] ;
		prsss_sta[2] = (!(Press_AD3)) ||  prsss_sta[2] ;
		prsss_sta[3] = (!(Press_AD4)) ||  prsss_sta[3] ;
		prsss_sta[4] = (!(Press_AD5)) ||  prsss_sta[4] ;
		prsss_sta[5] = (!(Press_AD6)) ||  prsss_sta[5] ;
		
		heartbert_val=1;
		
	}
}
/**
* 功能  ：按键值复位
  * 参数  ：无
  * 返回值：无    
  */
void job_press_rest(void)
{
//	sys_intx_disable( ) ;
//	memset(prsss_sta , 0x00 , 6 );  //缓存初始化
	
	prsss_sta[0] = 0 ;  prsss_sta[1] = 0 ;  prsss_sta[2] = 0 ;  
	prsss_sta[3] = 0 ;  prsss_sta[4] = 0 ;  prsss_sta[5] = 0 ;  
	
	heartbert_val=0;
//	sys_intx_enable( ) ;
}
//*******end********









