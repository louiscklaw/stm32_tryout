
#ifndef _WS2812_LIB_H
#define _WS2812_LIB_H

#include <string.h>
#include "logic_const.h"



// 30 and 60 depends on the main clock
// 72Mhz / (prescale=0)(arr=89)


// RUN CONFIGURATION

int helloworld = 0;
uint8_t test_RGB_1[3] = {0,1,2};

// int test_pattern_total_length = RET_PATTERN_LENGTH+(24*led_length);
int test_pattern_total_length;


uint16_t led_pattern[24];

int RET_pattern_size=40;
uint16_t RET_pattern[40]={0};

// current_sending_incidator
// 0 = RET
// 1 = LED
int CURRENT_SENDING =0;

// uint16_t final_test_pattern[test_pattern_total_length];
uint16_t *send_pattern = RET_pattern;
int send_size = 40;

#endif
