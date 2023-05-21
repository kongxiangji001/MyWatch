#ifndef _1_1menu_interface_H
#define _1_1menu_interface_H

#include "stm32f1xx_hal.h"
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"


//#include "app_config.h"
//#include "stdio.h"
//#include "string.h"
//#include "app_rtc.h"
//#include "dr_pwm.h"

//组态设置过程参数
typedef struct 
{
	int8_t display_shadow_flag;//阴影显示  
    int8_t ok;//是否进行参数选择  选中要修改参数时置1
    int8_t config_shade;//菜单选择   4宫格
    int8_t sys1_0_shade;//菜单参数 选择参数
    int8_t sys2_0_shade;//菜单参数 选择参数内容
    int8_t switch_shade;//菜单参数 选择参数内容
    int8_t data_wei;// 设置参数时移位
    int8_t font;//菜单参数选择   具体菜单项使用
    int8_t font_sum;//菜单参数的总个数
    int8_t font_sum2;//参数总数，输入通道有3个通道
    int8_t ok_num;//参数选择  阴影和参数选择的和
	
    int16_t i16_copy;
    float float_copy;
}_List_Set;

//结构体类型定义 
struct MenuItem     
{  
	const int8_t MenuCount; //结构体数组的元素个数 
	const int8_t Loc; //每个界面的固定位置
	int8_t RunLoc;//正在运行的界面
	int8_t Button_Loc; //按键所在位置  键码值
	void (*Subs)();  //执行的函数的指针. 
	void (*Key)(int8_t);  //执行的函数的指针. 
	struct MenuItem *Childrenms;  //指向子节点的指针 
	struct MenuItem *Parentms;  //指向父节点的指针 
}; 

extern _List_Set List_Set;//组态参数设
extern uint8_t CalibrateRunFlag;//校准标志位

void Interface_Change(int8_t key);//切换界面
void Enter_Next(int8_t lev);//进入下一级菜单
void Retern_Up(int8_t lev);//返回上一级菜单
void Same_Next(void);//切换到同级下一个界面
void Same_Up(void);//切换到同级上一个界面
void Interface_Change(int8_t key);//切换界面
void Retur_Main(void);//返回主菜单
void Same_Num(int8_t num);//同级任意一界面
int8_t Get_Leve(void);

#endif
