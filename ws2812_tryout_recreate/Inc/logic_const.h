
#ifndef _LOGIC_CONST_H_
#define _LOGIC_CONST_H_

#include <stdint.h>

#define get_array_length(x) sizeof(x)/sizeof(x[0])



#define RET_PATTERN_LENGTH 48

#define BIT0 30
#define BIT1 60

#define COLOR_CHANGE_TIME_MS 1000/60

// define the number of the led
int led_length=4;

// length of reset(RET) pattern

uint16_t black_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

int one_testbit_len = 24;
uint16_t r_led_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

uint16_t white_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    };

uint16_t g_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

uint16_t b_testbit[]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    };

uint16_t test_zero_test_one[]={BIT0, BIT1, BIT0, BIT1};
uint16_t test_four_zero[]={BIT0, BIT0, BIT0, BIT0};
uint16_t test_four_one[]={BIT1, BIT1, BIT1, BIT1};

uint16_t RET_PATTERN[RET_PATTERN_LENGTH]={0};

#endif //_LOGIC_CONST_H_
