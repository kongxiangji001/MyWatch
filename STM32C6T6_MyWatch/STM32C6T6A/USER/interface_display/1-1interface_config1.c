
#include "0_1interface_menu.h"



//功能配置界面
void Real_Config1_Dis(void)
{
    OLED_ShowNum(0,0,11,10,24,0);
    OLED_Refresh();

}

void Real_Config1_KEY(int8_t key)
{	
	switch (key) //根据按键键值  执行
	{
		case 1://按键1    右
		{
			
			Same_Next();
		}break;
		case 2://按键2  下
		{		
			
          
			
		}break;
		case 3://按键3   左
		{
			Retern_Up(0);
			
		}break;
		case 4://按键4 	确认	
		{
			
		}break;
		case 5://按键5   上
		{
			
		
		}break;
	
		case 6://按键6    取消
		{
			
		}break;
	}
}

