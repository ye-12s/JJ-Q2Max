#ifndef _STRUCT_H
#define _STRUCT_H
#include "const.h"
//#include "main.h"
#include <stdint.h>

//串口报文发送缓存区结构体
typedef struct  Send_Serial_BDP_FIFO
{
	unsigned char send_counter;             //发送次数
	unsigned char buf[MAX_FIFO_BUF_LEN];    //报文内容
	unsigned char len;                      //报文长度
} Send_Serial_BDP_FIFO;

//Flash存储结构
typedef struct
{
	unsigned short config_flag;      //已配置标志
} App_Info;

//点灯结构体
typedef struct
{
	unsigned short Valid_Flag;      //有效标志
	unsigned short LED_Channel;     //LED通道
	unsigned short Now_Count;       //当前移动位置
} LED_FIFO;

typedef struct
{
	char version[32];               //版本号
	char bleName[32];              //蓝牙名称
	char AudioName[32];            //音频名称
	uint16_t serverUUID;        //服务UUID
	uint16_t charUUID;          //特征UUID
	uint16_t charUUID2;         //特征UUID2
	uint16_t charUUID3;         //特征UUID3
	uint8_t volume;             //音量
	uint8_t bleState;             //状态
	uint8_t connectState;       //连接状态
	union
	{
		struct
		{
			uint32_t prompt_tone: 1; //提示音
			uint32_t connect_state: 1; //连接状态

		}strVal;
		uint32_t config_flag; //配置标志位
	} config;

} ble_info_t;

#endif
