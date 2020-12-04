#include "UI.h"
#include <iostream>
using namespace std;



void UI::setColor(int foreground, int background) {
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void UI::titleDraw() {
	setColor(WHITE, BLACK);
	cout << "\n\n\n\n\n";
	cout << "  #########   ##            #####     ##########    #########   ###      ###" << endl;
	cout << "  ##          ##          ##     ##   ##      ##    ##     ##   ###      ###" << endl;
	cout << "  ##          ##          ##     ##   ##      ##    ##     ##   ###      ###" << endl;
	cout << "  #########   ##          #########   ##########    #########   ############" << endl;
	cout << "  ##          ##          ##     ##   ##            ##              ####    " << endl;
	cout << "  ##          ##          ##     ##   ##            ##              ####    " << endl;
	cout << "  ##          #########   ##     ##   ##            ##              ####    " << endl;
	cout << "\n\n\n\n\n";
	cout << "              ########    #########   ########      #######                 " << endl;
	cout << "              ##     ##      ###      ###    ###    ##     ##               " << endl;
	cout << "              ##     ##      ###      ###    ###    ##     ##               " << endl;
	cout << "              #########      ###      #########     ##     ##               " << endl;
	cout << "              ##     ##      ###      ###    ###    ##     ##               " << endl;
	cout << "              ##     ##      ###      ###    ###    ##     ##               " << endl;
	cout << "              ########    #########   ###    ###    #######                 " << endl;
}

int UI::menuDraw() {
	control = new Control();
	int x = 30;
	int y = 32;

	control->gotoxy(x - 4, y - 3);
	cout << "[ Press W,S key to move ]\n";

	control->gotoxy(x, y);
	cout << "<< MENU >>\n";

	setColor(LIGHTGREEN, BLACK);
	control->gotoxy(x, y + 1);
	cout << "START GAME\n";

	control->gotoxy(x, y + 2);
	cout << "KEY INFO\n";

	control->gotoxy(x, y + 3);
	cout << "GAME OVER\n";

	setColor(WHITE, BLACK);


	while (1) {
		int n = control->keyControl();
		switch (n) {
		case UP:
			if (y > 33) {
				control->gotoxy(x - 2, y);
				cout << " ";
				control->gotoxy(x - 2, --y);
				cout << ">";
			}
			break;

		case DOWN:
			if (y < 35) {
				control->gotoxy(x - 2, y);
				cout << " ";
				control->gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;

		case SUBMIT:
			return y - 33;
			break;
		}
	}
}


void UI::deadDraw() {
	control = new Control();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n                            YOU ARE DEAD\n\n";
	cout << "                    PRESS SPACE BAR TO GO BACK TO MENU";
	while (1) {
		if (control->keyControl() == SUBMIT) {
			break;
		}
	}
}

int UI::levelDraw() {
	control = new Control();
	system("cls");
	setColor(WHITE, BLACK);
	int x = 30;
	int y = 12;

	control->gotoxy(x - 4, y - 3);
	cout << "[ Press W,S key to move ]\n";
	control->gotoxy(x, y);
	cout << "<< LEVEL >>\n";

	control->gotoxy(x, y + 1);
	setColor(LIGHTBLUE, BLACK);
	cout << "EASY MODE\n";

	control->gotoxy(x, y + 2);
	setColor(YELLOW, BLACK);
	cout << "MEDIUM MODE\n";

	control->gotoxy(x, y + 3);
	setColor(RED, BLACK);
	cout << "HARD MODE\n";

	setColor(WHITE, BLACK);


	while (1) {
		int n = control->keyControl();
		switch (n) {
		case UP:
			if (y > 13) {
				control->gotoxy(x - 2, y);
				cout << " ";
				control->gotoxy(x - 2, --y);
				cout << ">";
			}
			break;

		case DOWN:
			if (y < 15) {
				control->gotoxy(x - 2, y);
				cout << " ";
				control->gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;

		case SUBMIT:
			//0 : Easy
			//1 : SOSO
			//2 : HARD
			//3 : QUIT
			return y - 13;
		}
	}
}

void UI::infoDraw() {
	control = new Control();
	system("cls");
	cout << "\n\n\n\n\n\n";
	cout << "                    SELECT, JUMP : Space Bar     \n\n\n\n";
	cout << "                     ( PRESS Space Bar to exit )";

	while (1) {
		if (control->keyControl() == SUBMIT) {
			break;
		}
	}
}