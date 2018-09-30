//

#ifndef __WS2812_H__
#define __WS2812_H__

#define BIT0 30
#define BIT1 60


uint16_t mem_area_rgb_led[LEN_MEM_AREA_FOR_RGB_LED] = {0};

void helloworld();

void HSVtoRGB(float fR, float fG, float fB, float fH, float fS, float fV);

#endif
