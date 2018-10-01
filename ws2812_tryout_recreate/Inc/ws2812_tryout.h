#ifndef __WS2812_TRYOUT_H__
#define __WS2812_TRYOUT_H__

#define TEST_DEFINE 1

#define LEN_MEM_AREA_FOR_RGB_LED RET_PATTERN_LENGTH_FIRST_HALF + RGB_LED_BIT_LENGTH + RET_PATTERN_LENGTH_SECOND_HALF

void helloworld();
void ping_pong_one_led();
void rotate_rgb_one_led();
void turn_on_one_led_only(int pos, int r, int g, int b, uint8_t* output_array);
void convert_LED_to_binary(uint8_t RGB_value, uint16_t* binary_value);
void convert_channel_to_binary(uint8_t color_value, uint16_t* output_array);
void update_led_mem(void);

void tick_gpio_pin(DMA_HandleTypeDef *hdma);

#endif
