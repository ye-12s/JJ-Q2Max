
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
uint16_t  data_rx_con , data_delay_time , data_rx_sta ;    //接收处理数据指针,间隔时间ms,接收处理数据状态
//串口接收中断程序
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
//{
//    //判断是哪个串口触发的中断
//    //	if(huart == &huart1)	//两个判断都可以,这个需要包含#include "usart.h"
//    if(huart->Instance == USART1)
//    {
//		data_rx_buf[data_rx_con] = rx_buf[0] ;
//		data_rx_con++;            //接收处理数据指针
//		HAL_UART_Receive_IT(&huart1, rx_buf, 1);//&rx_buf[data_rx_con]
//		data_delay_time = 0 ;     //计时器 置零
//		data_rx_sta=1  ;
//    }
//}

//**  串口接收数据处理程序  **
void data_rx_job(void)
{
	uint8_t    i=0,j1;
	uint16_t  n1,n2,n3;
//	uint32_t  add1,add2,add3,n4;
	n1=data_rx_con;
	if((data_rx_con>(DATA_RX_BUF_LONG-1))||(data_delay_time>(DATA_RX_DEJAY_CON-1)))    data_rx_con=0;  //防止溢出	  
	if(data_rx_con>(4-1))
	{
		//数据帧头处理
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
		//***数据帧头符合
		if(i==0)
		{
			tx_buf[0]=DATA_FRAME_HEADER_0;    tx_buf[1]=DATA_FRAME_HEADER_1;  // 数据包帧头
			
			if(data_rx_con>(6-1))  //接收数据字节 6 个以上
			{
				
				if((data_rx_buf[2]==0x03)||(data_rx_buf[2]==0x10))  //查询命令,控制命令
				{
					n2 = CRC16(data_rx_buf , 4 ) ;					//CRC校验
					n3 = (data_rx_buf[4]<<8) |  data_rx_buf[5] ;
					if((n2==n3) || 0)              //CRC校验通过
					{
						data_rx_con=0;     //
						
						if(data_rx_buf[2]==0x03)  //查询命令
						{
							tx_buf[0]=DATA_FRAME_HEADER_0;    tx_buf[1]=DATA_FRAME_HEADER_1;    tx_buf[2]=0x03;
							if(data_rx_buf[3]==0x05)    //查询设备信息：设备型号，序列号，软件版本号
							{
								tx_buf[3]=0x05;
								n2=3*INFORMATION_LONG;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+INFORMATION_LONG] , serial_number_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+2*INFORMATION_LONG] , version_number_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+3*INFORMATION_LONG ) ;
								tx_buf[6+3*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+3*INFORMATION_LONG+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 6+3*INFORMATION_LONG+2 );
							}
							else if(data_rx_buf[3]==0x11)    //查询设备信息：1-8
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x12)    //查询设备信息：9-16
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf+INFORMATION_LONG/2 , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x13)    //查询设备信息：17-24
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  serial_number_buf , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x14)    //查询设备信息：25-32
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  serial_number_buf+INFORMATION_LONG/2 , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x15)    //查询设备信息：33-40
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  version_number_buf , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x16)    //查询设备信息：41-48
							{
								tx_buf[3]=data_rx_buf[3];
								n2=1*INFORMATION_LONG/2;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  version_number_buf+INFORMATION_LONG/2 , INFORMATION_LONG/2);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG/2] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG/2+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG/2+2 );
								HAL_Delay(TX_TIM_DELAY1);																
							}
							else if(data_rx_buf[3]==0x02)    //查询设备信息：设备型号 
							{
								tx_buf[3]=0x02;
								n2=1*INFORMATION_LONG;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  model_number_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG+2 );
								HAL_Delay(TX_TIM_DELAY1);
							}
							else if(data_rx_buf[3]==0x03)    //查询设备信息：设备型号 
							{
								tx_buf[3]=0x03;
								n2=1*INFORMATION_LONG;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  serial_number_buf, INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG+2 );
								HAL_Delay(TX_TIM_DELAY1);
							}
							else if(data_rx_buf[3]==0x04)    //查询设备信息：设备型号 
							{
								tx_buf[3]=0x04;
								n2=1*INFORMATION_LONG;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6]                ,  version_number_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+1*INFORMATION_LONG ) ;
								tx_buf[6+1*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+1*INFORMATION_LONG+1] = n3   ;
								HAL_Delay(TX_TIM_DELAY1/2);
								send_data_uart ( &huart1, tx_buf , 6+1*INFORMATION_LONG+2 );
								HAL_Delay(TX_TIM_DELAY1);
							}
							if(data_rx_buf[3]==0x15)    //查询升级中设备信息：设备型号，序列号，软件版本号
							{
								tx_buf[3]=0x15;
								n2=3*INFORMATION_LONG;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6] ,                 model_number_new_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+INFORMATION_LONG] , serial_number_new_buf , INFORMATION_LONG);
								memcpy( &tx_buf[6+2*INFORMATION_LONG] , version_number_new_buf , INFORMATION_LONG);
								n3 = CRC16( tx_buf , 6+3*INFORMATION_LONG ) ;
								tx_buf[6+3*INFORMATION_LONG] = n3 >>8 ;
								tx_buf[6+3*INFORMATION_LONG+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 6+3*INFORMATION_LONG+2 );
							}
							else if(data_rx_buf[3]==0x09)    //查询设备运行信息：00，IAP运行；01，APP运行，数据长度1Byte
							{
								tx_buf[3]=0x09;
								n2=1;                            //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								tx_buf[6] = PROGRAM_RUN_IN ;    //// 0,运行在IAP；1,运行在APP
								n3 = CRC16( tx_buf , 6+1 ) ;
								tx_buf[6+1] = n3 >>8 ;
								tx_buf[7+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 8+1 );
							}
							else if(data_rx_buf[3]==0x0a)    //查询 查询控制升级数据字：数据长度16Byte，小端模式
							{
								tx_buf[3]=0x0a;
								n2 = 2 * CONTROL_UPGRADE ;  //数据长度
								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
								memcpy( &tx_buf[6] ,        control_upgrade , 2*CONTROL_UPGRADE );
								n3 = CRC16( tx_buf , 6+2*CONTROL_UPGRADE ) ;
								tx_buf[6+2*CONTROL_UPGRADE] = n3 >>8 ;
								tx_buf[6+2*CONTROL_UPGRADE+1] = n3   ;
								send_data_uart ( &huart1, tx_buf , 6+2*CONTROL_UPGRADE+1+1) ;
							}
						}
						else if(data_rx_buf[2]==0x10)  //控制命令
						{
							tx_buf[2]=0x10;
							memcpy(  &tx_buf[2], &data_rx_buf[2] , 4 );
							if(data_rx_buf[3]==0x04) 
							{                              //心跳包，原命令数据帧返回
							}  		
							else if(data_rx_buf[3]==0x00)  
							{                             //执行用户APP程序  不作响应
//								printf("开始执行 用户代码!!\r\n");//**  运行用户APP  **
//								HAL_Delay(1000);
//								iap_load_app(FLASH_APP1_ADDR);  /* 执行FLASH APP代码 */
							}
							else if(data_rx_buf[3]==0x01)  
							{                             //开始软件升级
//								printf("开始执行 软件升级!!\r\n");
								sys_soft_reset( );
								while(1)
								{}
								
//								iap_load_app(FLASH_IAP1_ADDR);   /* 执行IAP代码 */
							}	
							else if(data_rx_buf[3]==0x02)  
							{                             //IAP，数据开始传输
								
//								stmflash_write( FLASH_SAVE_ADDR+3*INFORMATION_LONG , (uint16_t *)control_upgrade, CONTROL_UPGRADE);//  控制升级数据字
//								printf("开始执行 数据开始传输!!\r\n");
							}	
							else if(data_rx_buf[3]==0x03)  
							{                             //IAP，数据传输结束，升级完成
//								n1 = (control_upgrade[1]+1) % NUMBER_PACKET_WRITER ;
//								n2 =  control_upgrade[1] / NUMBER_PACKET_WRITER ;
//								if(n1>0)
//								{
//									add1 = FLASH_SAVE_NEW_ADDR + ( control_upgrade[1]-n1 )*PACKET_VOLUM ; 
//									stmflash_write( add1 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // 写入FLASH
//									n2 ++ ;
//								}
//								//数据迁移
//								for(i=0;i<n2;i++)
//								{
//									add2 = FLASH_SAVE_NEW_ADDR + i * CONTROL_UPGRADE_BUF_LONG ;
//									stmflash_read(  add2 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // 读出FLASH 
//									add2 = FLASH_APP_ADDR + i * CONTROL_UPGRADE_BUF_LONG ;
//									stmflash_write( add2 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // 写入FLASH
//								}
//								//恢复控制字
//								control_upgrade[0]=0;  control_upgrade[1]=0;  control_upgrade[2]=PACKET_VOLUM;     //赋初值:升级状态,当前数据包序号,数据包大小
//								stmflash_write( FLASH_SAVE_ADDR+3*INFORMATION_LONG , (uint16_t *)control_upgrade, CONTROL_UPGRADE);//  控制升级数据字
//								//**  运行用户APP  **
//								iap_load_app(FLASH_APP1_ADDR);  /* 执行FLASH APP代码 */
//								
//								printf("开始执行 数据传输结束，用户代码启动!!\r\n");
							}	
							if( !(data_rx_buf[3]==0x01))  //不是开始软件升级命令
							{
								send_data_uart ( &huart1, tx_buf , 6 ) ;
							}
						}
					}
				}
				else if( data_rx_buf[2]==0x20 )  //控制命令 带参数
				{
					n1 = data_rx_buf[4]<<8 |data_rx_buf[5] ;   //数据长度
					
					if(data_rx_con>(n1+8-1))    //
					{
						n2 =  CRC16(data_rx_buf , n1+8-2 ) ;					//CRC校验
						n3 =  data_rx_buf[n1+8-2]<<8 |data_rx_buf[n1+8-1] ;     
						if(n2==n3)                                  // CRC 校验通过
						{
							data_rx_con= 0 ;            //        
							if( data_rx_buf[3]==0x01 )  //  设置升级中软件信息：设备型号，序列号，软件版本号，数据长度48Byte，设备在开始升级后，接收升级包信息并存储。
							{
//								tx_buf[2]=0x20;  tx_buf[3]=0x01;
//								n2=1;                          //数据长度
//								tx_buf[4]=n2>>8;  tx_buf[5]=n2;
//								tx_buf[6] = 0x05 ;    // 
//								n3 = CRC16( tx_buf , 6+1 ) ;
//								tx_buf[6+1] = n3 >>8 ;
//								tx_buf[7+1] = n3   ;
//								send_data_uart ( &huart1, tx_buf , 7+1+1 );  // 设备应答 
//								//数据处理
//								memcpy( model_number_new_buf ,  &data_rx_buf[6]                    , INFORMATION_LONG );  //产品型号 
//								memcpy( serial_number_new_buf , &data_rx_buf[6+INFORMATION_LONG]   , INFORMATION_LONG );  //序列号；
//								memcpy( version_number_new_buf ,&data_rx_buf[6+2*INFORMATION_LONG] , INFORMATION_LONG );  //软件版本号
//								// 数据写入FLASH
//								stmflash_write(FLASH_SAVE_ADDR+3*INFORMATION_LONG+CONTROL_UPGRADE*2 , (uint16_t *)&data_rx_buf[6], 3*INFORMATION_LONG/2); //产品型号 

//								printf("设置升级中软件信息。");
							}
						}
					}
				}
				else if( data_rx_buf[2]==0xa0 )  //IAP数据传输命令
				{
//					n1 = data_rx_buf[4]<<8 |data_rx_buf[5] ;   //数据长度
//					if( data_rx_con>(n1+10-1) )
//					{
//						tx_buf[2]=0xa0;    tx_buf[3]=0x00;    tx_buf[4]=data_rx_buf[6];    tx_buf[5]=data_rx_buf[7];  
//						n2 =  CRC16(data_rx_buf , n1+10-2 ) ;					//CRC校验
//						n3 =  data_rx_buf[n1+10-2]<<8 |data_rx_buf[n1+10-1] ;     
//						if(( n2==n3 )&&( n1==control_upgrade[2] ))
//						{
//							data_rx_con= 0 ;            //        
//							n4= data_rx_buf[6]<<8 |data_rx_buf[7] ;   // 数据包序号
//							if( (n4==0) || (n4==(control_upgrade[1]+1)) )   //  
//							{
////																
//								//**  数据进入缓存  **
//								add1 = n4 % NUMBER_PACKET_WRITER ;
//								add2 = add1 * PACKET_VOLUM  ;
//								memcpy( &control_upgrade_buf[add2] ,  &data_rx_buf[8]  , PACKET_VOLUM ); 
//								control_upgrade[1] =  n4 ;        //下载进度保存
//								
//								//**  数据写入FLASH  **
//								if( add1 >= ( NUMBER_PACKET_WRITER-1 ) && ( n4>0 ) ) //缓存区写满
//								{
//									add3 = FLASH_SAVE_NEW_ADDR + ( n4 + 1 - NUMBER_PACKET_WRITER ) * PACKET_VOLUM  ;   //FLASH 缓存数据块存储地址
//									stmflash_write( add3 , (uint16_t *)control_upgrade_buf, FLASH_SAVE_RAM_LONG ); // 写入FLASH
//									memset( control_upgrade_buf , 0xff , CONTROL_UPGRADE_BUF_LONG );  //缓存初始化
//									stmflash_write( FLASH_SAVE_ADDR+3*INFORMATION_LONG , (uint16_t *)control_upgrade, CONTROL_UPGRADE);//  控制升级数据字  进度 存储
//									
//								}
//								
//								//通讯应答
//								tx_buf[6]= 0x05 ;  
//								n3 = CRC16( tx_buf , 6+1 ) ;
//								tx_buf[6+1] = n3 >>8 ;
//								tx_buf[7+1] = n3   ;
//								send_data_uart ( &huart1, tx_buf , 7+1+1 );  // 设备应答 
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
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
//int fputc(int ch, FILE *f)
//{
//	
//  HAL_UART_Transmit(&husart_debug, (uint8_t *)&ch, 1, 0xffff);
//  return ch;
//}

///**
//  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
//  * 输入参数: 无
//  * 返 回 值: 无
//  * 说    明：无
//  */
//int fgetc(FILE * f)
//{
//  uint8_t ch = 0;
//  HAL_UART_Receive(&husart_debug,&ch, 1, 0xffff);
//  return ch;
//}


//**初始化结束，开始
uint8_t model_number_buf[INFORMATION_LONG+1]={"0000000000000000\0"},
        serial_number_buf[INFORMATION_LONG+1]={"0000000000000000\0"},
		version_number_buf[INFORMATION_LONG+1]={"0000000000000000\0"} ; //产品型号；序列号；软件版本号
uint8_t model_number_new_buf[INFORMATION_LONG+1],serial_number_new_buf[INFORMATION_LONG+1],version_number_new_buf[INFORMATION_LONG+1] ; //产品型号；序列号；软件版本号
uint16_t control_upgrade[ CONTROL_UPGRADE ];  //控制升级数据字:升级状态,开始升级序号,数据包量
uint8_t  control_upgrade_buf[CONTROL_UPGRADE_BUF_LONG];  //数据包缓存
uint8_t  run_control_1=0;
//软件版本信息
const char MODEL_NUMBER_DEVICE_INFORMATION[INFORMATION_LONG+1]  ={"QJJ2024043001040\0"};	//硬件
const char SERIAL_NUMBER_DEVICE_INFORMATION[INFORMATION_LONG+1] ={"0000000000000000\0"};	//软件
const char VERSION_NUMBER_DEVICE_INFORMATION[INFORMATION_LONG+1]={"0000000000000000\0"};

void start_job(void)
{
//	uint8_t i;
	char    j[INFORMATION_LONG*4];
	HAL_Delay(10);
//	printf("\r\nHELLO,USERAPPjob is ok.\r\n");
	
	stmflash_read(FLASH_SAVE_ADDR                 ,   (uint16_t *)model_number_buf, INFORMATION_LONG/2);  //产品型号 
	
	stmflash_read(FLASH_SAVE_ADDR+INFORMATION_LONG ,  (uint16_t *)serial_number_buf, INFORMATION_LONG/2);// 序列号 
	
	stmflash_read(FLASH_SAVE_ADDR+2*INFORMATION_LONG , (uint16_t *)version_number_buf, INFORMATION_LONG/2);// 软件版本号
	
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
		
//		printf("修改信息!!");
	}
	
}

//**串口输出
uint8_t uart1_busy=0;
void send_data_uart ( UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size )
{
	while(uart1_busy)
	uart1_busy = 1 ;	
	HAL_UART_Transmit_IT( huart , pData , Size );
}
/**
  * @brief  USART发送回调执行函数
  * @param  无
  * @retval 无
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /*通过中断方式发送数据*/
  if ( UartHandle->Instance == USART1)
  {
		uart1_busy=0;  //USART发送结束
  }
}













