/**
* Author: RayleighZ
* Time: 2020-12-17 19:59
*/

#ifndef C51_GAMEBOY_GPU_H
#define C51_GAMEBOY_GPU_H
//通过输入数组进行集体显示
void showByList(int x[], int y[]);
//对某个坐标的点进行显示
void showByPoint(int x, int y);
//清屏
void cleanScreen();
#endif //C51_GAMEBOY_GPU_H
