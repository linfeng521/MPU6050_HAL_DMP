/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
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
/* USER CODE BEGIN PFP */
float Pitch;
float Roll;
float Yaw;
int temp;
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	while(w_mpu_init() != mpu_ok)
  {
	  printf("0x%x (ID_ERROR)\r\n", w_mpu_init());
		printf("a%.1fb%.1fc%.1f",mpu_pose_msg.pitch,mpu_pose_msg.roll,mpu_pose_msg.yaw);
	  HAL_Delay(100);
  }
	dmp_init();		//dmp初始化
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		read_dmp(&mpu_pose_msg);//读取mpu姿态
		w_mpu_read_all_raw_data(&mpu_raw_msg); //读取mpu6050有原始数据mpu_raw_msg.mpu_acce[0]
		printf("Pitch: %f\t ", mpu_pose_msg.pitch);
		printf("Roll:  %f\t ", mpu_pose_msg.roll);
		printf("Yaw:   %f\t ", mpu_pose_msg.yaw);
		printf("\r\n");
		HAL_Delay(100);
//******************************************原始数据读取********************************************************************************
//	  OLED_ShowString(0,3,"Ax:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_acce[0], 1, 20, 0);//XYZ轴加速度�?????????
//	  OLED_ShowString(0,18,"Ay:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_acce[1], 1, 20, 15);
//	  OLED_ShowString(0,33,"Az:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_acce[2], 1, 20, 30);



//	  OLED_ShowString(0,3,"Gx:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_gyro[0], 1, 20, 0);//XYZ轴陀螺仪�?????????
//	  OLED_ShowString(0,18,"Gy:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_gyro[1], 1, 20, 15);
//	  OLED_ShowString(0,33,"Gz:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_gyro[2], 1, 20, 30);
//



//******************************************DMP解算值********************************************************************************
//	  OLED_ShowString(0,3,"Pitch:");
//	  OLED_ShowFloat(mpu_pose_msg.pitch, 1, 50, 0);//XYZ轴陀螺仪�?????????
//	  OLED_ShowString(0,18,"Roll:");
//	  OLED_ShowFloat(mpu_pose_msg.roll, 1, 50, 15);
//	  OLED_ShowString(0,33,"Yaw:");
//	  OLED_ShowFloat(mpu_pose_msg.yaw, 1, 50, 30);

//	  OLED_ShowString(0,48,"Temp:");
//	  OLED_ShowFloat(mpu_raw_msg.mpu_temperature, 1, 50, 45);//温度
//  	HAL_Delay(100);
//  	OLED_Refresh_Gram();

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
}

/* USER CODE BEGIN 4 */

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
