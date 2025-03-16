#include "Initial.h"
#include "globaldata.h"
#include "globalfunc.h"
#include "main.h"
#include "Bluetooth.h"

//应用程序初始化
void System_App_Init(void)
{
	//蓝牙复位
	BT_RST_Low();
	HAL_Delay(500);
	BT_RST_High();
	HAL_Delay(500);
	Write_BT_Name();
	HAL_Delay(500);
	/*
    //读取Flash
    Read_App_Info_From_Flash();
    //未配置过
    if(g_App_Info.config_flag != FLASH_ALREADY_CONFIG_FLAG)
    {
        //写入Flash
        Write_App_Info_To_Flash();
    }
	*/
}


