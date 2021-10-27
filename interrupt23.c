
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void Error_Handler(void);

void uart_init();
int main(void)
{
	long i=0;
	SystemClock_Config();
	uart_init();
	NVIC_SetPriority(USART1_IRQn, 0);
	    NVIC_EnableIRQ(USART1_IRQn);
	for(;;)
	{
		//while(!(USART1->SR&(1<<7)));


	}
}
void USART1_IRQHandler(void)
{
	int i;
	USART1->DR='j';
			while(!(USART1->SR&(1<<6)));
			for(i=0;i<=100000;i++);
}
void uart_init()
{

	RCC->APB2ENR=(1<<4);
	RCC->AHB1ENR=1;
	GPIOA->MODER=(1<<19);
	GPIOA->OTYPER=0;
	GPIOA->AFR[1]=(7<<4)|(7<<8);
	GPIOA->OSPEEDR=~0;
	USART1->CR2=0;
	USART1->CR3=0;

	USART1->CR1=(1<<13)|(1<<3)|(1<<2)|(1<<15)|(1<<7);
	USART1->BRR=(937<<4)|4;
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
