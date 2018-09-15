
#define LD2_Pin GPIO_PIN_13
#define LD2_GPIO_Port GPIOC

#include "main.h"

#include <string.h>

// hal include
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

// cubemx include
#include "gpio.h"
#include "usart.h"
#include "dma.h"


int main(void);

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;


char msg[]="test message";

// init_stm32_main_template
int main(void){
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();



    hdma_usart2_tx.Instance = DMA1_Channel7;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_usart2_tx);



    while (1){
        HAL_DMA_Start(&hdma_usart2_tx,  (uint32_t)msg,  (uint32_t)&huart2.Instance->DR, strlen(msg));
        //Enable UART in DMA mode
        huart2.Instance->CR3 |= USART_CR3_DMAT;
        //Wait for transfer complete
        HAL_DMA_PollForTransfer(&hdma_usart2_tx, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
        //Disable UART DMA mode
        huart2.Instance->CR3 &= ~USART_CR3_DMAT;
        //Turn LD2 ON
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        HAL_Delay(500);
    };
    return 0;
}
