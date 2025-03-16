#ifndef _APP_H
#define _APP_H

//循环任务
void TaskStart(void);

//串口报文接收处理
void Task_USART1_Recv(void);

//处理串口1报文
void Proc_USART1_BDP(unsigned char * pbuf, unsigned short len);

void Add_Info_To_LED_FIFO(unsigned short LED_Channel);
void Proc_LED_FIFO(void);

//按键处理
void Proc_Push_Button(void);

//按键检测
unsigned char Scan_Push_Button(unsigned char mode);


#endif
