
#include "USE_JOB1.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include <string.h>

uint16_t time_con1,time_con2;
uint8_t time_consta1,time_consta2;

/**
  * @brief  SYSTICK callback.
  * @retval None
  */
void HAL_SYSTICK_Callback(void)
{
//	time_con1++;
//	if(time_con1>9)          // 10ms
//	{
//		time_con1 = 0 ;
//		time_consta1 = 1 ;
//	}
	
	if(data_delay_time>DATA_RX_DEJAY_CON)  
	{
		data_rx_con=0; 
	}
	else 
	{
		data_delay_time++;
	}
}


uint8_t  tx_buf[DATA_RX_BUF_LONG]={0xfe,0xa5,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x00};
uint8_t  rx_buf[DATA_RX_BUF_LONG];


uint8_t  data_rx_buf[DATA_RX_BUF_LONG];
uint16_t  data_rx_con , data_delay_time , data_rx_sta ;    //���մ�������ָ��,���ʱ��ms,���մ�������״̬
//���ڽ����жϳ���
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
//{
//    //�ж����ĸ����ڴ������ж�
//    //	if(huart == &huart1)	//�����ж϶�����,�����Ҫ����#include "usart.h"
//    if(huart->Instance == USART1)
//    {
//		data_rx_buf[data_rx_con] = rx_buf[0] ;
//		data_rx_con++;            //���մ�������ָ��
//		HAL_UART_Receive_IT(&huart1, rx_buf, 1);//&rx_buf[data_rx_con]
//		data_delay_time = 0 ;     //��ʱ�� ����
//		data_rx_sta=1  ;
//    }
//}

