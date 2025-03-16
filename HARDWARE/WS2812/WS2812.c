#include "WS2812.h"
#include "globaldata.h"
#include "timer.h"

void led_set(uint8_t led_id, uint8_t value_r, uint8_t value_g, uint8_t value_b)
{
	uint16_t i;
	
	uint16_t* p = (g_LED1_Buffer + RESET_PULSE_LEN) + (LED_DATA_LEN * led_id);
	for (i = 0; i < 8; i++)
	{
		p[i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		p[i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		p[i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
	}
}

//绿色移动模式
void Set_LED_Mode0(void)
{
	uint8_t i = 0;
	
	if(g_LED_Count >= 16)
	{
		g_LED_Count = 0;
		//灭灯
		Set_Led_All_Array(1, LED_ARRAY_OFF);
		Led1_Set_Running(g_Mode0_Color_R, g_Mode0_Color_G, g_Mode0_Color_B);
		Led1_Set_Cycle(g_Mode0_Color_R, g_Mode0_Color_G, g_Mode0_Color_B);
		Led_On_Same();
		//变化颜色
		g_LED_Cycle_Count++;
		if(g_LED_Cycle_Count >= 3)
		{
			g_LED_Cycle_Count = 0;
		}
		if(0 == g_LED_Cycle_Count)
		{
			g_Mode0_Color_R = COLOR_RED_R;
			g_Mode0_Color_G = COLOR_RED_G;
			g_Mode0_Color_B = COLOR_RED_B;
		}
		else if(1 == g_LED_Cycle_Count)
		{
			g_Mode0_Color_R = COLOR_GREEN_R;
			g_Mode0_Color_G = COLOR_GREEN_G;
			g_Mode0_Color_B = COLOR_GREEN_B;
		}
		else if(2 == g_LED_Cycle_Count)
		{
			g_Mode0_Color_R = COLOR_BLUE_R;
			g_Mode0_Color_G = COLOR_BLUE_G;
			g_Mode0_Color_B = COLOR_BLUE_B;
		}
		else if(3 == g_LED_Cycle_Count)
		{
			g_Mode0_Color_R = COLOR_ORANGE_R;
			g_Mode0_Color_G = COLOR_ORANGE_G;
			g_Mode0_Color_B = COLOR_ORANGE_B;
		}
		else if(4 == g_LED_Cycle_Count)
		{
			g_Mode0_Color_R = COLOR_YELLOW_R;
			g_Mode0_Color_G = COLOR_YELLOW_G;
			g_Mode0_Color_B = COLOR_YELLOW_B;
		}
	}
	
	for(i = 0; i < LED_NUM; i++)
	{
		g_LED1_Array[i] = (g_LED_Array_Mode1[g_LED_Count][i]);
	}
	Led1_Set_Running(g_Mode0_Color_R, g_Mode0_Color_G, g_Mode0_Color_B);
	Led1_Set_Cycle(g_Mode0_Color_R, g_Mode0_Color_G, g_Mode0_Color_B);
	Led_On_Same();
	g_LED_Count++;
}

void Led1_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{
	uint16_t* p = g_LED1_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		//设置颜色
		if(g_LED1_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led1_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{

	uint16_t* p = g_LED1_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED1_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led2_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{
	uint16_t* p = g_LED2_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		//设置颜色
		if(g_LED2_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led2_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{

	uint16_t* p = g_LED2_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED2_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led3_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{
	uint16_t* p = g_LED3_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		//设置颜色
		if(g_LED3_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led3_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{

	uint16_t* p = g_LED3_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED3_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led4_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{
	uint16_t* p = g_LED4_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		//设置颜色
		if(g_LED4_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led4_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{

	uint16_t* p = g_LED4_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED4_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led5_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{
	uint16_t* p = g_LED5_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		//设置颜色
		if(g_LED5_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led5_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{

	uint16_t* p = g_LED5_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED5_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led6_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{
	uint16_t* p = g_LED6_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_RUNNING_NUM; j++)
	{
		//设置颜色
		if(g_LED6_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led6_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B)
{

	uint16_t* p = g_LED6_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = LED_RUNNING_NUM; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED6_Array[j])
		{
			value_r = Color_R;
			value_g = Color_G;
			value_b = Color_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led2_Set_Buffer(void)
{

	uint16_t* p = g_LED2_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED2_Array[j])
		{
			value_r = COLOR_GREEN_R;
			value_g = COLOR_GREEN_G;
			value_b = COLOR_GREEN_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led3_Set_Buffer(void)
{

	uint16_t* p = g_LED3_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED3_Array[j])
		{
			value_r = COLOR_GREEN_R;
			value_g = COLOR_GREEN_G;
			value_b = COLOR_GREEN_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led4_Set_Buffer(void)
{

	uint16_t* p = g_LED4_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED4_Array[j])
		{
			value_r = COLOR_GREEN_R;
			value_g = COLOR_GREEN_G;
			value_b = COLOR_GREEN_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led5_Set_Buffer(void)
{

	uint16_t* p = g_LED5_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED5_Array[j])
		{
			value_r = COLOR_GREEN_R;
			value_g = COLOR_GREEN_G;
			value_b = COLOR_GREEN_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led6_Set_Buffer(void)
{

	uint16_t* p = g_LED6_Buffer + RESET_PULSE_LEN;
	uint8_t value_r, value_g, value_b;
	uint8_t i, j;
	for(j = 0; j < LED_NUM; j++)
	{
		//设置颜色
		if(g_LED6_Array[j])
		{
			value_r = COLOR_GREEN_R;
			value_g = COLOR_GREEN_G;
			value_b = COLOR_GREEN_B;
		}
		//不亮
		else
		{
			value_r = COLOR_BLACK_R;
			value_g = COLOR_BLACK_G;
			value_b = COLOR_BLACK_B;
		}
		for (i = 0; i < 8; i++)
		{
			p[LED_DATA_LEN * j + i]      = (value_g << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 8]  = (value_r << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
			p[LED_DATA_LEN * j + i + 16] = (value_b << i) & (0x80)? ONE_PULSE: ZERO_PULSE;
		}
	}
}

void Led1_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
}

void Led2_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, (uint32_t *)g_LED2_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, (uint32_t *)g_LED2_Buffer, DATA_BUFFER_LEN);
}

void Led3_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)g_LED3_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)g_LED3_Buffer, DATA_BUFFER_LEN);
}

void Led4_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)g_LED4_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)g_LED4_Buffer, DATA_BUFFER_LEN);
}

void Led5_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)g_LED5_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)g_LED5_Buffer, DATA_BUFFER_LEN);
}

void Led6_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, (uint32_t *)g_LED6_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, (uint32_t *)g_LED6_Buffer, DATA_BUFFER_LEN);
}

void Led_On(void)
{
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, (uint32_t *)g_LED2_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)g_LED3_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)g_LED4_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)g_LED5_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, (uint32_t *)g_LED6_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, (uint32_t *)g_LED2_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)g_LED3_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)g_LED4_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)g_LED5_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, (uint32_t *)g_LED6_Buffer, DATA_BUFFER_LEN);
}

void Led_On_Same(void)
{
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_Delay(1);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_3, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_3, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
	HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, (uint32_t *)g_LED1_Buffer, DATA_BUFFER_LEN);
}

