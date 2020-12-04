#include <vector>
#include "Wall.h"

using namespace std;

	Wall::Wall(int width) {
		//no wall, height 0
		for (int i = 0; i < width; i++)
			walls.push_back(false);

	}
	void Wall:: push(bool isWall ){//wall move
		//walls.pop_front();
		walls.push_back(isWall);
	}
	void Wall::pop() {
		walls.pop_front();
	}
	bool Wall:: checkPos(int pos) {
		return walls[pos]; 
	}