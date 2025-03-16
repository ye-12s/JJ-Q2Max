#include "Bluetooth.h"
#include "globaldata.h"
#include "globalfunc.h"
#include <stdio.h>
#include <string.h>		//memset
#include <stdlib.h>		//abs



void Write_BT_Name(void)
{
	sprintf((char *)com1_send_buf, "AT+NAME=Heatmai\r\n");
//	sprintf((char *)com1_send_buf, "AT+NAME=ONEPUNCH-Mini\r\n");
	//sprintf((char *)com1_send_buf, "AT+NAMB=MX-ONEPUNCH\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Write_BT_CHAR(void)
{
	sprintf((char *)com1_send_buf, "AT+CHAR=FFE4\r\n");
//	sprintf((char *)com1_send_buf, "AT+CHAR=FFE9\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Write_BT_WRITE(void)
{
	sprintf((char *)com1_send_buf, "AT+WRITE=FFE9\r\n");
//	sprintf((char *)com1_send_buf, "AT+WRITE=FFE4\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Write_BT_DEFAULT(void)
{
	sprintf((char *)com1_send_buf, "AT+DEFAULT\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Read_BT_Name(void)
{
//	sprintf((char *)com1_send_buf, "AT+NAME\r\n");
//	sprintf((char *)com1_send_buf, "AT+CHAR\r\n");
	sprintf((char *)com1_send_buf, "AT+WRITE\r\n");
//	sprintf((char *)com1_send_buf, "AT+MASTER\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Read_BT_WRITE(void)
{
	sprintf((char *)com1_send_buf, "AT+WRITE\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Read_BT_CHAR(void)
{
	sprintf((char *)com1_send_buf, "AT+CHAR\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

//波特率
void Write_Baudrate(void)
{
	sprintf((char *)com1_send_buf, "AT+BAUD=7\r\n");
//	sprintf((char *)com1_send_buf, "AT+WRITE=FFE4\r\n");
    com1_send_len = strlen(com1_send_buf);
	COM1_Send_BDP(com1_send_buf, com1_send_len);
}

void Send_BT_BDP(void)
{
	com1_send_buf[0] = 0xAA;
	com1_send_buf[1] = 0xBB;
	com1_send_buf[2] = 0xCC;
	com1_send_buf[3] = 0xCC;
	COM1_Send_BDP(com1_send_buf, 4);
}

//发送拳击点位计数
void Send_Point_Data_BDP(void)
{
	com1_send_buf[0] = BDP_HEAD;
	com1_send_buf[1] = BDP_CMD_READ;
	com1_send_buf[2] = 0;
	com1_send_buf[3] = 0x01;
	com1_send_buf[4] = 0;
	com1_send_buf[5] = 0x0C;
	com1_send_buf[6] = (g_Data_Perfect[0] >> 8) & 0xFF;
	com1_send_buf[7] = g_Data_Perfect[0] & 0xFF;
	com1_send_buf[8] = (g_Data_Perfect[1] >> 8) & 0xFF;
	com1_send_buf[9] = g_Data_Perfect[1] & 0xFF;
	com1_send_buf[10] = (g_Data_Perfect[2] >> 8) & 0xFF;
	com1_send_buf[11] = g_Data_Perfect[2] & 0xFF;
	com1_send_buf[12] = (g_Data_Perfect[3] >> 8) & 0xFF;
	com1_send_buf[13] = g_Data_Perfect[3] & 0xFF;
	com1_send_buf[14] = (g_Data_Perfect[4] >> 8) & 0xFF;
	com1_send_buf[15] = g_Data_Perfect[4] & 0xFF;
	com1_send_buf[16] = (g_Data_Perfect[5] >> 8) & 0xFF;
	com1_send_buf[17] = g_Data_Perfect[5] & 0xFF;
	com1_send_buf[18] = (g_Data_Good[0] >> 8) & 0xFF;
	com1_send_buf[19] = g_Data_Good[0] & 0xFF;
	com1_send_buf[20] = (g_Data_Good[1] >> 8) & 0xFF;
	com1_send_buf[21] = g_Data_Good[1] & 0xFF;
	com1_send_buf[22] = (g_Data_Good[2] >> 8) & 0xFF;
	com1_send_buf[23] = g_Data_Good[2] & 0xFF;
	com1_send_buf[24] = (g_Data_Good[3] >> 8) & 0xFF;
	com1_send_buf[25] = g_Data_Good[3] & 0xFF;
	com1_send_buf[26] = (g_Data_Good[4] >> 8) & 0xFF;
	com1_send_buf[27] = g_Data_Good[4] & 0xFF;
	com1_send_buf[28] = (g_Data_Good[5] >> 8) & 0xFF;
	com1_send_buf[29] = g_Data_Good[5] & 0xFF;
	
//	com1_send_buf[30] = (g_Data_Noll[0] >> 8) & 0xFF;
//	com1_send_buf[31] = g_Data_Noll[0] & 0xFF;
	
	com1_send_buf[30] = (g_Data_lj[0] >> 8) & 0xFF;
	com1_send_buf[31] = g_Data_lj[0] & 0xFF;
	com1_send_buf[32] = (g_Data_Max_lj[0] >> 8) & 0xFF;
	com1_send_buf[33] = g_Data_Max_lj[0] & 0xFF;
	

	com1_send_buf[34] = CalcChecksum(com1_send_buf, 34);
	COM1_Send_BDP(com1_send_buf, 35);
}

//模式3下向APP回告击打区域
void Send_Boxing_Loc_BDP(unsigned char channel)
{
	com1_send_buf[0] = BDP_HEAD;
	com1_send_buf[1] = BDP_CMD_READ;
	com1_send_buf[2] = 0;
	com1_send_buf[3] = 0x31;
	com1_send_buf[4] = channel;
	com1_send_buf[5] = CalcChecksum(com1_send_buf, 5);
	COM1_Send_BDP(com1_send_buf, 6);
}

