#ifndef DDGAME_H
#define DDGANE_H

#include "Object.h"
#include <random>

using namespace std;

class DDGame
{
private:
    Object *player; //플레이어 객체
    Object *Ddong[50]; //똥들 객체
    bool isDdongActive[50]; //똥들의 활성화 여부들 저장 배열
    char map[27][28]; //게임화면 문자열
    int point; //점수

    //랜덤 관련 객체들
    mt19937 gen;
    uniform_int_distribution<int> dis;

    bool IsCollision(); //플레이어과 똥과 충돌했는지 여부를 반환하는 함수
    void UpdateDdongs(); //똥들의 위치를 갱신하는 함수
    void MovePlayer(); //방향키 입력에 따라 플레이어를 움직이는 함수
    void MakeMap(); //게임화면을 문자열 형태로 만드는 함수
    void PrintMap(); //게임화면을 콘솔창에 출력하는 함수

public:
    DDGame(); //생성자; 멤버변수들 초기화
    void StartGame(); //게임을 시작하는 함수
};

#endif