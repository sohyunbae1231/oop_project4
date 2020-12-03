#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <Windows.h>

#include "numPuzzle.h"
#include "history.h"
using namespace std;

// 이 함수 사용해서 데이터 기록해주세요!
void writeHistory(string game, string name, int score) {
	ofstream ofile; ofile.open("file.txt", ios::app);
	ofile << game + "/" + name + "/" + to_string(score) + "\n"; 
	ofile.close();
}

int main() {
	char input[250];

	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n");
		printf("%35s", " "); cout << "---------------OOP_MINI_GAMES---------------\n\n";
		printf("%35s", " "); cout << "               0. 기록\n";
		printf("%35s", " "); cout << "               1. 길건너친구들\n";
		printf("%35s", " "); cout << "               2. 숫자 퍼즐\n";
		printf("%35s", " "); cout << "               3. Bulls and Cows\n";
		printf("%35s", " "); cout << "               4. 똥 피하기\n";
		printf("%35s", " "); cout << "               end. 종료\n\n";
		printf("%35s", " "); cout << "--------------------------------------------\n";
		printf("%35s", " "); cout << ": ";  cin >> input;



		// 기록 실행문 _ 정석훈
		int sort_opt = 1;
		if (!strcmp(input, "0")) {
			int searchNum;
			History hist("file.txt");
			hist.sorting(sort_opt);

			while (1)
			{
				system("cls");
				cout << "--------------------기록--------------------\n\n";
				cout << "               1. Search\n";
				cout << "               2. Sortin Option\n";
				cout << "               3. 종료\n\n";
				cout << "--------------------------------------------\n";
				cout << ": ";  cin >> searchNum;
				

				// 1번
				if (searchNum == 1) {
					while (1) {
						int select;
						string keyword;
						cout << "\n\n- Search -\n";
						cout << "1. Search by game\n";
						cout << "2. Search by name\n";
						cout << "3. List All\n";
						cin >> select;
						if (select == 1) { 
							cout << "game keyword? "; cin >> keyword; hist.print(select, keyword); 
							cout << "\n\n계속하실려면 아무 문장을 적고 ENTER를 눌러주세요."; cin >> keyword; break; 
						}
						else if (select == 2) { 
							cout << "name keyword? "; cin >> keyword; hist.print(select, keyword);
							cout << "\n\n계속하실려면 아무 단어을 적고 ENTER를 눌러주세요."; cin >> keyword; break;
						}
						else if (select == 3) { 
							hist.print(select, keyword); 
							cout << "\n\n계속하실려면 아무 단어을 적고 ENTER를 눌러주세요."; cin >> keyword; break;
						}
						else { cout << "1~3번 중 하나를 선택하시오\n\n"; }
						
					}
				}

				// 2번
				else if (searchNum == 2) {
					while (1)
					{
						int select;
						cout << "\n\n- Sorting Option -\n";
						cout << "1. Sort by game\n";
						cout << "2. Sort by name\n";
						cout << "3. Sort by score\n";
						cin >> select;
						if (select > 0 && select < 4) { sort_opt = select; hist.sorting(sort_opt); break; }
						else { cout << "1~3 번 중 하나를 선택하시오\n\n"; }
					}

				}

				//3번
				else if (searchNum == 3) {
					cout << "프로그램이 종료됩니다.\n"; break;
				}

				// 잘못된 입력
				else {
					cout << "잘못된 입력입니다.\n";
				}
			}

		}


		// 길건너친구들 실행문 _ 김효민
		else if (!strcmp(input, "1")) { 
			system("cls");

		}


		// 숫자 퍼즐 실행문 _ 정석훈
		else if (!strcmp(input, "2")) {
			char select[250];
			string player;
			bool isRank = false;
			int selHist;
			numBox *puzzle;

			while (1) {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n");
				printf("%35s", " "); cout << "--------------------------------------------\n";
				printf("%35s", " "); cout << "               1. 3 X 3\n";
				printf("%35s", " "); cout << "               2. 4 X 4\n";
				printf("%35s", " "); cout << "               3. 5 X 5\n\n";
				printf("%35s", " "); cout << "     **5 X 5는 점수를 기록할 수 없습니다**\n";
				printf("%35s", " "); cout << "--------------------------------------------\n";
				printf("%35s", " "); cout << ": ";  cin >> select;

				if (!strcmp(select, "1")) { numBox puzz = numBox(3, 3); puzzle = &puzz; isRank = true; break; }
				else if (!strcmp(select, "2")) { numBox puzz = numBox(4, 4); puzzle = &puzz; isRank = true; break;}
				else if (!strcmp(select, "3")) { numBox puzz = numBox(5, 5); puzzle = &puzz; break;}
				else printf("%35s", " "); cout << "- 목록에 존재하는 값을 입력해주세요\n\n.";
			}
			puzzle->shuffle();

			while (!puzzle->isComplete()) {
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n");
				puzzle->print();
				printf("\n%35s", " "); printf("움직인 횟수: %d\n", puzzle->count);
				printf("\n%35s", " "); printf("포기하고 싶으시다면 end를 입력해주세요", puzzle->count);
				printf("\n%35s", " "); cout << "몇 번째 칸을 움직이실 건가요?: ";  cin >> select;

				if (!strcmp(select, "end")) { isRank = false; break;}
				if (!atoi(select) | atoi(select) > puzzle->getSize()) { printf("\n%28s", " "); cout << "올바른 숫자를 입력해 주세요!"; Sleep(1000); }
				else if (puzzle->go(atoi(select) - 1)) puzzle->count++;
				else { printf("\n%35s", " "); cout << "해당위치로 이동할 수 없습니다!"; Sleep(1000); }

				if(puzzle->isComplete()) { printf("\n%28s", " "); printf("총 %d 번 움직여 완성했습니다.", puzzle->count); Sleep(3000); }
			}
			
			if (isRank) {
				printf("\n%28s", " "); printf("지금 점수를 기록하시겠습니까? 1. 예   2. 아니요 :"); cin >> selHist;
				if (selHist == 1) {
					printf("\n%28s", " "); cout << "기록할 이름을 정해주세요 : "; cin >> player;
					writeHistory("NumPuzzle", player, puzzle->count);
				}

			}
		}


		// Bulls and Cows _ 배소현
		else if (!strcmp(input, "3")) {
			system("cls");


		}


		// 똥 피하기 실행문 _ 임결
		else if (!strcmp(input, "4")) {
			system("cls");


		}


		// 종료
		else if (!strcmp(input, "end")) {
		printf("%35s", " "); cout << "- 프로그램을 종료하겠습니다.\n";
			return 0;
		}
		// 잘못된 값
		else {
			printf("%35s", " "); cout << "- 목록에 존재하는 값을 입력해주세요\n\n.";
			Sleep(1000);
		}


	}

}