//灯全灭
void Led_All_Off(void)
{
	Clear_All_Led_Array();
	Led1_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led2_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led3_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led4_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led5_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led6_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led1_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led2_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led3_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led4_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led5_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led6_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led_On();
}

//清除所有亮灯点位
void Clear_All_Led_Array(void)
{
	unsigned char i = 0;
	//清除亮灯点位
	for(i = 0; i < LED_NUM; i++)
	{
		g_LED1_Array[i] = 0;
		g_LED2_Array[i] = 0;
		g_LED3_Array[i] = 0;
		g_LED4_Array[i] = 0;
		g_LED5_Array[i] = 0;
		g_LED6_Array[i] = 0;
	}
}

//设置所有条形灯点位
void Set_Led_Line_Array(unsigned char channel, unsigned char on_off)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i++)
		{
			g_LED1_Array[i] = on_off;
		}
	}
	else if(2 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i++)
		{
			g_LED2_Array[i] = on_off;
		}
	}
	else if(3 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i++)
		{
			g_LED3_Array[i] = on_off;
		}
	}
	else if(4 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i++)
		{
			g_LED4_Array[i] = on_off;
		}
	}
	else if(5 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i++)
		{
			g_LED5_Array[i] = on_off;
		}
	}
	else if(6 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i++)
		{
			g_LED6_Array[i] = on_off;
		}
	}
}

