/**
* Author: RayleighZ
* Time: 2020-12-17 20:00
*/
#include "GPU.h"
#include "reg52.h"
#include "intrins.h"
#include "../delay_tool/DelayTool.h"
/*
sbit SRCLK= P3^6;
sbit LCLK= P3 ^5;
sbit SER= P3^4;
unsigned char ledduan[]={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
void hd595(unsigned char dat){
    unsigned char a;
    SRCLK=0;
    LCLK=0;
    for(a=0;a<8;a++)
    {
        SER=dat>>7;
        dat<<=1;

        SRCLK=1;
        _nop_();
        _nop_();
        SRCLK=0;
    }

    LCLK=1;
    _nop_();
    _nop_();
    RCLK=0;
}

void showByList(unsigned char * image){
    int i;
    P0 = 0xff;
    while (1){//此函数需要强行用中断进行打断
        for (i = 0; i < 8; ++i) {
            //首先完成对P0口的赋值
            P0 = ~ledduan[i];
            //接下来进行移位寄存器的处理
            hd595(image[i]);
            delay1ms();
            hd595(0x00);
        }
    }
}
*/
