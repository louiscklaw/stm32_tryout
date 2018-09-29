
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

void blink_ready(int num_to_blink);

#endif
