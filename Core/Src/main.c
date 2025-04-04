/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "sys.h"

#include "globaldata.h"
#include "globalfunc.h"
#include "APP.h"
#include "Bluetooth.h"
#include "Initial.h"
#include <stdio.h>
#include "fft.h"
#include "WS2812.h"
#include "USE_JOB1.h"
#include "job1.h"

#define UART_RB_SIZE  1024

static uint8_t g_uart_rb_buf[UART_RB_SIZE];

volatile uint8_t   n_count;
volatile uint8_t   n_done;
volatile uint16_t  adc_value;
volatile uint16_t  adc_d;
volatile uint32_t  fft_start_count = 0;

volatile unsigned short   g_Combo_Max_value;
volatile unsigned short   g_Combo_count;
volatile uint32_t         g_Combo_num;
volatile uint8_t          prew_ch;
volatile uint8_t          m_combo_mode;
volatile uint8_t          m_combo_buf[2];
bool                      g_Combo_flag;
extern  bool                        g_fft_frame_flag;
volatile uint32_t         spp_count;
extern  unsigned char       KONGJI_Flag;
bool  g_PAUSE_Trill_flg;
uint8_t   send_d[3];
extern  bool                            mak_fft_start;

extern  uint8_t                     led_buf[];
extern  uint16_t                    MAG[];
extern  bool                            flag_fft_first;
extern  double                      m_rand;
extern  unsigned short      g_Data_Max_value;
extern  unsigned char       SPP_Connect_Flag;

/* Private function prototypes -----------------------------------------------*/
extern  void    Set_LED_Mode_pwm( uint8_t  pwm );
extern  void    Set_LED_Mode0( void );
void SystemClock_Config( void );

int main( void )
{
	/* USER CODE BEGIN 1 */
	//  Flash_EnableReadProtection();   //insert
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_TIM5_Init();
	MX_TIM4_Init();
	Led_All_Off();
	MX_USART1_UART_Init();
	//  MX_IWDG_Init();

	rb_init( &g_uart_rb, g_uart_rb_buf, UART_RB_SIZE );
	//等待下一次接收中断
	HAL_UART_Receive_IT( &huart1, &com1_recv_one_byte, 1 );

	System_App_Init();

	MY_ADC_Init();
	TIM3_Init();


	mak_fft_start = true;
	m_combo_mode =  0;
	g_Combo_num = 0;
	g_Combo_count = 0;
	fft_start_count = 0;
	g_Combo_Max_value = 0;
	g_Combo_flag = false;
	spp_count = 0;
	g_PAUSE_Trill_flg = false;
	if( 0 == g_App_Mode_flag )
	{
		Led_All_Off();
		Led_On();
	}
	if( !HAL_GPIO_ReadPin( GPIOC, GPIO_PIN_12 ) )
	{
		g_BT_Connect_Flag = 0;
		SPP_Connect_Flag = 0;
		g_App_Mode_flag = 0;
		if( g_BT_Connect_Flag == 0 )
		{
			Led_On_Mode1( g_BT_Connect_Flag );
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
			if( ( g_App_Mode_flag == 0 ) && ( g_BT_Connect_Flag == 0 )    )
			{
				Led_All_Off();
				g_App_Mode_flag = 1;
				g_App_Mode = 6;
			}
			fft_start_count = 5;
		}
	}
	start_job();

	/* Infinite loop */
	while ( 1 )
	{
		// if( ( SPP_Connect_Flag == 1 ) && ( mak_fft_start == true ) )
		//此处表示蓝牙开始播放音乐
		if( ( g_ble_info.connectState == 0x02 ) && ( mak_fft_start == true ) )
		{
			if( 1 == KONGJI_Flag )
			{
				g_App_Mode = 3;
				KONGJI_Flag = 0;
			}
			while ( !n_done );
			fft();
			mag_to_buf();
			n_done = 0;

			adc_d = MAG[1];
			if( adc_d  > 5 )
			{
				adc_d -= 5;
			}
			else
			{
				adc_d = 0;
			}
			adc_d = adc_d << 1;

			if( ( adc_d > 5 ) && ( mak_fft_start == true ) )
			{
				adc_d = 5;
				if( !flag_fft_first )
				{
					Led_All_Off();
					g_App_Mode  = 7;
					flag_fft_first = true;
					g_2000ms_counter = 200;
					g_Data_Max_value = 0;

					FFT_Handle();

				}
				else if( g_2000ms_counter > 600 )
				{
					g_2000ms_counter = 200;
					g_Data_Max_value ++;

					FFT_Handle();

					g_Combo_Max_value = 0;
					g_Song_End_Count = 0;
				}
				else
				{
					g_Combo_Max_value++;
					g_Combo_count++;
				}
			}
		}
		TaskStart();

		if( data_rx_sta )
		{
			data_rx_sta = 0;
			data_rx_job( );
		}
	}
}

void Flash_EnableReadProtection( void )
{

	FLASH_OBProgramInitTypeDef OBInit;

	__HAL_FLASH_PREFETCH_BUFFER_DISABLE();

	HAL_FLASHEx_OBGetConfig( &OBInit );
	if( OBInit.RDPLevel == OB_RDP_LEVEL_0 )
	{
		OBInit.OptionType = OPTIONBYTE_RDP;
		OBInit.RDPLevel = OB_RDP_LEVEL_1;
		HAL_FLASH_Unlock();
		HAL_FLASH_OB_Unlock();
		HAL_FLASHEx_OBProgram( &OBInit );
		HAL_FLASH_OB_Lock();
		HAL_FLASH_Lock();
	}
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config( void )
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if ( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
	                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if ( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_2 ) != HAL_OK )
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler( void )
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while ( 1 )
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed( uint8_t *file, uint32_t line )
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

