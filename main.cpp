#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;

bool gameOver;
bool shutDown;
const int width = 20;
const int height = 12;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100], nTail;
enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void StartScreen()
{
	system("cls");
	cout << "\nWELCOME TO SNAKE GAME!"
	     << "\n\nPress 's' to Start, use WASD for direction control!"
	     << "\n\nPress 'q' to Quit"
	     << "\n\nYour Previous Score: " << score << endl;
}

void CoinSpawn()
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
	CoinSpawn();
	score = 0;
	nTail = 0;
}
void Draw()
{
	system("cls"); 
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
				cout << "$";
		
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
	
	if (dir == LEFT || dir == RIGHT)
	    Sleep(40);
    if (dir == UP || dir == DOWN)
    	Sleep(60);
	
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
	//if (x > width || x < 0 || y > height || y < 0) {
	//	gameOver = true;
	//	StartScreen();
	
	// magic snake can go through the wall!
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	if (x == foodX && y == foodY) {
		score += 10;
		nTail++;
		CoinSpawn();
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
				Sleep(50);
			}
		}
		else if (input == "q")
			shutDown = true;
	} while (shutDown == false);

    return 0;
}
