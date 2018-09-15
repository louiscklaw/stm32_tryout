
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "stm32f3xx_hal.h"
// #include "usart.h"
#include "gpio.h"
#include "stm32f3xx_hal_tim.h"

#define WELCOME_MSG "Welcome to the Nucleo management console\r\n"
#define MAIN_MENU   "Select the option you are interested in:\r\n\t1. Toggle LD2 LED\r\n\t2. Read USER BUTTON status\r\n\t3. Clear screen and print this message "
#define PROMPT "\r\n> "

void printWelcomeMessage(void);
uint8_t opt = 0;
uint8_t readUserInput(void);
uint8_t processUserInput(uint8_t opt);

GPIO_InitTypeDef GPIO_InitStruct;

void main(void){
	while (1)  {
		printWelcomeMessage();

        HAL_Delay(1000);
	}

}

void printWelcomeMessage(void) {
	// HAL_UART_Transmit(&huart2, (uint8_t*)"\033[0;0H", strlen("\033[0;0H"), HAL_MAX_DELAY);
	// HAL_UART_Transmit(&huart2, (uint8_t*)"\033[2J", strlen("\033[2J"), HAL_MAX_DELAY);
	// HAL_UART_Transmit(&huart2, (uint8_t*)WELCOME_MSG, strlen(WELCOME_MSG), HAL_MAX_DELAY);
	// HAL_UART_Transmit(&huart2, (uint8_t*)MAIN_MENU, strlen(MAIN_MENU), HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
}

uint8_t readUserInput(void) {
	char readBuf[1];

	HAL_UART_Transmit(&huart2, (uint8_t*)PROMPT, strlen(PROMPT), HAL_MAX_DELAY);
	HAL_UART_Receive(&huart2, (uint8_t*)readBuf, 1, HAL_MAX_DELAY);
	return atoi(readBuf);
}


uint8_t processUserInput(uint8_t opt) {
	char msg[30];

	if(!opt || opt > 3)
		return 0;

	sprintf(msg, "%d", opt);
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	switch(opt) {
	case 1:
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		break;
	case 2:
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
		break;
	case 3:
		return 2;
	};

	return 1;
}
