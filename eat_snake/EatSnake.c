/**
 * Author: RayleighZ
 * Time: 2020-12-15 20:40
 * Describe: C51 8位机 点阵屏 贪吃蛇游戏
 */
#include "EatSnake.h"
#include <stdlib.h>
#include "../delay_tool/DelayTool.h"

int up = 0;
int down = 1;
int left = 2;
int right = 3;

int beenX;
int beenY;

int screenSize = 8;//点阵屏的宽度大小

typedef struct SnackBody{
    struct SnackBody * prior;
    struct SnackBody * next;
    int x;
    int y;
    int dir;
} SnackBody;

//不修改头节点，就不添加返回值了
void addBody(){

}

struct SnackBody* createSnack(){
    struct SnackBody* snackHead = (struct SnackBody *) malloc (sizeof(struct SnackBody));
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

int isAlive(struct SnackBody * snackHead){
    int headX = snackHead->x;
    int headY = snackHead->y;
    struct SnackBody * cursor = snackHead;//检索遍历用的游标
    while (cursor->next != NULL){//遍历检索，如果蛇头和蛇身碰撞，就判定游戏结束
        if (cursor->y == headY && cursor->x == headX){
            return 0;
        }
        cursor = cursor->next;//游标移动
    }
    return 1;
}

void move(struct SnackBody * snackBody){
    switch (snackBody->dir) {
        case up:{
            snackBody->y = (snackBody->y++)%screenSize;
            break;
        }
        case down:{
            snackBody->y = (snackBody->y--)%screenSize;
            break;
        }
        case left:{
            snackBody->x = (snackBody->x--)%screenSize;
            break;
        }
        case right:{
            snackBody->x = (snackBody->x++)%screenSize;
            break;
        }
    }
}

void nextStep(struct SnackBody * head){
    //遍历蛇身，让它前进
    struct SnackBody * cursor = head;
    while (cursor->next != NULL){
        move(cursor);
    }
}

int chooseLevel(){
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

void createBeen(){

}

void delay(int level){
    switch (level) {
        case 0:{
            delay1s();
            break;
        }
        case 1:{
            delay700ms();
            break;
        }
        case 2:{
            delay500ms();
            break;
        }
        case 3:{
            delay300ms();
            break;
        }
    }
}

//在点阵屏上面展示蛇身
void showPic(struct SnackBody * head){
    //不知道会不会爆内存
    int xs[screenSize*screenSize];
    int ys[screenSize*screenSize];
    int position = 0;
    struct SnackBody * cursor = head;
    while (cursor->next != NULL){
        switch (cursor->x) {
            case 0:{
                P0 = P0&0x01;
                break;
            }
            case 1:{
                P0 = P0&0x02;
                break;
            }
            case 2:{
                P0 = P0&0x04;
                break;
            }
            case 3:{
                P0 = P0&0x08;
                break;
            }
            case 4:{
                P0 = P0&0x10;
                break;
            }
            case 5:{
                P0 = P0&0x20;
                break;
            }
            case 6:{
                P0 = P0&0x40;
                break;
            }
            case 7:{
                P0 = P0&0x80;
                break;
            }
        }
        position++;
    }
}

void main(){
    int level;
    struct SnackBody * snack = createSnack();
    //选择游戏难度
    level = chooseLevel();
    while (isAlive(snack)){
        //首先判断延迟时间（游戏速率）
        delay(level);
    }
}