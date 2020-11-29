#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;


// 연결리스트
typedef struct NODE {
	string name;
	string game;
	int score;
}LIST;

// 연결리스트 생성(일단 선입선출 방식)
LIST makebody(string game, string name, int score)
{
	LIST body = { "", "", 0 };

	body.name.append(name);
	body.game.append(game);
	body.score = score;

	return body;
}

bool compare1(LIST a, LIST b) { return a.game < b.game; }
bool compare2(LIST a, LIST b) { return a.name < b.name; }
bool compare3(LIST a, LIST b) { return a.score < b.score; }



class History {
	int size;
	LIST* std_list;

public:
	History(string fname) {
		size = 0;
		std_list = NULL;
		string std_line;
		std_list = new LIST[1000];

		ifstream file(fname);
		// '/' parse 과정
		while (getline(file, std_line))
		{
			if (std_line != "\n") {
				int str_cnt = 0;
				char* str = new char[1000];
				string* str_arr = new string[4];

				strcpy(str, std_line.c_str());

				char* tok = strtok(str, "/");
				while (tok != nullptr)
				{
					str_arr[str_cnt++] = string(tok);
					tok = strtok(nullptr, "/");
				}
				// 데이터 리스트에 집어넣기
				std_list[size++] = makebody(str_arr[0], str_arr[1], atoi(str_arr[2].c_str()));
			}
		}
	}

	// public 사용 함수
	int showSize() { return size; }
	LIST* showList() { return std_list; }


	//sort
	void sorting(int sort_opt) {
		LIST a, b;
		if (sort_opt == 1) { // game
			sort(std_list, std_list + size, compare1);
		}
		else if (sort_opt == 2) { //  name
			sort(std_list, std_list + size, compare2);
		}
		else if (sort_opt == 3) { //  score
			sort(std_list, std_list + size, compare3);
		}
	}
	// print
	void print(int select, string str) {
		printf("%-16s%-11s%-25s%\n", "Game", "Name", "Score");
		if (select == 1) {
			for (int i = 0; i < size; i++)
				if (std_list[i].game == str)
					printf("%-16s%-11s%-25d\n"
						, std_list[i].game.c_str(), std_list[i].name.c_str(), std_list[i].score);
		}
		else if (select == 2) {
			for (int i = 0; i < size; i++)
				if (std_list[i].name == str)
					printf("%-16s%-11s%-25d\n"
						, std_list[i].game.c_str(), std_list[i].name.c_str(), std_list[i].score);
		}
		else if (select == 3) {
			for (int i = 0; i < size; i++)
				printf("%-16s%-11s%-25d\n"
					, std_list[i].game.c_str(), std_list[i].name.c_str(), std_list[i].score);
		}
	}

};