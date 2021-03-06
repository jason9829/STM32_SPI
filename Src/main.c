
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "RCC.h"
#include "SPI.h"
#include "GPIO.h"
#include "USART.h"
#include <stdarg.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define MAX_BUFFER_SIZE	512
char uartPrintBuffer[MAX_BUFFER_SIZE];

void uartPrintf(char *message, ...){
	va_list args;
	int length, i;

	va_start(args, message);
	length = vsnprintf(uartPrintBuffer, 0, message, args);

	if(length > MAX_BUFFER_SIZE - 1){
		length = MAX_BUFFER_SIZE - 1;
	}

	vsnprintf(uartPrintBuffer, length +1, message, args);

	for(i = 0; i < length; i++){
		while(!(usartIsTxRegEmpty(uart5)));
		(uart5)->DR = uartPrintBuffer[i];
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint16_t temperature[128];

	uint16_t temp = 0;
	int i = 0;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  /* USER CODE BEGIN 2 */

  spiEnableClock(spi1);
  ENABLE_GPIOA_CLK_GATING();
  RESET_UART5_CLK_GATING();
   UNRESET_UART5_CLK_GATING();
   ENABLE_UART5_CLK_GATING();
   ENABLE_GPIOA_CLK_GATING();
   ENABLE_GPIOC_CLK_GATING();

   // UART5_TX
   GPIOConfigurePin(gpioC, gpioPin12, GPIO_ALT_FUNC|GPIO_VERY_HI_SPEED);
   GPIOConfigureAltFunc(gpioC, gpioPin12, AF8);

   usartConfigure(uart5, USART_OVERSAMPLING_16 | USART_WORD_LENGTH_9BITS |	\
 		  	  	  	  	USART_ENABLE | USART_STOP_BIT_1 | USART_PC_ENABLE | \
 						USART_PARITY_ODD \
 						| USART_TE_ENABLE  ,115200, 45000000);

  // SPI1 NSS PIN PA4
  /*
  GPIOConfigurePin(gpioA, gpioPin4, GPIO_ALT_FUNC|GPIO_VERY_HI_SPEED);
  GPIOConfigureAltFunc(gpioA, gpioPin4, AF5);
 */
  // SPI1 NSS PIN PA4
  GPIOConfigurePin(gpioA, gpioPin4, GPIO_OUTPUT|GPIO_VERY_HI_SPEED);

  // SPI1 MISO PIN PA6
  GPIOConfigurePin(gpioA, gpioPin6, GPIO_ALT_FUNC|GPIO_VERY_HI_SPEED);
  GPIOConfigureAltFunc(gpioA, gpioPin6, AF5);

  // SPI1 SCLK PIN PA5
  GPIOConfigurePin(gpioA, gpioPin5, GPIO_ALT_FUNC|GPIO_VERY_HI_SPEED);
  GPIOConfigureAltFunc(gpioA, gpioPin5, AF5);

  // SPI1_MOSI - PIN PA7
  //GPIOConfigurePin(gpioA, gpioPin7, GPIO_ALT_FUNC|GPIO_VERY_HI_SPEED);
  //GPIOConfigureAltFunc(gpioA, gpioPin7, AF5);

  /*
  configureSPI(spi1, SPI_EN | SPI_MASTER_MODE | SPI_CLKPHASE_2ND  | SPI_CLKPOLAR_L |\
		  SPI_SOFTWARE_SLAVE_MANAGEMENT | SPI_DATA_FRAME_8_BITS | SPI_SS_OUT_EN|
		  SPI_BIDIRECTIONAL_OUT_EN | SPI_BAUD_CONTRL_256 | SPI_NSS_HIGH | \
		  SPI_BIDIRECTIONAL_DATA_EN);
 */
  configureSPI(spi1, SPI_EN | SPI_MASTER_MODE | SPI_CLKPHASE_1ST  | SPI_CLKPOLAR_L |\
		  SPI_SOFTWARE_SLAVE_MANAGEMENT | SPI_DATA_FRAME_16_BITS |
		  SPI_BIDIRECTIONAL_OUT_EN | SPI_BAUD_CONTRL_256 | SPI_NSS_HIGH | \
		  SPI_BIDIRECTIONAL_DATA_EN);

  //GPIOwritePins(gpioA, gpioPin4, PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  GPIOwritePins(gpioA, gpioPin4, PIN_RESET);
	  if(isSpiTxBufferEmpty(spi1)){
		  spiWriteData(spi1, temperature[i]);
	  }
	  while(!isSpiTxBufferEmpty(spi1));
	  while(isSpiBusy(spi1));
	  //GPIOwritePins(gpioA, gpioPin4, PIN_SET);
	  //HAL_Delay(10);


	 if(isSpiRxBufferNotEmpty(spi1))
		 temp = spiReadData(spi1);
	 uartPrintf("Temperature : C \n");
	 while(isSpiBusy(spi1));

	  	 GPIOwritePins(gpioA, gpioPin4, PIN_SET);
	  	 HAL_Delay(10);

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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 108;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
