/**
 * Author: RayleighZ
 * Time: 2020-12-15 20:40
 * Describe: C51 8位机 点阵屏 贪吃蛇游戏
 */
#include "EatSnake.h"
#include <stdlib.h>
#include "../delay_tool/DelayTool.h"
#include "../gpu/GPU.h"
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

int beenX;
int beenY;

int screenSize = 8;//点阵屏的宽度大小

//成像数组，有待优化，因为这里进行了一次封装，
//所以只能通过大型数组来达到存储的效果
//也许可以考虑动态增添数组？
unsigned short *xs;
unsigned short *ys;
//链表的头节点
struct SnackBody *snack;

typedef struct SnackBody {
    struct SnackBody *prior;
    struct SnackBody *next;
    int x;
    int y;
    int dir;
} SnackBody;

//不修改头节点，就不添加返回值了
void addBody() {

}

struct SnackBody *createSnack() {
    struct SnackBody *snackHead = (struct SnackBody *) malloc(sizeof(struct SnackBody));
    //对生成的第一个头节点的方向进行赋值，默认蛇头方向为向上
    snackHead->dir = up;
    //对蛇头的初始位置进行赋值，默认位置为原点
    snackHead->x = 0;
    snackHead->y = 0;
    snackHead->next = NULL;
    //prior为null，标志着这个是头节点
    snackHead->prior = NULL;
    return snackHead;
}

int isAlive() {
    int headX = snack->x;
    int headY = snack->y;
    struct SnackBody *cursor = snack;//检索遍历用的游标
    while (cursor->next != NULL) {//遍历检索，如果蛇头和蛇身碰撞，就判定游戏结束
        if (cursor->y == headY && cursor->x == headX) {
            return 0;
        }
        cursor = cursor->next;//游标移动
    }
    return 1;
}

void move(struct SnackBody *snackBody) {
    switch (snackBody->dir) {
        case 0: {
            snackBody->y = (snackBody->y++) % screenSize;
            break;
        }
        case 1: {
            snackBody->y = (snackBody->y--) % screenSize;
            break;
        }
        case 2: {
            snackBody->x = (snackBody->x--) % screenSize;
            break;
        }
        case 3: {
            snackBody->x = (snackBody->x++) % screenSize;
            break;
        }
    }
}

void nextStep() {
    //遍历蛇身，让它前进
    struct SnackBody *cursor = snack;
    while (cursor->next != NULL) {
        move(cursor);
        cursor = cursor->next;
    }
}

int chooseLevel() {
    if (P3 != ~0x00) {
        delay10ms();
        if (P3 != ~0x00) {
            switch (P3) {
                case ~0x01: {//0001
                    return 0;
                }
                case ~0x02: {//0010
                    return 1;
                }
                case ~0x04: {//0100
                    return 2;
                }
                case ~0x08: {//1000
                    return 3;
                }
            }
        }
    }
}

void createBeen() {

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

//在点阵屏上面展示蛇身
void showPic() {
    //不知道会不会爆内存
    int position;
    struct SnackBody *cursor = snack;
    for (position = 0; position < screenSize * screenSize; ++position) {
        ys[position] = 0;
        xs[position] = 0;
    }
    position = 0;
    while (cursor->next != NULL) {
        xs[position] = cursor->x;
        ys[position] = cursor->y;
        position++;
    }
    showByList(xs, ys);
}

void preLoadImage() {//对成像数组进行预加载
    int position;
    //给数组分配内存空间
    xs = malloc(sizeof(unsigned short) * screenSize * screenSize);
    ys = malloc(sizeof(unsigned short) * screenSize * screenSize);
    for (position = 0; position < screenSize * screenSize; ++position) {
        ys[position] = 0;
        xs[position] = 0;
    }
}

void turnDir(unsigned char dir) {
    switch (dir) {
        {
            case 0x18:
                snack->dir = right;
            break;
            case 0x08://4
                snack->dir = up;
            break;
            case 0x5a:
                snack->dir = down;
            break;
            case 0x52:
                snack->dir = left;
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
        if (IrValue[2] != ~IrValue[3]) {
            turnDir(IrValue[2]);
            return;
        }
    }
}

void gameMain() {
    int level;
    snack = createSnack();
    //预加载成像数组
    preLoadImage();
    //选择游戏难度
    //level = chooseLevel();
    level = 0;
    //初始化红外遥控器
    irInit();
    xs[0] = 1;
    ys[0] = 1;
    showByList(xs , ys);
    /*while (1*//*isAlive()*//*) {
        //首先判断延迟时间（游戏速率）
        P0 = ~P0;
        delay(level);
        //nextStep();
        showPic();
    }*/
}