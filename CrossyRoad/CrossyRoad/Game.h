#pragma once


#include <vector>
#include <iostream>
#include "Lane.h"
#include "Player.h"
#include "UI.h"


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
	int levelui();
	void draw();
	void move();
	void logic(int carSpeed, int carNum);
	void run();
	void end();
};