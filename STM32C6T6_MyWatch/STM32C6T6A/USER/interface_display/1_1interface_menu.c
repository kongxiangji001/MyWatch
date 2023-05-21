#include "1_1interface_menu.h"

_List_Set List_Set; //组态参数设

//结构体声明
struct MenuItem m0_main[1];		//一级菜单  欢迎界面
struct MenuItem m1_main[6];		//二级菜单 实时显示
struct MenuItem m2_password[3]; //三级菜单 密码输入+组态选择
struct MenuItem m3_config[4];	//四级菜单  常规组态设置

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
//实时输出显示
void Real_TimeOutput_Dis(void);
void Real_TimeOutput_KEY(int8_t key);
//密码输入
void Password_Dis(void);
void Password_KEY(int8_t key);
//常规组态设置
void Real_Config_Dis(void);
void Real_Config_KEY(int8_t key);
//校准选择
void Calibrate_Config_Dis(void);
void Calibrate_Config_KEY(int8_t key);
//组态--通道
void Real_ConfigChannel_Dis(void);
void Real_ConfigChannel_KEY(int8_t key);
//组态--输出
void Real_ConfigOutput_Dis(void);
void Real_ConfigOutput_KEY(int8_t key);
//组态--通讯
void Real_ConfigCommunicate_Dis(void);
void Real_ConfigCommunicate_KEY(int8_t key);
//组态--系统
void Real_ConfigSystem_Dis(void);
void Real_ConfigSystem_KEY(int8_t key);

//结构体实现

//一级菜单  欢迎界面
struct MenuItem m0_main[1] =
	{
		{2, 1, 0, 0, Welcom_Dis, Welcom_KEY, m1_main, 0},							//欢迎界面
//		{2, 2, 0, 0, Configuration_Table_Dis, Configuration_Table_KEY, m1_main, 0}, //功能菜单界面
};
//二级菜单 实时显示
struct MenuItem m1_main[6] =
	{
		{6, 1, 0, 0, Real_Time1_Dis, Real_Time1_KEY, m2_password, m0_main},
		{6, 2, 0, 0, Real_Time2_Dis, Real_Time2_KEY, m2_password, m0_main},
		{6, 3, 0, 0, Real_Time3_Dis, Real_Time3_KEY, m2_password, m0_main},
		{6, 4, 0, 0, Real_Time4_Dis, Real_Time4_KEY, m2_password, m0_main},
		{6, 5, 0, 0, Real_Time_Totle_Dis, Real_Time_Totle_KEY, m2_password, m0_main},
        {6, 6, 0, 0, Real_TimeOutput_Dis, Real_TimeOutput_KEY, m2_password, m0_main},
};
//三级菜单 密码输入
struct MenuItem m2_password[3] =
	{
		{3, 1, 0, 0, Password_Dis, Password_KEY, 0, m1_main},
        {3, 2, 0, 0, Real_Config_Dis, Real_Config_KEY, m3_config, m1_main},
		{3, 3, 0, 1, Calibrate_Config_Dis, Calibrate_Config_KEY, 0, m1_main},
};
    
//五级菜单  常规组态设置
struct MenuItem m3_config[4] =
	{
		{4, 1, 0, 0, Real_ConfigChannel_Dis, Real_ConfigChannel_KEY, 0, m2_password},
		{4, 2, 0, 0, Real_ConfigOutput_Dis, Real_ConfigOutput_KEY, 0, m2_password},
//		{4, 3, 0, 0, Real_ConfigCommunicate_Dis, Real_ConfigCommunicate_KEY, 0, m2_password},
//		{4, 4, 0, 0, Real_ConfigSystem_Dis, Real_ConfigSystem_KEY, 0, m2_password},
};



static struct MenuItem *manyou = m0_main; //开始的位置

//执行界面
static void Run(int8_t key)
{
	List_Set.display_shadow_flag=1-List_Set.display_shadow_flag;
	if (key != 0)
	{
        manyou->Key(key);
	}
	manyou->Subs();
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

//切换到同级上一个界面
void Same_Up(void)
{
	//寻找下一个界面的坐标
	if (manyou->Loc > 1)
	{
		manyou = (manyou - 1); //切换
	}
	else
	{
		manyou = (manyou + (manyou->MenuCount - 1)); //切换
	}
}

//同级任意一界面
void Same_Num(int8_t num)
{
    //寻找下一个界面的坐标
    if(num<manyou->MenuCount)
    {
        manyou = (manyou + (num - manyou->Loc+1)); //切换        
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

void ReturnMainInterface(void)
{
    manyou = &m0_main[0]; //开始的位置
}

uint8_t GetLeve(void)
{
    return manyou > &m1_main[4];
}

void Interface_Change(int8_t key) //界面切换  参数设定
{
    static uint8_t return_tim=0;
    if(key==16)
    {
        BSP_IO_L(POWER);
        OLED_Refresh();
        OLED_Refresh();
        while(1);
    } 
    if((!key)&&(GetLeve()))
    {
    //    return_tim++;
        if(return_tim>30)
        {//连续15秒未有按键操作
            return_tim=0;
            ReturnMainInterface();
        }
    }
    else
    {
        return_tim=0;
    }

	Run( key); //执行  指向的界面
	OLED_Refresh(); //刷新屏幕显示
}
