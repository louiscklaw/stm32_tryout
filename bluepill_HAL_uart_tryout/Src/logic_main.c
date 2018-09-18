
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "dma.h"

int main(void);


void blink_fast(int time_to_blink);
void turn_led_off(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN);
void turn_led_on(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN);

uint8_t blink_led = 0;

uint8_t dataArrived = 0;
char *test_msg = "abcdefg";
uint8_t data[7];

int main(void){
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();

    huart2.Instance->CR3 |= USART_CR3_DMAT;


    while(1){
        try_receive_uart();
        try_send_uart(test_msg);

        HAL_Delay(3000);
    }
    return 0;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    blink_fast(3);
}

void blink_fast(int time_to_blink){
    for(int i =0;i < time_to_blink;i+=1){
        turn_led_off(GPIOC, GPIO_PIN_13);
        HAL_Delay(100);
        turn_led_on(GPIOC, GPIO_PIN_13);
        HAL_Delay(200);
    }
    turn_led_off(GPIOC, GPIO_PIN_13);

}


void turn_led_off(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN){
    HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, GPIO_PIN_SET);
}

void turn_led_on(GPIO_TypeDef  *GPIO_PORT, uint16_t GPIO_PIN){
    HAL_GPIO_WritePin(GPIO_PORT, GPIO_PIN, GPIO_PIN_RESET);
}
