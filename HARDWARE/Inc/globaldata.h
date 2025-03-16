#ifndef _GLOBALDATA_H
#define _GLOBALDATA_H

#include "const.h"
#include "struct.h"





extern App_Info g_App_Info;  //应用程序信息Flash存储
extern unsigned short	a;
extern unsigned char com1_timeout_count;  //串口1通信超时计数器
extern unsigned short com1_recvbyte_count, com1_recvbyte_count_1; //串口1通信接收数据计数器
extern unsigned char com1_buf[USART1_BDP_LEN];       //串口1缓冲区
extern unsigned char com1_recv_one_byte;

extern unsigned char g_com1_frame_flag;

extern unsigned char com1_send_buf[USART1_BDP_LEN];
extern unsigned char com1_send_len;

//定时器 定时标志相关定义
extern unsigned short g_Line_Count, g_Cycle_Count;
extern unsigned char  g_Line_Flag, g_Cycle_Flag;
extern unsigned short g_2000ms_counter, g_500ms_counter;
extern unsigned char  g_2000ms_flag, g_500ms_flag;

//串口发送报文缓存区
extern Send_Serial_BDP_FIFO g_Send_Serial_BDP_FIFO[MAX_SERIAL_FIFO_DEP];
extern unsigned char g_Send_Serial_Index;
extern unsigned char g_Add_Serial_Index;
extern unsigned char g_Serial_RingBuf_Num;

//灯显示计数
extern unsigned char g_LED_Count;
extern unsigned char g_LED_Cycle_Count;

//每个计数对应亮灯位置(0不亮;1亮)
extern unsigned char g_LED_Array[LED_CYCLE_COUNT][LED_NUM];
extern unsigned char g_LED_Array_Mode1[LED_CYCLE_COUNT][LED_NUM];
extern unsigned char g_LED_Array_Mode0_Step1[32][LED_NUM];
extern unsigned char g_LED_Array_Mode0_Step2[28][LED_NUM];
extern unsigned char g_LED_Array_Mode0_Step3[17][LED_NUM];

//LED点亮点位
extern unsigned char g_LED1_Array[LED_NUM];
extern unsigned char g_LED2_Array[LED_NUM];
extern unsigned char g_LED3_Array[LED_NUM];
extern unsigned char g_LED4_Array[LED_NUM];
extern unsigned char g_LED5_Array[LED_NUM];
extern unsigned char g_LED6_Array[LED_NUM];

//点WS2812数组
extern uint16_t g_LED1_Buffer[DATA_BUFFER_LEN];
extern uint16_t g_LED2_Buffer[DATA_BUFFER_LEN];
extern uint16_t g_LED3_Buffer[DATA_BUFFER_LEN];
extern uint16_t g_LED4_Buffer[DATA_BUFFER_LEN];
extern uint16_t g_LED5_Buffer[DATA_BUFFER_LEN];
extern uint16_t g_LED6_Buffer[DATA_BUFFER_LEN];

//每个点位的FIFO
extern LED_FIFO g_LED_FIFO[MAX_LED_FIFO_DEP];
extern unsigned char g_LED_RingBuf_Num;
extern unsigned char g_Add_LED_Index;

//循环周期
extern unsigned short g_Line_Period;
extern unsigned short g_Cycle_Period;

//记录点位数据
extern unsigned short g_Data_Perfect[6];	//正确数
extern unsigned short g_Data_Good[6];		//超前数
extern unsigned short g_Data_Noll[6];
extern unsigned short g_Data_lj[6] ;		//连击
extern unsigned short g_Data_Max_lj[6];		//最大连击

//模式
extern unsigned char g_App_Mode_flag;
extern unsigned char g_App_Mode;
extern unsigned char g_App_Mode4_Running;	//模式4几种跑马灯
extern unsigned char g_App_Mode4_Running_Channel;	//模式4几种跑马灯通道
extern unsigned char g_App_Mode4_Running_Count;	//模式4几种跑马灯计数

//歌曲结束计时
extern unsigned char g_Song_End_Count;

//环形灯击打
extern unsigned short g_Cycle_Light_Time;
extern unsigned char g_Cycle_Light_Flag[6];
extern unsigned short g_Cycle_Light_Count[6];

//颜色
extern unsigned char g_Line_Color_R;
extern unsigned char g_Line_Color_G;
extern unsigned char g_Line_Color_B;

extern unsigned char g_Cycle_Color_Perfect_R;
extern unsigned char g_Cycle_Color_Perfect_G;
extern unsigned char g_Cycle_Color_Perfect_B;

extern unsigned char g_Cycle_Color_Good_R;
extern unsigned char g_Cycle_Color_Good_G;
extern unsigned char g_Cycle_Color_Good_B;

extern unsigned char g_Mode4_Line_Color_R;
extern unsigned char g_Mode4_Line_Color_G;
extern unsigned char g_Mode4_Line_Color_B;

extern unsigned char g_Mode4_Cycle_Color_R;
extern unsigned char g_Mode4_Cycle_Color_G;
extern unsigned char g_Mode4_Cycle_Color_B;

extern unsigned char g_Mode0_Color_R;
extern unsigned char g_Mode0_Color_G;
extern unsigned char g_Mode0_Color_B;

//击打分界点
extern unsigned char g_Result_Good;

//检测到有键按下
extern unsigned char g_Push_Button_Value;

//开机动画计时
extern unsigned char g_Start_Count;

//蓝牙连接标志
extern unsigned char g_BT_Connect_Flag;

//模式0步骤
extern unsigned char g_Mode0_Step_Flag;

#endif
