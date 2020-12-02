#include <deque>
#include "Lane.h"

using namespace std;

	Lane::Lane(int width) {
		for (int i = 0; i < width; i++)
			cars.push_front(false);
		right = rand() % 2;
	}
	void Lane:: move(int carNum ){//car move
		//int val = rand() % 20;
		if (right) {
			if (rand()%carNum == 1)
				cars.push_front(true);
			else
				cars.push_front(false);
			cars.pop_back();
		}
		else {
			if (rand()%carNum == 1)
				cars.push_back(true);
			else
				cars.push_back(false);
			cars.pop_front();
		}
	}
	bool Lane:: checkPos(int pos) {
		return cars[pos]; 
	}
	void Lane:: changeDir() { 
		right = !right; 
	}
