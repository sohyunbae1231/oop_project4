#pragma once


#include <vector>
#include <iostream>
#include "Lane.h"
#include "Player.h"
#include "UI.h"

<<<<<<< HEAD

=======
>>>>>>> 8b4dea3e1cfadf12abc3a182b49da3ff0c4ee0ec
using namespace std;

class Game {
private:
	bool quit;
	int laneNum;
	int width;
	int score;
	Player* player;
	UI* ui;
	vector<Lane*>map;
public:
	Game(int w = 20, int h = 10);
	~Game();
	void init();
	void draw();
	void move();
	void logic(int carSpeed, int carNum);
	void run();
	void end();
};
