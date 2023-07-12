#include "AirWar.h"

int main() {
	air air_Player;
	air Enemy[ENEMY_NUM];
	init_airPlayer(&air_Player);
	init_airEnemy(Enemy);

	while (1) {
		show();
		updateNoInput(&air_Player, Enemy);
		updateInput(&air_Player);
	}

	return 0;
}