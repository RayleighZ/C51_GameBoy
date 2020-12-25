/**
 * Author: RayleighZ
 * Time: 2020-12-15 20:40
 * Describe: C51 8位机 点阵屏 贪吃蛇游戏
 */
#include "reg52.h"
#include "EatSnake.h"
#include "intrins.h"
#include <stdlib.h>
#include "../delay_tool/DelayTool.h"
#include "../game_pad/RedRemote.h"

sbit IRIN = P3 ^2;
unsigned char IrValue[6];
unsigned char Time;
typedef unsigned int u16;
typedef unsigned char u8;

int up = 0;
int down = 1;
int left = 2;
int right = 3;
int timer = 0;
unsigned char flag = 1;

int beenX;
int beenY;

int screenSize = 8;//点阵屏的宽度大小
typedef struct SnackBody {
    struct SnackBody * next;
    int x;
    int y;
    int dir;
} SnackBody;

SnackBody snack;

void createSnack() {
    snack.x = 1;
    snack.y = 1;
    snack.next = NULL;
    snack.dir = up;
}

int isAlive() {
    int headX = snack.x;
    int headY = snack.y;
    SnackBody *cursor = &snack;//检索遍历用的游标
    while (cursor->next != NULL) {//遍历检索，如果蛇头和蛇身碰撞，就判定游戏结束
        if (cursor->y == headY && cursor->x == headX) {
            return 0;
        }
        cursor = cursor->next;//游标移动
    }
    return 1;
}

void nextStep() {
    //遍历蛇身，让它前进
    SnackBody *cursor = &snack;
    SnackBody *prior = &snack;
    while (cursor != NULL) {
        switch ((*cursor).dir) {
            case 0: {
                (*cursor).y = ((*cursor).y+1)%9;
                break;
            }
            case 1: {
                (*cursor).y = ((*cursor).y-1)%9;
                break;
            }
            case 2: {
                (*cursor).x = ((*cursor).x-1)%9;
                break;
            }
            case 3: {
                (*cursor).x = ((*cursor).x+1)%9;
                break;
            }
        }
        if ((*cursor).dir == right || ((*cursor).dir) == up){
            if ((*cursor).y == 0){
                (*cursor).y = 1;
            }
            if ((*cursor).x == 0){
                (*cursor).x = 1;
            }
        } else {
            if ((*cursor).y == 0){
                (*cursor).y = 8;
            }
            if ((*cursor).x == 0){
                (*cursor).x = 8;
            }
        }
        cursor->dir = prior->dir;
        prior = cursor;
        //接下来将父节点的dir给子节点
        cursor = cursor->next;
    }
}

//不修改头节点，就不添加返回值了
//思路为头节点后面直接补充一个
void addBody() {
    SnackBody * cursor = &snack;
    SnackBody tail;
    while (cursor->next != NULL){
        cursor = cursor->next;
    }
    tail.next = NULL;
    tail.dir = cursor->dir;
    tail.x = cursor->x;
    tail.y = cursor->y;
    switch (cursor->dir) {
        case 0: {
            tail.y = ((*cursor).y-1)%9;
            break;
        }
        case 1: {
            tail.y = ((*cursor).y+1)%9;
            break;
        }
        case 2: {
            tail.x = ((*cursor).x+1)%9;
            break;
        }
        case 3: {
            tail.x = ((*cursor).x-1)%9;
            break;
        }
    }
    if ((*cursor).dir == right || ((*cursor).dir) == up){
        if (tail.y == 0){
            tail.y = 1;
        }
        if (tail.x == 0){
            tail.x = 1;
        }
    } else {
        if (tail.y == 0){
            tail.y = 8;
        }
        if (tail.x == 0){
            tail.x = 8;
        }
    }
    cursor->next = &tail;
}

void createBeen() {
    beenX = rand()%8 + 1;
    beenY = rand()%8 + 1;
}

void DelayMs(unsigned int i) //0.14ms误差 0us
{
    while (i--);
}

