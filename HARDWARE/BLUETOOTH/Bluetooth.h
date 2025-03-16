#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

//#include <stdint.h>

//设置蓝牙名称
void Write_BT_Name(void);

void Write_BT_CHAR(void);
void Write_BT_WRITE(void);

void Write_BT_DEFAULT(void);

void Read_BT_Name(void);

void Read_BT_WRITE(void);
void Read_BT_CHAR(void);

void Send_BT_BDP(void);
//波特率修改
void Write_Baudrate(void);


void Send_Point_Data_BDP(void);

void Send_Boxing_Loc_BDP(unsigned char channel);

#endif
