#include "stm32f1xx_hal.h"
#include "main.h"
#include  <string.h>

void start_job(void);

void send_data_uart( UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size );


extern UART_HandleTypeDef huart1;

extern uint16_t time_con1,time_con2;
extern uint8_t time_consta1,time_consta2;

extern uint8_t  tx_buf[],rx_buf[];

#define   DATA_RX_BUF_LONG   128    // ���մ������ݳ���
#define   DATA_RX_DEJAY_CON  150     //data_delay_time
extern uint8_t  data_rx_buf[];
extern uint16_t  data_rx_con,data_delay_time,data_rx_sta;    //���մ�������ָ��,���ʱ��ms


extern uint8_t uart1_busy;

extern uint8_t model_number_buf[ ],serial_number_buf[ ],version_number_buf[ ] ; //��Ʒ�ͺţ����кţ�����汾�Ų�Ʒ�ͺţ����кţ�����汾��
extern uint8_t model_number_new_buf[ ],serial_number_new_buf[ ],version_number_new_buf[ ] ; //��Ʒ�ͺţ����кţ�����汾��

extern uint16_t control_upgrade[];  //��������������:����״̬,��ʼ�������,���ݰ���

extern uint8_t  control_upgrade_buf[];

extern uint8_t  run_control_1 ;

#include "./IAP/iap.h"
#include "./STMFLASH/stmflash.h"
#include "./sys/sys.h"

#define LED1_ON                       HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)    // ����ߵ�ƽ
#define LED1_OFF                      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)  // ����͵�ƽ
#define LED1_TOGGLE                   HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin)                // �����ת

#define LED7_ON                       HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_SET)    // ����ߵ�ƽ
#define LED7_OFF                      HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_RESET)  // ����͵�ƽ
#define LED7_TOGGLE                   HAL_GPIO_TogglePin(LED7_GPIO_Port,LED7_Pin)                // �����ת

#define READ_BTLK_STATE               HAL_GPIO_ReadPin(BTLK_STATE_GPIO_Port,BTLK_STATE_Pin)

#define   husart_debug  huart1   //printf ����


#define FLASH_SAVE_ADDR    FLASH_APP1_ADDR-0x800    /* ����FLASH ���濪ʼ��ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С + 0X08000000) */
#define INFORMATION_LONG      16    /* �洢��Ϣ����,����Ϊż��  ��λ�ֽ� */

#define DATA_FRAME_HEADER_0  0xfe  
#define DATA_FRAME_HEADER_1  0xa5  

#define PROGRAM_RUN_IN     1     // 0,������IAP��1,������APP
#define PACKET_VOLUM       64*1  //    ÿ֡������Ч���ݰ����ȣ�64*2��n�η� ������1024
#define CONTROL_UPGRADE    8     //     �������������� uint16_t

#define FLASH_IAP1_ADDR         0x08000000 
#define FLASH_SAVE_NEW_ADDR   0x08028000  // FLASH ���������򻺴��ַ
#define FLASH_APP_ADDR        0x08010000       // FLASH �� APP�����ַ
#define FLASH_SAVE_RAM_LONG   1024*2      // �������� RAM ���泤��  �ֽ�
#define NUMBER_PACKET_WRITER  FLASH_SAVE_RAM_LONG/PACKET_VOLUM    //ÿ��д�ڴ���Ҫ�����ݰ�����

#define CONTROL_UPGRADE_BUF_LONG     FLASH_SAVE_RAM_LONG  // �������ݻ����С


#define TX_TIM_DELAY1      600     //�������� ��ʱ ms

void data_rx_job(void);

unsigned int   CRC16(unsigned char *puchMsg, unsigned int usDataLen)  ;















