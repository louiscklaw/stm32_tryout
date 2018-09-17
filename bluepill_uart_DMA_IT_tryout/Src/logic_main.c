
#include <string.h>
#include <stdio.h>

#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "dma.h"
#include "usart.h"

int main(void);





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
