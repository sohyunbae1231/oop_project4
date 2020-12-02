#pragma once


#include <deque>

using namespace std;

class Lane {
private:
	deque <bool> cars;
	bool right;
public:
	Lane(int width);
	void move(int carNum);
	bool checkPos(int pos);
	void changeDir();
};