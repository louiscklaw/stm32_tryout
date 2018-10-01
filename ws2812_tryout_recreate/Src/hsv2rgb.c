/*****Please include following header files*****/
// math.h
/***********************************************/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>

#include "hsv2rgb.h"


void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *oR, uint8_t *oG, uint8_t *oB )
{

    if (s == 0)
    {
        // achromatic (grey)
        *oR = *oG = *oB = v;
    }
    else
    {
      float R,G,B;
      float degree_60_255 = ((float)60/360)*255;
      float h_dash = (float)h/degree_60_255;  //2.56

      float scale_v = (float)v/255;
      float scale_s = (float)s/255;

      float c = (scale_v * scale_s);
      float m = scale_v - c;

      float x = c * (1.0f - fabs(fmod(h_dash,2)  - 1));
      // float x =0;


      // printf("%f %f %f" , c,x,m);

      switch((int)trunc(h_dash)){
        case 0:
          R = c;
          G=x;
          B=0;
          break;
        case 1:
          R = x;
          G=c;
          B=0;
          break;

        case 2:
          R = 0;
          G=c;
          B=x;
          break;
        case 3:
          R = 0;
          G=x;
          B=c;
          break;
        case 4:
          R = x;
          G=0;
          B=c;
          break;
        default:
          R = c;
          G=0;
          B=x;
          break;
      }
      // printf("h_dash=%f\n", h_dash);
      // printf("degree_60_255=%f\n", degree_60_255);
      // printf("fmod=%f\n" ,  fabs(fmod(h_dash,2)  - 1));
      // printf("scale_v=%f\n", scale_v);
      // printf("scale_s=%f\n", scale_s);
      // // printf("h=%d\n", h);
      // // printf("s=%d\n", s);
      // // printf("v=%d\n", v);


      // printf("c=%f\n",c);
      // printf("x=%f\n",x);
      // printf("m=%f\n",m);

      *oR = (m+R) * 255;
      *oG = (m+G) * 255;
      *oB = (m+B) * 255;

    }
}



void helloworld_hsv()
{

}
