#ifndef _menu_interface_H
#define _menu_interface_H

#include "stm32f1xx_hal.h"
//#include "dr_display.h"
#include "oled.h"
//组态设置过程参数
typedef struct 
{
	int16_t set_loc1;
	int16_t set_loc2;
	int16_t summ;
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

void Interface_Change(int8_t key);//切换界面
void Enter_Next(int8_t lev);//进入下一级菜单
void Retern_Up(int8_t lev);//返回上一级菜单
void Same_Next(void);//切换到同级下一个界面
void Interface_Change(int8_t key);//切换界面
void Retur_Main(void);//返回主菜单
void Same_Num(int8_t num);//同级任意一界面
int8_t Get_Leve(void);

#endif
