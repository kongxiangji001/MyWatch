/***
 * @Author: g753388438
 * @Date: 2022-04-02 21:09:35
 * @LastEditTime: 2022-04-05 20:35:27
 * @LastEditors: g753388438
 * @Description: 界面切换
 * @Version: Ver1.0
 * @FilePath: \MDK-ARMf:\BIBL\01Stm32SmallProject\STM32F103C_SSS\Project\stm32f103c8\STM32F103C_SSS\USER\interfacedisplay\interface_menu.c
 * @Company:
 * @版权所有,盗版必究。
 */
#include "0_1interface_menu.h"
#include "dr_gpio.h"
#include "stdio.h"

_List_Set List_Set; //组态参数设

//结构体声明
struct MenuItem m0_main[2];		//一级菜单  欢迎界面
struct MenuItem m1_main[5];		//二级菜单 实时显示
struct MenuItem m2_password[1]; //三级菜单 密码输入
struct MenuItem m4_config[4];	//四级菜单  组态设置

//欢迎界面
void Welcom_Dis(void);
void Welcom_KEY(int8_t key);
//设备配置列表
void Configuration_Table_Dis(void);
void Configuration_Table_KEY(int8_t key);
//实时曲线1
void Real_Time1_Dis(void);
void Real_Time1_KEY(int8_t key);
//实时曲线2
void Real_Time2_Dis(void);
void Real_Time2_KEY(int8_t key);
//实时曲线3
void Real_Time3_Dis(void);
void Real_Time3_KEY(int8_t key);
//实时曲线4
void Real_Time4_Dis(void);
void Real_Time4_KEY(int8_t key);
//实时数据汇总
void Real_Time_Totle_Dis(void);
void Real_Time_Totle_KEY(int8_t key);
//密码输入
void Password_Dis(void);
void Password_KEY(int8_t key);
//组态设置
void Real_Config1_Dis(void);
void Real_Config1_KEY(int8_t key);
//组态设置
void Real_Config2_Dis(void);
void Real_Config2_KEY(int8_t key);
//组态设置
void Real_Config3_Dis(void);
void Real_Config3_KEY(int8_t key);
//组态设置
void Real_Config4_Dis(void);
void Real_Config4_KEY(int8_t key);

//结构体实现

//一级菜单  欢迎界面
struct MenuItem m0_main[2] =
	{
		{2, 1, 0, 0, Welcom_Dis, Welcom_KEY, m1_main, 0},							//欢迎界面
		{2, 2, 0, 0, Configuration_Table_Dis, Configuration_Table_KEY, m1_main, 0}, //功能菜单界面
};
//二级菜单 实时显示
struct MenuItem m1_main[5] =
	{
		{5, 1, 0, 0, Real_Time1_Dis, Real_Time1_KEY, m2_password, m0_main},
		{5, 2, 0, 0, Real_Time2_Dis, Real_Time2_KEY, m2_password, m0_main},
		{5, 3, 0, 0, Real_Time3_Dis, Real_Time3_KEY, m2_password, m0_main},
		{5, 4, 0, 0, Real_Time4_Dis, Real_Time4_KEY, m2_password, m0_main},
		{5, 5, 0, 0, Real_Time_Totle_Dis, Real_Time_Totle_KEY, m2_password, m0_main},
};
//三级菜单 密码输入
struct MenuItem m2_password[1] =
	{
		{1, 1, 0, 0, Password_Dis, Password_KEY, m4_config, m1_main},
};
//四级菜单  组态设置
struct MenuItem m4_config[4] =
	{
		{4, 1, 0, 0, Real_Config1_Dis, Real_Config1_KEY, 0, m2_password},
		{4, 2, 0, 0, Real_Config2_Dis, Real_Config2_KEY, 0, m2_password},
		{4, 3, 0, 0, Real_Config3_Dis, Real_Config3_KEY, 0, m2_password},
		{4, 4, 0, 0, Real_Config4_Dis, Real_Config4_KEY, 0, m2_password},
};

static struct MenuItem *manyou = m0_main; //开始的位置

//执行界面
static void Run(struct MenuItem *many, int8_t key)
{
	if (key != 0)
	{
		(*(many->Key))(key); //执行当前指向函数按键
	}

	(*(manyou->Subs))(manyou); //执行当前指向函数
}

//切换到同级下一个界面
void Same_Next(void)
{
	//寻找下一个界面的坐标
	if (manyou->Loc < (manyou->MenuCount))
	{
		manyou = (manyou + 1); //切换
	}
	else
	{
		manyou = (manyou - (manyou->MenuCount - 1)); //切换
	}
}

//进入下一级菜单的第几个界面
void Enter_Next(int8_t lev)
{
	if (manyou->Childrenms != 0)
	{ //进入下一级菜单
		if (lev < manyou->Childrenms->MenuCount)
		{
			manyou->Childrenms->RunLoc = manyou->Loc; //记录上一级时的所在界面
			manyou = (manyou->Childrenms + lev);
		}
	}
}

//返回上一级菜单的第几个界面
void Retern_Up(int8_t lev)
{
	if (manyou->Parentms != 0)
	{ //返回上一级菜单
		if ((lev < manyou->Parentms->MenuCount) || (lev == 99))
		{
			manyou->Button_Loc = 0; //按键归位
			if (lev == 99)
			{
				manyou = (manyou->Parentms + manyou->RunLoc - 1);
			}
			else
			{
				manyou = (manyou->Parentms + lev);
			}
		}
	}
}

void Interface_Change(int8_t key) //界面切换  参数设定
{
    if(key==11)
    {
        BSP_IO_L(POWER);
    } 
	Run(manyou, key); //执行  指向的界面
    snprintf(LCD_CACHE,20,"%d",key);
    Oled_Disp_String(100,0,LCD_CACHE);   
	DisplayRefresh(); //刷新屏幕显示
}
