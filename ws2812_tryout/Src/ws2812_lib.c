
#define get_array_length(x) sizeof(x)/sizeof(x[0])


#include <string.h>

#include "main.h"

#define TOTAL_LED_NUM 8

// length of reset(RET) pattern
#define RET_PATTERN_LENGTH 80


// 30 and 60 depends on the main clock
// 72Mhz / (prescale=0)(arr=89)

#define BIT0 30
#define BIT1 60


// RUN CONFIGURATION
#define COLOR_CHANGE_TIME_MS 1000

int helloworld = 0;

uint8_t test_RGB_1[3] = {0,1,2};

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




void flatten_array(uint8_t (*p)[8], int num_row, uint8_t *output_array){
    for(int i=0; i < num_row; i+=1){
        for(int j=0; j<8;j+=1){
            int pos = i*8+j;
            output_array[pos] = p[i][j];
        }
    }
}



void convert_channel_to_binary(int color_value, uint8_t* output_array)
{
    int j =0;
    for(int i = 128U; i >0; i = i >> 1){
        if (color_value >= i){
            output_array[j]=1;
            color_value -= i;
        }else{
            output_array[j]=0;
        }
        j+=1;
    }

}

void convert_binary_to_delay(uint8_t * binary_array, uint8_t * delay_array, uint8_t get_array_length, uint8_t delay1, uint8_t delay0)
{
    // uint8_t test_value = 0;
    // uint8_t * pdelay1 = &test_value;
    // uint8_t * pdelay0 = &test_value;

    for (int i =0;i<get_array_length; i+=1)
    {
    //     memcpy(delay_array+i, binary_array[i]==1?pdelay1:pdelay0,sizeof(uint8_t));
        if (binary_array[i]==1){
            delay_array[i] = delay1;
        }else{
            delay_array[i] = delay0;
        }
    }
}

void convert_RGB_to_ws2812_duty(uint8_t* input_RGB_int, uint8_t (*output_RGB_binary)[8],int no_of_channel, int no_of_bit){
    uint8_t temp_array[8]={0};

    for(int i=0; i < no_of_channel; i+=1){
        convert_channel_to_binary(input_RGB_int[i], temp_array);

        // output_RGB_binary[i] => solved as 1-dimensional array
        convert_binary_to_delay(temp_array, output_RGB_binary[i], get_array_length(temp_array), BIT1, BIT0);
    }
}

void get_RGB_ws2812_duty_array(uint8_t * RGB, uint8_t * array_duty){
    for (int i=0; i<3;i+=1){
        uint8_t binary_array[3][8];
        convert_RGB_to_ws2812_duty(RGB+i,binary_array,3 , 8);
        flatten_array(binary_array,3,array_duty);
    }
}
