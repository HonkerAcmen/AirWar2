#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h> 

#endif // !__MAIN_H__

// �ɻ��Ľṹ��
typedef struct {
	int x;
	int y;
}air;

// �����ĸ߿�
#define HIGH 15
#define WIDTH 25

#define ENEMY_NUM 5  
enum
{
	EMPTY = 0, // �ո�
	PLARYER, // ���
	BULL, // �ӵ�
	ENEMY // ����
};


void gotoxy(int x, int y);
void HideCursor();
void init_airPlayer(air *air_Player);
void init_airEnemy(air *airEnemy);
void show();
void updateNoInput(air *air_Player, air *air_Enemy);
void updateInput(air *air_Player);