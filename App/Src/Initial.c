#include "Initial.h"
#include "globaldata.h"
#include "globalfunc.h"
#include "main.h"
#include "Bluetooth.h"

//应用程序初始化
void System_App_Init( void )
{

	// HAL_Delay(500);
	// Write_BT_Name();
	// HAL_Delay(500);
	// Write_BT_NOTI();

	Write_BLE_Config();
}


