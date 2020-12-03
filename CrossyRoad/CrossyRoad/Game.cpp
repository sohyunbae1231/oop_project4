#include <vector>
#include "Game.h"


using namespace std;


	Game::Game(int w , int h ) {//w=30, h=5

		laneNum = h;
		width = w;
		quit = false;
	}
	Game::~Game() {
		delete player;
		delete ui;
		for (int i = 0; i < map.size(); i++) {
			Lane* current = map.back();
			map.pop_back();
			delete current;
		}
	}

	void Game::init() {
		//Size of Window and title
		system("mode con cols=80 lines=60 | title Crossy Road");
		//Set quit(dead) state false
		quit = false;
		//set score 0
		score = 0;
		//Hide Cursor
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);//get console handle
		CONSOLE_CURSOR_INFO ConsoleCursor;
		ConsoleCursor.bVisible = 0;// 0 : cursor hide
		ConsoleCursor.dwSize = 1;
		SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

		//Initialize map with no cars
		for (int i = 0; i < laneNum; i++)
			map.push_back(new Lane(width));

		player = new Player(width);
		ui = new UI();
	}

	void Game:: draw() {
		ui->setColor(WHITE, BLACK);
		COORD pos;
		for (int i = 0; i < laneNum; i++) {
			for (int j = 0; j < width; j++) {
				pos.X = j+24;
				pos.Y = i+10;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
				if (i == 0 && (j == 0 || j == width - 1))
					cout << "□";
				if (i == laneNum - 1 && (j == 0 || j == width - 1))
					cout << "■";
				if (map[i]->checkPos(j) && i != 0 && i != laneNum - 1) {
					ui->setColor(RED, BLACK);
					cout << "▣";
				}
				else if (player->x == j && player->y == i) {
					ui->setColor(LIGHTCYAN, BLACK);
					cout << "▽";
				}
				else
					cout << " ";
			}
			cout << endl;
		}
		cout << "Score: " << score << endl;
	}

	void Game::logic(int carSpeed, int carNum) {
		for (int i = 1; i < laneNum - 1; i++) {
			if (rand()%carSpeed == 1)//car moves randomly
				map[i]->move(carNum);
			if (map[i]->checkPos(player->x) && player->y == i) {
				quit = true;
				ui->deadDraw();
			}
		}
		if (player->y == laneNum - 1) {//when player gets to the finish line
			score++;
			player->y = 0;
			cout << "\x07";//alarm sound
			map[rand() % laneNum]->changeDir();
		}
	}

	void Game::move() {
		if (_kbhit()) {
			char key = _getch();
			switch (key) {
			case 'w':
				if (player->y - 1 >= 0)
					player->y--;
				break;
			case 's':
					player->y++;
				break;

			case 'd':
				if(player->x+1<width)
				 player->x++;
				break;
			case 'a':
				if(player->x-1>0)
					player->x--;
				break;
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
		while (1) {
			init();
			int menuCode, levelCode;
			
			ui->titleDraw();
			menuCode=ui->menuDraw();
			if (menuCode == 0) {//Game Start
				system("cls");
				levelCode = ui->levelDraw();//Level Select Menu

				int carSpeed, carNum;//game becomes harder when carSpeed, carNum gets smaller

				if (levelCode == 0) {
					carSpeed = 10;
					carNum = 20;
				}
				else if (levelCode == 1) {
					carSpeed = 8;
					carNum = 15;
				}
				else if (levelCode == 2) {
					carSpeed = 5;
					carNum = 14;
				}

				system("cls");
				while (!quit) {//게임에서 죽을 때까지 3가지 반복
					move();
					draw();
					logic(carSpeed, carNum);
				}
			}
			else if (menuCode == 1) {//KEY info 화면
				ui->infoDraw();
			}
			else if (menuCode == 2) {//Game 종료
				system("cls");
				return;
			}
			system("cls");
		}
	}