//**  ���ڽ������ݴ������  **
void data_rx_job(void)
{
	uint8_t    i=0,j1;
	uint16_t  n1,n2,n3;
//	uint32_t  add1,add2,add3,n4;
	n1=data_rx_con;
	if((data_rx_con>(DATA_RX_BUF_LONG-1))||(data_delay_time>(DATA_RX_DEJAY_CON-1)))    data_rx_con=0;  //��ֹ���	  
	if(data_rx_con>(4-1))
	{
		//����֡ͷ����
		while( !((data_rx_buf[i]==DATA_FRAME_HEADER_0)&&(data_rx_buf[i+1]==DATA_FRAME_HEADER_1)) && (i<(n1-1)) )
		{
			i++;
		}
		//****
		if(i>0)
		{
			for(j1=0;j1<(n1-i);j1++)
			{
				data_rx_buf[j1] = data_rx_buf[i+j1] ;
			}
			if(data_rx_con==n1)    data_rx_con= n1-i ;      
			else                   {  data_rx_buf[j1+1]= data_rx_buf[n1] ;  data_rx_con= j1+2; }
		}
		//***����֡ͷ����
		if(i==0)
		{
			tx_buf[0]=DATA_FRAME_HEADER_0;    tx_buf[1]=DATA_FRAME_HEADER_1;  // ���ݰ�֡ͷ
			
			if(data_rx_con>(6-1))  //���������ֽ� 6 ������
			{
				
				if((data_rx_buf[2]==0x03)||(data_rx_buf[2]==0x10))  //��ѯ����,��������
				{
					n2 = CRC16(data_rx_buf , 4 ) ;					//CRCУ��
					n3 = (data_rx_buf[4]<<8) |  data_rx_buf[5] ;
					if((n2==n3) || 0)              //CRCУ��ͨ��
					{
						data_rx_con=0;     //
						
						if(data_rx_buf[2]==0x03)  //��ѯ����
						{
							tx_buf[0]=DATA_FRAME_HEADER_0;    tx_buf[1]=DATA_FRAME_HEADER_1;    tx_buf[2]=0x03;
							if(data_rx_buf[3]==0x05)    //��ѯ�豸��Ϣ���豸�ͺţ����кţ�����汾��
							{
								tx_buf[3]=0x05;
								n2=3*INFORMATION_LONG;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+INFORMATION_LONG] , serial_number_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+2*INFORMATION_LONG] , version_number_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+3*INFORMATION_LONG ) ;
								tx_buf[6+3*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+3*INFORMATION_LONG+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 6+3*INFORMATION_LONG+2 );
							}
							else if(data_rx_buf[3]==0x11)    //��ѯ�豸��Ϣ��1-8
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x12)    //��ѯ�豸��Ϣ��9-16
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf+INFORMATION_LONG/2 , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x13)    //��ѯ�豸��Ϣ��17-24
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  serial_number_buf , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x14)    //��ѯ�豸��Ϣ��25-32
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  serial_number_buf+INFORMATION_LONG/2 , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x15)    //��ѯ�豸��Ϣ��33-40
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  version_number_buf , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x16)    //��ѯ�豸��Ϣ��41-48
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  version_number_buf+INFORMATION_LONG/2 , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x02)    //��ѯ�豸��Ϣ���豸�ͺ� 
							{
								tx_buf[3]=0x02;
								n2=1*INFORMATION_LONG;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG+2 );
								HAL_Delay(TX_TIM_DELAY1);
							}
							else if(data_rx_buf[3]==0x03)    //��ѯ�豸��Ϣ���豸�ͺ� 
							{
								tx_buf[3]=0x03;
								n2=1*INFORMATION_LONG;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  serial_number_buf, INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG+2 );
								HAL_Delay(TX_TIM_DELAY1);
							}
							else if(data_rx_buf[3]==0x04)    //��ѯ�豸��Ϣ���豸�ͺ� 
							{
								tx_buf[3]=0x04;
								n2=1*INFORMATION_LONG;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  version_number_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG+2 );
								HAL_Delay(TX_TIM_DELAY1);
							}
							if(data_rx_buf[3]==0x15)    //��ѯ�������豸��Ϣ���豸�ͺţ����кţ�����汾��
							{
								tx_buf[3]=0x15;
								n2=3*INFORMATION_LONG;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6] ,                 model_number_new_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+INFORMATION_LONG] , serial_number_new_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+2*INFORMATION_LONG] , version_number_new_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+3*INFORMATION_LONG ) ;
								tx_buf[6+3*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+3*INFORMATION_LONG+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 6+3*INFORMATION_LONG+2 );
							}
							else if(data_rx_buf[3]==0x09)    //��ѯ�豸������Ϣ��00��IAP���У�01��APP���У����ݳ���1Byte
							{
								tx_buf[3]=0x09;
								n2=1;                            //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								tx_buf[6] = PROGRAM_RUN_IN ;    //// 0,������IAP��1,������APP
								n3 = CRC16( tx_buf , 6+1 ) ;
								tx_buf[6+1] = n3 >>8 ;
								tx_buf[7+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 8+1 );
							}
							else if(data_rx_buf[3]==0x0a)    //��ѯ ��ѯ�������������֣����ݳ���16Byte��С��ģʽ
							{
								tx_buf[3]=0x0a;
								n2 = 2 * CONTROL_UPGRADE ;  //���ݳ���
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6] ,        control_upgrade , 2*CONTROL_UPGRADE );
								n3 = CRC16( tx_buf , 6+2*CONTROL_UPGRADE ) ;
								tx_buf[6+2*CONTROL_UPGRADE] = n3 >>8 ;
								tx_buf[6+2*CONTROL_UPGRADE+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 6+2*CONTROL_UPGRADE+1+1) ;
							}
						}
						else if(data_rx_buf[2]==0x10)  //��������
						{
							tx_buf[2]=0x10;
							memcpy(  &tx_buf[2], &data_rx_buf[2] , 4 );
							if(data_rx_buf[3]==0x04) 
							{                              //��������ԭ��������֡����
							}  		
							else if(data_rx_buf[3]==0x00)  
							{                             //ִ���û�APP����  ������Ӧ
//								printf("��ʼִ�� �û�����!!\r\n");//**  �����û�APP  **
//								HAL_Delay(1000);
//								iap_load_app(FLASH_APP1_ADDR);  /* ִ��FLASH APP���� */
							}
							else if(data_rx_buf[3]==0x01)  
							{                             //��ʼ�������
//								printf("��ʼִ�� �������!!\r\n");
								sys_soft_reset( );
								while(1)
								{}
								
//								iap_load_app(FLASH_IAP1_ADDR);   /* ִ��IAP���� */
							}	
							else if(data_rx_buf[3]==0x02)  
							{                             //IAP�����ݿ�ʼ����
								
//								stmflash_write( FLASH_SAVE_ADDR+3*INFORMATION_LONG , (uint16_t *)control_upgrade, CONTROL_UPGRADE);//  ��������������
//								printf("��ʼִ�� ���ݿ�ʼ����!!\r\n");
							}	
							else if(data_rx_buf[3]==0x03)  
							{                             //IAP�����ݴ���������������
//								n1 = (control_upgrade[1]+1) % NUMBER_PACKET_WRITER ;
//								n2 =  control_upgrade[1] / NUMBER_PACKET_WRITER ;
//								if(n1>0)
//								{
//									add1 = FLASH_SAVE_NEW_ADDR + ( control_upgrade[1]-n1 )*PACKET_VOLUM ; 
//									stmflash_write( add1 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // д��FLASH
//									n2 ++ ;
//								}
//								//����Ǩ��
//								for(i=0;i<n2;i++)
//								{
//									add2 = FLASH_SAVE_NEW_ADDR + i * CONTROL_UPGRADE_BUF_LONG ;
//									stmflash_read(  add2 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // ����FLASH 
//									add2 = FLASH_APP_ADDR + i * CONTROL_UPGRADE_BUF_LONG ;
//									stmflash_write( add2 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // д��FLASH
//								}
//								//�ָ�������
//								control_upgrade[0]=0;  control_upgrade[1]=0;  control_upgrade[2]=PACKET_VOLUM;     //����ֵ:����״̬,��ǰ���ݰ����,���ݰ���С
//								stmflash_write( FLASH_SAVE_ADDR+3*INFORMATION_LONG , (uint16_t *)control_upgrade, CONTROL_UPGRADE);//  ��������������
//								//**  �����û�APP  **
//								iap_load_app(FLASH_APP1_ADDR);  /* ִ��FLASH APP���� */
//								
//								printf("��ʼִ�� ���ݴ���������û���������!!\r\n");
							}	
							if( !(data_rx_buf[3]==0x01))  //���ǿ�ʼ�����������
							{
								send_data_uart ( &huart1, tx_buf , 6 ) ;
							}
						}
					}
				}
				else if( data_rx_buf[2]==0x20 )  //�������� ������
				{
					n1 = data_rx_buf[4]<<8 |data_rx_buf[5] ;   //���ݳ���
					
					if(data_rx_con>(n1+8-1))    //
					{
						n2 =  CRC16(data_rx_buf , n1+8-2 ) ;					//CRCУ��
						n3 =  data_rx_buf[n1+8-2]<<8 |data_rx_buf[n1+8-1] ;     
						if(n2==n3)                                  // CRC У��ͨ��
						{
							data_rx_con= 0 ;            //        
							if( data_rx_buf[3]==0x01 )  //  ���������������Ϣ���豸�ͺţ����кţ�����汾�ţ����ݳ���48Byte���豸�ڿ�ʼ�����󣬽�����������Ϣ���洢��
							{
//								tx_buf[2]=0x20;  tx_buf[3]=0x01;
//								n2=1;                          //���ݳ���
//								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
//								tx_buf[6] = 0x05 ;    // 
//								n3 = CRC16( tx_buf , 6+1 ) ;
//								tx_buf[6+1] = n3 >>8 ;
//								tx_buf[7+1] = n3   ;
//								send_data_uart ( &huart1, tx_buf , 7+1+1 );  // �豸Ӧ�� 
//								//���ݴ���
//								memcpy( model_number_new_buf ,  &data_rx_buf[6]                    , INFORMATION_LONG );  //��Ʒ�ͺ� 
//								memcpy( serial_number_new_buf , &data_rx_buf[6+INFORMATION_LONG]   , INFORMATION_LONG );  //���кţ�
//								memcpy( version_number_new_buf ,&data_rx_buf[6+2*INFORMATION_LONG] , INFORMATION_LONG );  //����汾��
//								// ����д��FLASH
//								stmflash_write(FLASH_SAVE_ADDR+3*INFORMATION_LONG+CONTROL_UPGRADE*2 , (uint16_t *)&data_rx_buf[6], 3*INFORMATION_LONG/2); //��Ʒ�ͺ� 

//								printf("���������������Ϣ��");
							}
						}
					}
				}
				else if( data_rx_buf[2]==0xa0 )  //IAP���ݴ�������
				{
//					n1 = data_rx_buf[4]<<8 |data_rx_buf[5] ;   //���ݳ���
//					if( data_rx_con>(n1+10-1) )
//					{
//						tx_buf[2]=0xa0;    tx_buf[3]=0x00;    tx_buf[4]=data_rx_buf[6];    tx_buf[5]=data_rx_buf[7];  
//						n2 =  CRC16(data_rx_buf , n1+10-2 ) ;					//CRCУ��
//						n3 =  data_rx_buf[n1+10-2]<<8 |data_rx_buf[n1+10-1] ;     
//						if(( n2==n3 )&&( n1==control_upgrade[2] ))
//						{
//							data_rx_con= 0 ;            //        
//							n4= data_rx_buf[6]<<8 |data_rx_buf[7] ;   // ���ݰ����
//							if( (n4==0) || (n4==(control_upgrade[1]+1)) )   //  
//							{
////																
//								//**  ���ݽ��뻺��  **
//								add1 = n4 % NUMBER_PACKET_WRITER ;
//								add2 = add1 * PACKET_VOLUM  ;
//								memcpy( &control_upgrade_buf[add2] ,  &data_rx_buf[8]  , PACKET_VOLUM ); 
//								control_upgrade[1] =  n4 ;        //���ؽ��ȱ���
//								
//								//**  ����д��FLASH  **
//								if( add1 >= ( NUMBER_PACKET_WRITER-1 ) && ( n4>0 ) ) //������д��
//								{
//									add3 = FLASH_SAVE_NEW_ADDR + ( n4 + 1 - NUMBER_PACKET_WRITER ) * PACKET_VOLUM  ;   //FLASH �������ݿ�洢��ַ
//									stmflash_write( add3 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // д��FLASH
//									memset( control_upgrade_buf , 0xff , CONTROL_UPGRADE_BUF_LONG );  //�����ʼ��
//									stmflash_write( FLASH_SAVE_ADDR+3*INFORMATION_LONG , (uint16_t *)control_upgrade, CONTROL_UPGRADE);//  ��������������  ���� �洢
//									
//								}
//								
//								//ͨѶӦ��
//								tx_buf[6]= 0x05 ;  
//								n3 = CRC16( tx_buf , 6+1 ) ;
//								tx_buf[6+1] = n3 >>8 ;
//								tx_buf[7+1] = n3   ;
//								send_data_uart ( &huart1, tx_buf , 7+1+1 );  // �豸Ӧ�� 
//							}
//						}
//					}
//					
				}
			}
		}
	}	
}


