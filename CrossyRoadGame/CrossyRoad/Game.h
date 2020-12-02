#pragma once


#include <vector>
#include <iostream>
#include "Lane.h"
#include "Player.h"
#include "UI.h"

//#define UP 0
//#define DOWN 1
//#define LEFT 2
//#define RIGHT 3
//#define SUBMIT 4

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
	//Game();
	Game(int w = 20, int h = 10);
	~Game();
	void init();/*
	void ui();
	int menuui();
	void titleui();
	void infoui();
	void deadui();
	int levelui();*/
	void draw();
	void move();
	/*void gotoxy(int x, int y);
	int keyControl();*/
	void logic(int carSpeed, int carNum);
	void run();
	void end();
};