#include "Game.h"
#include <time.h>

int main() {
	srand(time(NULL));
	Game game(30, 6);
	game.run();
	game.end();
	return 0;
}