//设置条形灯奇数点位
void Set_Led_Line_Odd_Array(unsigned char channel, unsigned char on_off)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i = i + 3)
		{
			g_LED1_Array[i] = on_off;
		}
	}
	else if(2 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i = i + 3)
		{
			g_LED2_Array[i] = on_off;
		}
	}
	else if(3 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i = i + 3)
		{
			g_LED3_Array[i] = on_off;
		}
	}
	else if(4 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i = i + 3)
		{
			g_LED4_Array[i] = on_off;
		}
	}
	else if(5 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i = i + 3)
		{
			g_LED5_Array[i] = on_off;
		}
	}
	else if(6 == channel)
	{
		for(i = 0; i < LED_RUNNING_NUM; i = i + 3)
		{
			g_LED6_Array[i] = on_off;
		}
	}
}

//设置所有环形灯点位
void Set_Led_Cycle_Array(unsigned char channel, unsigned char on_off)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i++)
		{
			g_LED1_Array[i] = on_off;
		}
	}
	else if(2 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i++)
		{
			g_LED2_Array[i] = on_off;
		}
	}
	else if(3 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i++)
		{
			g_LED3_Array[i] = on_off;
		}
	}
	else if(4 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i++)
		{
			g_LED4_Array[i] = on_off;
		}
	}
	else if(5 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i++)
		{
			g_LED5_Array[i] = on_off;
		}
	}
	else if(6 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i++)
		{
			g_LED6_Array[i] = on_off;
		}
	}
}

//设置环形灯奇数点位
void Set_Led_Cycle_Odd_Array(unsigned char channel, unsigned char on_off)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i = i + 3)
		{
			g_LED1_Array[i] = on_off;
		}
	}
	else if(2 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i = i + 3)
		{
			g_LED2_Array[i] = on_off;
		}
	}
	else if(3 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i = i + 3)
		{
			g_LED3_Array[i] = on_off;
		}
	}
	else if(4 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i = i + 3)
		{
			g_LED4_Array[i] = on_off;
		}
	}
	else if(5 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i = i + 3)
		{
			g_LED5_Array[i] = on_off;
		}
	}
	else if(6 == channel)
	{
		for(i = LED_RUNNING_NUM; i < LED_NUM; i = i + 3)
		{
			g_LED6_Array[i] = on_off;
		}
	}
}

//设置所有灯点位
void Set_Led_All_Array(unsigned char channel, unsigned char on_off)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED1_Array[i] = on_off;
		}
	}
	else if(2 == channel)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED2_Array[i] = on_off;
		}
	}
	else if(3 == channel)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED3_Array[i] = on_off;
		}
	}
	else if(4 == channel)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED4_Array[i] = on_off;
		}
	}
	else if(5 == channel)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED5_Array[i] = on_off;
		}
	}
	else if(6 == channel)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED6_Array[i] = on_off;
		}
	}
}

//设置奇数灯点位
void Set_Led_Odd_Array(unsigned char channel, unsigned char on_off)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		for(i = 0; i < LED_NUM; i = i + 3)
		{
			g_LED1_Array[i] = on_off;
		}
	}
	else if(2 == channel)
	{
		for(i = 0; i < LED_NUM; i = i + 3)
		{
			g_LED2_Array[i] = on_off;
		}
	}
	else if(3 == channel)
	{
		for(i = 0; i < LED_NUM; i = i + 3)
		{
			g_LED3_Array[i] = on_off;
		}
	}
	else if(4 == channel)
	{
		for(i = 0; i < LED_NUM; i = i + 3)
		{
			g_LED4_Array[i] = on_off;
		}
	}
	else if(5 == channel)
	{
		for(i = 0; i < LED_NUM; i = i + 3)
		{
			g_LED5_Array[i] = on_off;
		}
	}
	else if(6 == channel)
	{
		for(i = 0; i < LED_NUM; i = i + 3)
		{
			g_LED6_Array[i] = on_off;
		}
	}
}

