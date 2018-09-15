
#include "main.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f3xx_hal_tim.h"


void init_test_LD5(void);

GPIO_InitTypeDef GPIO_InitStruct;

int main(void){
    HAL_Init();

    SystemClock_Config();

    init_test_LD5();

    while(1){
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(1000);
    }
    return 0;
}

void init_test_LD5(){
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PA5 - LD2 LED */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
