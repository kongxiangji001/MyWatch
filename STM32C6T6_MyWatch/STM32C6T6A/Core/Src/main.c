/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "oled.h"
#include "bmp.h"
#include "multi_button.h"
int fputc(int ch, FILE *f)
{
 uint8_t temp[1] = {ch};
 HAL_UART_Transmit(&huart1, temp, 1, 2);
 return ch;
}
uint32_t num;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void BTN1_PRESS_DOWN_Handler(void* btn);
void BTN1_PRESS_UP_Handler(void* btn);
void BTN2_PRESS_DOWN_Handler(void* btn);
void BTN2_PRESS_UP_Handler(void* btn);
void BTN3_PRESS_DOWN_Handler(void* btn);
void BTN3_PRESS_UP_Handler(void* btn);
void BTN4_PRESS_DOWN_Handler(void* btn);
void BTN4_PRESS_UP_Handler(void* btn);
void BTN5_PRESS_DOWN_Handler(void* btn);
void BTN5_PRESS_UP_Handler(void* btn);
void BTN6_PRESS_DOWN_Handler(void* btn);
void BTN6_PRESS_UP_Handler(void* btn);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static button btn1; //定义按键1
static button btn2; //定义按键2
static button btn3; //定义按键3
static button btn4; //定义按键4
static button btn5; //定义按键5
static button btn6; //定义按键6
uint8_t read_button1_GPIO() 
{
	return HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
}

uint8_t read_button2_GPIO() 
{
	return HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
}
uint8_t read_button3_GPIO() 
{
	return HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
}
uint8_t read_button4_GPIO() 
{
	return HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin);
}
uint8_t read_button5_GPIO() 
{
	return HAL_GPIO_ReadPin(BUTTON5_GPIO_Port, BUTTON5_Pin);
}
uint8_t read_button6_GPIO() 
{
	return HAL_GPIO_ReadPin(BUTTON6_GPIO_Port, BUTTON6_Pin);
}
uint8_t key_num = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  //MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */
  //uint8_t t=' ';
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示


	button_init(&btn1, read_button1_GPIO, 1);
	button_init(&btn2, read_button2_GPIO, 1);
	button_init(&btn3, read_button3_GPIO, 1);
	button_init(&btn4, read_button4_GPIO, 1);
	button_init(&btn5, read_button5_GPIO, 1);
	button_init(&btn6, read_button6_GPIO, 1);
	button_attach(&btn1, PRESS_DOWN,       BTN1_PRESS_DOWN_Handler);
	button_attach(&btn1, PRESS_UP,         BTN1_PRESS_UP_Handler);
	button_attach(&btn2, PRESS_DOWN,       BTN2_PRESS_DOWN_Handler);
	button_attach(&btn2, PRESS_UP,         BTN2_PRESS_UP_Handler);
	button_attach(&btn3, PRESS_DOWN,       BTN3_PRESS_DOWN_Handler);
	button_attach(&btn3, PRESS_UP,         BTN3_PRESS_UP_Handler);
	button_attach(&btn4, PRESS_DOWN,       BTN4_PRESS_DOWN_Handler);
	button_attach(&btn4, PRESS_UP,         BTN4_PRESS_UP_Handler);
	button_attach(&btn5, PRESS_DOWN,       BTN5_PRESS_DOWN_Handler);
	button_attach(&btn5, PRESS_UP,         BTN5_PRESS_UP_Handler);
	button_attach(&btn6, PRESS_DOWN,       BTN6_PRESS_DOWN_Handler);
	button_attach(&btn6, PRESS_UP,         BTN6_PRESS_UP_Handler);
	//button_attach(&btn1, PRESS_REPEAT,     BTN1_PRESS_REPEAT_Handler);
	//button_attach(&btn1, SINGLE_CLICK,     BTN1_SINGLE_Click_Handler);
	//button_attach(&btn1, DOUBLE_CLICK,     BTN1_DOUBLE_Click_Handler);
	//button_attach(&btn1, LONG_RRESS_START, BTN1_LONG_RRESS_START_Handler);
	//button_attach(&btn1, LONG_PRESS_HOLD,  BTN1_LONG_PRESS_HOLD_Handler);
	//
	//button_attach(&btn2, PRESS_DOWN,       BTN2_PRESS_DOWN_Handler);
	//button_attach(&btn2, PRESS_UP,         BTN2_PRESS_UP_Handler);
	//button_attach(&btn2, PRESS_REPEAT,     BTN2_PRESS_REPEAT_Handler);
	//button_attach(&btn2, SINGLE_CLICK,     BTN2_SINGLE_Click_Handler);
	//button_attach(&btn2, DOUBLE_CLICK,     BTN2_DOUBLE_Click_Handler);
	//button_attach(&btn2, LONG_RRESS_START, BTN2_LONG_RRESS_START_Handler);
	//button_attach(&btn2, LONG_PRESS_HOLD,  BTN2_LONG_PRESS_HOLD_Handler);
	button_start(&btn1);
	button_start(&btn2);
	button_start(&btn3);
	button_start(&btn4);
	button_start(&btn5);
	button_start(&btn6);
	//make the timer invoking the button_ticks() interval 5ms.
	//This function is implemented by yourself.
	//__timer_start(button_ticks, 0, 5); 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//printf("Hello World!\r\n");
    button_ticks();

    num++;
    OLED_ShowNum(0,0,num,10,24,0);
    OLED_Refresh();
		//OLED_ShowPicture(0,0,128,64,BMP1,1);
		//OLED_Refresh();
		//HAL_Delay(500);
		//OLED_Clear();
		//OLED_ShowChinese(0,0,0,16,1);//中
		//OLED_ShowChinese(18,0,1,16,1);//景
		//OLED_ShowChinese(36,0,2,16,1);//园
		//OLED_ShowChinese(54,0,3,16,1);//电
		//OLED_ShowChinese(72,0,4,16,1);//子
		//OLED_ShowChinese(90,0,5,16,1);//技
		//OLED_ShowChinese(108,0,6,16,1);//术
		//OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
		//OLED_ShowString(20,32,"2014/05/01",16,1);
		//OLED_ShowString(0,48,"ASCII:",16,1);  
		//OLED_ShowString(63,48,"CODE:",16,1);
		//OLED_ShowChar(48,48,t,16,1);//显示ASCII字符	   
		//t++;
		//if(t>'~')t=' ';
		//OLED_ShowNum(103,48,t,3,16,1);
		//OLED_Refresh();
		//HAL_Delay(500);
		//OLED_Clear();
		//OLED_ShowChinese(0,0,0,16,1);  //16*16 中
		//OLED_ShowChinese(16,0,0,24,1); //24*24 中
		//OLED_ShowChinese(24,20,0,32,1);//32*32 中
		//OLED_ShowChinese(64,0,0,64,1); //64*64 中
		//OLED_Refresh();
		//HAL_Delay(500);
		//OLED_Clear();
		//OLED_ShowString(0,0,"ABC",8,1);//6*8 “ABC”
		//OLED_ShowString(0,8,"ABC",12,1);//6*12 “ABC”
		//OLED_ShowString(0,20,"ABC",16,1);//8*16 “ABC”
		//OLED_ShowString(0,36,"ABC",24,1);//12*24 “ABC”
		//OLED_Refresh();
		//HAL_Delay(500);
		//OLED_ScrollDisplay(11,4,1);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void BTN1_PRESS_DOWN_Handler(void* btn)
{
	//do something...
  printf("button1 down!\r\n");
  OLED_ShowPicture(0,0,128,64,BMP1,1);
  OLED_Refresh();
  key_num = 1;
}
void BTN1_PRESS_UP_Handler(void* btn)
{
	//do something...
  printf("button1 up!\r\n");
}

