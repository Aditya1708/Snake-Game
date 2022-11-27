#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<cstdlib>
#include<queue>
using namespace std;

bool gameStarted, gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
char ar[width][height];
queue<pair<int, int>> body;

void Setup() {
	gameStarted = false;
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {
			if (j == 0 || j == height - 1 || i == 0 || i == width - 1 ) { ar[i][j] = '#'; }
			else { ar[i][j] = ' '; }
		}
	}
	ar[x][y] = 'O';
	ar[fruitX][fruitY] = 'F';
	body.push(make_pair(x, y));
}

void Draw() {
	srand(time(0));
	system("cls");

	for (int i = 0; i < 80; ++i) { cout << "#"; }
	cout << "\n                          Snake                        Score : " << score << "\n";
	for (int i = 0; i < 80; ++i) { cout << "#"; }

	if (gameOver) {
		cout << "\n\n\n\n\n\n\n\t\t\t\tGame Over\t\t\t\t\n\n\n\n\n\n\n";
		return;
	}
	if (gameStarted) {
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				cout << ar[i][j];
			}
			cout << "\n";
		}
	}
	else{
		cout << "\n\n\t\tPress 'a' or 's' or 'd' or 'w' key to start the game\t\t\n\n";
	}
}

void Input() {
	if (_kbhit()) {
		gameStarted = true;
		char c = _getch();
		if (((c == 'd' && dir == LEFT) || (c == 'a' && dir == RIGHT) ||
			(c == 'w' && dir == DOWN) || (c == 's' && dir == UP)) && body.size()!=1) { return; }
		switch (c)
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	
	if (dir == LEFT && ar[x][y - 1] == 'O') {
		ar[x][y - 1] = 'X';
		gameOver = true;
	}
	if (dir == RIGHT && ar[x][y + 1] == 'O') {
		ar[x][y + 1] = 'X';
		gameOver = true;
	}
	if (dir == UP && ar[x-1][y] == 'O') {
		ar[x - 1][y] = 'X';
		gameOver = true;
	}
	if (dir == DOWN && ar[x+1][y] == 'O') {
		ar[x + 1][y] = 'X';
		gameOver = true;
	}

	switch (dir)
	{
	case LEFT:
		--y;
		if (y == 0) { gameOver = true; }
		break;
	case RIGHT:
		++y;
		if (y == height - 1) { gameOver = true; }
		break;
	case UP:
		--x;
		if (x == 0) { gameOver = true; }
		break;
	case DOWN:
		++x;
		if (x == width - 1) { gameOver = true; }
		break;
	default:
		break;
	}
	
	if (ar[x][y] == 'X') {
		int xp = (body.front()).first, yp = (body.front()).second;
		ar[xp][yp] = ' ';
		body.pop();
	}
	else if (x == fruitX && y == fruitY) {
		++score;
		while(ar[fruitX][fruitY]!=' ') {
			fruitX = (rand() % (height - 2)) + 1;
			fruitY = (rand() % (width - 2)) + 1;
		}
		ar[fruitX][fruitY] = 'F';
		body.push(make_pair(x, y));
		ar[x][y] = 'O';
	}
	else {
		body.push(make_pair(x, y));
		ar[x][y] = 'O';
		int xp = (body.front()).first,yp=(body.front()).second;
		ar[xp][yp] = ' ';
		body.pop();
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Sleep(300);
		Input();
		Logic();
		Draw();
	}
	Draw();
}