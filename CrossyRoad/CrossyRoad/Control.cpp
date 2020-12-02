#include "Control.h"
#include <Windows.h>

int Control::keyControl() {
	char key = _getch();
	if (key == 'w' || key == 'W') {
		return UP;
	}
	else if (key == 'a' || key == 'A') {
		return LEFT;
	}
	else if (key == 's' || key == 'S') {
		return DOWN;
	}
	else if (key == 'd' || key == 'D') {
		return RIGHT;
	}
	else if (key == ' ') {
		return SUBMIT;
	}
}
void Control::gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}