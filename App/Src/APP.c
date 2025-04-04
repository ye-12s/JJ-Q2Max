#include "APP.h"
#include <stdbool.h>
#include "globaldata.h"
#include "globalfunc.h"
#include "WS2812.h"
#include "Bluetooth.h"
#include <string.h>
/*heartbeat*/
#include "job1.h"
//bool  Send_Point_Flag = false;
unsigned char                       PEILIAN_Flag;
unsigned char                       KONGJI_Flag = 0;

extern  bool                        mak_fft_start;
extern  bool                        flag_fft_first;
extern unsigned char                g_fft_frame_flag;
extern  uint8_t                     fft_buf[9];
extern  unsigned char               SPP_Connect_Flag;
extern  volatile uint8_t            m_combo_mode;
extern  volatile uint8_t            m_combo_buf[2];
extern   bool                       g_Combo_flag;

extern   volatile uint32_t          fft_start_count;
extern   bool                       First_FFT_flg;
extern   bool                       g_PAUSE_Trill_flg;
void trill_display( void );
static inline void uart_process_task( void );

void TaskStart( void )
{
	// if( !HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_12 ) )
	if( g_ble_info.config.strVal.connect_state == 0
	        && g_ble_info.connectState != 2 )
	{
		g_BT_Connect_Flag = 0;
		SPP_Connect_Flag = 0;
		fft_start_count = 0;
		g_App_Mode_flag = 0;
		if( g_BT_Connect_Flag == 0 )
		{
			if( g_App_Mode != 0 )
			{
				g_App_Mode = 1;
			}
		}
	}
	else
	{
		if( fft_start_count > 5 )
		{
			SPP_Connect_Flag = 1;
			if( ( g_App_Mode_flag == 0 ) && ( g_BT_Connect_Flag == 0 ) )
			{

				Led_All_Off();
				g_App_Mode_flag = 1;
				g_App_Mode = 6;
			}
			fft_start_count = 5;
		}
	}
	Task_USART1_Recv();

	if( ( 2 == g_App_Mode )    || ( 3 == g_App_Mode ) || ( 7 == g_App_Mode ) )
	{
		g_Push_Button_Value = Scan_Push_Button( 0 );
		if( 2 == g_Cycle_Light_Flag[0] )
		{
			g_Cycle_Light_Flag[0] = 0;
			Set_Led_Cycle_Array( 1, LED_ARRAY_OFF );
			Led1_Set_Cycle( COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B );
			Led1_On();
			flag_line = 1;
		}
		else if( 2 == g_Cycle_Light_Flag[1] )
		{
			g_Cycle_Light_Flag[1] = 0;
			Set_Led_Cycle_Array( 2, LED_ARRAY_OFF );
			Led2_Set_Cycle( COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B );
			Led2_On();
			flag_line = 1;
		}
		else if( 2 == g_Cycle_Light_Flag[2] )
		{
			g_Cycle_Light_Flag[2] = 0;
			Set_Led_Cycle_Array( 3, LED_ARRAY_OFF );
			Led3_Set_Cycle( COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B );
			Led3_On();
			flag_line = 1;
		}
		else if( 2 == g_Cycle_Light_Flag[3] )
		{
			g_Cycle_Light_Flag[3] = 0;
			Set_Led_Cycle_Array( 4, LED_ARRAY_OFF );
			Led4_Set_Cycle( COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B );
			Led4_On();
			flag_line = 1;
		}
		else if( 2 == g_Cycle_Light_Flag[4] )
		{
			g_Cycle_Light_Flag[4] = 0;
			Set_Led_Cycle_Array( 5, LED_ARRAY_OFF );
			Led5_Set_Cycle( COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B );
			Led5_On();
			flag_line = 1;
		}
		else if( 2 == g_Cycle_Light_Flag[5] )
		{
			g_Cycle_Light_Flag[5] = 0;
			Set_Led_Cycle_Array( 6, LED_ARRAY_OFF );
			Led6_Set_Cycle( COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B );
			Led6_On();
			flag_line = 1;
		}


		if( 3 == g_App_Mode )
		{
			if( g_Push_Button_Value )
			{
				if( 1 == g_Push_Button_Value )
				{
					Set_Led_Cycle_Array( 1, LED_ARRAY_ON );
					Led1_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
					Led1_On();
					g_Cycle_Light_Flag[0] = 1;
				}
				else if( 2 == g_Push_Button_Value )
				{
					Set_Led_Cycle_Array( 2, LED_ARRAY_ON );
					Led2_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
					Led2_On();
					g_Cycle_Light_Flag[1] = 1;
				}
				else if( 3 == g_Push_Button_Value )
				{
					Set_Led_Cycle_Array( 3, LED_ARRAY_ON );
					Led3_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
					Led3_On();
					g_Cycle_Light_Flag[2] = 1;
				}
				else if( 4 == g_Push_Button_Value )
				{
					Set_Led_Cycle_Array( 4, LED_ARRAY_ON );
					Led4_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
					Led4_On();
					g_Cycle_Light_Flag[3] = 1;
				}
				else if( 5 == g_Push_Button_Value )
				{
					Set_Led_Cycle_Array( 5, LED_ARRAY_ON );
					Led5_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
					Led5_On();
					g_Cycle_Light_Flag[4] = 1;
				}
				else if( 6 == g_Push_Button_Value )
				{
					Set_Led_Cycle_Array( 6, LED_ARRAY_ON );
					Led6_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
					Led6_On();
					g_Cycle_Light_Flag[5] = 1;
				}
				Send_Boxing_Loc_BDP( g_Push_Button_Value );
				g_Push_Button_Value = 0;
			}
		}
		else if( ( 2 == g_App_Mode ) || ( 7 == g_App_Mode ) )
		{
			if( g_Push_Button_Value )
			{
				Proc_Push_Button();
				g_Push_Button_Value = 0;
			}
		}
	}

	if( g_Line_Flag == 1 )
	{
		g_Line_Flag = 0;

		if( 0 == g_App_Mode )
		{
			if( 0 == g_Mode0_Step_Flag )
			{
				Led_All_Off();
				g_Mode0_Step_Flag = 1;
			}
			else if( 1 == g_Mode0_Step_Flag )
			{
				Led_On_Mode0_Step1();
			}
			else if( 2 == g_Mode0_Step_Flag )
			{
				Led_On_Mode0_Step2();
			}
			else if( 3 == g_Mode0_Step_Flag )
			{
				Led_On_Mode0_Step3();
				g_App_Mode_flag = 1;
			}
		}
		else if( 2 == g_App_Mode )
		{
			Proc_LED_FIFO();
			Led1_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
			Led2_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
			Led3_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
			Led4_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
			Led5_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
			Led6_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
			Led_On();
		}
		else if( 7 == g_App_Mode )
		{
			trill_display();
		}

		else if( 4 == g_App_Mode )
		{
			if( 4 == g_App_Mode4_Running )
			{
				Set_LED_Mode4_Running( g_App_Mode4_Running_Channel, 0, LED_NUM );
			}
			else if( 5 == g_App_Mode4_Running )
			{
				Set_LED_Mode4_Running( g_App_Mode4_Running_Channel, 0, LED_RUNNING_NUM );
			}
		}

		else if( 5 == g_App_Mode )
		{
			g_Cycle_Period = 50;
			g_Line_Period = 50;
			flag_fft_first = false;
			if( 0 == g_BT_Connect_Flag )
			{
				Led_On_Mode1( g_BT_Connect_Flag );
			}
			else if( ( 5 == g_App_Mode ) && ( PEILIAN_Flag == 0 ) )
			{
				if( 0 == Stanley_Mode5_Light1_Flag )
				{
					Led_All_Off();
				}
				else if( 1 == Stanley_Mode5_Light1_Flag )
				{
					Stanley_Mode5_Light1();
					HAL_Delay( 10 );
				}
				else if( 2 == Stanley_Mode5_Light1_Flag )
				{
					Stanley_Mode5_Light2();
					HAL_Delay( 10 );
				}
				else if( 3 == Stanley_Mode5_Light1_Flag )
				{
					Stanley_Mode5_Light3();
					HAL_Delay( 10 );
				}
				else if( 4 == Stanley_Mode5_Light1_Flag )
				{
					Stanley_Mode5_Light4();
				}
				else if( 5 == Stanley_Mode5_Light1_Flag )
				{
					Stanley_Mode5_Light5();
					HAL_Delay( 10 );
				}
			}
		}
	}

	if( g_Cycle_Flag == 1 )
	{
		g_Cycle_Flag = 0;

		if( 4 == g_App_Mode )
		{
			if( 6 == g_App_Mode4_Running )
			{
				Set_LED_Mode4_Running( g_App_Mode4_Running_Channel, LED_RUNNING_NUM, LED_NUM );
			}
		}
	}

	if( g_2000ms_flag == 1 )
	{
		g_2000ms_flag = 0;

		if( 2 == g_App_Mode )
		{
			g_Song_End_Count++;

			if( g_Song_End_Count >= 10 )
			{
				g_Song_End_Count = 0;

				if( g_BT_Connect_Flag == 1 )
				{
					g_App_Mode = 5;
				}
			}
		}
		if( 7 == g_App_Mode )
		{
			g_Song_End_Count++;

			if( g_Song_End_Count >= 10 )
			{
				g_Song_End_Count = 0;
				if( 0 == PEILIAN_Flag )
				{
					g_App_Mode = 5;
				}
			}
		}

		if( 5 == g_App_Mode )
		{
			if( g_BT_Connect_Flag == 1 )
			{
				g_Song_End_Count++;
				if( g_Song_End_Count >= 10 )
				{
					g_Song_End_Count = 0;
					Stanley_Mode5_Light1_Flag = 1;
				}
			}
		}

		if( 1 == g_App_Mode )
		{
			if( 0 == g_BT_Connect_Flag )
			{
				Led_On_Mode1( g_BT_Connect_Flag );
			}
		}
	}

	if( g_500ms_flag == 1 )
	{
		g_500ms_flag = 0;
		IWDG_Feed();
	}
}

