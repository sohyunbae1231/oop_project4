#pragma once

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4
#include <conio.h>

class Control {
public:
	int keyControl();
	void gotoxy(int x, int y);
};