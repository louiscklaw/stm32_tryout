
#include "main.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f3xx_hal_tim.h"

void init_timer_TIM6(void);


TIM_HandleTypeDef htim6;

int main(void){
    MX_GPIO_Init();

    init_timer_TIM6();
    HAL_TIM_Base_Start_IT(&htim6);

    while (1);
}

void init_timer_TIM6(){
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 36000-1; //72MHz/36000 = 2000Hz
  htim6.Init.Period = 100-1;      //2000HZ / 1000 = 2Hz = 0.5s

  __HAL_RCC_TIM6_CLK_ENABLE();

  HAL_NVIC_SetPriority(TIM6_DAC1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC1_IRQn);

  HAL_TIM_Base_Init(&htim6);
}

void TIM6_DAC1_IRQHandler(void) {
  HAL_TIM_IRQHandler(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if(htim->Instance == TIM6)
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}
