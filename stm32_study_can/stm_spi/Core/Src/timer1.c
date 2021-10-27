/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"

#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void Error_Handler(void);
void gpio_init();
void timer_init();
unsigned char seg[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xe6};
int main(void)
{
	int i=0,j,k;
	SystemClock_Config();
	gpio_init();
	timer_init();
	for(;;)
	{
		for(i=0;i<10;i++)
		{
			for(j=0;j<10;j++)
			{
				for(k=0;k<=499;k++)
				{
				GPIOD->ODR=1;
				GPIOG->ODR=seg[i];
				while((TIM1->SR&1)==0);
				TIM1->SR&=~1;
				GPIOD->ODR=2;
				GPIOG->ODR=seg[j];
				while((TIM1->SR&1)==0);
				TIM1->SR&=~1;
				}
			}
		}




	}
}
void timer_init()
{
	RCC->APB2ENR|=1;
	TIM1->PSC=7200;
	TIM1->ARR=10000;
	TIM1->CR1=1;


}
void gpio_init()
{
	RCC->AHB1ENR|=1<<6|1<<3;
	GPIOG->MODER=0x55555555;
	GPIOG->OTYPER=0;
	GPIOG->OSPEEDR=0;
	GPIOD->MODER=0x55555555;
	GPIOD->OTYPER=0;
	GPIOD->OSPEEDR=0;
}
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	  /** Configure the main internal regulator output voltage
	  */
	  __HAL_RCC_PWR_CLK_ENABLE();
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
	  /** Initializes the RCC Oscillators according to the specified parameters
	  * in the RCC_OscInitTypeDef structure.
	  */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLM = 4;
	  RCC_OscInitStruct.PLL.PLLN = 72;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 3;
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
	  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	  PeriphClkInitStruct.PLLSAI.PLLSAIN = 50;
	  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
	  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

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
