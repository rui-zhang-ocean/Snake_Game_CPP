#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;

bool gameOver;
bool shutDown;
const int width = 25;
const int height = 15;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100], nTail;
enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void StartScreen()
{
	system("cls");
	cout << "\nWELCOME TO SNAKE GAME!"
	     << "\n\nPress 's' to Start, Use WASD for direction control!"
	     << "\n\nPress 'q' to Quit"
	     << "\n\nYour Previous Score: " << score << endl;
}

void FoodSpawn()
{
	foodX = rand() % width;
	foodY = rand() % height;
}
void Setup() 
{
	gameOver = false;
	shutDown = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	FoodSpawn();
	score = 0;
	nTail = 0;
}
void Draw()
{
	system("cls"); //clear screen
	for (int i = 0; i < width + 2; i++) {
		cout << "#";}
	cout << endl;
	
	for (int i = 0; i < height; i++) 
	{
		for (int j = 0; j < width; j++) 
		{
			if (j == 0) 
				cout << "#";
			
			if (i == y && j == x) 
				cout << "O";
			
			else if (i == foodY && j == foodX) 
				cout << "F";
		
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}		
				}
				if(!print)
					cout << " ";
			}
			
			if (j == width - 1) 
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
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

	switch (dir)
	{
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
	}
	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true;
		StartScreen();
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == foodX && y == foodY) {
		score++;
		nTail++;
		FoodSpawn();
	}
}
int main()
{
	do {
		StartScreen();
		string input;
		cin >> input;
		if (input == "s")
		{
			Setup();
			while (!gameOver)
			{
				Draw();
				Input();
				Logic();
				Sleep(100);
			}
		}
		else if (input == "q")
			shutDown = true;
	} while (shutDown == false);

    return 0;
}
