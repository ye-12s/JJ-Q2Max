#include "APP.h"
#include "globaldata.h"
#include "globalfunc.h"
#include "WS2812.h"
#include "Bluetooth.h"
#include <string.h>		//strstr

//循环任务
void TaskStart(void)
{
    //串口报文接收处理
    Task_USART1_Recv();
	
		if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12))
		g_BT_Connect_Flag = 0;
	//按键处理
	
	if( (2 == g_App_Mode)	 || (3 == g_App_Mode) )
	{
		g_Push_Button_Value = Scan_Push_Button(0);
		//计时到灭灯
		if(2 == g_Cycle_Light_Flag[0])
		{
			g_Cycle_Light_Flag[0] = 0;
			//灭环形灯
			//设置灯颜色
			Set_Led_Cycle_Array(1, LED_ARRAY_OFF);
			Led1_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
			Led1_On();
		}
		else if(2 == g_Cycle_Light_Flag[1])
		{
			g_Cycle_Light_Flag[1] = 0;
			//灭环形灯
			//设置灯颜色
			Set_Led_Cycle_Array(2, LED_ARRAY_OFF);
			Led2_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
			Led2_On();
		}
		else if(2 == g_Cycle_Light_Flag[2])
		{
			g_Cycle_Light_Flag[2] = 0;
			//灭环形灯
			//设置灯颜色
			Set_Led_Cycle_Array(3, LED_ARRAY_OFF);
			Led3_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
			Led3_On();
		}
		else if(2 == g_Cycle_Light_Flag[3])
		{
			g_Cycle_Light_Flag[3] = 0;
			//灭环形灯
			//设置灯颜色
			Set_Led_Cycle_Array(4, LED_ARRAY_OFF);
			Led4_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
			Led4_On();
		}
		else if(2 == g_Cycle_Light_Flag[4])
		{
			g_Cycle_Light_Flag[4] = 0;
			//灭环形灯
			//设置灯颜色
			Set_Led_Cycle_Array(5, LED_ARRAY_OFF);
			Led5_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
			Led5_On();
		}
		else if(2 == g_Cycle_Light_Flag[5])
		{
			g_Cycle_Light_Flag[5] = 0;
			//灭环形灯
			//设置灯颜色
			Set_Led_Cycle_Array(6, LED_ARRAY_OFF);
			Led6_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
			Led6_On();
		}
		//模式3
		if(3 == g_App_Mode)
		{
			if(g_Push_Button_Value)
			{
				if(1 == g_Push_Button_Value)
				{
					Set_Led_Cycle_Array(1, LED_ARRAY_ON);
					Led1_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
					Led1_On();
					//开始灭灯倒计时
					g_Cycle_Light_Flag[0] = 1;
				}
				else if(2 == g_Push_Button_Value)
				{
					Set_Led_Cycle_Array(2, LED_ARRAY_ON);
					Led2_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
					Led2_On();
					//开始灭灯倒计时
					g_Cycle_Light_Flag[1] = 1;
				}
				else if(3 == g_Push_Button_Value)
				{
					Set_Led_Cycle_Array(3, LED_ARRAY_ON);
					Led3_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
					Led3_On();
					//开始灭灯倒计时
					g_Cycle_Light_Flag[2] = 1;
				}
				else if(4 == g_Push_Button_Value)
				{
					Set_Led_Cycle_Array(4, LED_ARRAY_ON);
					Led4_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
					Led4_On();
					//开始灭灯倒计时
					g_Cycle_Light_Flag[3] = 1;
				}
				else if(5 == g_Push_Button_Value)
				{
					Set_Led_Cycle_Array(5, LED_ARRAY_ON);
					Led5_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
					Led5_On();
					//开始灭灯倒计时
					g_Cycle_Light_Flag[4] = 1;
				}
				else if(6 == g_Push_Button_Value)
				{
					g_Cycle_Light_Flag[5] = 1;
					Set_Led_Cycle_Array(6, LED_ARRAY_ON);
					Led6_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
					Led6_On();
					//开始灭灯倒计时
					g_Cycle_Light_Flag[5] = 1;
				}
				Send_Boxing_Loc_BDP(g_Push_Button_Value);
				g_Push_Button_Value = 0;
			}
		}
		//模式2
		else if(2 == g_App_Mode)
		{
			if(g_Push_Button_Value)
			{
				Proc_Push_Button();
				g_Push_Button_Value = 0;
			}
		}
	}
    //条形灯循环时间到
    if(g_Line_Flag == 1)
    {
        g_Line_Flag = 0;
		//初始化
		if(0 == g_App_Mode)
		{
			if(0 == g_Mode0_Step_Flag)
			{
				//清除点灯
				Led_All_Off();
				g_Mode0_Step_Flag = 1;
			}
			else if(1 == g_Mode0_Step_Flag)
			{
				Led_On_Mode0_Step1();
			}
			else if(2 == g_Mode0_Step_Flag)
			{
				Led_On_Mode0_Step2();
			}
			else if(3 == g_Mode0_Step_Flag)
			{
				Led_On_Mode0_Step3();
				g_App_Mode_flag =1;
			}
		}
		//点歌模式
		else if(2 == g_App_Mode)
		{
			//
			Proc_LED_FIFO();
			Led1_Set_Running(g_Line_Color_R, g_Line_Color_G, g_Line_Color_B);
			Led2_Set_Running(g_Line_Color_R, g_Line_Color_G, g_Line_Color_B);
			Led3_Set_Running(g_Line_Color_R, g_Line_Color_G, g_Line_Color_B);
			Led4_Set_Running(g_Line_Color_R, g_Line_Color_G, g_Line_Color_B);
			Led5_Set_Running(g_Line_Color_R, g_Line_Color_G, g_Line_Color_B);
			Led6_Set_Running(g_Line_Color_R, g_Line_Color_G, g_Line_Color_B);
			Led_On();
		}
		//模式4
		else if(4 == g_App_Mode)
		{
			if(4 == g_App_Mode4_Running)
			{
				Set_LED_Mode4_Running(g_App_Mode4_Running_Channel, 0, LED_NUM);
			}
			else if(5 == g_App_Mode4_Running)
			{
				Set_LED_Mode4_Running(g_App_Mode4_Running_Channel, 0, LED_RUNNING_NUM);
			}
		}
    }
    //环形灯循环时间到
    if(g_Cycle_Flag == 1)
    {
        g_Cycle_Flag = 0;
		//模式4
		if(4 == g_App_Mode)
		{
			if(6 == g_App_Mode4_Running)
			{
				Set_LED_Mode4_Running(g_App_Mode4_Running_Channel, LED_RUNNING_NUM, LED_NUM);
			}
		}    
	}
	//2秒定时
    if(g_2000ms_flag == 1)
    {
        g_2000ms_flag = 0;
		/*
		//开机动画显示
		if(0 == g_App_Mode)
		{
			g_Start_Count++;
			if(g_Start_Count >= 5)
			{
				g_Start_Count = 0;
				g_App_Mode = 1;
			}
		}
		*/
        //歌曲结束计时
        if(2 == g_App_Mode)
        {
        	g_Song_End_Count++;
			if(g_Song_End_Count >= 10)
			{
				g_Song_End_Count = 0;
				g_App_Mode = 1;
			}
        }
		//模式1显示蓝牙连接状态
		if(1 == g_App_Mode)
		{
			//显示固定指示灯
			Led_On_Mode1(g_BT_Connect_Flag);
		}
    }
    //500毫秒定时
    if(g_500ms_flag == 1)
    {
        g_500ms_flag = 0;
		//喂狗
		IWDG_Feed();
    }
}

