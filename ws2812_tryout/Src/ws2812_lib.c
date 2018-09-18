
#include <string.h>

#include "main.h"

#define TOTAL_LED_NUM 1

// length of reset(RET) pattern
#define RET_PATTERN_LENGTH 62


// 30 and 60 depends on the main clock
// 72Mhz / (prescale=0)(arr=89)

#define BIT0 30
#define BIT1 60

int helloworld = 0;

uint16_t RET_PATTERN[RET_PATTERN_LENGTH] = {0};

int test_pattern_total_length = RET_PATTERN_LENGTH+(24*TOTAL_LED_NUM);

uint16_t black_testbit[24]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

uint16_t r_testbit[24]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

uint16_t white_testbit[24]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    };

uint16_t g_testbit[24]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    };

uint16_t b_testbit[24]={
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0,
    BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT0, BIT1,
    };


int hellofunc(void){
    return 1;
}

void hellomemcpy(uint16_t * test_pattern){

    memcpy(test_pattern, RET_PATTERN, sizeof(RET_PATTERN));
    memcpy(test_pattern+RET_PATTERN_LENGTH, r_testbit, sizeof(r_testbit));

}


// convert from int to bit array, for all R,G,B

// combine R,G,B to become a 24 bit led bit array

// convert bit array to bit0/bit1
