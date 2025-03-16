#ifndef __WS2812_H
#define __WS2812_H

#include "main.h"


void led_set(uint8_t led_id, uint8_t value_r, uint8_t value_g, uint8_t value_b);

void Set_LED_Mode0(void);

//设置跑马灯颜色
void Led1_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led2_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led3_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led4_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led5_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led6_Set_Running(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
//设置环形灯颜色
void Led1_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led2_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led3_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led4_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led5_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led6_Set_Cycle(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);

void Led2_Set_Buffer(void);
void Led3_Set_Buffer(void);
void Led4_Set_Buffer(void);
void Led5_Set_Buffer(void);
void Led6_Set_Buffer(void);
void Led1_On(void);
void Led2_On(void);
void Led3_On(void);
void Led4_On(void);
void Led5_On(void);
void Led6_On(void);
void Led_On(void);
void Led_On_Same(void);

void Led_All_Off(void);

//清除所有亮灯点位
void Clear_All_Led_Array(void);

//设置所有条形灯点位
void Set_Led_Line_Array(unsigned char channel, unsigned char on_off);
//设置条形灯奇数点位
void Set_Led_Line_Odd_Array(unsigned char channel, unsigned char on_off);
//设置所有环形灯点位
void Set_Led_Cycle_Array(unsigned char channel, unsigned char on_off);
//设置环形灯奇数点位
void Set_Led_Cycle_Odd_Array(unsigned char channel, unsigned char on_off);
//设置所有灯点位
void Set_Led_All_Array(unsigned char channel, unsigned char on_off);
//设置奇数灯点位
void Set_Led_Odd_Array(unsigned char channel, unsigned char on_off);

//模式1指示灯固定显示
void Led_On_Mode1(unsigned char BT_Connect);

//模式4-4~4-6
void Set_LED_Mode4_Running(unsigned char channel, unsigned char led_start, unsigned char led_end);

//模式0的第1步
void Led_On_Mode0_Step1(void);

//模式0的第2步
void Led_On_Mode0_Step2(void);

//模式0的第3步
void Led_On_Mode0_Step3(void);

#endif