//串口报文接收处理
void Task_USART1_Recv(void)
{ 
    if(g_com1_frame_flag == 1)
    {
        g_com1_frame_flag = 0;
        Proc_USART1_BDP(com1_buf, com1_recvbyte_count_1);
		
    }
}

//处理串口1报文
void Proc_USART1_BDP(unsigned char * pbuf, unsigned short len)
{	
	unsigned char m_Head, m_Cmd;
	unsigned short m_Addr, m_Data;
	unsigned char i;
	m_Head = pbuf[0];
	m_Cmd = pbuf[1];
	m_Addr = pbuf[2] * 256 + pbuf[3];
	m_Data = pbuf[6] * 256 + pbuf[7];
	//蓝牙连接断开处理
	//蓝牙连接

		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12))
	{
		g_BT_Connect_Flag = 1;
	}
	//蓝牙断开
	else if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12))
	{
		g_BT_Connect_Flag = 0;
		//断开蓝牙切回模式1
		if(g_App_Mode_flag)
		g_App_Mode = 1;
	}
	
//	if( strstr(pbuf,"IM_CONN") != NULL )
//	{
//		g_BT_Connect_Flag = 1;
//		
//	}
//	//蓝牙断开
//	else if( strstr(pbuf,"IM_DISC") != NULL )
//	{
//		g_BT_Connect_Flag = 0;
//		//断开蓝牙切回模式1
//		g_App_Mode = 1;
//	}
	//收到命令回复
	if(m_Head == BDP_HEAD)
    {
        COM1_Send_BDP(com1_buf, com1_recvbyte_count_1);
    }
	//开机关机命令
	if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_1) )
	{
		//开机
		if(0x01 == pbuf[7])
		{
			g_App_Mode = 2;
			for(i = 0; i < 6; i++)
			{
				g_Data_Perfect[i] = 0;
				g_Data_Good[i] = 0;
				g_Data_lj[0] = 0; 
				g_Data_Max_lj[0] = 0; 
			}
		}
		//关机
		else if(0x00 == pbuf[7])
		{
		}
	}
	//模式2拳击点设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_2) )
	{g_App_Mode=2;
		if(2 == g_App_Mode)
		{
			g_Song_End_Count = 0;
			//循环周期改变
			g_Line_Period = pbuf[6];
			//加入FIFO
			Add_Info_To_LED_FIFO(pbuf[7]);
		
		}
	}
	//模式设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_3) )
	{
		g_App_Mode = pbuf[7];
		//切换模式清除点灯
		Led_All_Off();
		//显示固定指示灯
		Led_On_Mode1(g_BT_Connect_Flag);
	}
	//跑马灯颜色设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_4) )
	{
		g_Line_Color_R = pbuf[4];
		g_Line_Color_G = pbuf[5];
		g_Line_Color_B = pbuf[6];
	}
	//环形灯颜色设定击打成功
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_5) )
	{
		g_Cycle_Color_Perfect_R = pbuf[4];
		g_Cycle_Color_Perfect_G = pbuf[5];
		g_Cycle_Color_Perfect_B = pbuf[6];
	}
	//环形灯颜色设定击打超前
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_6) )
	{
		g_Cycle_Color_Good_R = pbuf[4];
		g_Cycle_Color_Good_G = pbuf[5];
		g_Cycle_Color_Good_B = pbuf[6];
	}
	//条形灯时间间隔设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_7) )
	{
		g_Line_Period = pbuf[7];
	}
	//环形灯时间间隔设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_8) )
	{
		g_Cycle_Period = pbuf[7];
	}
	//击打环形灯点亮时间设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_9) )
	{
		g_Cycle_Light_Time = pbuf[7] * 100;
	}
	//击打环形灯点亮时间设定
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == BDP_ADDR_10) )
	{
		g_Result_Good = pbuf[7];
	}
	//读取点数命令
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_READ)  && (m_Addr == BDP_ADDR_1) )
	{
		HAL_Delay(10);
//		g_Data_Noll[0]=(a-2);
		HAL_Delay(20);
		Send_Point_Data_BDP();
		HAL_Delay(50);	
	}
	//模式4的条形灯同时亮
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == 0x0041) )
	{
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		if(1 == pbuf[8])
		{	
			Set_Led_Line_Odd_Array(1, LED_ARRAY_ON);
			Led1_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led1_On();
		}
		else if(2 == pbuf[8])
		{
			Set_Led_Line_Odd_Array(2, LED_ARRAY_ON);
			Led2_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led2_On();
		}
		else if(3 == pbuf[8])
		{
			Set_Led_Line_Odd_Array(3, LED_ARRAY_ON);
			Led3_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led3_On();
		}
		else if(4 == pbuf[8])
		{
			Set_Led_Line_Odd_Array(4, LED_ARRAY_ON);
			Led4_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led4_On();
		}
		else if(5 == pbuf[8])
		{
			Set_Led_Line_Odd_Array(5, LED_ARRAY_ON);
			Led5_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led5_On();
		}
		else if(6 == pbuf[8])
		{
			Set_Led_Line_Odd_Array(6, LED_ARRAY_ON);
			Led6_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led6_On();
		}
	}
	//模式4的环形灯同时亮
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == 0x0042) )
	{
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		if(1 == pbuf[8])
		{
			Set_Led_Cycle_Odd_Array(1, LED_ARRAY_ON);
			Led1_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led1_On();
		}
		else if(2 == pbuf[8])
		{
			Set_Led_Cycle_Odd_Array(2, LED_ARRAY_ON);
			Led2_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led2_On();
		}
		else if(3 == pbuf[8])
		{
			Set_Led_Cycle_Odd_Array(3, LED_ARRAY_ON);
			Led3_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led3_On();
		}
		else if(4 == pbuf[8])
		{
			Set_Led_Cycle_Odd_Array(4, LED_ARRAY_ON);
			Led4_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led4_On();
		}
		else if(5 == pbuf[8])
		{
			Set_Led_Cycle_Odd_Array(5, LED_ARRAY_ON);
			Led5_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led5_On();
		}
		else if(6 == pbuf[8])
		{
			Set_Led_Cycle_Odd_Array(6, LED_ARRAY_ON);
			Led6_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led6_On();
		}
	}
	//模式4的条形灯、环形灯同时亮
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == 0x0043) )
	{
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		if(1 == pbuf[8])
		{
			Set_Led_Odd_Array(1, LED_ARRAY_ON);
			Led1_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led1_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led1_On();
		}
		else if(2 == pbuf[8])
		{
			Set_Led_Odd_Array(2, LED_ARRAY_ON);
			Led2_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led2_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led2_On();
		}
		else if(3 == pbuf[8])
		{
			Set_Led_Odd_Array(3, LED_ARRAY_ON);
			Led3_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led3_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led3_On();
		}
		else if(4 == pbuf[8])
		{
			Set_Led_Odd_Array(4, LED_ARRAY_ON);
			Led4_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led4_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led4_On();
		}
		else if(5 == pbuf[8])
		{
			Set_Led_Odd_Array(5, LED_ARRAY_ON);
			Led5_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led5_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led5_On();
		}
		else if(6 == pbuf[8])
		{
			Set_Led_Odd_Array(6, LED_ARRAY_ON);
			Led6_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led6_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led6_On();
		}
	}
	//模式4的条形灯、环形灯跑马灯
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == 0x0044) )
	{
		g_App_Mode = 4;
		g_App_Mode4_Running = 4;
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		g_App_Mode4_Running_Channel = pbuf[8];
		g_App_Mode4_Running_Count = 0;
		Set_LED_Mode4_Running(g_App_Mode4_Running_Channel, 0, LED_NUM);
	}
	//模式4的条形灯跑马灯
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == 0x0045) )
	{
		g_App_Mode = 4;
		g_App_Mode4_Running = 5;
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		g_App_Mode4_Running_Channel = pbuf[8];
		g_App_Mode4_Running_Count = 0;
		Set_LED_Mode4_Running(g_App_Mode4_Running_Channel, 0, LED_RUNNING_NUM);
	}
	//模式4的环形灯跑马灯
	else if( (m_Head == BDP_HEAD) && (m_Cmd == BDP_CMD_WRITE)  && (m_Addr == 0x0046) )
	{
		g_App_Mode = 4;
		g_App_Mode4_Running = 6;
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		g_App_Mode4_Running_Channel = pbuf[8];
		g_App_Mode4_Running_Count = LED_RUNNING_NUM;
		Set_LED_Mode4_Running(g_App_Mode4_Running_Channel, LED_RUNNING_NUM, LED_NUM);
	}

}

