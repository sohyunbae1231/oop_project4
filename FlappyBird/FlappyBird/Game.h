#pragma once
#include <iostream>
#include "Wall.h"
#include "Player.h"
#include "UI.h"

using namespace std;

class Game {
private:
	bool die;
	int laneNum;
	int width;
	int score;
	int speed;
	Player* player;
	UI* ui;
	vector<Wall*>map;
	Control* control;
public:
	Game(int w , int h );
	~Game();
	void init();
	void draw();
	void move();
	void logic(int wallNum);
	void run();
	void end();
};
