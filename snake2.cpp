#include <iostream> 
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define OFFSET_X 2
#define OFFSET_Y 3

#define FRUIT_CH (char)254
#define SNAKE_HEAD_CH 'O'
#define SNAKE_TAIL_CH 'o'
#define FRAME_TOP_LEFT_CH (char)218
#define FRAME_TOP_CH (char)196
#define FRAME_TOP_RIGHT_CH (char)191
#define FRAME_LEFT_CH (char)179
#define FRAME_RIGHT_CH (char)179
#define FRAME_BOTTOM_LEFT_CH (char)192
#define FRAME_BOTTOM_CH (char)196
#define FRAME_BOTTOM_RIGHT_CH (char)217

using namespace std;

bool gameOver;
const int width = 25;
const int height = 25;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void gotoxy(int x = 0, int y = 0)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}

void GoToXY(int x = OFFSET_X, int y = OFFSET_Y)
{
	gotoxy(x + OFFSET_X, y + OFFSET_Y);
}

void Setup() {

	gameOver = false;
	dir = STOP;

	x = width / 2;
	y = height / 2;

	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void DrawFrame()
{
	system("cls");
	gotoxy(OFFSET_X, 1);
	cout << "Snake ver. 2";
	GoToXY(0, 0);
	cout << FRAME_TOP_LEFT_CH;

	for (int i = 0; i < width; i++) {
		GoToXY(i+1, 0);
		cout << FRAME_TOP_CH;
	}
	GoToXY(width + 1, 0);
	cout << FRAME_TOP_RIGHT_CH;
	cout << endl;
	
	for (int i = 0; i < height; i++) {
		GoToXY(0, i+1);
		cout << FRAME_LEFT_CH;
		GoToXY(1, i + 1);
		for (int j = 0; j < width; j++)
			cout << " ";
		GoToXY(width + 1, i + 1);
		cout << FRAME_RIGHT_CH;
		cout << endl;
	}

	GoToXY(0, height+1);
	cout << FRAME_BOTTOM_LEFT_CH;
	for (int i = 0; i < width; i++) {
		GoToXY(i+1, height+1);
		cout << FRAME_BOTTOM_CH;
	}
	GoToXY(width + 1, height+1);
	cout << FRAME_BOTTOM_RIGHT_CH;
}

void DrawScore()
{
	GoToXY(0, height + 3);
	cout << "Score: " << score << endl;
}

void ClearSnake()
{
	GoToXY(fruitX+1, fruitY+1);
	cout << " ";
	GoToXY(x+1, y+1);
	cout << " ";
	for (int k = 0; k < nTail; k++) {
		GoToXY(tailX[k]+1, tailY[k]+1);
		cout << " ";
	}
}

void DrawSnake()
{
	GoToXY(fruitX + 1, fruitY + 1);
	cout << FRUIT_CH;
	GoToXY(x + 1, y + 1);
	cout << SNAKE_HEAD_CH;
	for (int k = 0; k < nTail; k++) {
		GoToXY(tailX[k]+1, tailY[k]+1);
		cout << SNAKE_TAIL_CH;
	}
}

void Input() {

	if (_kbhit()) {
		switch (_getch()) {
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

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}


	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width-1 || x < 0 || y > height-1 || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;



	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}


int main()
{
	ShowConsoleCursor(false);
	srand(time(NULL));
	Setup();
	DrawFrame();

	while (!gameOver) {
		//Draw();
		Input();
		ClearSnake();
		Logic();
		DrawSnake();
		DrawScore();
		Sleep(100);
	}
	return 0;
}