void delay(int level) {
    switch (level) {
        case 0: {
            delay1s();
            break;
        }
        case 1: {
            delay700ms();
            break;
        }
        case 2: {
            delay500ms();
            break;
        }
        case 3: {
            delay300ms();
            break;
        }
    }
}
unsigned char image [8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
struct SnackBody *cursor;
//在点阵屏上面展示蛇身
void showPic() {

    int a;
    cursor = &snack;
    for (a = 0; a < 8; ++a) {
        image[a] = 0x00;
    }
    while (cursor != NULL) {
        //image[0] = image[0] | single<<(0);
        //将xy坐标转译为char数组
        if (cursor->x != 0 && cursor->y != 0){
            image[cursor->y - 1] = image[cursor->y - 1] | 0x80>>(cursor->x - 1);
        }
        cursor = cursor->next;
    }
    //接下来展示豆子
    image[beenY - 1] = image[beenY - 1] | 0x80>>(beenX - 1);
    if (snack.x == beenX && snack.y == beenY){
        //表示蛇已经恰倒了实物
        createBeen();
        addBody();
    }
}

void turnDir(unsigned char dir) {
    switch (dir) {
        {
            case 0x18:
                snack.dir = up;
            break;
            case 0x08://4
                snack.dir = left;
            break;
            case 0x5a:
                snack.dir = right;
            break;
            case 0x52:
                snack.dir = down;
            break;
        }
    }
}

void onKeyDown() interrupt 0
{
    u8 j, k;
    u16 err;
    Time = 0;
    DelayMs(700);
    if (IRIN == 0) {
        err = 1000;
        while ((IRIN == 0) && (err > 0)) {
            DelayMs(1);
            err--;
        }
        if (IRIN == 1) {
            err = 500;
            while ((IRIN == 1) && (err > 0)) {
                DelayMs(1);
                err--;
            }
            for (k = 0; k < 4; k++) {
                for (j = 0; j < 8; j++) {

                    err = 60;
                    while ((IRIN == 0) && (err > 0)) {
                        DelayMs(1);
                        err--;
                    }
                    err = 500;
                    while ((IRIN == 1) && (err > 0)) {
                        DelayMs(10); //0.1ms
                        Time++;
                        err--;
                        if (Time > 30) {
                            return;
                        }
                    }
                    IrValue[k] >>= 1;
                    if (Time >= 8) {
                        IrValue[k] |= 0x80;
                    }
                    Time = 0;
                }
            }
        }
        turnDir(IrValue[2]);
        if (IrValue[2] != ~IrValue[3]) {
            return;
        }
    }
}
/*void timerConfig() {
    TMOD |= 0x10; //设置定时计数器工作方式1为定时器
    TH1 = 0xff;
    TL1 = 0xff;
    ET1 = 1; //开启定时器1中断
    TR1 = 1; //开启定时器
}*/

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
        _nop_();
        _nop_();
        SRCLK=1;
        SRCLK=0;
    }

    LCLK=1;
    _nop_();
    _nop_();
    RCLK=0;
}

void showByList(){
    int i;
    int a = 0;
    P0 = 0xff;
    while (a <= 1000){
        for (i = 0; i < 8; ++i) {
            //首先完成对P0口的赋值
            P0 = ~image[i];
            //接下来进行移位寄存器的处理
            hd595(ledduan[i]);
            delay1ms();
            hd595(0x00);
            a++;
        }
    }
    //在这里之后需要启动下一步
    nextStep();
    showPic();
    showByList();
}

/*void timeCur() *//*interrupt 3*//*
{
    TH1 = 0xff; //重新赋初值
    TL1 = 0xff;
    timer++;
    if (timer >= 100000 *//*&& isAlive()*//*){
        timer = 0;
        //进行下一步操作
        nextStep();
        showPic();
    }
}*/


void gameMain() {
    int level;
    createSnack();
    createBeen();
    //选择游戏难度
    //level = chooseLevel();
    level = 0;
    //初始化红外遥控器
    irInit();
    //正式打开游戏
    showPic();
    showByList();
}