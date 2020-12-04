#pragma once


#include <deque>

using namespace std;

class Wall {
private:
	deque<bool> walls;
	int height;

public:
	Wall(int width);
	void push(bool isWall);
	void pop();
	bool checkPos(int pos);
	void changeDir();
};