//模式1指示灯固定显示
void Led_On_Mode1(unsigned char BT_Connect)
{
	Clear_All_Led_Array();
	g_LED1_Array[12] = 1;
	g_LED2_Array[12] = 1;
	g_LED3_Array[12] = 1;
	g_LED4_Array[12] = 1;
	g_LED5_Array[12] = 1;
	g_LED6_Array[12] = 1;
	if(BT_Connect)
	{
		Led1_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
		Led2_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
		Led3_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
		Led4_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
		Led5_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
		Led6_Set_Running(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	}
	else
	{
		Led1_Set_Running(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
		Led2_Set_Running(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
		Led3_Set_Running(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
		Led4_Set_Running(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
		Led5_Set_Running(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
		Led6_Set_Running(COLOR_WHITE_R, COLOR_WHITE_G, COLOR_WHITE_B);
	}
	Led1_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led2_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led3_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led4_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led5_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led6_Set_Cycle(COLOR_BLACK_R, COLOR_BLACK_G, COLOR_BLACK_B);
	Led_On();
}

//模式4-4~4-6
void Set_LED_Mode4_Running(unsigned char channel, unsigned char led_start, unsigned char led_end)
{
	unsigned char i = 0;
	if(1 == channel)
	{
		//清除亮灯点位
		for(i = led_start; i < led_end; i++)
		{
			g_LED1_Array[i] = 0;
		}
		//最后一个亮灯后,灭灯
		if(g_App_Mode4_Running_Count >= led_end)
		{
			g_App_Mode4_Running = 0;
			Led1_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led1_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led1_On();
			return;
		}
		//移动点位
		g_LED1_Array[g_App_Mode4_Running_Count] = 1;
		Led1_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
		Led1_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
		Led1_On();
		//移动到下一个点
		g_App_Mode4_Running_Count++;
	}
	else if(2 == channel)
	{
		//清除亮灯点位
		for(i = led_start; i < led_end; i++)
		{
			g_LED2_Array[i] = 0;
		}
		//最后一个亮灯后,灭灯
		if(g_App_Mode4_Running_Count >= led_end)
		{
			g_App_Mode4_Running = 0;
			Led2_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led2_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led2_On();
			return;
		}
		//移动点位
		g_LED2_Array[g_App_Mode4_Running_Count] = 1;
		Led2_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
		Led2_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
		Led2_On();
		//移动到下一个点
		g_App_Mode4_Running_Count++;
	}
	else if(3 == channel)
	{
		//清除亮灯点位
		for(i = led_start; i < led_end; i++)
		{
			g_LED3_Array[i] = 0;
		}
		//最后一个亮灯后,灭灯
		if(g_App_Mode4_Running_Count >= led_end)
		{
			g_App_Mode4_Running = 0;
			Led3_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led3_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led3_On();
			return;
		}
		//移动点位
		g_LED3_Array[g_App_Mode4_Running_Count] = 1;
		Led3_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
		Led3_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
		Led3_On();
		//移动到下一个点
		g_App_Mode4_Running_Count++;
	}
	else if(4 == channel)
	{
		//清除亮灯点位
		for(i = led_start; i < led_end; i++)
		{
			g_LED4_Array[i] = 0;
		}
		//最后一个亮灯后,灭灯
		if(g_App_Mode4_Running_Count >= led_end)
		{
			g_App_Mode4_Running = 0;
			Led4_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led4_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led4_On();
			return;
		}
		//移动点位
		g_LED4_Array[g_App_Mode4_Running_Count] = 1;
		Led4_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
		Led4_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
		Led4_On();
		//移动到下一个点
		g_App_Mode4_Running_Count++;
	}
	else if(5 == channel)
	{
		//清除亮灯点位
		for(i = led_start; i < led_end; i++)
		{
			g_LED5_Array[i] = 0;
		}
		//最后一个亮灯后,灭灯
		if(g_App_Mode4_Running_Count >= led_end)
		{
			g_App_Mode4_Running = 0;
			Led5_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led5_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led5_On();
			return;
		}
		//移动点位
		g_LED5_Array[g_App_Mode4_Running_Count] = 1;
		Led5_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
		Led5_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
		Led5_On();
		//移动到下一个点
		g_App_Mode4_Running_Count++;
	}
	else if(6 == channel)
	{
		//清除亮灯点位
		for(i = led_start; i < led_end; i++)
		{
			g_LED6_Array[i] = 0;
		}
		//最后一个亮灯后,灭灯
		if(g_App_Mode4_Running_Count >= led_end)
		{
			g_App_Mode4_Running = 0;
			Led6_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
			Led6_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
			Led6_On();
			return;
		}
		//移动点位
		g_LED6_Array[g_App_Mode4_Running_Count] = 1;
		Led6_Set_Running(g_Mode4_Line_Color_R, g_Mode4_Line_Color_G, g_Mode4_Line_Color_B);
		Led6_Set_Cycle(g_Mode4_Cycle_Color_R, g_Mode4_Cycle_Color_G, g_Mode4_Cycle_Color_B);
		Led6_On();
		//移动到下一个点
		g_App_Mode4_Running_Count++;
	}

}

//模式0的第1步
void Led_On_Mode0_Step1(void)
{
	uint8_t i = 0;
	for(i = 0; i < LED_NUM; i++)
	{
		g_LED2_Array[i] = (g_LED_Array_Mode0_Step1[g_LED_Count][i]);
	}
	Led2_Set_Running(0xF0, 0x35, 0xF0);
	Led2_Set_Cycle(0xF0, 0x35, 0xF0);
	Led2_On();
	//循环计数
	g_LED_Count++;
	if(g_LED_Count >= 32)
	{
		g_LED_Count = 0;
		g_Mode0_Step_Flag = 2;
	}
}


//模式0的第2步
void Led_On_Mode0_Step2(void)
{
	uint8_t i = 0;
	
	if(0 == g_LED_Cycle_Count)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED3_Array[i] = (g_LED_Array_Mode0_Step2[g_LED_Count][i]);
		}
		Led3_Set_Running(0xF0, 0x35, 0xF0);
		Led3_Set_Cycle(0xF0, 0x35, 0xF0);
		Led3_On();
	}
	else if(1 == g_LED_Cycle_Count)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED4_Array[i] = (g_LED_Array_Mode0_Step2[g_LED_Count][i]);
		}
		Led4_Set_Running(0xF0, 0x35, 0xF0);
		Led4_Set_Cycle(0xF0, 0x35, 0xF0);
		Led4_On();
	}
	else if(2 == g_LED_Cycle_Count)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED5_Array[i] = (g_LED_Array_Mode0_Step2[g_LED_Count][i]);
		}
		Led5_Set_Running(0xF0, 0x35, 0xF0);
		Led5_Set_Cycle(0xF0, 0x35, 0xF0);
		Led5_On();
	}
	else if(3 == g_LED_Cycle_Count)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED6_Array[i] = (g_LED_Array_Mode0_Step2[g_LED_Count][i]);
		}
		Led6_Set_Running(0xF0, 0x35, 0xF0);
		Led6_Set_Cycle(0xF0, 0x35, 0xF0);
		Led6_On();
	}
	else if(4 == g_LED_Cycle_Count)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED1_Array[i] = (g_LED_Array_Mode0_Step2[g_LED_Count][i]);
		}
		Led1_Set_Running(0xF0, 0x35, 0xF0);
		Led1_Set_Cycle(0xF0, 0x35, 0xF0);
		Led1_On();
	}
	else if(5 == g_LED_Cycle_Count)
	{
		for(i = 0; i < LED_NUM; i++)
		{
			g_LED2_Array[i] = (g_LED_Array_Mode0_Step2[g_LED_Count][i]);
		}
		Led2_Set_Running(0xF0, 0x35, 0xF0);
		Led2_Set_Cycle(0xF0, 0x35, 0xF0);
		Led2_On();
	}
	//循环计数
	g_LED_Count++;
	if(g_LED_Count >= 28)
	{
		g_LED_Count = 0;
		g_LED_Cycle_Count++;
		if(g_LED_Cycle_Count >= 6)
		{
			g_Mode0_Step_Flag = 3;
		}
	}
}

//模式0的第3步
void Led_On_Mode0_Step3(void)
{
	uint8_t i = 0;
	for(i = 0; i < LED_NUM; i++)
	{
		g_LED1_Array[i] = (g_LED_Array_Mode0_Step3[g_LED_Count][i]);
	}
	Led1_Set_Running(0x1F, 0xC5, 0xFF);
	Led1_Set_Cycle(0x1F, 0xC5, 0xFF);
	Led_On_Same();
	//循环计数
	g_LED_Count++;
	if(g_LED_Count >= 17)
	{
		g_LED_Count = 0;
		g_App_Mode = 1;
		//显示固定指示灯
		Led_On_Mode1(g_BT_Connect_Flag);
	}
}

