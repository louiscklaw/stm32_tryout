//

#ifndef __WS2812_H__
#define __WS2812_H__

#define BIT0 30
#define BIT1 60

#define RET_PATTERN_LENGTH 48
#define RET_PATTERN_LENGTH_FIRST_HALF 24
#define RET_PATTERN_LENGTH_SECOND_HALF 24

// 0,1,2
#define NUM_OF_WS2812 8
#define ONE_TESTBIT_LENGTH 24
#define RGB_LED_BIT_LENGTH NUM_OF_WS2812 * ONE_TESTBIT_LENGTH

// mem reserved for update rgbled
#define LEN_MEM_AREA_FOR_RGB_LED RET_PATTERN_LENGTH_FIRST_HALF + RGB_LED_BIT_LENGTH + RET_PATTERN_LENGTH_SECOND_HALF

#define COLOR_CHANGE_TIME_MS 1000/60


uint16_t test_zero_test_one[]={BIT0, BIT1, BIT0, BIT1};
uint16_t test_four_zero[]={BIT0, BIT0, BIT0, BIT0};
uint16_t test_four_one[]={BIT1, BIT1, BIT1, BIT1};

// length of reset(RET) pattern

uint16_t RET_PATTERN[RET_PATTERN_LENGTH]={0};
uint16_t RET_TESTBIT_FIRST_HALF[RET_PATTERN_LENGTH_FIRST_HALF]={0};
uint16_t RET_TESTBIT_SECOND_HALF[RET_PATTERN_LENGTH_SECOND_HALF]={0};

uint16_t* led_test_array;
uint16_t* starting_address;

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

uint16_t mem_area_rgb_led[LEN_MEM_AREA_FOR_RGB_LED] = {0};

// hold the rgb_value of the led array
// 0=>R, 1=>G, 2=>B
uint8_t rgb_value_array[3][NUM_OF_WS2812]={0};

// hold the PWM value of led array
uint16_t rgb_pwm_value_array[3][NUM_OF_WS2812]={0};

int len_led_rgb_values = NUM_OF_WS2812*3;
uint8_t led_rgb_values[NUM_OF_WS2812*3]={0};

void helloworld();

void HSVtoRGB(float fR, float fG, float fB, float fH, float fS, float fV);

#endif
