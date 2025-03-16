#ifndef _STRUCT_H
#define _STRUCT_H
#include "const.h"
//#include "main.h"
#include <stdint.h>

//串口报文发送缓存区结构体
typedef struct  Send_Serial_BDP_FIFO
{
	unsigned char send_counter;				//发送次数
	unsigned char buf[MAX_FIFO_BUF_LEN];	//报文内容
	unsigned char len;						//报文长度
} Send_Serial_BDP_FIFO;

//Flash存储结构
typedef struct
{
	unsigned short config_flag;      //已配置标志
} App_Info;

//点灯结构体
typedef struct
{
	unsigned short Valid_Flag;		//有效标志
	unsigned short LED_Channel;		//LED通道
	unsigned short Now_Count;		//当前移动位置
}LED_FIFO;


#endif
