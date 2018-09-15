
#include "main.h"
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_tim.h"
#include "gpio.h"

uint16_t Pin_to_test = GPIO_PIN_5;

uint16_t ALL_GPIOA_PIN = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|LD2_Pin|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_15;

uint16_t ALL_GPIOB_PIN = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;

uint16_t ALL_GPIOC_PIN = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;

int main(void){
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    while (1)
    {
            HAL_GPIO_WritePin(GPIOA, ALL_GPIOA_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, ALL_GPIOB_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOC, ALL_GPIOC_PIN, GPIO_PIN_SET);
            HAL_Delay(10);

            // HAL_GPIO_WritePin(GPIOA, LD2_Pin|GPIO_PIN_2, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, ALL_GPIOA_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, ALL_GPIOB_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC, ALL_GPIOC_PIN, GPIO_PIN_RESET);
            HAL_Delay(10);
    }
}
