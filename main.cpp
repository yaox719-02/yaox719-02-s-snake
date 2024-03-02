#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <graphics.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <atlstr.h>
int width = 20;
int height = 15;
int speed = 25;
#define BLOCK 20
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
//int map[height+2][WIDTH + 2] = {0};
std::vector<std::vector<int>> map;
int snakeX = 3;
int snakeY = 1;
int snakeDir = RIGHT;
int snakeLength = 3;
int foodX = 0;
int foodY = 0;
int tick = 0;
void initMap() {
	map.resize(height + 2);
	for (auto& i : map) {
		i.resize(width + 2);
	}
	for (auto& i : map) {
		for (auto& j : i) {
			j = 0;
		}
	}
	for (int i = 0; i < width + 2; i++) {
		map[0][i] = -1;
		map[height + 1][i] = -1;
	}
	for (int j = 1; j < height + 1; j++) {
		map[j][0] = -1;
		map[j][width + 1] = -1;
	}
	map[1][1] = 1;
	map[1][2] = 2;
	map[1][3] = 3;
	srand((unsigned int)time(NULL));
	foodY = rand() % height + 1;
	foodX = rand() % width + 1;
	map[foodY][foodX] = -2;
}
void printMap() {
	for (int i = 0; i < height + 2; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (map[i][j] == -1) {
				setfillcolor(WHITE);
				solidrectangle(BLOCK * j, BLOCK * i, BLOCK * (j + 1), BLOCK * (i + 1));
			}
			else if (map[i][j] == 0) {
				setfillcolor(BLACK);
				solidrectangle(BLOCK * j, BLOCK * i, BLOCK * (j + 1), BLOCK * (i + 1));
			}
			else if (map[i][j] == -2) {
				setfillcolor(YELLOW);
				solidrectangle(BLOCK * j, BLOCK * i, BLOCK * (j + 1), BLOCK * (i + 1));
			}
			else {
				//setfillcolor(BLUE);
				int t = 256 / (5+snakeLength);
				int tt = map[i][j]+4;
				setfillcolor(tt *t*65536+ tt * t *256+ tt * t * 1);
				solidrectangle(BLOCK * j, BLOCK * i, BLOCK * (j + 1), BLOCK * (i + 1));
			}
		}
	}
	setfillcolor(BLACK);
	solidrectangle(BLOCK * (width + 2), 0, BLOCK * (width + 2) + 100, BLOCK * (height + 2));
	std::string s = "score:"; s += std::to_string(snakeLength);
	CString s2 = s.c_str();

	outtextxy(BLOCK * (width + 2), 0, (LPCTSTR)s2);
}
/*
do{
	foodY = rand() % HEIGHT + 1;
	foodX = rand() % WIDTH + 1;
}while(map[foodY][foodX] <= 0);
map[foodY][foodX] = -2;
*/
void setFood() {
	do {
		foodY = rand() % height + 1;
		foodX = rand() % width + 1;
	} while (map[foodY][foodX] != 0);
	map[foodY][foodX] = -2;
}
void moveSnake() {
	if (snakeDir == UP && map[snakeY - 1][snakeX] == -2) {
		map[snakeY - 1][snakeX] = snakeLength + 1;
		snakeLength++;
		snakeY--;
		setFood();

	}
	else if (snakeDir == DOWN && map[snakeY + 1][snakeX] == -2) {
		map[snakeY + 1][snakeX] = snakeLength + 1;
		snakeLength++;
		snakeY++;

		setFood();
	}
	else if (snakeDir == LEFT && map[snakeY][snakeX - 1] == -2) {
		map[snakeY][snakeX - 1] = snakeLength + 1;
		snakeLength++;
		snakeX--;

		setFood();
	}
	else if (snakeDir == RIGHT && map[snakeY][snakeX + 1] == -2) {
		map[snakeY][snakeX + 1] = snakeLength + 1;
		snakeLength++;
		snakeX++;
		setFood();
	}
	else {
		for (int i = 0; i < height + 2; i++) {
			for (int j = 0; j < width + 2; j++) {
				if (map[i][j] > 0) {
					map[i][j]--;
				}
			}
		}
		if (snakeDir == UP) {
			map[snakeY - 1][snakeX] = snakeLength;
			snakeY--;
		}
		if (snakeDir == DOWN) {
			map[snakeY + 1][snakeX] = snakeLength;
			snakeY++;
		}
		if (snakeDir == RIGHT) {
			map[snakeY][snakeX + 1] = snakeLength;
			snakeX++;
		}
		if (snakeDir == LEFT) {
			map[snakeY][snakeX - 1] = snakeLength;
			snakeX--;
		}
	}
}
int snakeDie() {
	if (snakeDir == UP && (map[snakeY - 1][snakeX] == -1 || map[snakeY - 1][snakeX] > 0)) {
		return 1;
	}
	if (snakeDir == DOWN && (map[snakeY + 1][snakeX] == -1 || map[snakeY + 1][snakeX] > 0)) {
		return 1;
	}
	if (snakeDir == RIGHT && (map[snakeY][snakeX + 1] == -1 || map[snakeY][snakeX + 1] > 0)) {
		return 1;
	}

	if (snakeDir == LEFT && (map[snakeY][snakeX - 1] == -1 || map[snakeY][snakeX - 1] > 0)) {
		return 1;
	}
	else {
		return 0;
	}
}
int main() {
	bool flag = true;
	while (flag) {
		std::cout << "高(>=5):";
		std::cin >> height;
		if (height >= 5) {
			flag = false;
		}
	}
	flag = true;
	while (flag) {
		std::cout << "宽(>=5):";
		std::cin >> width;
		if (width >= 5) {
			flag = false;
		}
	}
	flag = true;
	while (flag) {
		std::cout << "速度(慢:40 中等:25 快:10):";
		std::cin >> speed;
		if (speed >= 1) {
			flag = false;
		}
	}
	initgraph(BLOCK * (width + 2) + 200, BLOCK * (height + 2));
	setlinestyle(PS_SOLID);
	setbkcolor(BLACK);
	settextcolor(WHITE);
	settextstyle(32, 0, _T("Consolas"));
	initMap();
	printMap();
	while (1) {
		if (tick % speed == 0) {
			if (!(snakeDie())) {
				moveSnake();
			}
			else {
				goto a;
			}
			//cleardevice();
			printMap();
			tick = 1;
		}
		else {
			char c;
			if (_kbhit()) {
				c = _getch();
				if (c == 'w' && snakeDir != DOWN) {
					snakeDir = UP;
				}
				else if (c == 'a' && snakeDir != RIGHT) {
					snakeDir = LEFT;
				}
				else if (c == 's' && snakeDir != UP) {
					snakeDir = DOWN;
				}
				else if (c == 'd' && snakeDir != LEFT) {
					snakeDir = RIGHT;
				}
			}
			Sleep(1);
			tick++;
		}

	}
a:
	setfillcolor(BLACK);
	solidrectangle(BLOCK * (width + 2), 0, BLOCK * (width + 2) + 100, BLOCK * (height + 2));
	outtextxy(BLOCK * (width + 2), 0, _T("GAME OVER"));
	Sleep(500);
	_getch();
	closegraph();
	return 0;
}