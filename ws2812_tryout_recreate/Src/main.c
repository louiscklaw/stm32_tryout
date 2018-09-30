
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


// define the number of the led

uint16_t mem_area_rgb_led[LEN_MEM_AREA_FOR_RGB_LED] = {0};

// length of reset(RET) pattern

uint16_t test_zero_test_one[]={BIT0, BIT1, BIT0, BIT1};
uint16_t test_four_zero[]={BIT0, BIT0, BIT0, BIT0};
uint16_t test_four_one[]={BIT1, BIT1, BIT1, BIT1};

uint16_t RET_PATTERN[RET_PATTERN_LENGTH]={0};
uint16_t RET_TESTBIT_FIRST_HALF[RET_PATTERN_LENGTH_FIRST_HALF]={0};
uint16_t RET_TESTBIT_SECOND_HALF[RET_PATTERN_LENGTH_SECOND_HALF]={0};


// uint16_t ONE_BIT_RET_PATTERN[one_testbit_len]={0};

uint16_t* led_test_array;
uint16_t* starting_address;

// RUN CONFIGURATION
int test_pattern_total_length;

uint16_t black_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

uint16_t white_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    };

uint16_t r_led_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };
uint16_t r_led_testbit_length=24;

uint16_t g_led_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };
uint16_t g_led_testbit_length=24;

uint16_t b_led_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    };

uint8_t color_control=0;

// hold the rgb_value of the led array
// 0=>R, 1=>G, 2=>B
uint8_t rgb_value_array[3][NUM_OF_WS2812]={0};

// hold the PWM value of led array
uint16_t rgb_pwm_value_array[3][NUM_OF_WS2812]={0};

int len_led_rgb_values = NUM_OF_WS2812*3;
uint8_t led_rgb_values[NUM_OF_WS2812*3]={0};
uint8_t led_rgb_value;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

void blink_ready(int num_to_blink);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  // led_test_array = malloc(length_test_array * sizeof(uint16_t));


  led_rgb_values[0]=1;
  led_rgb_values[1]=0;
  led_rgb_values[2]=0;

  led_rgb_values[3+0]=0;
  led_rgb_values[3+1]=1;
  led_rgb_values[3+2]=0;



  // memcpy(starting_address , RET_TESTBIT_FIRST_HALF, RET_PATTERN_LENGTH_FIRST_HALF * sizeof(uint16_t));
  // starting_address +=RET_PATTERN_LENGTH_FIRST_HALF;


  update_led_mem();



  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)mem_area_rgb_led, LEN_MEM_AREA_FOR_RGB_LED);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    ping_pong_one_led();
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void update_led_mem(void){
  starting_address=mem_area_rgb_led;


  uint16_t test_led_pwm_value[24]={0};


  memcpy(starting_address ,RET_TESTBIT_FIRST_HALF , RET_PATTERN_LENGTH_FIRST_HALF * sizeof(uint16_t));
  starting_address +=RET_PATTERN_LENGTH_FIRST_HALF;

  for (int i =0;i<len_led_rgb_values;i++){

    led_rgb_value = led_rgb_values[i];
    convert_LED_to_binary(led_rgb_value, test_led_pwm_value);

    int length_per_color_value = 8;


    memcpy(starting_address, test_led_pwm_value, length_per_color_value * sizeof(uint16_t));
    starting_address +=length_per_color_value;
  }

  memcpy(starting_address ,RET_TESTBIT_SECOND_HALF , RET_PATTERN_LENGTH_SECOND_HALF * sizeof(uint16_t));
  starting_address +=RET_PATTERN_LENGTH_SECOND_HALF;

}

void update_led_g_mem(void){
  starting_address=mem_area_rgb_led;
  memcpy(starting_address ,RET_TESTBIT_FIRST_HALF , RET_PATTERN_LENGTH_FIRST_HALF * sizeof(uint16_t));
  starting_address +=RET_PATTERN_LENGTH_FIRST_HALF;

  memcpy(starting_address, g_led_testbit, g_led_testbit_length * sizeof(uint16_t));
  starting_address +=g_led_testbit_length;

  memcpy(starting_address, g_led_testbit, g_led_testbit_length * sizeof(uint16_t));
  starting_address +=g_led_testbit_length;

  memcpy(starting_address ,RET_TESTBIT_SECOND_HALF , RET_PATTERN_LENGTH_SECOND_HALF * sizeof(uint16_t));
  starting_address +=RET_PATTERN_LENGTH_SECOND_HALF;

}

void convert_channel_to_binary(uint8_t color_value, uint16_t* output_array)
{
    int j =0;
    for(int i = 128U; i >0; i = i >> 1){
        if (color_value >= i){
            output_array[j]=BIT1;
            color_value -= i;
        }else{
            output_array[j]=BIT0;
        }
        j+=1;
    }

}

void convert_LED_to_binary(uint8_t RGB_value, uint16_t* binary_value)
{
  // g define from 0 -> 8
  convert_channel_to_binary(RGB_value, binary_value);

}

void define_color_1()
{

  led_rgb_values[0]=1;
  led_rgb_values[1]=0;
  led_rgb_values[2]=0;

  led_rgb_values[3+0]=0;
  led_rgb_values[3+1]=1;
  led_rgb_values[3+2]=0;

}

void define_color_2()
{

  led_rgb_values[0+0]=0;
  led_rgb_values[0+1]=1;
  led_rgb_values[0+2]=0;

  led_rgb_values[3+0]=0;
  led_rgb_values[3+1]=0;
  led_rgb_values[3+2]=1;

}

void turn_on_one_led_only(int pos, int r, int g, int b, uint8_t* output_array)
{
  for(int led_pos =0;led_pos<NUM_OF_WS2812;led_pos++)
  {
    int bit_g_pos = led_pos*3;
    int bit_r_pos = bit_g_pos + 1;
    int bit_b_pos = bit_g_pos + 2;

    if (led_pos == pos)
    {
      output_array[bit_g_pos]=g;
      output_array[bit_r_pos]=r;
      output_array[bit_b_pos]=b;
    }else{
      // blackout the others
      output_array[bit_g_pos]=0;
      output_array[bit_r_pos]=0;
      output_array[bit_b_pos]=0;
    }
  }
}

void rotate_rgb_one_led(){

    for (int i=0;i<NUM_OF_WS2812;i++){
      turn_on_one_led_only(i,128,0,0,led_rgb_values);
      HAL_Delay(100);
    }

    for (int i=0;i<NUM_OF_WS2812;i++){
      turn_on_one_led_only(i,0,0,128,led_rgb_values);
      HAL_Delay(100);
    }

    for (int i=0;i<NUM_OF_WS2812;i++){
      turn_on_one_led_only(i,0,128,0,led_rgb_values);
      HAL_Delay(100);
    }

}

void ping_pong_one_led()
{
    int j = 0;
    int random_r = rand() % 32;
    int random_g = rand() % 32;
    int random_b = rand() % 32;
    for (int i=0;i<NUM_OF_WS2812*2-2;i++){
      if (i<=7){
        j = i;
      }else{
        j = 7-(i-7);
      }
      turn_on_one_led_only(j,random_r,random_g,random_b,led_rgb_values);


      HAL_Delay(100);
    }

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