char *get_cmd_strstr( char *cmd, const char *str, int len )
{
	char *p = strstr( cmd, str );
	if( p != NULL )
	{
		return p + len + 1; // +1 for '+'
	}
	return NULL;
}

static void process_command( char *cmd, uint32_t len )
{
	char *p = 0;
	if( ( p = get_cmd_strstr( cmd, "AT", 2 ) ) )
	{
		strncpy( g_ble_info.version, p, sizeof( g_ble_info.version ) );
	}
	else if( ( p = get_cmd_strstr( cmd, "QA", 2 ) ) )
	{
		int value = atoi( p );
		g_ble_info.volume = value;
	}
	else if( ( p = get_cmd_strstr( cmd, "TD", 2 ) ) )
	{
		strncpy( g_ble_info.AudioName, p, sizeof( g_ble_info.AudioName ) );
	}
	else if( ( p = get_cmd_strstr( cmd, "TM", 2 ) ) )
	{
		strncpy( g_ble_info.bleName, p, sizeof( g_ble_info.bleName ) );
	}
	else if( ( p = get_cmd_strstr( cmd, "T6", 2 ) ) )
	{
		g_ble_info.serverUUID = strtol( p, NULL, 16 );
	}
	else if( ( p = get_cmd_strstr( cmd, "T7", 2 ) ) )
	{
		g_ble_info.charUUID = strtol( p, NULL, 16 );
	}
	else if( ( p = get_cmd_strstr( cmd, "T8", 2 ) ) )
	{
		g_ble_info.charUUID2 = strtol( p, NULL, 16 );
	}
	else if( ( p = get_cmd_strstr( cmd, "T9", 2 ) ) )
	{
		g_ble_info.charUUID3 = strtol( p, NULL, 16 );
	}
	else if( ( p = get_cmd_strstr( cmd, "TL", 2 ) ) )
	{
		int value = atoi( p );
		g_ble_info.bleState = value;
		if( value == 3 )
		{
			g_ble_info.config.strVal.connect_state = 1;
		}
		else
		{
			g_ble_info.config.strVal.connect_state = 0;
		}
	}
	else if( ( p = get_cmd_strstr( cmd, "TS", 2 ) ) )
	{
		int value = atoi( p );
		g_ble_info.connectState = value;
	}
}

