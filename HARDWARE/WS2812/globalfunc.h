#ifndef _GLOBALFUNC_H
#define _GLOBALFUNC_H

#include <stdint.h>

//串口发送
void COM1_Send_BDP(unsigned char * buf, unsigned char len);

//IO控制
void BT_RST_Low(void) ;
void BT_RST_High(void) ;

//运行灯
void run_led_ctl(void);

//Flash相关
uint16_t FLASH_ReadHalfWord(uint32_t Address);
void FLASH_WriteHalfWord(uint32_t Address, uint16_t * Data, uint32_t Len);

void Read_App_Info_From_Flash(void);
void Write_App_Info_To_Flash(void);

//看门狗相关
void IWDG_Feed(void);

//发送串口缓存区报文
void Send_Serial_BDP(void);

//把发送报文加到环形缓存区
unsigned char Add_BDP_To_Serial_RingBuf(unsigned char send_counter, unsigned char * pbuf, unsigned char len);

//判断校验和
unsigned char JudgeChecksum(unsigned char * pbuf, unsigned short len);
//计算校验和
unsigned char CalcChecksum(unsigned char * pbuf, unsigned short len);

#endif
