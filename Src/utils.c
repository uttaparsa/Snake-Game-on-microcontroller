#include "stm32f3xx_hal.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

uint16_t current_cursor = 0;
unsigned char data[1];
unsigned char reshte[150];
unsigned char send_buffer[150] = "Fu";
uint8_t turn = 0;
void uart_send(UART_HandleTypeDef* huart2p , char* message){
	int n = sprintf((char *)send_buffer ,"%s",message);
	HAL_UART_Transmit(huart2p , send_buffer , n ,1000);
}

void set_cursor(uint16_t num){
	current_cursor = num;

}

uint16_t get_cursor(){
	return current_cursor;
}
void numberToBcd (int i) {
	int x1 = i&1;
	int x2 = i&2;
	int x3 = i&4;
	int x4 = i&8;
	if(x1>0) x1=1;
	if(x2>0) x2=1;
	if(x3>0) x3=1;
	if(x4>0) x4=1;

	HAL_GPIO_WritePin(GPIOC , GPIO_PIN_0 , x1);
	HAL_GPIO_WritePin(GPIOC , GPIO_PIN_1 , x2);
	HAL_GPIO_WritePin(GPIOC , GPIO_PIN_2 , x3);
	HAL_GPIO_WritePin(GPIOC , GPIO_PIN_3 , x4);
	
}
void printToSeg(int numberOnLeft, int numberOnRight){
		
		if(turn == 1){
			uint8_t first_tens = (numberOnLeft/10)%10;
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_10| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13,  0);
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_10 , 1);
			numberToBcd(first_tens);
			turn = 2;
		}else if (turn == 2){
			uint8_t first_ones = numberOnLeft%10;
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_10| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13,  0);
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_11 , 1);
			numberToBcd(first_ones);
			turn = 3;
		}else if (turn == 3){
			uint8_t first_tens = (numberOnRight/10)%10;
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_10| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13,  0);
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12 , 1);
			numberToBcd(first_tens);
			turn = 0;
		}else if (turn == 0){
			uint8_t first_ones = numberOnRight%10;
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_10| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13,  0);
			HAL_GPIO_WritePin(GPIOB , GPIO_PIN_13 , 1);
			numberToBcd(first_ones);
			turn = 1;
		}
}