void Task_USART1_Recv( void )
{
#if 0
	if( g_com1_frame_flag == 1 )
	{
		g_com1_frame_flag = 0;
		Proc_USART1_BDP( com1_buf, com1_recvbyte_count_1 );
	}
	else   if( g_fft_frame_flag == 1 )
	{
		if( g_Combo_flag == true )
		{
			if( m_combo_mode == 0 )
			{
				fft_buf[7]  = m_combo_buf[0];
			}
			else
			{
				fft_buf[7]  = m_combo_buf[1];
			}
			g_Combo_flag = false;
		}
		else
		{
			g_fft_frame_flag = 0;
		}
		Proc_USART1_BDP( fft_buf, 9 );
	}
#endif

	uart_process_task();

	if( g_fft_frame_flag == 1 )
	{
		if( g_Combo_flag == true )
		{
			if( m_combo_mode == 0 )
			{
				fft_buf[7]  = m_combo_buf[0];
			}
			else
			{
				fft_buf[7]  = m_combo_buf[1];
			}
			g_Combo_flag = false;
		}
		else
		{
			g_fft_frame_flag = 0;
		}
		Proc_USART1_BDP( fft_buf, 9 );
	}
}
uint32_t packet_count = 0;
static inline void uart_process_task( void )
{
#define PACKET_FLAG_TRANSMIT 0x01   //透传数据
#define PACKET_FLAG_COMMAND  0x02   //命令数据
	const char DCP_HEAD = 0xfc;
	const uint32_t BDP_LEN = 9;
	uint8_t cache_char = 0;
	static uint32_t packet_flag = 0;
	static uint8_t cmd_buff[128];
	static uint32_t cmd_len = 0;
	if( rb_is_empty( &g_uart_rb ) )
	{
		return;
	}

	if( rb_read( &g_uart_rb, &cache_char, 1 ) == 1 )
	{
		static uint8_t packet_len = 0;
		if ( cache_char == DCP_HEAD )
		{
			cmd_len = 0; // 检测到包头，清空缓冲区，前面可能有垃圾数据，或丢失数据
			cmd_buff[cmd_len++] = cache_char;
			packet_len = 1;
			packet_flag = PACKET_FLAG_TRANSMIT;
		}
		//TODO此处后续需要加入新的缓冲区，做指令数据的存储
		else if ( ( packet_flag == PACKET_FLAG_TRANSMIT ) && cmd_len > 0 && cmd_len < BDP_LEN )
		{
			cmd_buff[cmd_len++] = cache_char;
			packet_len++;
		}

		if ( packet_flag == PACKET_FLAG_TRANSMIT && packet_len == BDP_LEN )
		{
			// 处理透传数据包
			Proc_USART1_BDP( cmd_buff, cmd_len );
			cmd_len = 0;
			packet_len = 0;
			packet_flag = 0;
		}

		// 检测命令数据
		if ( packet_flag != PACKET_FLAG_TRANSMIT )
		{
			cmd_buff[cmd_len++] = cache_char;

			if ( cache_char == '\n' ) // 命令以换行符结尾
			{
				cmd_buff[cmd_len] = '\0'; // 确保字符串以NULL结尾
				// 处理命令数据
				process_command( ( char * )cmd_buff, cmd_len );
				cmd_len = 0;
			}
			else if ( cmd_len >= sizeof( cmd_buff ) ) // 防止缓冲区溢出
			{
				cmd_len = 0;
			}
		}

		// if ( packet_len == 9 )
		// {
		//  // Process the 9-byte packet stored in cmd_buff
		//  cmd_len = 0;
		//  packet_len = 0;
		//  //              static char str_buf[256] = {0};
		//  //
		//  //              packet_count++;
		//  //              snprintf( str_buf, sizeof( str_buf ), "Received count(%d) packet\r\n", packet_count );
		//  //              static char hex_buf[48] = {0};
		//  //              for( int i = 0; i < 9; i++ )
		//  //              {
		//  //                  snprintf( hex_buf + 3 * i, sizeof( hex_buf ), "%02X ", cmd_buff[i] );
		//  //              }
		//  //              strcat( str_buf, hex_buf );
		//  //              strcat( str_buf, "\r\n" );
		//  //              int len = strlen( str_buf );
		//  //              extern UART_HandleTypeDef huart1;
		//  //              HAL_UART_Transmit( &huart1, str_buf, len, 0xff );
		//  //              memset( str_buf, 0, sizeof( str_buf ) );
		//  Proc_USART1_BDP( cmd_buff, cmd_len );
		// }
	}
}
void Proc_USART1_BDP( unsigned char *pbuf, unsigned short len )
{
	unsigned char m_Head, m_Cmd;
	unsigned short m_Addr;
	unsigned char i;
	m_Head = pbuf[0];
	m_Cmd = pbuf[1];
	m_Addr = pbuf[2] * 256 + pbuf[3];

	if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_11 ) )
	{
		if( 0x01 == pbuf[7] )
		{
			g_BT_Connect_Flag = 1;
			g_BT_Connect_Flag = 2;
			g_BT_Connect_Flag = 1;
			g_Song_End_Count = 0;
			g_App_Mode = 2;

		}
		else
		{
			g_BT_Connect_Flag = 0;
			if( 0 == g_BT_Connect_Flag )
			{
				g_App_Mode = 1;
				Led_All_Off();
				Led_On_Mode1( g_BT_Connect_Flag );
			}
		}
	}

	if( HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_12 ) )
	{
		if( fft_start_count > 5 )
		{
			SPP_Connect_Flag = 1;
			SPP_Connect_Flag = 2;
			SPP_Connect_Flag = 1;
			if( ( g_App_Mode_flag == 0 ) && ( g_BT_Connect_Flag == 0 )    )
			{
				Led_All_Off();
				g_App_Mode_flag = 1;
				g_App_Mode = 6;
			}
			fft_start_count = 5;
		}
	}
	else
	{
		SPP_Connect_Flag = 0;
		fft_start_count = 0;
		g_App_Mode_flag = 0;
		if( g_BT_Connect_Flag == 0 )
		{
			if( g_App_Mode != 0 )
			{
				g_App_Mode = 1;
			}
		}
	}

	if( m_Head == BDP_HEAD )
	{
		COM1_Send_BDP( com1_buf, com1_recvbyte_count_1 );
	}

	if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_1 ) )
	{
		if( 0x01 == pbuf[7] )
		{
			if( g_BT_Connect_Flag == 0 )
			{
				g_App_Mode = 0;
			}
			else
			{
				g_App_Mode = 1;
			}

			for( i = 0; i < 6; i++ )
			{
				g_Data_Perfect[i] = 0;
				g_Data_Good[i] = 0;
				g_Data_lj[0] = 0;
				g_Data_Max_lj[0] = 0;
			}
			Stanley_Mode5_Light1_Flag = 0;
		}

		else if( 0x00 == pbuf[7] )
		{
			if( g_BT_Connect_Flag == 1 )
			{
				g_App_Mode = 5;
				Stanley_Mode5_Light1_Flag = 0;
			}
			else
			{
				g_App_Mode = 1;
			}
		}
		else if( 0x02 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 7;
			Led_All_Off();
			PEILIAN_Flag = 1;
		}
		else if( 0x03 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 7;
			Led_All_Off();

		}
		else if( 0x04 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 3;
			g_Line_Flag = 0;
			KONGJI_Flag = 1;
		}
		else if( 0x05 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 7;
		}
		else if( 0x06 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 7;
		}
		else if( 0x07 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 7;
		}
		else if( 0x08 == pbuf[7] )
		{
			g_light_Flag = 0;
			g_App_Mode = 7;
		}
		else if( 0x09 == pbuf[7] )
		{
			mak_fft_start  = false;
			HAL_NVIC_DisableIRQ( TIM3_IRQn );
		}
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_2 ) )
	{
		if( 7 != g_App_Mode )
		{
			g_App_Mode = 2;
		}
		if( ( 2 == g_App_Mode )    || ( 7 == g_App_Mode ) )
		{
			g_Song_End_Count = 0;
			g_light_Flag = 0;
			g_Line_Period = pbuf[6];
			Add_Info_To_LED_FIFO( pbuf[7] );
			if( 4 == num_lj_b )
			{
				num_lj_b = 1;
				num_lj_b_f = 0;
			}
		}
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_3 ) )
	{
		num_lj_b = 0;
		g_App_Mode = pbuf[7];
		Led_All_Off();
		g_Song_End_Count = 0;
		g_light_Flag = 0;
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_4 ) )
	{
		g_Line_Color_R = pbuf[4];
		g_Line_Color_G = pbuf[5];
		g_Line_Color_B = pbuf[6];
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_5 ) )
	{
		g_Cycle_Color_Perfect_R = pbuf[4];
		g_Cycle_Color_Perfect_G = pbuf[5];
		g_Cycle_Color_Perfect_B = pbuf[6];
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_6 ) )
	{
		g_Cycle_Color_Good_R = pbuf[4];
		g_Cycle_Color_Good_G = pbuf[5];
		g_Cycle_Color_Good_B = pbuf[6];
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_7 ) )
	{
		g_Line_Period = pbuf[7];
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_8 ) )
	{
		g_Cycle_Period = pbuf[7];
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_9 ) )
	{
		g_Cycle_Light_Time = pbuf[7] * 80;
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_10 ) )
	{
		g_Result_Good = pbuf[7];
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_READ )  && ( m_Addr == BDP_ADDR_1 ) )
	{
		HAL_Delay( 100 );
		Send_Point_Data_BDP();

	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == BDP_ADDR_12 ) )
	{
		Led_All_Off();
		if( 0x01 == pbuf[7] )
		{
			if( g_BT_Connect_Flag == 0 )
			{
				g_App_Mode = 1;
				g_Song_End_Count = 0;
			}
			else
			{
				g_App_Mode = 2;
				g_Song_End_Count = 0;
			}
			g_light_Flag = 0;
		}
		else if( 0x00 == pbuf[7] )
		{
			if( g_BT_Connect_Flag == 1 )
			{
				g_App_Mode = 5;
				g_Song_End_Count = 0;
			}
		}
		else if( 0x02 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
			PEILIAN_Flag = 0;                                       // 20240711  ADD
		}
		else if( 0x03 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
		}
		else if( 0x04 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
		}
		else if( 0x05 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
		}
		else if( 0x06 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
		}
		else if( 0x07 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
		}
		else if( 0x08 == pbuf[7] )
		{
			g_App_Mode = 2;
			g_Song_End_Count = 0;
		}

		else if( 0x0a == pbuf[7] )
		{
			mak_fft_start = true;
			HAL_NVIC_EnableIRQ( TIM3_IRQn );
			g_App_Mode = 2;
			g_Song_End_Count = 0;

		}
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == 0x0041 ) )
	{
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		if( 1 == pbuf[8] )
		{
			Set_Led_Line_Odd_Array( 1, LED_ARRAY_ON );
			Led1_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led1_On();
		}
		else if( 2 == pbuf[8] )
		{
			Set_Led_Line_Odd_Array( 2, LED_ARRAY_ON );
			Led2_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led2_On();
		}
		else if( 3 == pbuf[8] )
		{
			Set_Led_Line_Odd_Array( 3, LED_ARRAY_ON );
			Led3_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led3_On();
		}
		else if( 4 == pbuf[8] )
		{
			Set_Led_Line_Odd_Array( 4, LED_ARRAY_ON );
			Led4_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led4_On();
		}
		else if( 5 == pbuf[8] )
		{
			Set_Led_Line_Odd_Array( 5, LED_ARRAY_ON );
			Led5_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led5_On();
		}
		else if( 6 == pbuf[8] )
		{
			Set_Led_Line_Odd_Array( 6, LED_ARRAY_ON );
			Led6_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led6_On();
		}
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == 0x0042 ) )
	{
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		if( 1 == pbuf[8] )
		{
			Set_Led_Cycle_Odd_Array( 1, LED_ARRAY_ON );
			Led1_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led1_On();
		}
		else if( 2 == pbuf[8] )
		{
			Set_Led_Cycle_Odd_Array( 2, LED_ARRAY_ON );
			Led2_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led2_On();
		}
		else if( 3 == pbuf[8] )
		{
			Set_Led_Cycle_Odd_Array( 3, LED_ARRAY_ON );
			Led3_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led3_On();
		}
		else if( 4 == pbuf[8] )
		{
			Set_Led_Cycle_Odd_Array( 4, LED_ARRAY_ON );
			Led4_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led4_On();
		}
		else if( 5 == pbuf[8] )
		{
			Set_Led_Cycle_Odd_Array( 5, LED_ARRAY_ON );
			Led5_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led5_On();
		}
		else if( 6 == pbuf[8] )
		{
			Set_Led_Cycle_Odd_Array( 6, LED_ARRAY_ON );
			Led6_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led6_On();
		}
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == 0x0043 ) )
	{
		g_App_Mode = 4;
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		if( 1 == pbuf[8] )
		{
			Set_Led_Odd_Array( 1, LED_ARRAY_ON );
			Led1_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led1_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led1_On();
		}
		else if( 2 == pbuf[8] )
		{
			Set_Led_Odd_Array( 2, LED_ARRAY_ON );
			Led2_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led2_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led2_On();
		}
		else if( 3 == pbuf[8] )
		{
			Set_Led_Odd_Array( 3, LED_ARRAY_ON );
			Led3_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led3_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led3_On();
		}
		else if( 4 == pbuf[8] )
		{
			Set_Led_Odd_Array( 4, LED_ARRAY_ON );
			Led4_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led4_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led4_On();
		}
		else if( 5 == pbuf[8] )
		{
			Set_Led_Odd_Array( 5, LED_ARRAY_ON );
			Led5_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led5_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led5_On();
		}
		else if( 6 == pbuf[8] )
		{
			Set_Led_Odd_Array( 6, LED_ARRAY_ON );
			Led6_Set_Running( g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B );
			Led6_Set_Cycle( g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B );
			Led6_On();
		}
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == 0x0044 ) )
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
		Set_LED_Mode4_Running( g_App_Mode4_Running_Channel, 0, LED_NUM );
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == 0x0045 ) )
	{
		g_App_Mode = 4;
		g_App_Mode4_Running = 5;
		g_Mode4_Line_Color_R = pbuf[4];
		g_Mode4_Line_Color_G = pbuf[5];
		g_Mode4_Line_Color_B = pbuf[6];
		g_App_Mode4_Running_Channel = pbuf[8];
		g_App_Mode4_Running_Count = 0;
		Set_LED_Mode4_Running( g_App_Mode4_Running_Channel, 0, LED_RUNNING_NUM );
	}

	else if( ( m_Head == BDP_HEAD ) && ( m_Cmd == BDP_CMD_WRITE )  && ( m_Addr == 0x0046 ) )
	{
		g_App_Mode = 4;
		g_App_Mode4_Running = 6;
		g_Mode4_Cycle_Color_R = pbuf[4];
		g_Mode4_Cycle_Color_G = pbuf[5];
		g_Mode4_Cycle_Color_B = pbuf[6];
		g_App_Mode4_Running_Channel = pbuf[8];
		g_App_Mode4_Running_Count = LED_RUNNING_NUM;
		Set_LED_Mode4_Running( g_App_Mode4_Running_Channel, LED_RUNNING_NUM, LED_NUM );
	}
}

