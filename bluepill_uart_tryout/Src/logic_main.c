
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "gpio.h"

char test_msg[1];
uint8_t test_send_int ;
char  readBuf[1];
uint8_t test_receive_int = 9;

int main(void);
int get_random_integer(uint8_t MAX_INT);

// init_stm32_main_template
int main(void){
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_USART2_UART_Init();

    srand(time(NULL));

    while (1){
        test_send_int = get_random_integer(9);
        itoa(test_send_int, test_msg, 10);

        HAL_UART_Transmit(&huart2, (uint8_t*)test_msg, 1, HAL_MAX_DELAY);
        HAL_UART_Receive(&huart2, (uint8_t*)readBuf, 1, HAL_MAX_DELAY);
        test_receive_int = atoi(readBuf);

        if (test_send_int == test_receive_int){
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }else{

        }

        HAL_Delay(2);
    }
    return 0;
}

int get_random_integer(uint8_t MAX_INT){
    return rand() % MAX_INT;
}