/**
  * ��������: �ض���c�⺯��printf��DEBUG_USARTx
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ������
  */
//int fputc(int ch, FILE *f)
//{
//	
//  HAL_UART_Transmit(&husart_debug, (uint8_t *)&ch, 1, 0xffff);
//  return ch;
//}

///**
//  * ��������: �ض���c�⺯��getchar,scanf��DEBUG_USARTx
//  * �������: ��
//  * �� �� ֵ: ��
//  * ˵    ������
//  */
//int fgetc(FILE * f)
//{
//  uint8_t ch = 0;
//  HAL_UART_Receive(&husart_debug,&ch, 1, 0xffff);
//  return ch;
//}


//**��ʼ����������ʼ
uint8_t model_number_buf[INFORMATION_LONG+1]={"0000000000000000\0"},
        serial_number_buf[INFORMATION_LONG+1]={"0000000000000000\0"},
		version_number_buf[INFORMATION_LONG+1]={"0000000000000000\0"} ; //��Ʒ�ͺţ����кţ�����汾��
uint8_t model_number_new_buf[INFORMATION_LONG+1],serial_number_new_buf[INFORMATION_LONG+1],version_number_new_buf[INFORMATION_LONG+1] ; //��Ʒ�ͺţ����кţ�����汾��
uint16_t control_upgrade[ CONTROL_UPGRADE ];  //��������������:����״̬,��ʼ�������,���ݰ���
uint8_t  control_upgrade_buf[CONTROL_UPGRADE_BUF_LONG];  //���ݰ�����
uint8_t  run_control_1=0;
//����汾��Ϣ
const char MODEL_NUMBER_DEVICE_INFORMATION[INFORMATION_LONG+1]  ={"QJJ2024043001040\0"};	//Ӳ��
const char SERIAL_NUMBER_DEVICE_INFORMATION[INFORMATION_LONG+1] ={"0000000000000000\0"};	//���
const char VERSION_NUMBER_DEVICE_INFORMATION[INFORMATION_LONG+1]={"0000000000000000\0"};

