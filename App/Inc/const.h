#ifndef _CONST_H
#define _CONST_H

#define LED_PWM_PERIOD			50

#define USART1_BDP_LEN			50
#define BDP_HEAD					0xFC
#define BDP_CMD_WRITE			0x55
#define BDP_CMD_READ			0xAA
#define BDP_ADDR_1				0x0001
#define BDP_ADDR_2				0x0002
#define BDP_ADDR_3				0x0003
#define BDP_ADDR_4				0x0004
#define BDP_ADDR_5				0x0005
#define BDP_ADDR_6				0x0006
#define BDP_ADDR_7				0x0007
#define BDP_ADDR_8				0x0008
#define BDP_ADDR_9				0x0009
#define BDP_ADDR_10				0x000A
#define BDP_ADDR_11				0x000B
#define BDP_ADDR_12				0x000C
#define MAX_SERIAL_FIFO_DEP		4
#define MAX_FIFO_BUF_LEN		USART1_BDP_LEN
#define FLASH_APP_INFO				0x0800D800

#define FLASH_ALREADY_CONFIG_FLAG	0xD5

#define Press_AD6	HAL_GPIO_ReadPin(Press_AD1_GPIO_Port, Press_AD1_Pin)
#define Press_AD5	HAL_GPIO_ReadPin(Press_AD2_GPIO_Port, Press_AD2_Pin)
#define Press_AD4	HAL_GPIO_ReadPin(Press_AD3_GPIO_Port, Press_AD3_Pin)
#define Press_AD3	HAL_GPIO_ReadPin(Press_AD4_GPIO_Port, Press_AD4_Pin)
#define Press_AD2	HAL_GPIO_ReadPin(Press_AD5_GPIO_Port, Press_AD5_Pin)
#define Press_AD1	HAL_GPIO_ReadPin(Press_AD6_GPIO_Port, Press_AD6_Pin)

#define ONE_PULSE	60
#define ZERO_PULSE	30                        

#define LED_RUNNING_NUM		16
#define LED_RUNNING_NUM2		7
#define LED_Cycle_Start		7								
#define LED_NUM						44
#define LED_DATA_LEN			24
#define RESET_PULSE_LEN		300
#define DATA_BUFFER_LEN		RESET_PULSE_LEN + (LED_DATA_LEN * LED_NUM)
#define LED_CYCLE_COUNT		LED_RUNNING_NUM

#define MAX_LED_FIFO_DEP	4

#define COLOR_BLACK_R		0x00
#define COLOR_BLACK_G		0x00
#define COLOR_BLACK_B		0x00

#define COLOR_GREEN_R		0x00
#define COLOR_GREEN_G		0xFF
#define COLOR_GREEN_B		0x00

#define COLOR_RED_R			0xFF
#define COLOR_RED_G			0x00
#define COLOR_RED_B			0x00

#define COLOR_BLUE_R		0x00
#define COLOR_BLUE_G		0x00
#define COLOR_BLUE_B		0xFF

#define COLOR_WHITE_R		0xFF
#define COLOR_WHITE_G		0xFF
#define COLOR_WHITE_B		0xFF

#define COLOR_ORANGE_R		0xFF
#define COLOR_ORANGE_G		0xA5
#define COLOR_ORANGE_B		0x00

#define COLOR_YELLOW_R		0xFF
#define COLOR_YELLOW_G		0xFF
#define COLOR_YELLOW_B		0x00

#define LED_ARRAY_ON		1
#define LED_ARRAY_OFF		0

#endif
