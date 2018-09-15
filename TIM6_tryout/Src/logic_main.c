
#include "main.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f3xx_hal_tim.h"

void init_timer_TIM6(void);
void init_and_start_htim(TIM_HandleTypeDef *htim_to_start);

TIM_HandleTypeDef htim6;

GPIO_InitTypeDef GPIO_InitStruct;

int main(void){
    HAL_Init();
    SystemClock_Config();

    init_test_LD5();
    init_timer_TIM6();

    init_and_start_htim(&htim6);

    while(1);
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
}

void init_timer_TIM6(){
    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 36000-1; //72MHz/36000 = 2000Hz
    htim6.Init.Period = 999;      //2000HZ / 1000 = 2Hz = 0.5s

    __HAL_RCC_TIM6_CLK_ENABLE();

    HAL_NVIC_SetPriority(TIM6_DAC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC1_IRQn);
}

void TIM6_DAC1_IRQHandler(void) {
    // __HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
    HAL_TIM_IRQHandler(&htim6);
}

void init_and_start_htim(TIM_HandleTypeDef *htim_to_start){
    HAL_TIM_Base_Init(htim_to_start);
    HAL_TIM_Base_Start_IT(htim_to_start);
}

void deinit_and_stop(TIM_HandleTypeDef *htim_to_stop){
    HAL_TIM_Base_Stop_IT(htim_to_stop);
    HAL_TIM_Base_DeInit(htim_to_stop);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if(htim->Instance == TIM6){
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
  }
}
