// 아직 

#include <iostream> // std 
#include <stdio.h> 
#include <stdlib.h> // rand 함수를 위한 헤더 파일 

int ComputerInput[3];
int UserInput[3]; 
int randComputer[10];
int count = 0;// 회차 -> 총 9회가 되면 게임 끝
int strike = 0; // 스트라이크 수
int ball = 0; // 볼의 수
int out; // out의 수
int score;

void StartScreen();
void RandFunc();
void PlayBBall();
void PrintStrikeResult();
void PrintBallResult();
void PrintOutResult();

int main() {
	StartScreen();
	RandFunc();
	PlayBBall();
}

void StartScreen()
{
    std::cout << "                                           " << std::endl;
    std::cout << "     *                               *     " << std::endl;
    std::cout << "    *~*                             *~*    " << std::endl;
    std::cout << "   *~*~*   다가오는 크리스마스엔-  *~*~*   " << std::endl;
    std::cout << "  *~*~*~*    집에서 숫-자야구를   *~*~*~*  " << std::endl;
    std::cout << " *~*~*~*~*       즐겨보아요      *~*~*~*~* " << std::endl;
    std::cout << "    ***                             ***    " << std::endl;
    std::cout << "    ***                             ***    " << std::endl;
    std::cout << "                                           " << std::endl;
}

void RandFunc()
{
    for (int i = 0; i < 3; ++i)
    {
        randComputer[i] = rand() % 10;
    }
}

void PlayBBall()
{
    while(1)
    {
        std::cout << "[" << count << "회/9회]" << std::endl;
        while(1)
        { 
            std::cout << "1~9 사이의 숫자 중, 중복 없이 3개를 입력하세요. " << std::endl; 
            std::cin >> UserInput[0] >> UserInput[1] >> UserInput[2];
            for (int i=0; i < 3; i++)
            {
                if(UserInput[i] < 1 || UserInput[i] > 9)
                    std::cout << "유효한 범위의 숫자를 입력하세요." << std::endl;
                    continue; 
            } 
            if(UserInput[0] == UserInput[1] || UserInput[1] == UserInput[2] || UserInput[2] == UserInput[0]) 
            {
                std::cout << "중복되지 않은 숫자를 입력하세요." << std::endl;
                continue; 
            } 
            break;
        }
    }
    
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++) 
        {
            if (ComputerInput[i] == UserInput[j])
            {
                if (i == j) // 같은 위치일 경우 
                    strike++; // 자릿수와 숫자가 모두 같으므로 strike count 증가
                else 
                    ball++; // 자릿수는 다르지만 값은 같으므로 ball count 증가
            }
            
        }    
    }
    
    count++;
    
    if (strike == 3) 
    {
        std::cout << count << "번 만에 맞췄습니다." << std::endl;
        score = (11 - count) * 10;
        std::cout << "점수는" << score << "점입니다." << std::endl;
    } 
    else 
    { 
        // strike, ball, out의 결과를 출력
        PrintStrikeResult();
        PrintBallResult();
        PrintOutResult();
        // 초기화
        strike = 0;
        ball = 0;
        out = 0;
    }
}

void PrintStrikeResult()
{
    switch(strike)
    {
        case 0:
            std::cout << "STRIKE : ○○○" << std::endl;
            break;
        case 1:
            std::cout << "STRIKE : ●○○" << std::endl;
            break;
        case 2:
            std::cout << "STRIKE : ●●○" << std::endl;
            break;
        case 3:
            std::cout << "STRIKE : ●●●" << std::endl;
            break;
        default:
            std::cout << "ERROR" << std::endl;
            break;
    }
}

void PrintBallResult()
{
    switch(ball)
    {
        case 0:
            std::cout << "BALL : ○○○" << std::endl;
            break;
        case 1:
            std::cout << "BALL : ●○○" << std::endl;
            break;
        case 2:
            std::cout << "BALL : ●●○" << std::endl;
            break;
        case 3:
            std::cout << "BALL : ●●●" << std::endl;
            break;
        default:
            std::cout << "ERROR" << std::endl;
            break;
    }
}

void PrintOutResult()
{
    switch(out)
    {
        case 0:
            std::cout << "OUT : ○" << std::endl;
            break;
        case 1:
            std::cout << "OUT : ●" << std::endl;
            break;
        default:
            std::cout << "ERROR" << std::endl;
            break;
    }
}
