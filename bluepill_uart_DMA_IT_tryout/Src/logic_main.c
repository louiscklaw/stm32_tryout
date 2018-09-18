
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "dma.h"
#include "usart.h"

char * msg = "      ";

int main(void);
void try_send_uart(void);


int main(void){
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();

    while(1){
        // huart2.Instance->CR3 |= USART_CR3_DMAT;

        try_send_uart();
        HAL_Delay(500);


    }

    return 0;
}


void DMATransferComplete(DMA_HandleTypeDef *hdma) {
    if(hdma->Instance == DMA1_Channel7) {
        //Disable UART DMA mode
        huart2.Instance->CR3 &= ~USART_CR3_DMAT;
    }
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void try_send_uart(void){
    HAL_DMA_Start_IT(&hdma_usart2_tx,  (uint32_t)msg,  (uint32_t)&huart2.Instance->DR, strlen(msg));
    huart2.Instance->CR3 |= USART_CR3_DMAT;

}
