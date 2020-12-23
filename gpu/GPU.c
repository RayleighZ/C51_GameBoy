/**
* Author: RayleighZ
* Time: 2020-12-17 20:00
*/
#include "GPU.h"
#include "reg52.h"
#include "intrins.h"
#include "../delay_tool/DelayTool.h"
sbit CLK = P3^6;
sbit SER = P3^4;
sbit clean = P3^5;

void showByList(const unsigned short * x, const unsigned short * y){
    int i;
    int yOnScreen[8];
    for (i = 0; i < 64; ++i) {
        //先清零
        switch (x[i]) {
            case 1:{
                P0 = P0&0x01;
                break;
            }
            case 2:{
                P0 = P0&0x02;
                break;
            }
            case 3:{
                P0 = P0&0x04;
                break;
            }
            case 4:{
                P0 = P0&0x08;
                break;
            }
            case 5:{
                P0 = P0&0x10;
                break;
            }
            case 6:{
                P0 = P0&0x20;
                break;
            }
            case 7:{
                P0 = P0&0x40;
                break;
            }
            case 8:{
                P0 = P0&0x80;
                break;
            }
        }
    }

    for (i = 0; i < 8; ++i) {
        yOnScreen[i] = 0;
    }

    for (i = 0; i < 64; ++i) {
        //基本思路是循环先形成yOnScreen
        if (y[i] != 0){
            yOnScreen[y[i]-1] = 1;
        }
    }

    /*clean = 1;
    clean = 0;
    clean = 1;*/
    clean = 0;
    CLK = 0;
    for (i = 0; i < 4; ++i) {
        //写入移位寄存器
        SER = 1/*yOnScreen[i]*/;
        CLK = 1;
        _nop_();
        _nop_();
        CLK = 0;//形成上升沿
    }
    for (i = 4; i < 8; ++i) {
        //写入移位寄存器
        SER = 0/*yOnScreen[i]*/;
        CLK = 1;
        _nop_();
        _nop_();
        CLK = 0;//形成上升沿
    }
    CLK = 1;
    _nop_();
    _nop_();
    CLK = 0;//形成上升沿
}
