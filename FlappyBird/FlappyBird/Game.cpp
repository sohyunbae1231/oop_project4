#include <vector>
#include <time.h>
#include "Game.h"


using namespace std;


	Game::Game(int w , int h ) {//w=30, h=10
		laneNum = h;
		width = w;
		die = false;
		speed = 0;//player's falling speed
		//Initialize map with no walls
		for (int i = 0; i < laneNum; i++)
			map.push_back(new Wall(width));

		player = new Player(laneNum / 2);
		ui = new UI();
	}
	Game::~Game() {
		delete player;
		delete ui;
		for (int i = 0; i < map.size(); i++) {
			Wall* current = map.back();
			map.pop_back();
			delete current;
		}
	}

	void Game::init() {
		system("cls");
		//Set dead state false
		die = false;
		//set score 0
		score = 0;
		//Hide Cursor
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//get console handle
		CONSOLE_CURSOR_INFO ConsoleCursor;
		ConsoleCursor.bVisible = 0;// 0 : cursor hide
		ConsoleCursor.dwSize = 1;
		SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
	}

	void Game:: draw() {
		ui->setColor(WHITE, BLACK);
		COORD pos;
		for (int i = 0; i < laneNum; i++) {
			for (int j = 0; j < width; j++) {
				pos.X = j+24;
				pos.Y = i+10;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				//game boundary
				if ((i == 0 && j >= 0)||(i==laneNum-1&&j>=0)) {
					ui->setColor(WHITE, BLACK);
					cout << "¡Ø";
				}
				//draw player position
				else if (j==1 && player->y == i) {
					ui->setColor(LIGHTCYAN, BLACK);
					cout << "¡ä";
					ui->setColor(WHITE, BLACK);
				}
				//draw wall
				else if (map[i]->checkPos(j) && i != 0 && i != laneNum - 1) {
					ui->setColor(RED, BLACK);
					cout << "¡á";
				}
				//draw blank space
				else {
					cout << " ";
				}
			}
			ui->setColor(WHITE, BLACK);
			cout << endl;
		}
		cout << "Score: " << score << endl;
	}

	void Game::logic(int wallNum) {
		//make wall by Height and move wall
		int height = rand() % 8;
		int up = rand() % 2;
		if (rand() % wallNum == 1) {
			if (up==0) {
				for (int i = 1; i <= 1+height; i++) {
					map[i]->push(true);//make wall until height
				}
				for (int i = 2+height; i <= laneNum - 1; i++) {
					map[i]->push(false);//no wall after height
				}
			}
			else {
				for (int i = laneNum - 1; i >= laneNum - 1 - height; i--) {
					map[i]->push(true);
				}
				for (int i = laneNum - 2 - height; i >= 1; i--) {
					map[i]->push(false);
				}
			}
		}
		else {
			for (int i = 1; i <= laneNum-1 ; i++) {
				map[i]->push(false);
			}
		}
		//pop to move wall
		for (int i = 1; i <= laneNum - 1; i++) {
			map[i]->pop();
		}

		//when player dies
		if (player->y >= laneNum-1) {//if player fall down
			die = true;
			system("cls");
			ui->deadDraw();
		}
		for (int i = 1; i < laneNum - 1; i++) {//if player collide with wall
			if (map[i]->checkPos(player->x) && player->y == i) {
				die = true;
				system("cls");
				ui->deadDraw();
			}
		}
	}

	void Game::move() {
		if (_kbhit()) {
			char key = _getch();
			if (key == ' ') {
				if (player->y - 1 >= 1) {//if player can go up
					player->y--;
					score++;//score goes up when player jumps
				}
			}
		}
		//player goes down if no input
		else {
			speed++;
			if (speed == 2) {
				player->y++;
				speed = 0;
			}
		
		}
	}

	void Game::end() {
		cout << "\n\n\n\n\n";
		cout << "   ########     #####       ######     ##########                            " << endl;
		cout << "  ##          ##     ##   ##  ##  ##   ##                                    " << endl;
		cout << "  ##          ##     ##   ##  ##  ##   ##                                    " << endl;
		cout << "  ##  #####   #########   ##  ##  ##   ##########                            " << endl;
		cout << "  ##     ##   ##     ##   ##  ##  ##   ##                                    " << endl;
		cout << "  ##     ##   ##     ##   ##      ##   ##                                    " << endl;
		cout << "   ########   ##     ##   ##      ##   ##########                           " << endl;
		cout << "\n\n\n\n\n";
		cout << "                           #######    ##      ##    #########   ########    " << endl;
		cout << "                          ##     ##   ##      ##    ##          ##     ##   " << endl;
		cout << "                          ##     ##   ##      ##    ##          ##     ##   " << endl;
		cout << "                          ##     ##   ##      ##    #########   ########    " << endl;
		cout << "                          ##     ##   ##      ##    ##          ##     ##   " << endl;
		cout << "                          ##     ##    ##    ##     ##          ##     ##   " << endl;
		cout << "                           #######       ####       #########   ##     ##   " << endl;
	}
	
	void Game:: run() {
		//Size of Window and title
		system("mode con cols=80 lines=60 | title Flappy Bird");
		while (1) {
			init();
			int menuCode, levelCode;
			ui->titleDraw();
			menuCode=ui->menuDraw();
			if (menuCode == 0) {//Game Start
				system("cls");
				levelCode = ui->levelDraw();//Level Select Menu

				int wallNum=0;//game becomes harder when carSpeed, carNum gets smaller

				if (levelCode == 0) {
					wallNum = 15;
				}
				else if (levelCode == 1) {
					wallNum = 13;
				}
				else if (levelCode == 2) {
					wallNum = 8;
				}

				system("cls");
				while (!die) {//repeat until death
					if (wallNum) {
						move();
						logic(wallNum);
						draw();
					}
					else {//if level is not selected(press spacebar without moving)
						system("cls");
						control->gotoxy(24, 10);
						cout << "Select Level\n\n\n";
						cout << "(Press Space Bar to go to main menu)";
						while (1) {
							if (control->keyControl() == SUBMIT) {
								break;
							}
						}
						break;
					}
				}
			}
			else if (menuCode == 1) {//KEY info
				ui->infoDraw();
			}
			else if (menuCode == 2) {//Game End
				system("cls");
				return;
			}
			system("cls");
		}
	}

	int main() {
		srand(time(NULL));
		Game game(30, 20);
		game.run();
		game.end();
		return 0;
	}