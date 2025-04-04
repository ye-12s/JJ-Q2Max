#include "Bluetooth.h"
#include "globaldata.h"
#include "globalfunc.h"
#include <stdio.h>
#include <string.h>     //memset
#include <stdlib.h>     //abs

#define CONST_STRING(str)  str, sizeof(str) - 1

extern  unsigned short g_Data_Max_value;    //


void Write_BT_UUID( void )
{
	COM1_Send_BDP( CONST_STRING( "AT+U0FFE0\r\n" ) );
	HAL_Delay( 100 );
	COM1_Send_BDP( CONST_STRING( "AT+U1FFE2\r\n" ) );
	HAL_Delay( 100 );
	COM1_Send_BDP( CONST_STRING( "AT+U2FFE1\r\n" ) );
	HAL_Delay( 100 );
	COM1_Send_BDP( CONST_STRING( "AT+U3FFE2\r\n" ) );
	HAL_Delay( 100 );
}

void Write_BLE_Config( void )
{
	Write_BT_UUID();
	COM1_Send_BDP( CONST_STRING( "AT+CN00\r\n" ) );
    HAL_Delay( 100 );
	COM1_Send_BDP( CONST_STRING( "AT+BMONEPUNCH Q2 Max\r\n" ) );      //ONEPUNCH Q2 Max
	HAL_Delay( 100 );
	COM1_Send_BDP( CONST_STRING( "AT+CZ\r\n" ) );
}


void Write_BT_Name( void )
{
	sprintf( ( char * )com1_send_buf, "AT+NAME=ONEPUNCH Q2 Max\r\n" );      //ONEPUNCH Q2 Max
	//  sprintf((char *)com1_send_buf, "AT+NAME=TuneBoxer Pro\r\n");            //BLE通道名称
	//  sprintf((char *)com1_send_buf, "AT+NAME=ONEPUNCH-Mini\r\n");            //MagicBoxing R1
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Write_BT_CHAR( void )
{
	sprintf( ( char * )com1_send_buf, "AT+CHAR=FFE4\r\n" );
	//  sprintf((char *)com1_send_buf, "AT+CHAR=FFE9\r\n");
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Write_BT_WRITE( void )
{
	sprintf( ( char * )com1_send_buf, "AT+WRITE=FFE9\r\n" );
	//  sprintf((char *)com1_send_buf, "AT+WRITE=FFE4\r\n");
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Write_BT_NOTI( void )                                                                  //20240704
{
	sprintf( ( char * )com1_send_buf, "AT+NOTI=0\r\n" );
	//  sprintf((char *)com1_send_buf, "AT+WRITE=FFE4\r\n");
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Write_BT_DEFAULT( void )
{
	sprintf( ( char * )com1_send_buf, "AT+DEFAULT\r\n" );
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Read_BT_Name( void )
{
	//  sprintf((char *)com1_send_buf, "AT+NAME\r\n");
	//  sprintf((char *)com1_send_buf, "AT+CHAR\r\n");
	sprintf( ( char * )com1_send_buf, "AT+WRITE\r\n" );
	//  sprintf((char *)com1_send_buf, "AT+MASTER\r\n");
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Read_BT_WRITE( void )
{
	sprintf( ( char * )com1_send_buf, "AT+WRITE\r\n" );
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Read_BT_CHAR( void )
{
	sprintf( ( char * )com1_send_buf, "AT+CHAR\r\n" );
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

//
void Write_BT_Baudrate( void )
{
	//字符行指令
	sprintf( ( char * )com1_send_buf, "AT+BAUD=5\r\n" );    //D30=7， BT22:5   20240329
	com1_send_len = strlen( ( char const * )com1_send_buf );
	COM1_Send_BDP( com1_send_buf, com1_send_len );
}

void Send_BT_BDP( void )
{
	com1_send_buf[0] = 0xAA;
	com1_send_buf[1] = 0xBB;
	com1_send_buf[2] = 0xCC;
	com1_send_buf[3] = 0xCC;
	COM1_Send_BDP( com1_send_buf, 4 );
}

//发送拳击点位计数                                          20240326 SPP在播放期间一直有数据上传 ？
void Send_Point_Data_BDP( void )
{

	com1_send_buf[0] = BDP_HEAD;
	com1_send_buf[1] = BDP_CMD_READ;

	com1_send_buf[2] = g_Data_Perfect[0] & 0xFF;
	com1_send_buf[3] = g_Data_Perfect[1] & 0xFF;
	com1_send_buf[4] = g_Data_Perfect[2] & 0xFF;
	com1_send_buf[5] = g_Data_Perfect[3] & 0xFF;
	com1_send_buf[6] = g_Data_Perfect[4] & 0xFF;
	com1_send_buf[7] = g_Data_Perfect[5] & 0xFF;
	com1_send_buf[8] = g_Data_Good[0] & 0xFF;
	com1_send_buf[9] = g_Data_Good[1] & 0xFF;
	com1_send_buf[10] = g_Data_Good[2] & 0xFF;
	com1_send_buf[11] = g_Data_Good[3] & 0xFF;
	com1_send_buf[12] = g_Data_Good[4] & 0xFF;
	com1_send_buf[13] = g_Data_Good[5] & 0xFF;

	com1_send_buf[14] = g_Data_lj[0] & 0xFF;
	com1_send_buf[15] = g_Data_Max_lj[0] & 0xFF;

	com1_send_buf[16] = CalcChecksum( com1_send_buf, 16 );
	COM1_Send_BDP( com1_send_buf, 17 );

}

void Send_Boxing_Loc_BDP( unsigned char channel )
{
	com1_send_buf[0] = BDP_HEAD;
	com1_send_buf[1] = BDP_CMD_READ;
	com1_send_buf[2] = 0;
	com1_send_buf[3] = 0x31;
	com1_send_buf[4] = channel;
	com1_send_buf[5] = CalcChecksum( com1_send_buf, 5 );
	COM1_Send_BDP( com1_send_buf, 6 );
}

