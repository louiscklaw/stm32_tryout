#ifndef __WS2812_TRYOUT_H__
#define __WS2812_TRYOUT_H__

#define TEST_DEFINE 1


#define BIT0 30
#define BIT1 60

#define RET_PATTERN_LENGTH_FIRST_HALF 70
#define RET_PATTERN_LENGTH_SECOND_HALF RET_PATTERN_LENGTH_FIRST_HALF*1/10

#define RET_PATTERN_LENGTH RET_PATTERN_LENGTH_FIRST_HALF+RET_PATTERN_LENGTH_SECOND_HALF

// 0,1,2
#define NUM_OF_WS2812 8
#define ONE_TESTBIT_LENGTH 24
#define RGB_LED_BIT_LENGTH NUM_OF_WS2812 * ONE_TESTBIT_LENGTH

#define LED_MEM_AREA_LENGTH RET_PATTERN_LENGTH+RGB_LED_BIT_LENGTH

// mem reserved for update rgbled


#define COLOR_CHANGE_TIME_MS 1000/60


#define LEN_MEM_AREA_FOR_RGB_LED RET_PATTERN_LENGTH_FIRST_HALF + RGB_LED_BIT_LENGTH + RET_PATTERN_LENGTH_SECOND_HALF

void helloworld();
void ping_pong_one_led();
void rotate_rgb_one_led();
void turn_on_one_led_only(int pos, int r, int g, int b, uint8_t* output_array);
void convert_LED_to_binary(uint8_t RGB_value, uint16_t* binary_value);
void convert_channel_to_binary(uint8_t color_value, uint16_t* output_array);
void update_led_mem(void);

void tick_gpio_pin(DMA_HandleTypeDef *hdma);

int get_random_color(int max_brightness);

void rotate_rainbow_one_led(int per_delay, int change_color_speed);
void rainbow_led(int per_delay, int hsv_h_offset, int hsv_h_min, int hsv_h_max, int hsv_s, int hsv_v);
void rotate_rainbow_led(int per_delay, int hsv_h_min, int hsv_h_max, int hsv_h_step, int hsv_s, int hsv_v);

void assign_color(int pos, int r, int g, int b, uint8_t* output_array);

int HELLOWORLD;

#endif
