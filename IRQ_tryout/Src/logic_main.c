
#include "main.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f3xx_hal_tim.h"

void init_test_B1(void);
void init_test_LD5(void);

GPIO_InitTypeDef GPIO_InitStruct;

int main(void){
    HAL_Init();

    SystemClock_Config();

    init_test_LD5();
    init_test_B1();

    while(1);
    return 0;
}

void init_test_B1(){
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PC13 - USER BUTTON */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void init_test_LD5(){
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PA5 - LD2 LED */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// for B1 EXTI callback
void EXTI15_10_IRQHandler(void) {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
