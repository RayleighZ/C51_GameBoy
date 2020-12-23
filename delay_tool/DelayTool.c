/**
* Author: RayleighZ
* Time: 2020-12-16 17:44
*/
#include "DelayTool.h"

void delay1s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void delay700ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=223;c>0;c--)
        for(b=64;b>0;b--)
            for(a=23;a>0;a--);
}

void delay500ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}

void delay300ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=123;c>0;c--)
        for(b=116;b>0;b--)
            for(a=9;a>0;a--);
}

void delay10ms(void)   //误差 0us
{
    unsigned char a, b, c;
    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--);
}