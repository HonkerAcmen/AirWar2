#include "AirWar.h"

// 画布
int canvas[HIGH][WIDTH] = { EMPTY };
// 分数
int score = 0;
// 敌人的移动速度
int EnemyMoveSpeed = 20;

// 指定光标位置
void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// 隐藏光标
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 初始化本机
void init_airPlayer(air *air_Player) {
	air_Player->x = HIGH - 1;
	air_Player->y = WIDTH / 2;
	canvas[air_Player->x][air_Player->y] = PLARYER;
}

// 初始化敌机
void init_airEnemy(air *airEnemy) {
	srand((unsigned)time(NULL));
	for (int index_ENEMY_NUM = 0; index_ENEMY_NUM < ENEMY_NUM; index_ENEMY_NUM++) {
		airEnemy[index_ENEMY_NUM].x = rand() % 2;
		airEnemy[index_ENEMY_NUM].y = rand() % WIDTH;
		canvas[airEnemy[index_ENEMY_NUM].x][airEnemy[index_ENEMY_NUM].y] = ENEMY;
	}
	HideCursor(); // 隐藏光标
}

// 显示各类值
void show() {
	gotoxy(0, 0);
	for (int index_HIGH = 0; index_HIGH < HIGH; index_HIGH++) {
		for (int index_WIDTH = 0; index_WIDTH < WIDTH; index_WIDTH++) {
			if (canvas[index_HIGH][index_WIDTH] == EMPTY) {
				printf(" "); // 空格，表示没有东西
			}
			else if (canvas[index_HIGH][index_WIDTH] == PLARYER) {
				printf("*"); // * 是玩家
			}
			else if (canvas[index_HIGH][index_WIDTH] == BULL) {
				printf("|"); // 子弹
			}
			else if (canvas[index_HIGH][index_WIDTH] == ENEMY) {
				printf("@"); // 敌人
			}
		}
		printf("\n");
	}
	printf("歼敌数：%d\n", score);
	Sleep(20);
}

void updateNoInput(air *air_Player, air *air_Enemy) {
	for (int index_HIGH = 0; index_HIGH < HIGH; index_HIGH++) {
		for (int index_WIDTH = 0; index_WIDTH < WIDTH; index_WIDTH++) {
			if (canvas[index_HIGH][index_WIDTH] == BULL) {
				// 关于子弹的交互
				for (int index_ENEMY_NUM = 0; index_ENEMY_NUM < ENEMY_NUM; index_ENEMY_NUM++) {
					if (air_Enemy[index_ENEMY_NUM].x == index_HIGH && air_Enemy[index_ENEMY_NUM].y == index_WIDTH) {
						score++;
						// 置空被子弹击中的敌军
						canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = EMPTY;
						// 重新生成敌军
						air_Enemy[index_ENEMY_NUM].x = rand() % 2;
						air_Enemy[index_ENEMY_NUM].y = rand() % WIDTH;
						// 重新在画布上将重新生成的敌军赋值
						canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = ENEMY;
						// 子弹为空
						canvas[index_HIGH][index_WIDTH] = EMPTY;
					}
				}
				// 移动子弹
				canvas[index_HIGH][index_WIDTH] = EMPTY;
				if (index_HIGH > 0) {
					canvas[index_HIGH - 1][index_WIDTH] = BULL;
				}
			}
		}
	}

	static int speed = 0;
	if (speed < EnemyMoveSpeed) {
		speed++;
	}

	for (int index_ENEMY_NUM = 0; index_ENEMY_NUM < ENEMY_NUM; index_ENEMY_NUM++) {
		// 敌机如果和我机碰撞
		if (air_Player->x == air_Enemy[index_ENEMY_NUM].x && air_Player->y == air_Enemy[index_ENEMY_NUM].y || score < 0) {
			system("cls");
			printf("游戏结束\n");
			system("pause");
			exit(0);
		}

		// 敌机如果逃了
		if (air_Enemy[index_ENEMY_NUM].x > HIGH) {
			score--;
			canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = EMPTY;
			// 重新生成敌军
			air_Enemy[index_ENEMY_NUM].x = rand() % 2;
			air_Enemy[index_ENEMY_NUM].y = rand() % WIDTH;
			canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = ENEMY;
		}

		if (speed == EnemyMoveSpeed) {
			for (int index_ENEMY_NUM = 0; index_ENEMY_NUM < ENEMY_NUM; index_ENEMY_NUM++) {
				canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = EMPTY;
				air_Enemy[index_ENEMY_NUM].x++;
				speed = 0;
				canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = ENEMY;
			}
		}
	}
}

void updateInput(air *air_Player) {
	char input;
	// 判断用户是否有输入
	if (kbhit()) {
		input = getch();
		if (input == 'a' && air_Player->y > 0) {
			canvas[air_Player->x][air_Player->y] = EMPTY;
			air_Player->y--;
			canvas[air_Player->x][air_Player->y] = PLARYER;
		}
		else if (input == 'd' && air_Player->y < WIDTH) {
			canvas[air_Player->x][air_Player->y] = EMPTY;
			air_Player->y++;
			canvas[air_Player->x][air_Player->y] = PLARYER;
		}
		else if (input == 'w' && air_Player->x > 0) {
			canvas[air_Player->x][air_Player->y] = EMPTY;
			air_Player->x--;
			canvas[air_Player->x][air_Player->y] = PLARYER;
		}
		else if (input == 's' && air_Player->x < HIGH) {
			canvas[air_Player->x][air_Player->y] = EMPTY;
			air_Player->x++;
			canvas[air_Player->x][air_Player->y] = PLARYER;
		}
		else if (input == ' ') {
			// 指定子弹的初始位置
			canvas[air_Player->x - 1][air_Player->y] = BULL;
		}
	}
}