void Add_Info_To_LED_FIFO(unsigned short LED_Channel)
{
    //存储空间已经满了
    if(g_LED_RingBuf_Num == MAX_LED_FIFO_DEP)
    {
    }
    else
    {a=a+1;
        g_LED_FIFO[g_Add_LED_Index].Valid_Flag = 1;
        g_LED_FIFO[g_Add_LED_Index].LED_Channel = LED_Channel;
        g_LED_FIFO[g_Add_LED_Index].Now_Count = 0;
        g_Add_LED_Index++;
        if(g_Add_LED_Index == MAX_LED_FIFO_DEP)
        {
            g_Add_LED_Index = 0;
        }
        g_LED_RingBuf_Num++;
    }
}

void Proc_LED_FIFO(void)
{
	unsigned char i = 0, j = 0;
	//清除亮灯点位
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		g_LED1_Array[j] = 0;
		g_LED2_Array[j] = 0;
		g_LED3_Array[j] = 0;
		g_LED4_Array[j] = 0;
		g_LED5_Array[j] = 0;
		g_LED6_Array[j] = 0;
	}
	//点位合并
	for(i = 0; i < MAX_LED_FIFO_DEP; i++)
	{
		//通道1亮灯点位合并
		if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 1) )
		{
			for(j = 0; j < LED_RUNNING_NUM; j++)
			{
				g_LED1_Array[j] = (g_LED1_Array[j]) | (g_LED_Array[g_LED_FIFO[i].Now_Count][j]);
			}

		}
		//通道2亮灯点位合并
		if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 2) )
		{
			for(j = 0; j < LED_RUNNING_NUM; j++)
			{
				g_LED2_Array[j] = (g_LED2_Array[j]) | (g_LED_Array[g_LED_FIFO[i].Now_Count][j]);
			}
		}
		//通道3亮灯点位合并
		if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 3) )
		{
			for(j = 0; j < LED_RUNNING_NUM; j++)
			{
				g_LED3_Array[j] = (g_LED3_Array[j]) | (g_LED_Array[g_LED_FIFO[i].Now_Count][j]);
			}
		}
		//通道4亮灯点位合并
		if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 4) )
		{
			for(j = 0; j < LED_RUNNING_NUM; j++)
			{
				g_LED4_Array[j] = (g_LED4_Array[j]) | (g_LED_Array[g_LED_FIFO[i].Now_Count][j]);
			}
		}
		//通道5亮灯点位合并
		if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 5) )
		{
			for(j = 0; j < LED_RUNNING_NUM; j++)
			{
				g_LED5_Array[j] = (g_LED5_Array[j]) | (g_LED_Array[g_LED_FIFO[i].Now_Count][j]);
			}
		}
		//通道6亮灯点位合并
		if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 6) )
		{
			for(j = 0; j < LED_RUNNING_NUM; j++)
			{
				g_LED6_Array[j] = (g_LED6_Array[j]) | (g_LED_Array[g_LED_FIFO[i].Now_Count][j]);
			}
		}
	}
	//当前移动位置+1
	for(i = 0; i < MAX_LED_FIFO_DEP; i++)
	{
		if(g_LED_FIFO[i].Valid_Flag == 1)
		{
			g_LED_FIFO[i].Now_Count++;
			//到最后一个点就清除
			if(g_LED_FIFO[i].Now_Count >= LED_CYCLE_COUNT)
			{
				g_LED_FIFO[i].Valid_Flag = 0;
				g_LED_FIFO[i].LED_Channel = 0;
				g_LED_FIFO[i].Now_Count = 0;
				//FIFO总数减1
				g_LED_RingBuf_Num--;
				
				g_Data_lj[0] = 0;
				Send_Point_Data_BDP();
			}
		}
	}
}
//按键处理
void Proc_Push_Button(void)
{
	unsigned char i = 0, j = 0;
	unsigned short m_Max_Count = 0;			//最早那次跑马灯移动位置
	unsigned short m_Max_Count_Loc = 0;		//最早那次跑马灯在FIFO位置
	//按键1
	if(1 == g_Push_Button_Value)
	{
		//找到当前通道最早那次跑马灯
		for(i = 0; i < MAX_LED_FIFO_DEP; i++)
		{
			if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 1) )
			{
				if(g_LED_FIFO[i].Now_Count > m_Max_Count)
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		//当前通道没有跑马灯
		if(m_Max_Count == 0)
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}
		//根据移动位置点环形灯
		//good
		if(g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good)
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED1_Array[j] = 1;
			}
			Led1_Set_Cycle(g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B);
			//点环形灯
			Led1_On();
			//记录数据
			g_Data_Good[0]++;	
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;			
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//perfect
		else
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED1_Array[j] = 1;
			}
			Led1_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
			//点环形灯
			Led1_On();
			//记录数据
			g_Data_Perfect[0]++;
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;		
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//开始灭灯倒计时
		g_Cycle_Light_Flag[0] = 1;
	}
	//按键2
	else if(2 == g_Push_Button_Value)
	{
		//找到当前通道最早那次跑马灯
		for(i = 0; i < MAX_LED_FIFO_DEP; i++)
		{
			if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 2) )
			{
				if(g_LED_FIFO[i].Now_Count > m_Max_Count)
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		//当前通道没有跑马灯
		if(m_Max_Count == 0)
		{
			g_Data_lj[0]=0;
			Send_Point_Data_BDP();
			return;
		}
		//根据移动位置点环形灯
		//good
		if(g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good)
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED2_Array[j] = 1;
			}
			Led2_Set_Cycle(g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B);
			//点环形灯
			Led2_On();
			//记录数据
			g_Data_Good[1]++;	
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;			
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//perfect
		else
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED2_Array[j] = 1;
			}
			Led2_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
			//点环形灯
			Led2_On();
			//记录数据
			g_Data_Perfect[1]++;
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;		
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//开始灭灯倒计时
		g_Cycle_Light_Flag[1] = 1;
	}
	//按键3
	else if(3 == g_Push_Button_Value)
	{
		//找到当前通道最早那次跑马灯
		for(i = 0; i < MAX_LED_FIFO_DEP; i++)
		{
			if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 3) )
			{
				if(g_LED_FIFO[i].Now_Count > m_Max_Count)
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		//当前通道没有跑马灯
		if(m_Max_Count == 0)
		{
			g_Data_lj[0]=0;
			Send_Point_Data_BDP();
			return;
		}
		//根据移动位置点环形灯
		//good
		if(g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good)
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED3_Array[j] = 1;
			}
			Led3_Set_Cycle(g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B);
			//点环形灯
			Led3_On();
			//记录数据
			g_Data_Good[2]++;	
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;			
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//perfect
		else
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED3_Array[j] = 1;
			}
			Led3_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
			//点环形灯
			Led3_On();
			//记录数据
			g_Data_Perfect[2]++;
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;		
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//开始灭灯倒计时
		g_Cycle_Light_Flag[2] = 1;
	}
	//按键4
	else if(4 == g_Push_Button_Value)
	{
		//找到当前通道最早那次跑马灯
		for(i = 0; i < MAX_LED_FIFO_DEP; i++)
		{
			if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 4) )
			{
				if(g_LED_FIFO[i].Now_Count > m_Max_Count)
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		//当前通道没有跑马灯
		if(m_Max_Count == 0)
		{
			g_Data_lj[0]=0;
			Send_Point_Data_BDP();
			return;
		}
		//根据移动位置点环形灯
		//good
		if(g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good)
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED4_Array[j] = 1;
			}
			Led4_Set_Cycle(g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B);
			//点环形灯
			Led4_On();
			//记录数据
			g_Data_Good[3]++;	
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;			
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//perfect
		else
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED4_Array[j] = 1;
			}
			Led4_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
			//点环形灯
			Led4_On();
			//记录数据
			g_Data_Perfect[3]++;
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;		
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//开始灭灯倒计时
		g_Cycle_Light_Flag[3] = 1;
	}
	//按键5
	else if(5 == g_Push_Button_Value)
	{
		//找到当前通道最早那次跑马灯
		for(i = 0; i < MAX_LED_FIFO_DEP; i++)
		{
			if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 5) )
			{
				if(g_LED_FIFO[i].Now_Count > m_Max_Count)
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		//当前通道没有跑马灯
		if(m_Max_Count == 0)
		{
			g_Data_lj[0]=0;
			Send_Point_Data_BDP();
			return;
		}
		//根据移动位置点环形灯
		//good
		if(g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good)
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED5_Array[j] = 1;
			}
			Led5_Set_Cycle(g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B);
			//点环形灯
			Led5_On();
			//记录数据
			g_Data_Good[4]++;	
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;			
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//perfect
		else
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED5_Array[j] = 1;
			}
			Led5_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
			//点环形灯
			Led5_On();
			//记录数据
			g_Data_Perfect[4]++;
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;		
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//开始灭灯倒计时
		g_Cycle_Light_Flag[4] = 1;
	}
	//按键6
	else if(6 == g_Push_Button_Value)
	{
		//找到当前通道最早那次跑马灯
		for(i = 0; i < MAX_LED_FIFO_DEP; i++)
		{
			if( (g_LED_FIFO[i].Valid_Flag == 1) && (g_LED_FIFO[i].LED_Channel == 6) )
			{
				if(g_LED_FIFO[i].Now_Count > m_Max_Count)
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		//当前通道没有跑马灯
		if(m_Max_Count == 0)
		{
			g_Data_lj[0]=0;
			Send_Point_Data_BDP();
			return;
		}
		//根据移动位置点环形灯
		//good
		if(g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good)
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED6_Array[j] = 1;
			}
			Led6_Set_Cycle(g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B);
			//点环形灯
			Led6_On();
			//记录数据
			g_Data_Good[5]++;	
				g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;			
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//perfect
		else
		{
			//设置灯颜色
			for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
			{
				g_LED6_Array[j] = 1;
			}
			Led6_Set_Cycle(g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B);
			//点环形灯
			Led6_On();
			//记录数据
			g_Data_Perfect[5]++;
			g_Data_lj[0]++;
			//清除数据
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;		
			//FIFO总数减1
			g_LED_RingBuf_Num--;
		}
		//开始灭灯倒计时
		g_Cycle_Light_Flag[5] = 1;
	}
	if(g_Data_lj[0]>g_Data_Max_lj[0])
		g_Data_Max_lj[0]=g_Data_lj[0];
	
		Send_Point_Data_BDP();

}

//按键检测
unsigned char Scan_Push_Button(unsigned char mode)
{
	static unsigned char key_up = 1;	//按键按松开标志
	if(mode) key_up = 1;  				//支持连按
	if( key_up && ( (Press_AD1 == 0) || (Press_AD2 == 0) || (Press_AD3 == 0) || (Press_AD4 == 0) || (Press_AD5 == 0) || (Press_AD6 == 0) ) )
	{
		HAL_Delay(10);	//去抖动 
		key_up = 0;
		if(Press_AD1 == 0) return 1;
		else if(Press_AD2 == 0) return 2;
		else if(Press_AD3 == 0) return 3;
		else if(Press_AD4 == 0) return 4;
		else if(Press_AD5 == 0) return 5;
		else if(Press_AD6 == 0) return 6;
	}
	else if( (Press_AD1 == 1) && (Press_AD2 == 1) && (Press_AD3 == 1) && (Press_AD4 == 1) && (Press_AD5 == 1) && (Press_AD6 == 1) )
	{
		key_up = 1;
	}
 	return 0;	// 无按键按下
}