void BTN2_PRESS_DOWN_Handler(void* btn)
{
	//do something...
  printf("button2 down!\r\n");
  OLED_ShowPicture(0,0,128,64,BMP2,1);
  OLED_Refresh();
  key_num = 2;
}
void BTN2_PRESS_UP_Handler(void* btn)
{
	//do something...
  printf("button2 up!\r\n");
}

void BTN3_PRESS_DOWN_Handler(void* btn)
{
	//do something...
  printf("button3 down!\r\n");
  OLED_ShowPicture(0,0,128,64,BMP2,1);
  OLED_Refresh();
  key_num = 3;
}
void BTN3_PRESS_UP_Handler(void* btn)
{
	//do something...
  printf("button3 up!\r\n");
}

void BTN4_PRESS_DOWN_Handler(void* btn)
{
	//do something...
  printf("button4 down!\r\n");
  OLED_ShowPicture(0,0,128,64,BMP2,1);
  OLED_Refresh();
  key_num = 4;
}
void BTN4_PRESS_UP_Handler(void* btn)
{
	//do something...
  printf("button4 up!\r\n");
}

void BTN5_PRESS_DOWN_Handler(void* btn)
{
	//do something...
  printf("button5 down!\r\n");
  OLED_ShowPicture(0,0,128,64,BMP2,1);
  OLED_Refresh();
  key_num = 5;
}
void BTN5_PRESS_UP_Handler(void* btn)
{
	//do something...
  printf("button5 up!\r\n");
}


void BTN6_PRESS_DOWN_Handler(void* btn)
{
	//do something...
  printf("button6 down!\r\n");
  OLED_ShowPicture(0,0,128,64,BMP2,1);
  OLED_Refresh();
  key_num = 6;
}
void BTN6_PRESS_UP_Handler(void* btn)
{
	//do something...
  printf("button6 up!\r\n");
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
