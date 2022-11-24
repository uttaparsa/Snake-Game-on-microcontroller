/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
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
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "game.h"
#include "LiquidCrystal.h"

uint8_t loadState = 0;
int loadStartTime = 0;
uint16_t prev_interrupt_millis = 0;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern ADC_HandleTypeDef hadc2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart2;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line0 interrupt.
*/
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */
	if(HAL_GetTick() - prev_interrupt_millis  < KEYBOUNCING_DELAY){
		return;
	}
	prev_interrupt_millis = HAL_GetTick();
	for(int i = 0 ; i < 4 ; ++i){
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4 , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5 , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_6 , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_7 , GPIO_PIN_RESET);
		if(i == 1){
			HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5 , GPIO_PIN_SET);
			if(HAL_GPIO_ReadPin(GPIOD , GPIO_PIN_0) ){
				setMovDir('w');
			}
		}
		
	}
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_6 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_7 , GPIO_PIN_SET);
	while(HAL_GPIO_ReadPin(GPIOD , GPIO_PIN_0));
  /* USER CODE END EXTI0_IRQn 1 */
}

/**
* @brief This function handles EXTI line1 interrupt.
*/
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */
	if(HAL_GetTick() - prev_interrupt_millis  < KEYBOUNCING_DELAY){
		return;
	}
	prev_interrupt_millis = HAL_GetTick();
	for(int i = 0 ; i < 4 ; ++i){
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4 , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5 , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_6 , GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOD , GPIO_PIN_7 , GPIO_PIN_RESET);
		if(i == 0){
			HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4 , GPIO_PIN_SET);
			if(HAL_GPIO_ReadPin(GPIOD , GPIO_PIN_1) ){
				setMovDir('a');
			}
			
		}else if(i == 1){
			HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5 , GPIO_PIN_SET);
			if(HAL_GPIO_ReadPin(GPIOD , GPIO_PIN_1) ){
				setMovDir('s');
			}
		}else if(i == 2){
			HAL_GPIO_WritePin(GPIOD , GPIO_PIN_6 , GPIO_PIN_SET);
			if(HAL_GPIO_ReadPin(GPIOD , GPIO_PIN_1) ){
				setMovDir('d');
			}
		}
		
	}
	set_cursor(get_cursor()+1);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_6 , GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD , GPIO_PIN_7 , GPIO_PIN_SET);
	while(HAL_GPIO_ReadPin(GPIOD , GPIO_PIN_1));
  /* USER CODE END EXTI1_IRQn 1 */
}

/**
* @brief This function handles EXTI line2 and Touch Sense controller.
*/
void EXTI2_TSC_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_TSC_IRQn 0 */

  /* USER CODE END EXTI2_TSC_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  /* USER CODE BEGIN EXTI2_TSC_IRQn 1 */

  /* USER CODE END EXTI2_TSC_IRQn 1 */
}

/**
* @brief This function handles EXTI line3 interrupt.
*/
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */

  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
* @brief This function handles ADC1 and ADC2 interrupts.
*/
void ADC1_2_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_2_IRQn 0 */

  /* USER CODE END ADC1_2_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc2);
  /* USER CODE BEGIN ADC1_2_IRQn 1 */
	int x = HAL_ADC_GetValue(&hadc2);
	float speed = ((float)x *6.0f)/64.0f;
	if(get_snake_speed() > speed ){
		set_snake_speed(speed);
	}
	HAL_ADC_Start_IT(&hadc2);	
	
  /* USER CODE END ADC1_2_IRQn 1 */
}

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */
	/*
	THIS TIMER IS RUNNED EACH 30 MILLIS
	*/
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
	printToSeg((int) (get_snake_speed()*10.0f) , get_snake_length());
  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
	/*
	THIS TIMER IS RUNNED EACH 100 MILLIS (10 TIMES A SECOND)
	*/
	
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
	updateSnakePlace();
	

  /* USER CODE END TIM4_IRQn 1 */
}

/**
* @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
*/
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	if(loadState){
		if(HAL_GetTick() - loadStartTime > 10000){
			loadState = 0;
		}
		if(data[0] == 202){
			
			clear();
			load_game_from_receive_buffer();
			HAL_TIM_Base_Start_IT(&htim4);
			HAL_GPIO_WritePin(GPIOA , GPIO_PIN_8 ,  0);
			set_cursor(0);
			loadState = 0;
		}else{
			reshte[get_cursor()] = data[0];
			reshte[get_cursor()+1] = '\0';
			set_cursor(get_cursor()+1);
		}
		
	}else if(strchr(DIR_KEYS, data[0]) != NULL)
  {
    setMovDir(data[0]);
  }else if(data[0] == 'r'){
		HAL_TIM_Base_Stop_IT(&htim4);
		HAL_GPIO_WritePin(GPIOE , GPIO_PIN_8 |  GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 , 0 );
		clear();
		init_default_game();
		HAL_TIM_Base_Start_IT(&htim4);
	}else if(data[0] == 201){
		HAL_TIM_Base_Stop_IT(&htim4);
		loadStartTime = HAL_GetTick();
		HAL_GPIO_WritePin(GPIOA , GPIO_PIN_8 ,  1);
		loadState = 1;
	}
	
	HAL_UART_Receive_IT(&huart2 , data, sizeof(data));
  /* USER CODE END USART2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
