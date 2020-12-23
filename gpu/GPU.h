/**
* Author: RayleighZ
* Time: 2020-12-17 19:59
*/

#ifndef C51_GAMEBOY_GPU_H
#define C51_GAMEBOY_GPU_H
//通过输入数组进行集体显示
void showByList(const unsigned short x[], const unsigned short y[]);
//对某个坐标的点进行显示
void showByPoint(unsigned short x[], unsigned short y[]);
//清屏
void cleanScreen();
#endif //C51_GAMEBOY_GPU_H
