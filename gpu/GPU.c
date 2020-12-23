/**
* Author: RayleighZ
* Time: 2020-12-17 20:00
*/
#include "GPU.h"
#include "reg52.h"
void showByList(int x[], int y[]){
    int i;
    int yOnScreen[8];
    for (i = 0; i < 8; ++i) {
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

    for (i = 0; i < 8; ++i) {
        //基本思路是循环先形成yOnScreen
        yOnScreen[y[i]] = 1;
    }
    for (i = 0; i < 8; ++i) {
        //写入移位寄存器

    }
}
