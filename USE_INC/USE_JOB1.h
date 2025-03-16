#include "stm32f1xx_hal.h"
#include "main.h"
#include  <string.h>

void start_job(void);

void send_data_uart( UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size );


extern UART_HandleTypeDef huart1;

extern uint16_t time_con1,time_con2;
extern uint8_t time_consta1,time_consta2;

extern uint8_t  tx_buf[],rx_buf[];

#define   DATA_RX_BUF_LONG   128    // 接收处理数据长度
#define   DATA_RX_DEJAY_CON  150     //data_delay_time
extern uint8_t  data_rx_buf[];
extern uint16_t  data_rx_con,data_delay_time,data_rx_sta;    //接收处理数据指针,间隔时间ms


extern uint8_t uart1_busy;

extern uint8_t model_number_buf[ ],serial_number_buf[ ],version_number_buf[ ] ; //产品型号；序列号；软件版本号产品型号；序列号；软件版本号
extern uint8_t model_number_new_buf[ ],serial_number_new_buf[ ],version_number_new_buf[ ] ; //产品型号；序列号；软件版本号

extern uint16_t control_upgrade[];  //控制升级数据字:升级状态,开始升级序号,数据包量

extern uint8_t  control_upgrade_buf[];

extern uint8_t  run_control_1 ;

#include "./IAP/iap.h"
#include "./STMFLASH/stmflash.h"
#include "./sys/sys.h"

#define LED1_ON                       HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)    // 输出高电平
#define LED1_OFF                      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)  // 输出低电平
#define LED1_TOGGLE                   HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin)                // 输出反转

#define LED7_ON                       HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_SET)    // 输出高电平
#define LED7_OFF                      HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_RESET)  // 输出低电平
#define LED7_TOGGLE                   HAL_GPIO_TogglePin(LED7_GPIO_Port,LED7_Pin)                // 输出反转

#define READ_BTLK_STATE               HAL_GPIO_ReadPin(BTLK_STATE_GPIO_Port,BTLK_STATE_Pin)

#define   husart_debug  huart1   //printf 定向


#define FLASH_SAVE_ADDR    FLASH_APP1_ADDR-0x800    /* 设置FLASH 保存开始地址(必须为偶数，且其值要大于本代码所占用FLASH的大小 + 0X08000000) */
#define INFORMATION_LONG      16    /* 存储信息长度,必须为偶数  单位字节 */

#define DATA_FRAME_HEADER_0  0xfe  
#define DATA_FRAME_HEADER_1  0xa5  

#define PROGRAM_RUN_IN     1     // 0,运行在IAP；1,运行在APP
#define PACKET_VOLUM       64*1  //    每帧传输有效数据包长度，64*2的n次方 不大于1024
#define CONTROL_UPGRADE    8     //     升级控制字数量 uint16_t

#define FLASH_IAP1_ADDR         0x08000000 
#define FLASH_SAVE_NEW_ADDR   0x08028000  // FLASH 内升级程序缓存地址
#define FLASH_APP_ADDR        0x08010000       // FLASH 内 APP缓存地址
#define FLASH_SAVE_RAM_LONG   1024*2      // 升级程序 RAM 缓存长度  字节
#define NUMBER_PACKET_WRITER  FLASH_SAVE_RAM_LONG/PACKET_VOLUM    //每次写内存需要的数据包数量

#define CONTROL_UPGRADE_BUF_LONG     FLASH_SAVE_RAM_LONG  // 升级数据缓存大小


#define TX_TIM_DELAY1      600     //发送数据 延时 ms

void data_rx_job(void);

unsigned int   CRC16(unsigned char *puchMsg, unsigned int usDataLen)  ;