void Add_Info_To_LED_FIFO( unsigned short LED_Channel )
{
	if( g_LED_RingBuf_Num == MAX_LED_FIFO_DEP )
	{
	}
	else
	{
		g_LED_FIFO[g_Add_LED_Index].Valid_Flag = 1;
		g_LED_FIFO[g_Add_LED_Index].LED_Channel = LED_Channel;
		g_LED_FIFO[g_Add_LED_Index].Now_Count = 0;
		g_Add_LED_Index++;
		if( g_Add_LED_Index == MAX_LED_FIFO_DEP )
		{
			g_Add_LED_Index = 0;
		}
		g_LED_RingBuf_Num++;
	}
}

void Proc_LED_FIFO( void )
{
	unsigned char i = 0, j = 0;
	for( j = 0; j < LED_RUNNING_NUM; j++ )
	{
		g_LED1_Array[j] = 0;
		g_LED2_Array[j] = 0;
		g_LED3_Array[j] = 0;
		g_LED4_Array[j] = 0;
		g_LED5_Array[j] = 0;
		g_LED6_Array[j] = 0;
	}
	for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
	{
		if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 1 ) )
		{
			for( j = 0; j < LED_RUNNING_NUM; j++ )
			{
				g_LED1_Array[j] = ( g_LED1_Array[j] ) | ( g_LED_Array[g_LED_FIFO[i].Now_Count][j] );
			}
		}
		if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 2 ) )
		{
			for( j = 0; j < LED_RUNNING_NUM; j++ )
			{
				g_LED2_Array[j] = ( g_LED2_Array[j] ) | ( g_LED_Array[g_LED_FIFO[i].Now_Count][j] );
			}
		}
		if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 3 ) )
		{
			for( j = 0; j < LED_RUNNING_NUM; j++ )
			{
				g_LED3_Array[j] = ( g_LED3_Array[j] ) | ( g_LED_Array[g_LED_FIFO[i].Now_Count][j] );
			}
		}
		if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 4 ) )
		{
			for( j = 0; j < LED_RUNNING_NUM; j++ )
			{
				g_LED4_Array[j] = ( g_LED4_Array[j] ) | ( g_LED_Array[g_LED_FIFO[i].Now_Count][j] );
			}
		}
		if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 5 ) )
		{
			for( j = 0; j < LED_RUNNING_NUM; j++ )
			{
				g_LED5_Array[j] = ( g_LED5_Array[j] ) | ( g_LED_Array[g_LED_FIFO[i].Now_Count][j] );
			}
		}
		if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 6 ) )
		{
			for( j = 0; j < LED_RUNNING_NUM; j++ )
			{
				g_LED6_Array[j] = ( g_LED6_Array[j] ) | ( g_LED_Array[g_LED_FIFO[i].Now_Count][j] );
			}
		}
	}
	for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
	{
		if( g_LED_FIFO[i].Valid_Flag == 1 )
		{
			g_LED_FIFO[i].Now_Count++;
			if( g_LED_FIFO[i].Now_Count >= LED_CYCLE_COUNT )
			{
				g_LED_FIFO[i].Valid_Flag = 0;
				g_LED_FIFO[i].LED_Channel = 0;
				g_LED_FIFO[i].Now_Count = 0;
				g_LED_RingBuf_Num--;

				g_Data_lj[0] = 0;

				Send_Point_Data_BDP();

			}
		}
	}
}

