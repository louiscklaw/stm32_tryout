//

#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal.h"

#include "ws2812_tryout.h"
#include "hsv2rgb.h"
#include <math.h>

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

uint16_t RET_PATTERN[RET_PATTERN_LENGTH]={0};
uint16_t RET_TESTBIT_FIRST_HALF[RET_PATTERN_LENGTH_FIRST_HALF]={0};
uint16_t RET_TESTBIT_SECOND_HALF[RET_PATTERN_LENGTH_SECOND_HALF]={0};


// RUN CONFIGURATION
int test_pattern_total_length;

uint8_t color_control=0;

// hold the rgb_value of the led array
// 0=>R, 1=>G, 2=>B
uint8_t rgb_value_array[3][NUM_OF_WS2812]={0};

// hold the PWM value of led array
uint16_t rgb_pwm_value_array[3][NUM_OF_WS2812]={0};



uint16_t test_zero_test_one[]={BIT0, BIT1, BIT0, BIT1};
uint16_t test_four_zero[]={BIT0, BIT0, BIT0, BIT0};
uint16_t test_four_one[]={BIT1, BIT1, BIT1, BIT1};


int len_led_rgb_values = NUM_OF_WS2812*3;


uint8_t led_rgb_values[NUM_OF_WS2812*3]={0};

extern uint16_t * mem_area_rgb_led;
extern uint16_t* starting_address;

uint8_t led_rgb_value;

uint8_t num_of_ws2812 = NUM_OF_WS2812;

void turn_on_one_led_only(int pos, int r, int g, int b, uint8_t* output_array)
{

  for(int led_pos =0;led_pos<NUM_OF_WS2812;led_pos++)
  {
    if (led_pos==pos)
    {
      assign_color(led_pos,r,g,b,output_array);
    }else{
      assign_color(led_pos,0,0,0,output_array);
    }
  }
}

void assign_color(int pos, int r, int g, int b, uint8_t* output_array)
{

    int bit_g_pos = pos*3;
    int bit_r_pos = bit_g_pos + 1;
    int bit_b_pos = bit_g_pos + 2;

    output_array[bit_g_pos]=g;
    output_array[bit_r_pos]=r;
    output_array[bit_b_pos]=b;


}

void rotate_rgb_one_led(int per_delay)
{

    for (int i=0;i<NUM_OF_WS2812;i++){
      turn_on_one_led_only(i,get_random_color(128),0,0,led_rgb_values);
      HAL_Delay(per_delay);
    }

    for (int i=0;i<NUM_OF_WS2812;i++){
      turn_on_one_led_only(i,0,0,get_random_color(128),led_rgb_values);
      HAL_Delay(per_delay);
    }

    for (int i=0;i<NUM_OF_WS2812;i++){
      turn_on_one_led_only(i,0,get_random_color(128),0,led_rgb_values);
      HAL_Delay(per_delay);
    }

}


void rotate_rainbow_one_led(int per_delay, int change_color_speed)
{
      uint8_t r, g, b;
      uint8_t * pr=&r;
      uint8_t * pg=&g;
      uint8_t * pb=&b;

    for (int d_h=0; d_h < 255; d_h+=change_color_speed){
      hsv_to_rgb(d_h, 255, 4, pr,pg,pb);
      for (int i=0;i<NUM_OF_WS2812;i++){
        turn_on_one_led_only(i,r,g,b,led_rgb_values);
        HAL_Delay(per_delay);
      }
    }

}

void rainbow_led(int per_delay, int hsv_h_offset, int hsv_h_min, int hsv_h_max, int hsv_s, int hsv_v)
{
    uint8_t r, g, b;
    uint8_t * pr=&r;
    uint8_t * pg=&g;
    uint8_t * pb=&b;

    int hsv_h_range = hsv_h_max-hsv_h_min;
    int color_delta=trunc(hsv_h_range/num_of_ws2812);
    int d_h=hsv_h_offset+hsv_h_min;

    for (int i=0;i<num_of_ws2812;i++)
    {
      if (d_h > hsv_h_max){
        d_h=(d_h-hsv_h_max)+hsv_h_min;
      }

      hsv_to_rgb(d_h, hsv_s, hsv_v, pr,pg,pb);
      assign_color(i,r,g,b,led_rgb_values);
      d_h = d_h + color_delta;

    }

    HAL_Delay(per_delay);
}

void rotate_rainbow_led(int per_delay, int hsv_h_min, int hsv_h_max, int hsv_h_step, int hsv_s, int hsv_v)
{

  for(int i =hsv_h_min;i<hsv_h_max;i+=hsv_h_step)
  {
    // rainbow_led(0, i, hsv_h_min, hsv_h_max, 255, 25);
    // rainbow_led(0, i, 0, 255, 255, 25);
    // rainbow_led(0, i, 0, 128, 255, 25);
    // rainbow_led(0, i, 128, 255, 255, 16);
    rainbow_led(0,i,hsv_h_min, hsv_h_max, hsv_s, hsv_v);
    HAL_Delay(per_delay);
  }
}


void ping_pong_one_led(int per_delay)
{
    int j = 0;
    int random_r = get_random_color(32);
    int random_g = get_random_color(32);
    int random_b = get_random_color(32);
    for (int i=0;i<NUM_OF_WS2812*2-2;i++){
      if (i<=7){
        j = i;
      }else{
        j = 7-(i-7);
      }
      turn_on_one_led_only(j,random_r,random_g,random_b,led_rgb_values);

      HAL_Delay(per_delay);
    }


}

int get_random_color(int max_brightness)
{
  return rand() % max_brightness;
}

void convert_LED_to_binary(uint8_t RGB_value, uint16_t* binary_value)
{
  // g define from 0 -> 8
  convert_channel_to_binary(RGB_value, binary_value);

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


void update_led_mem(void)
{
  starting_address=&mem_area_rgb_led;
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


void tick_gpio_pin(DMA_HandleTypeDef *hdma){
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
  update_led_mem();
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
}
