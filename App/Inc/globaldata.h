#ifndef _GLOBALDATA_H
#define _GLOBALDATA_H

#include "const.h"
#include "struct.h"
#include "ringbuffer.h"

extern ringbuffer_t g_uart_rb;
extern ble_info_t g_ble_info; //蓝牙信息
extern App_Info g_App_Info;  //应用程序信息Flash存储

extern uint32_t g_last_com_time; //上次通信时间

extern unsigned short   a;
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
extern unsigned short Line_time;                                        //跑马灯延时  20240613

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
extern unsigned char g_LED_Array_Mode0_Step3[30][LED_NUM];
extern unsigned char g_LED_Array_T[17][LED_NUM];
extern unsigned char g_LED_Array_CountDown[26][LED_NUM];
extern unsigned char g_LED_Array_djs[64][LED_NUM];
extern unsigned char g_LED_Array_djs2[32][LED_NUM];     //倒计时效果
//  20240517
extern unsigned char g_LED_Array_DS[30][LED_NUM];
extern unsigned char g_LED_Array_DS_1[28][LED_NUM];
extern unsigned char g_LED_Array_DS_2[70][LED_NUM];
extern unsigned char g_LED_Array_DS_3[30][LED_NUM];
extern unsigned char g_LED_Array_color[100][3];
extern unsigned char g_LED_Array_DS_4[30][LED_NUM];
extern unsigned char g_LED_Array_DS_5[30][LED_NUM];
extern unsigned char g_LED_Array_DS_6[30][LED_NUM];
extern unsigned char g_LED_Array_DS_7[50][LED_NUM];
extern unsigned char g_LED_Array_DS_8[30][LED_NUM];
extern unsigned char g_LED_Array_DS_9[50][LED_NUM];

//倒计时
extern unsigned char g_LED_Array_Countdown1[17][LED_NUM];
extern unsigned char g_LED_Array_Countdown2[17][LED_NUM];
extern unsigned char g_LED_Array_Countdown3[17][LED_NUM];
extern unsigned char g_LED_Count_flag;
extern unsigned char g_LED_Array_Countdown0[32];

//LED点亮点位
extern  unsigned char g_LED1_Array[LED_NUM];
extern  unsigned char g_LED2_Array[LED_NUM];
extern  unsigned char g_LED3_Array[LED_NUM];
extern  unsigned char g_LED4_Array[LED_NUM];
extern  unsigned char g_LED5_Array[LED_NUM];
extern  unsigned char g_LED6_Array[LED_NUM];

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
extern unsigned short g_Data_Perfect[6];        //正确数
extern unsigned short g_Data_Good[6];               //超前数
extern unsigned short g_Data_Noll[6];               //20240613  ADD
extern unsigned short g_Data_lj[6];                 //连击数
extern unsigned short g_Data_Max_lj[6];         //连击数
extern unsigned char num_lj_flag;                       //连击数清零标志、
extern unsigned char num_lj_a;                          //连击数清零标志、
extern unsigned char num_lj_b;
extern unsigned char flag_qj ;   //拳击点设定标志
extern unsigned char NUM ;
extern unsigned char num_lj_b_f;                                //20240604  ADD
//模式
extern unsigned char g_App_Mode_flag;
extern unsigned char g_App_Mode;
extern unsigned char g_App_Mode4_Running;   //模式4几种跑马灯
extern unsigned char g_App_Mode4_Running_Channel;   //模式4几种跑马灯通道
extern unsigned char g_App_Mode4_Running_Count; //模式4几种跑马灯计数

//歌曲结束计时
extern unsigned char g_Song_End_Count;

//环形灯击打
extern unsigned short g_Cycle_Light_Time;
extern unsigned char g_Cycle_Light_Flag[6];
extern unsigned short g_Cycle_Light_Count[6];
extern unsigned char flag_line_time[6];
extern unsigned char flag_line;

//灯光颜色设置
extern unsigned char g_LED_Color_Num ;
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
//20240604  ADD
extern unsigned char g_Mode5_Cycle_Color_R ;
extern unsigned char g_Mode5_Cycle_Color_G ;
extern unsigned char g_Mode5_Cycle_Color_B ;

extern unsigned char g_Mode5_Line_Color_R ;
extern unsigned char g_Mode5_Line_Color_G ;
extern unsigned char g_Mode5_Line_Color_B ;

//击打分界点
extern unsigned char g_Result_Good;

//检测到有键按下
extern unsigned char g_Push_Button_Value;

//开机动画计时
extern unsigned char g_Start_Count;

//蓝牙连接标志
extern unsigned char g_BT_Connect_Flag;

//灯光效果标志
extern unsigned char g_light_Flag;                  //20240517  ADD

//模式0步骤
extern unsigned char g_Mode0_Step_Flag;

extern const uint16_t index_wave[];

extern float h, s, v;

extern  uint16_t pwm_index ;                    //用于PWM查表
extern  uint16_t amplitude_cnt ;            //持续时间
extern uint16_t rgb_led_time;
//extern uint16_t rgb_led_time_flag;
extern const uint16_t R[];
extern const uint16_t G[];
extern const uint16_t B[];

//颜色修改标志
//extern unsigned char g_LED_running_flag ;
/*灯效标志*/
//extern unsigned char Led_On_light_flag;               //20240604 ADD
//初始化灯光效果
extern unsigned char Led_On_Mode0_Step2_flag;   //20240604 ADD

/*Mode5  */
extern unsigned char Stanley_Mode5_Light1_Flag;
extern unsigned char g_LED_Array_Mode5_Step1[32][LED_NUM];
extern unsigned char g_LED_Array_Mode5_Step2[32][LED_NUM];
extern unsigned char g_LED_Array_Mode5_Step3[32][LED_NUM];
extern unsigned char g_LED_Array_Mode5_Step4[40][LED_NUM];
extern unsigned char g_LED_Array_Mode5_Step5[32][LED_NUM];
extern unsigned char g_LED_Array_Mode5_Step6[32][LED_NUM];

#endif