void Proc_Push_Button( void )
{
	unsigned char i = 0, j = 0;
	unsigned short m_Max_Count = 0;
	unsigned short m_Max_Count_Loc = 0;

	if( 1 == g_Push_Button_Value )
	{

		for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
		{
			if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 1 ) )
			{
				if( g_LED_FIFO[i].Now_Count > m_Max_Count )
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}

		if( m_Max_Count == 0 )
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}

		if( g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good )
		{

			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED1_Array[j] = 1;
			}
			Led1_Set_Cycle( g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B );

			Led1_On();

			g_Data_Good[0]++;
			g_Data_lj[0]++;

			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}

		else
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED1_Array[j] = 1;
			}
			Led1_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );

			Led1_On();

			g_Data_Perfect[0]++;
			g_Data_lj[0]++;

			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}

		g_Cycle_Light_Flag[0] = 1;
	}

	else if( 2 == g_Push_Button_Value )
	{
		for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
		{
			if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 2 ) )
			{
				if( g_LED_FIFO[i].Now_Count > m_Max_Count )
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		if( m_Max_Count == 0 )
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}
		if( g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good )
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED2_Array[j] = 1;
			}
			Led2_Set_Cycle( g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B );
			Led2_On();
			g_Data_Good[1]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		else
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED2_Array[j] = 1;
			}
			Led2_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
			Led2_On();
			g_Data_Perfect[1]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		g_Cycle_Light_Flag[1] = 1;
	}
	else if( 3 == g_Push_Button_Value )
	{
		for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
		{
			if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 3 ) )
			{
				if( g_LED_FIFO[i].Now_Count > m_Max_Count )
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		if( m_Max_Count == 0 )
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}
		if( g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good )
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED3_Array[j] = 1;
			}
			Led3_Set_Cycle( g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B );
			Led3_On();
			g_Data_Good[2]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		else
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED3_Array[j] = 1;
			}
			Led3_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
			Led3_On();
			g_Data_Perfect[2]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		g_Cycle_Light_Flag[2] = 1;
	}
	else if( 4 == g_Push_Button_Value )
	{
		for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
		{
			if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 4 ) )
			{
				if( g_LED_FIFO[i].Now_Count > m_Max_Count )
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		if( m_Max_Count == 0 )
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}
		if( g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good )
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED4_Array[j] = 1;
			}
			Led4_Set_Cycle( g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B );
			Led4_On();
			g_Data_Good[3]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		else
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED4_Array[j] = 1;
			}
			Led4_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
			Led4_On();
			g_Data_Perfect[3]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		g_Cycle_Light_Flag[3] = 1;
	}
	else if( 5 == g_Push_Button_Value )
	{
		for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
		{
			if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 5 ) )
			{
				if( g_LED_FIFO[i].Now_Count > m_Max_Count )
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		if( m_Max_Count == 0 )
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}
		if( g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good )
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED5_Array[j] = 1;
			}
			Led5_Set_Cycle( g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B );
			Led5_On();
			g_Data_Good[4]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		else
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED5_Array[j] = 1;
			}
			Led5_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
			Led5_On();
			g_Data_Perfect[4]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
			flag_line_time[4] = 2;
		}
		g_Cycle_Light_Flag[4] = 1;
	}
	else if( 6 == g_Push_Button_Value )
	{
		for( i = 0; i < MAX_LED_FIFO_DEP; i++ )
		{
			if( ( g_LED_FIFO[i].Valid_Flag == 1 ) && ( g_LED_FIFO[i].LED_Channel == 6 ) )
			{
				if( g_LED_FIFO[i].Now_Count > m_Max_Count )
				{
					m_Max_Count = g_LED_FIFO[i].Now_Count;
					m_Max_Count_Loc = i;
				}
			}
		}
		if( m_Max_Count == 0 )
		{
			g_Data_lj[0] = 0;
			Send_Point_Data_BDP();
			return;
		}
		if( g_LED_FIFO[m_Max_Count_Loc].Now_Count <= g_Result_Good )
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED6_Array[j] = 1;
			}
			Led6_Set_Cycle( g_Cycle_Color_Good_R, g_Cycle_Color_Good_G, g_Cycle_Color_Good_B );
			Led6_On();
			g_Data_Good[5]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		else
		{
			for( j = LED_RUNNING_NUM; j < LED_NUM; j++ )
			{
				g_LED6_Array[j] = 1;
			}
			Led6_Set_Cycle( g_Cycle_Color_Perfect_R, g_Cycle_Color_Perfect_G, g_Cycle_Color_Perfect_B );
			Led6_On();
			g_Data_Perfect[5]++;
			g_Data_lj[0]++;
			g_LED_FIFO[m_Max_Count_Loc].Valid_Flag = 0;
			g_LED_FIFO[m_Max_Count_Loc].LED_Channel = 0;
			g_LED_FIFO[m_Max_Count_Loc].Now_Count = 0;
			g_LED_RingBuf_Num--;
		}
		g_Cycle_Light_Flag[5] = 1;
	}
	if( g_Data_lj[0] > g_Data_Max_lj[0] )
	{
		g_Data_Max_lj[0] = g_Data_lj[0];
	}

	Send_Point_Data_BDP();

}

