#include "main.h"
#include "API_uart.h"
#include "API_debounce.h"
#include "API_delay.h"

#define LED_GREEN_INITIAL_BLINK_DELAY_MS 	100
#define LED_BLUE_INITIAL_BLINK_DELAY_MS 	500
#define LED_RED_INITIAL_BLINK_DELAY_MS 		1000

#define LED_GREEN_ALTERED_BLINK_DELAY_MS	500
#define LED_BLUE_ALTERED_BLINK_DELAY_MS 	500
#define LED_RED_ALTERED_BLINK_DELAY_MS 		500

static void SystemClock_Config(void);
static void Error_Handler(void);
void customErrorHandler(void);

int main(void)
{
	HAL_Init();

	SystemClock_Config();

	BSP_LED_Init(LED_GREEN);
	BSP_LED_Init(LED_BLUE);
	BSP_LED_Init(LED_RED);

	delay_t greenLedDelay;
	delay_t blueLedDelay;
	delay_t redLedDelay;

	bool_t initialBlinking = true;

	//uint32_t lastPressCount = 0;

	configureDelayErrorHandler(&customErrorHandler);

	delayInit (&greenLedDelay, LED_GREEN_INITIAL_BLINK_DELAY_MS);
	delayInit (&blueLedDelay, LED_BLUE_INITIAL_BLINK_DELAY_MS);
	delayInit (&redLedDelay, LED_RED_INITIAL_BLINK_DELAY_MS);

	uartInit();
	debounceInit();

	while (1)
	{
		if (delayRead(&greenLedDelay))
		{
			BSP_LED_Toggle(LED_GREEN);
		}

		if (delayRead(&blueLedDelay))
		{
			BSP_LED_Toggle(LED_BLUE);
		}

		if (delayRead(&redLedDelay)){
			BSP_LED_Toggle(LED_RED);
		}

		debounceUpdate();

		if (consumeSinglePressEvent())
		{
			if (initialBlinking)
			{
				delayWrite (&greenLedDelay,LED_GREEN_ALTERED_BLINK_DELAY_MS);
				delayWrite (&blueLedDelay,LED_BLUE_ALTERED_BLINK_DELAY_MS);
				delayWrite (&redLedDelay,LED_RED_ALTERED_BLINK_DELAY_MS);
				initialBlinking = false;

				printf("Alternative Blinking\n\r");
			}
			else
			{
				delayWrite (&greenLedDelay,LED_GREEN_INITIAL_BLINK_DELAY_MS);
				delayWrite (&blueLedDelay,LED_BLUE_INITIAL_BLINK_DELAY_MS);
				delayWrite (&redLedDelay,LED_RED_INITIAL_BLINK_DELAY_MS);
				initialBlinking = true;
				printf("*Initial Blinking*\n\r");
			}
		}
		//lastPressCount = buttonPressedCount();
	}
}

void customErrorHandler()
{
	  /* Turn LED2 on */
	  BSP_LED_On(LED_RED);
	  while (1)
	  {
	  }
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
