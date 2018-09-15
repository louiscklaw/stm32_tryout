
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"

void init_test_PC13(void);
GPIO_InitTypeDef GPIO_InitStruct;

uint16_t PORTA_ALL_PIN = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 |
                GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 |
                GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 |
                GPIO_PIN_12|GPIO_PIN_15;

uint16_t PORTB_ALL_PIN = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 |
                GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 |
                GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 |
                GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;

uint16_t PORTC_ALL_PIN = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 |
                GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 |
                GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 |
                GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;

int main(void);

int main(void){

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();

    while(1){
        HAL_GPIO_TogglePin(GPIOA, PORTA_ALL_PIN);
        HAL_GPIO_TogglePin(GPIOB, PORTB_ALL_PIN);
        HAL_GPIO_TogglePin(GPIOC, PORTC_ALL_PIN);
        HAL_Delay(10);
    }

    return 0;
}
