#include "DDGame.h"
#include <iostream>
#include <Winuser.h>
#include <windows.h>
#include <string>

//생성자; 멤버변수들 초기화
DDGame::DDGame()
{
    player = new Object(13, 25, 'O'); //플레이어 객체 생성

    //똥 활성화 배열 초기화
    for (int i = 0; i < 50; i++)
        isDdongActive[i] = false;

    //기본 게임화면 틀 생성
    for (int i = 0; i <= 26; i++)
    {
        map[0][i] = '*';
        map[26][i] = '*';
    }

    for (int i = 1; i <= 25; i++)
    {
        map[i][0] = '*';
        map[i][26] = '*';
    }

    for (int i = 1; i <= 25; i++)
    {
        for (int j = 1; j <= 25; j++)
            map[i][j] = ' ';
    }

    for (int i = 0; i <= 26; i++)
        map[i][27] = 0;

    point = 0; //점수 초기화

    //랜덤 객체 생성
    random_device rd;
    gen = mt19937(rd());
    dis = uniform_int_distribution<int>(1, 25);
}

//플레이어과 똥과 충돌했는지 여부를 반환하는 함수
bool DDGame::IsCollision()
{
    for (int i = 0 ; i < 50; i++)
    {
        if (isDdongActive[i])
        {
            if (Ddong[i]->GetX() == player->GetX() && Ddong[i]->GetY() == player->GetY())
                return true;
        }
    }

    return false;
}

//똥들의 위치를 갱신하는 함수
void DDGame::UpdateDdongs()
{
    for (int i = 0; i < 50; i++)
    {
        if (isDdongActive[i]) //존재하는 똥에 대해
        {
            if (Ddong[i]->GetY() >= 25) //똥이 바닥에 닿으면
            {
                delete Ddong[i];
                isDdongActive[i] = false;
            }
            else //똥이 바닥에 닿은 상태가 아니면
            {
                Ddong[i]->SetY(Ddong[i]->GetY() + 1); //똥은 아래로 이동
            }
        }
        else //존재하지 않는 똥에 대해
        {
            if (dis(gen) < 2) //일정 확률로 똥 새로 생성
            {
                Ddong[i] = new Object(dis(gen), 1, 'v');
                isDdongActive[i] = true;
            }
        }
    }
}

//방향키 입력에 따라 플레이어를 움직이는 함수
void DDGame::MovePlayer()
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) //왼쪽 방향키
		player->SetX(player->GetX() - 1);
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) //오른쪽 방향키
		player->SetX(player->GetX() + 1);

	if (player->GetX() < 1) //맵 왼쪽 끝에 도달
		player->SetX(1);
	else if (player->GetX() > 25) //맵 오른쪽 끝에 도달
		player->SetX(25);
}

//게임화면을 문자열 형태로 만드는 함수
void DDGame::MakeMap()
{
    //배경
    for (int i = 1; i <= 25; i++)
    {
        for (int j = 1; j <= 25; j++)
            map[i][j] = ' ';
    }

    //똥들
    for (int i = 0; i < 50; i++)
    {
        if (isDdongActive[i])
            map[Ddong[i]->GetY()][Ddong[i]->GetX()] = Ddong[i]->GetShape();
    }

    map[player->GetY()][player->GetX()] = player->GetShape(); //플레이어
}

//게임화면을 콘솔창에 출력하는 함수
void DDGame::PrintMap()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0}); //커서를 (0, 0)으로 이동
    //게임화면 그리기
    cout << map[0] << endl << map[1] << " 점수" << endl << map[2] << " " << point << endl;
    for (int i = 3; i <= 26; i++)
        cout << map[i] << endl;
}

//게임을 시작하는 함수
void DDGame::StartGame()
{
    do
	{
        point++;

		UpdateDdongs();
		MovePlayer();

        MakeMap();
        PrintMap();

        Sleep(50);
	} while (!IsCollision()); //플레이어가 돌이나 레이저에 부딪히지 않으면 계속 반복

    player->SetShape('@');
    MakeMap();
    PrintMap();

    cout << "아웃!" << endl;
    
    system("pause");
}
