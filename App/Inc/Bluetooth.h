#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include <stdint.h>

void Write_BLE_Config( void );

uint8_t BLE_is_connected( void );
uint8_t BLE_is_playing( void );

//设置蓝牙名称
void Write_BT_Name( void );

void Write_BT_CHAR( void );
void Write_BT_WRITE( void );
void Write_BT_NOTI( void );
void Write_BT_DEFAULT( void );
void BLE_Read_BleState();

void Read_BT_Name( void );

void Read_BT_WRITE( void );
void Read_BT_CHAR( void );

void Send_BT_BDP( void );
void Write_BT_Baudrate( void );

void Send_Point_Data_BDP( void );

void Send_Boxing_Loc_BDP( unsigned char channel );

#endif