unsigned char Scan_Push_Button( unsigned char mode )
{
	static unsigned char key_up = 1;

#if  PRESS_TIM_VAL_ENABLE

	if( key_up && ( ( Press_AD1 == 0 ) || ( Press_AD2 == 0 ) || ( Press_AD3 == 0 ) || ( Press_AD4 == 0 ) || ( Press_AD5 == 0 ) || ( Press_AD6 == 0 ) ) )
	{
		HAL_Delay( 1 );
		key_up = 0;
		if( Press_AD1 == 0 )
		{
			return 1;
		}
		else if( Press_AD2 == 0 )
		{
			return 2;
		}
		else if( Press_AD3 == 0 )
		{
			return 3;
		}
		else if( Press_AD4 == 0 )
		{
			return 4;
		}
		else if( Press_AD5 == 0 )
		{
			return 5;
		}
		else if( Press_AD6 == 0 )
		{
			return 6;
		}
	}
	else if( ( Press_AD1 == 1 ) && ( Press_AD2 == 1 ) && ( Press_AD3 == 1 ) && ( Press_AD4 == 1 ) && ( Press_AD5 == 1 ) && ( Press_AD6 == 1 ) )
	{
		key_up = 1;
	}
	return 0;
#else
	uint8_t  i = 0;
	if( heartbert_val || 1 )
	{
		if( key_up && ( ( prsss_sta[0] ) || ( prsss_sta[1] )  || ( prsss_sta[2] )  || ( prsss_sta[3] ) || ( prsss_sta[4] )  || ( prsss_sta[5] ) ) )
		{
			HAL_Delay( 10 );
			key_up = 0;
			if(  prsss_sta[0] )
			{
				i = 1;
			}
			else  if(  prsss_sta[1] )
			{
				i = 2;
			}
			else  if(  prsss_sta[2] )
			{
				i = 3;
			}
			else  if(  prsss_sta[3] )
			{
				i = 4;
			}
			else  if(  prsss_sta[4] )
			{
				i = 5;
			}
			else  if(  prsss_sta[5] )
			{
				i = 6;
			}
		}
		else if( !( prsss_sta[0] || prsss_sta[1] || prsss_sta[2] || prsss_sta[3] || prsss_sta[4] || prsss_sta[5] ) )
		{
			key_up = 1;
			i = 0;
		}
		job_press_rest( ) ;

		return   i   ;
	}
	else
	{
		return 0;
	}
#endif
}

void trill_display( void )
{
	Proc_LED_FIFO();
	Led1_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
	Led2_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
	Led3_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
	Led4_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
	Led5_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
	Led6_Set_Running( g_Line_Color_R, g_Line_Color_G, g_Line_Color_B );
	Led_On();
}
