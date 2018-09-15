
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f1xx_it.h"


int readUserInput(void);
void processUserInput(int8_t opt);

void blink_PC13(int pin_state);

int main(void);

int UartReady = 0;
int8_t opt =-1;

char test_send_message[1] = "0";
char test_receive_message[1];
char readBuf[1];
int receive_from_uart = -1;

// init_stm32_main_template
int main(void){
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    srand(time(NULL));


    while (1) {
        receive_from_uart = readUserInput();

        if(receive_from_uart != -1){

        }
        HAL_UART_Transmit_IT(&huart2, (uint8_t*)test_send_message, strlen(test_send_message));
        HAL_Delay(1000);
    }

    return 0;
}

void blink_PC13(int pin_state){
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

int readUserInput(void) {
    int retVal = -1;

    if(UartReady == 1) {
        UartReady = 0;
        HAL_UART_Receive_IT(&huart2, (uint8_t*)readBuf, 1);
        retVal = atoi(readBuf);
    }

    return retVal;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
    /* Set transmission flag: transfer complete*/
    UartReady = 1;
    blink_PC13(0);
}

int get_random_number(int MAX_INT){
    return random() % MAX_INT;
}
