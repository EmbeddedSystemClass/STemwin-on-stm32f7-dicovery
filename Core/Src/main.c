/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "crc.h"
#include "dcmi.h"
#include "eth.h"
#include "fatfs.h"
#include "gfxsimulator.h"
#include "i2c.h"
#include "quadspi.h"
#include "rng.h"
#include "rtc.h"
#include "sai.h"
#include "sdmmc.h"
#include "spdifrx.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_ts.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
void MX_FREERTOS_Init(void);
extern void GRAPHICS_HW_Init(void);
extern void GRAPHICS_Init(void);
extern void GRAPHICS_MainTask(void);
/* USER CODE BEGIN PFP */
void TouchTimer_Init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
//  SCB_EnableDCache();

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
  MX_ADC3_Init();
  MX_CRC_Init();
  MX_DCMI_Init();
//  MX_ETH_Init();    // Slow
  MX_GFXSIMULATOR_Init();
  MX_I2C1_Init();
  MX_I2C3_Init();
  MX_QUADSPI_Init();
  MX_RTC_Init();
  MX_SAI2_Init();
  MX_SDMMC1_SD_Init();
  MX_SPDIFRX_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM12_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

  TouchTimer_Init();

  printf("Hi\n");

  /* USER CODE END 2 */

/* Initialise the graphical hardware */
  GRAPHICS_HW_Init();

  /* Initialise the graphical stack engine */
  GRAPHICS_Init();
      
  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();



  
//  GUI_SetBkColor(GUI_BLACK);
//  GUI_Clear();
//
//  GUI_AA_EnableGammaAA4(GUI_AA_TRANS);
//  GUI_AA_EnableHiRes();
//
//  GUI_EnableAlpha(0);
////  GUI_SetAlpha(0xe0);
////  GUI_SetUserAlpha();
//
//  int aa = 4;
//  GUI_AA_SetFactor(aa);
//
//  GUI_AA_EnableHiRes();
//  GUI_AA_SetDrawMode(GUI_AA_NOTRANS);
//
//  GUI_SetColor(GUI_RED);
//  GUI_SetFont(&GUI_Font16_1);
//  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-80)/2);
//
//  GUI_SetColor(GUI_GREEN);
//  GUI_SetFont(&GUI_Font24_1);
//  GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
//
//  GUI_SetColor(GUI_BLUE);
//  GUI_SetFont(&GUI_FontD80);
//  GUI_DispStringAt("0123456789", (LCD_GetXSize()-200)/2, (LCD_GetYSize()+60)/2);
//
////  GUI_Delay(100);
//  GUI_SetColor(GUI_WHITE);
//  GUI_SetFont(&GUI_Font16_1);
//  for (uint16_t y = 0; y < LCD_GetYSize(); y+=20)
//  {
////    GUI_Delay(100);
//    GUI_DispStringAt("Hello world!", 10, y+10);
//  }
//
//
//  GUI_AA_SetGammaAA4(0x40);
//
//  GUI_SetPenSize(20);
//
//  GUI_SetColor(GUI_LIGHTRED);
//  GUI_AA_DrawLine(40, 40, LCD_GetXSize()*aa - 40, LCD_GetYSize()*aa - 40);
//  GUI_AA_DrawLine(40, LCD_GetYSize()*aa - 40, LCD_GetXSize()*aa - 40, 40);
////  GUI_DrawLine(10, LCD_GetYSize() - 10, LCD_GetXSize() - 10, 10);
//
//  GUI_SetColor(GUI_LIGHTGREEN);
////  GUI_DrawCircle(LCD_GetXSize()/2, LCD_GetYSize()/2, 80);
////  GUI_AA_DrawCircle(LCD_GetXSize()/2*aa, LCD_GetYSize()/2*aa, 80*aa);
//  GUI_AA_DrawArc(LCD_GetXSize()/2*aa, LCD_GetYSize()/2*aa, 80*aa, 80*aa, 0, 270);
//
//
//  GUI_SetColor(GUI_LIGHTBLUE);
//  GUI_AA_FillCircle(LCD_GetXSize()/4*aa, LCD_GetYSize()/2*aa, 35*aa);
//
////  GUI_SetColor(GUI_LIGHTMAGENTA);
//  GUI_SetColor(0xFFFF80FF);
//
////  GUI_AA_FillRoundedRect(200*aa, 100*aa, 280*aa, 156*aa, 10*aa);
//  GUI_AA_DrawRoundedRect(200*aa, 100*aa, 280*aa, 156*aa, 10*aa);
//
////  GUI_DrawPixel(240, 20);
//
///* USER CODE END GRAPHICS_MainTask */
//  while(1)
//  {
//    int x = rand() % 480;
//    int y = rand() % 272;
//    uint8_t r = rand() % 255;
//    uint8_t g = rand() % 255;
//    uint8_t b = rand() % 255;
//    uint32_t color = 0xff000000 | (r << 16) | (g << 8) | b;
//    GUI_SetColor(color);
//    GUI_DispStringAt("Hello world!", x, y);
//
//    GUI_Delay(100);
//  }


  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    PollTouchScreen2();
//    dmc_putc('.');

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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPDIFRX|RCC_PERIPHCLK_LTDC
                              |RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_USART6|RCC_PERIPHCLK_SAI2
                              |RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C3
                              |RCC_PERIPHCLK_SDMMC1|RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 100;
  PeriphClkInitStruct.PLLI2S.PLLI2SP = RCC_PLLP_DIV2;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PLLI2SDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInitStruct.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLLSAI;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void TouchTimer_Init()
{
  BSP_TS_Init(480, 272);

  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    while(1);
  }
  if (HAL_TIM_Base_Start_IT(&htim3) != HAL_OK)
  {
    while(1);
  }
}

void PollTouchScreen2(void)
{
  GUI_PID_STATE TS_State;               /* Structure that reports the touch state to STemWin */
  static TS_StateTypeDef prev_state;    /* Previous touch state from the touch sensor used from BSP package */
  TS_StateTypeDef ts;                   /* Actual touch state from the touch sensor used from BSP package */
  BSP_TS_GetState(&ts);                 /* Read the touch state from touch sensor (BSP API) */
  TS_State.Pressed = ts.touchDetected;  /* Store pressed state to STemWin structure */

  if (prev_state.touchDetected != ts.touchDetected)
  {
//    dmc_putc('.');
    prev_state.touchDetected != ts.touchDetected;
    /* Check touch variations */
    if((ts.touchX[0] != 0) &&  (ts.touchY[0] != 0))
    {
      prev_state.touchX[0] = ts.touchX[0];
      prev_state.touchY[0] = ts.touchY[0];
    }
    TS_State.Layer = 0;
    TS_State.x = prev_state.touchX[0];
    TS_State.y = prev_state.touchY[0];

    dmc_putint((uint16_t)TS_State.x);
    dmc_putc(' ');
    dmc_putint((uint16_t)TS_State.y);
    dmc_putcr();

    /* Send touch state to STemWin */
    GUI_TOUCH_StoreStateEx(&TS_State);

  }
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
//    PollTouchScreen();
//    dmc_putc('.');
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM3) {
//    PollTouchScreen();
//    dmc_putc('.');
  }

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