void start_job(void)
{
//	uint8_t i;
	char    j[INFORMATION_LONG*4];
	HAL_Delay(10);
//	printf("\r\nHELLO,USERAPPjob is ok.\r\n");
	
	stmflash_read(FLASH_SAVE_ADDR                 ,   (uint16_t *)model_number_buf, INFORMATION_LONG/2);  //��Ʒ�ͺ� 
	
	stmflash_read(FLASH_SAVE_ADDR+INFORMATION_LONG ,  (uint16_t *)serial_number_buf, INFORMATION_LONG/2);// ���к� 
	
	stmflash_read(FLASH_SAVE_ADDR+2*INFORMATION_LONG , (uint16_t *)version_number_buf, INFORMATION_LONG/2);// ����汾��
	
	if( strcmp((char *)model_number_buf  ,MODEL_NUMBER_DEVICE_INFORMATION  ) ||
		strcmp((char *)serial_number_buf ,SERIAL_NUMBER_DEVICE_INFORMATION ) ||
		strcmp((char *)version_number_buf,VERSION_NUMBER_DEVICE_INFORMATION) ) 
	{
		memcpy( &j[0]                  , MODEL_NUMBER_DEVICE_INFORMATION  , INFORMATION_LONG);
		memcpy( &j[INFORMATION_LONG]   , SERIAL_NUMBER_DEVICE_INFORMATION , INFORMATION_LONG);
		memcpy( &j[INFORMATION_LONG*2] ,VERSION_NUMBER_DEVICE_INFORMATION , INFORMATION_LONG);
		
		stmflash_write(FLASH_SAVE_ADDR , (uint16_t *)j ,  3*INFORMATION_LONG/2 ) ;
		
		memcpy( model_number_buf   , MODEL_NUMBER_DEVICE_INFORMATION  , INFORMATION_LONG);
		memcpy( serial_number_buf  , SERIAL_NUMBER_DEVICE_INFORMATION , INFORMATION_LONG);
		memcpy( version_number_buf ,VERSION_NUMBER_DEVICE_INFORMATION , INFORMATION_LONG);
		
//		printf("�޸���Ϣ!!");
	}
	
}

//**�������
uint8_t uart1_busy=0;
void send_data_uart ( UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size )
{
	while(uart1_busy)
	uart1_busy = 1 ;	
	HAL_UART_Transmit_IT( huart , pData , Size );
}
/**
  * @brief  USART���ͻص�ִ�к���
  * @param  ��
  * @retval ��
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /*ͨ���жϷ�ʽ��������*/
  if ( UartHandle->Instance == USART1)
  {
		uart1_busy=0;  //USART���ͽ���
  }
}













