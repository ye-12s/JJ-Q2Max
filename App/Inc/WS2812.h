#ifndef __WS2812_H
#define __WS2812_H

#include "main.h"

void Set_LED_Mode_pwm(uint8_t  pwm);

void led_set(uint8_t led_id, uint8_t value_r, uint8_t value_g, uint8_t value_b);

void Set_LED_Mode0(void);
//待机灯光颜色设置
void Led1_Set_Running_color(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led2_Set_Running_color(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led3_Set_Running_color(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led4_Set_Running_color(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led5_Set_Running_color(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led6_Set_Running_color(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);

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

//灭灯
void Led1_Set_Run(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led2_Set_Run(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led3_Set_Run(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led4_Set_Run(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led5_Set_Run(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);
void Led6_Set_Run(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B);

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

/*	待机light*/
void Stanley_Mode5_Light1(void);
void Stanley_Mode5_Light2(void);
void Stanley_Mode5_Light3(void);
void Stanley_Mode5_Light4(void);
void Stanley_Mode5_Light5(void);

//灯光效果模式
void Led_On_light(void);

//灯光效果模式		静态					20240604
void Led_On_light(void);
void Led_On_light1(void);
void Led_On_light2(void);
void Led_On_light3(void);
void Led_On_light4(void);
void Led_On_light5(void);
void Led_On_light6(void);
void Led_On_light7(void);
void Led_On_light8(void);
void Led_On_light9(void);

//rgb2hsv
unsigned char RGB_to_HSV(unsigned char Color_R, unsigned char Color_G, unsigned char Color_B,float *h,float *s,float *v);
//hsb2rgb
unsigned char HSV_to_RGB(unsigned char* Color_R, unsigned char *Color_G, unsigned char *Color_B,float h,float s,float v);

#endif

