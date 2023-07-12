#include "AirWar.h"

// ����
int canvas[HIGH][WIDTH] = { EMPTY };
// ����
int score = 0;
// ���˵��ƶ��ٶ�
int EnemyMoveSpeed = 20;

// ָ�����λ��
void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

// ���ع��
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// ��ʼ������
void init_airPlayer(air *air_Player) {
	air_Player->x = HIGH - 1;
	air_Player->y = WIDTH / 2;
	canvas[air_Player->x][air_Player->y] = PLARYER;
}

// ��ʼ���л�
void init_airEnemy(air *airEnemy) {
	srand((unsigned)time(NULL));
	for (int index_ENEMY_NUM = 0; index_ENEMY_NUM < ENEMY_NUM; index_ENEMY_NUM++) {
		airEnemy[index_ENEMY_NUM].x = rand() % 2;
		airEnemy[index_ENEMY_NUM].y = rand() % WIDTH;
		canvas[airEnemy[index_ENEMY_NUM].x][airEnemy[index_ENEMY_NUM].y] = ENEMY;
	}
	HideCursor(); // ���ع��
}

// ��ʾ����ֵ
void show() {
	gotoxy(0, 0);
	for (int index_HIGH = 0; index_HIGH < HIGH; index_HIGH++) {
		for (int index_WIDTH = 0; index_WIDTH < WIDTH; index_WIDTH++) {
			if (canvas[index_HIGH][index_WIDTH] == EMPTY) {
				printf(" "); // �ո񣬱�ʾû�ж���
			}
			else if (canvas[index_HIGH][index_WIDTH] == PLARYER) {
				printf("*"); // * �����
			}
			else if (canvas[index_HIGH][index_WIDTH] == BULL) {
				printf("|"); // �ӵ�
			}
			else if (canvas[index_HIGH][index_WIDTH] == ENEMY) {
				printf("@"); // ����
			}
		}
		printf("\n");
	}
	printf("�ߵ�����%d\n", score);
	Sleep(20);
}

void updateNoInput(air *air_Player, air *air_Enemy) {
	for (int index_HIGH = 0; index_HIGH < HIGH; index_HIGH++) {
		for (int index_WIDTH = 0; index_WIDTH < WIDTH; index_WIDTH++) {
			if (canvas[index_HIGH][index_WIDTH] == BULL) {
				// �����ӵ��Ľ���
				for (int index_ENEMY_NUM = 0; index_ENEMY_NUM < ENEMY_NUM; index_ENEMY_NUM++) {
					if (air_Enemy[index_ENEMY_NUM].x == index_HIGH && air_Enemy[index_ENEMY_NUM].y == index_WIDTH) {
						score++;
						// �ÿձ��ӵ����еĵо�
						canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = EMPTY;
						// �������ɵо�
						air_Enemy[index_ENEMY_NUM].x = rand() % 2;
						air_Enemy[index_ENEMY_NUM].y = rand() % WIDTH;
						// �����ڻ����Ͻ��������ɵĵо���ֵ
						canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = ENEMY;
						// �ӵ�Ϊ��
						canvas[index_HIGH][index_WIDTH] = EMPTY;
					}
				}
				// �ƶ��ӵ�
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
		// �л�������һ���ײ
		if (air_Player->x == air_Enemy[index_ENEMY_NUM].x && air_Player->y == air_Enemy[index_ENEMY_NUM].y || score < 0) {
			system("cls");
			printf("��Ϸ����\n");
			system("pause");
			exit(0);
		}

		// �л��������
		if (air_Enemy[index_ENEMY_NUM].x > HIGH) {
			score--;
			canvas[air_Enemy[index_ENEMY_NUM].x][air_Enemy[index_ENEMY_NUM].y] = EMPTY;
			// �������ɵо�
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
	// �ж��û��Ƿ�������
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
			// ָ���ӵ��ĳ�ʼλ��
			canvas[air_Player->x - 1][air_Player->y] = BULL;
		}
	}
}