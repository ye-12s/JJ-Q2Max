#include "globalfunc.h"
#include "globaldata.h"
#include "usart.h"
#include "tim.h"
#include "iwdg.h"
#include <stdio.h>
#include <string.h>		//memset
#include <stdlib.h>		//abs

//串口发送
void COM1_Send_BDP(unsigned char * buf, unsigned char len)
{
    while(HAL_UART_Transmit_IT(&huart1, buf, len) == HAL_OK);
}

//串口接收
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
    //判断是哪个串口触发的中断
    //	if(huart == &huart1)	//两个判断都可以,这个需要包含#include "usart.h"
    if(huart->Instance == USART1)
    {
        com1_timeout_count = 10;	//10ms间隔认为一条报文结束
        com1_buf[com1_recvbyte_count] = com1_recv_one_byte;
        com1_recvbyte_count++;
        //超过接收长度则不处理
        if(com1_recvbyte_count > USART1_BDP_LEN)
        {
            com1_recvbyte_count = 0;
        }
        //等待下一次接收中断
        HAL_UART_Receive_IT(huart, &com1_recv_one_byte, 1);
    }
}


//IO控制
void BT_RST_Low(void)
{
    HAL_GPIO_WritePin(BT_RST_GPIO_Port, BT_RST_Pin, GPIO_PIN_RESET);
}
void BT_RST_High(void)
{
    HAL_GPIO_WritePin(BT_RST_GPIO_Port, BT_RST_Pin, GPIO_PIN_SET);
}

//运行灯
void run_led_ctl(void)
{
    //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

//Flash相关
uint16_t FLASH_ReadHalfWord(uint32_t Address)
{
    return (*((volatile uint16_t *)(Address)));
}

void FLASH_WriteHalfWord(uint32_t Address, uint16_t * Data, uint32_t Len)
{
    uint32_t i = 0;
    //擦除FLASH
    FLASH_EraseInitTypeDef FlashSet;	//初始化FLASH_EraseInitTypeDef
    uint32_t PageError = 0;				//设置PageError
    //关中断
    //__disable_irq();
    // 1.解锁FLASH
    HAL_FLASH_Unlock();
    // 2.擦除FLASH
    FlashSet.TypeErase = FLASH_TYPEERASE_PAGES;				//擦除方式页擦除FLASH_TYPEERASE_PAGES，块擦除FLASH_TYPEERASE_MASS
    FlashSet.Banks = FLASH_BANK_1;
    FlashSet.PageAddress = Address;							//擦除地址
    FlashSet.NbPages = 1;									//擦除页数
    if(HAL_FLASHEx_Erase(&FlashSet, &PageError) != HAL_OK)	//调用擦除函数
    {
        HAL_FLASH_Lock();
        return;
    }
    // 3.对FLASH烧写
    while(i < Len)
    {
        if(HAL_OK == HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address + 2 * i, Data[i]))
        {
            i++;
        }
        else
        {
            HAL_FLASH_Lock();
            return;
        }
    }
    // 4.锁住FLASH
    HAL_FLASH_Lock();
    //开中断
    //__enable_irq();
}

//读取相关信息
void Read_App_Info_From_Flash(void)
{
    uint32_t i = 0;
    for(i = 0; i < sizeof(App_Info) / 2; i++)
    {
        *(uint16_t *)(&g_App_Info.config_flag + i) = FLASH_ReadHalfWord(FLASH_APP_INFO + 2 * i);
    }
}

//存储相关信息
void Write_App_Info_To_Flash(void)
{
    uint32_t i = 0;
    uint16_t temp_buf[48] = {0};
    g_App_Info.config_flag = FLASH_ALREADY_CONFIG_FLAG;
    for(i = 0 ; i < sizeof(App_Info) / 2; i++)
    {
        temp_buf[i] = *(uint16_t *)(&g_App_Info.config_flag + i);
    }
    FLASH_WriteHalfWord(FLASH_APP_INFO, temp_buf, sizeof(App_Info) / 2);
}


//看门狗相关
void IWDG_Feed(void)
{
    //Refresh IWDG: reload counter
    HAL_IWDG_Refresh(&hiwdg);
}


//发送串口缓存区报文
void Send_Serial_BDP(void)
{
    if(g_Serial_RingBuf_Num > 0)
    {
        if(g_Send_Serial_BDP_FIFO[g_Send_Serial_Index].send_counter > 0)
        {
            //发送一次报文
            g_Send_Serial_BDP_FIFO[g_Send_Serial_Index].send_counter--;
            COM1_Send_BDP(g_Send_Serial_BDP_FIFO[g_Send_Serial_Index].buf, g_Send_Serial_BDP_FIFO[g_Send_Serial_Index].len);
            //此条报文发送完毕
            if(g_Send_Serial_BDP_FIFO[g_Send_Serial_Index].send_counter == 0)
            {
                //memset((char *)g_Send_Serial_BDP_FIFO[g_Send_Serial_Index].buf, 0, MAX_FIFO_BUF_LEN);
                g_Send_Serial_Index++;
                if(g_Send_Serial_Index == MAX_SERIAL_FIFO_DEP)
                {
                    g_Send_Serial_Index = 0;
                }
                g_Serial_RingBuf_Num--;
            }
        }
    }
    else
    {
        //缓存区中无报文
    }
}

//把发送报文加到环形缓存区
unsigned char Add_BDP_To_Serial_RingBuf(unsigned char send_counter, unsigned char * pbuf, unsigned char len)
{
    unsigned char m_ret  = 0;
    //存储空间已经满了
    if(g_Serial_RingBuf_Num == MAX_SERIAL_FIFO_DEP)
    {
        m_ret = 0;
    }
    else
    {
        g_Send_Serial_BDP_FIFO[g_Add_Serial_Index].send_counter = send_counter;
        g_Send_Serial_BDP_FIFO[g_Add_Serial_Index].len = len;
        memcpy((char *)g_Send_Serial_BDP_FIFO[g_Add_Serial_Index].buf, pbuf, len);
        g_Add_Serial_Index++;
        if(g_Add_Serial_Index == MAX_SERIAL_FIFO_DEP)
        {
            g_Add_Serial_Index = 0;
        }
        g_Serial_RingBuf_Num++;
        m_ret = 1;
    }
    return m_ret;
}

//判断校验和
unsigned char JudgeChecksum(unsigned char * pbuf, unsigned short len)
{
    unsigned char ret = 0, sum1 = 0;
    unsigned short sum = 0;
    unsigned short i = 0;
    for(i = 0; i < len - 1; i++)
    {
        sum += pbuf[i];
    }
    sum1 = sum & 0xff;
    if(sum1 == pbuf[len - 1])
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

//计算校验和
unsigned char CalcChecksum(unsigned  char * pbuf, unsigned short len)
{
    unsigned char data = 0;
    unsigned short i = 0;
    for(i = 0; i < len; i++)
    {
        data += pbuf[i];
    }
    return data;
}

