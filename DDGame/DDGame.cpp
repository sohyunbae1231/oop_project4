#include "DDGame.h"
#include <iostream>
#include <Winuser.h>
#include <windows.h>
#include <string>

//������; ��������� �ʱ�ȭ
DDGame::DDGame()
{
    player = new Object(13, 25, 'O'); //�÷��̾� ��ü ����

    //�� Ȱ��ȭ �迭 �ʱ�ȭ
    for (int i = 0; i < 50; i++)
        isDdongActive[i] = false;

    //�⺻ ����ȭ�� Ʋ ����
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

    point = 0; //���� �ʱ�ȭ

    //���� ��ü ����
    random_device rd;
    gen = mt19937(rd());
    dis = uniform_int_distribution<int>(1, 25);
}

//�÷��̾�� �˰� �浹�ߴ��� ���θ� ��ȯ�ϴ� �Լ�
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

//�˵��� ��ġ�� �����ϴ� �Լ�
void DDGame::UpdateDdongs()
{
    for (int i = 0; i < 50; i++)
    {
        if (isDdongActive[i]) //�����ϴ� �˿� ����
        {
            if (Ddong[i]->GetY() >= 25) //���� �ٴڿ� ������
            {
                delete Ddong[i];
                isDdongActive[i] = false;
            }
            else //���� �ٴڿ� ���� ���°� �ƴϸ�
            {
                Ddong[i]->SetY(Ddong[i]->GetY() + 1); //���� �Ʒ��� �̵�
            }
        }
        else //�������� �ʴ� �˿� ����
        {
            if (dis(gen) < 2) //���� Ȯ���� �� ���� ����
            {
                Ddong[i] = new Object(dis(gen), 1, 'v');
                isDdongActive[i] = true;
            }
        }
    }
}

//����Ű �Է¿� ���� �÷��̾ �����̴� �Լ�
void DDGame::MovePlayer()
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0) //���� ����Ű
		player->SetX(player->GetX() - 1);
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0) //������ ����Ű
		player->SetX(player->GetX() + 1);

	if (player->GetX() < 1) //�� ���� ���� ����
		player->SetX(1);
	else if (player->GetX() > 25) //�� ������ ���� ����
		player->SetX(25);
}

//����ȭ���� ���ڿ� ���·� ����� �Լ�
void DDGame::MakeMap()
{
    //���
    for (int i = 1; i <= 25; i++)
    {
        for (int j = 1; j <= 25; j++)
            map[i][j] = ' ';
    }

    //�˵�
    for (int i = 0; i < 50; i++)
    {
        if (isDdongActive[i])
            map[Ddong[i]->GetY()][Ddong[i]->GetX()] = Ddong[i]->GetShape();
    }

    map[player->GetY()][player->GetX()] = player->GetShape(); //�÷��̾�
}

//����ȭ���� �ܼ�â�� ����ϴ� �Լ�
void DDGame::PrintMap()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0}); //Ŀ���� (0, 0)���� �̵�
    //����ȭ�� �׸���
    cout << map[0] << endl << map[1] << " ����" << endl << map[2] << " " << point << endl;
    for (int i = 3; i <= 26; i++)
        cout << map[i] << endl;
}

//������ �����ϴ� �Լ�
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
	} while (!IsCollision()); //�÷��̾ ���̳� �������� �ε����� ������ ��� �ݺ�

    player->SetShape('@');
    MakeMap();
    PrintMap();

    cout << "�ƿ�!" << endl;
    
    system("pause");
}
