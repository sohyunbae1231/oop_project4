#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


class num {
private:
	int order;
	int number;


public:
	num(int _order, int _num) {
		order = _order; number = _num;
	}
	bool isZero() { if (number == 0) return 1; else return 0; }
	void change(num& x) {
		int temp_num = x.number; 
		x.number = number;
		number = temp_num;
	}
	int getNumber() { return number; }
};

class numBox {
private:
	num* boxes;
	int size;
	int row;
	int col;
	int zeroPos;

public:
	int count;
	numBox(int r, int c) {
		row = r; col = c; size = r * c;
		boxes = (num*)malloc(sizeof(num) * size);
		zeroPos = size - 1;
		count = 0;

		for (int i = 0; i < size - 1; i++) // 모든 박스 생성
			boxes[i] = num(i, i + 1);
		boxes[size - 1] = num(size - 1, 0); // 제일 마지막 타일은 0으로

	}
	int getZero() { return zeroPos; }
	int getSize() { return size; }
	bool go(int to) {
		if (to < size && to >= 0) // 블럭 범위 내에 있는 숫자
		 {
			if (zeroPos%row == 0 && to == zeroPos - 1) return false; // 왼쪽벽 부분 재한 조건
			if (zeroPos % row == row - 1 && to == zeroPos + 1) return false; // 오른벽 부분 재한 조건
			if (to == zeroPos - 1 | to == zeroPos + 1 | to == zeroPos - row | to == zeroPos + row) {
				boxes[to].change(boxes[zeroPos]); zeroPos = to; return true;
			}
		}
		return false;
	}
	bool isComplete() { // 숫자퍼즐이 맞춰졌는지 확인
		for (int i = 0; i < size - 1; i++) 
			if (boxes[i].getNumber() != i + 1) return false;
		return true;
	}
	void shuffle() { // 숫자 퍼즐을 섞는 함수
		srand(time(NULL));
		int random;
		for (int i = 0; i < 100; i++) {
			random = rand() % 4;
			switch (random)
			{
			case 0:
				go(zeroPos - row); break;
			case 1:
				go(zeroPos + row); break;
			case 2:
				go(zeroPos - 1); break;
			case 3:
				go(zeroPos + 1); break;
			default:
				break;
			}
		}
	}
	void print() { // 숫자퍼즐 그림 출력
		for (int i = 0; i < col; i++) {
			printf("%35s", " ");  for (int j = 0; j < row; j++) { printf(" ------ "); } printf("\n");
			printf("%35s", " ");
			
			for (int j = 0; j < row; j++) {
				if (boxes[i * row + j].getNumber() == 0) { printf("|       "); }
				else printf("|  %2d   ", boxes[i * row + j].getNumber()); 
			} printf("|\n");
		} 
		
		printf("%35s", " ");  for (int j = 0; j < row; j++) { printf(" ------ "); } printf("\n");

	}
};