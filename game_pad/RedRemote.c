
#include "RedRemote.h"
#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
sbit IRIN = P3 ^ 2;
void irInit() {
    IT0 = 1; //下降沿触发
    EX0 = 1; //打开中断0允许
    EA = 1;  //打开总中断
    IRIN = 1; //初始化端口
}