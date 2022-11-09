#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;
bool GameOver;
const int width = 20;
const int height = 20;
int x,y,FruitX,FruitY,score;
int tailX[100],tailY[100];
int nTail;
int a = rand() % width;
int b = rand() % height;
enum eDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void Setup()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	FruitX = a;
	FruitY = b;
	score = 0;
}
void Draw()
{
	system("cls"); //Limpiar la pantalla
	for(int i = 0; i<width+1; i++){
		cout<<"#";
	}
	for(int i = 0; i<height;i++){
		for(int j = 0; j<width+2;j++){
			if(j == 0){
				cout<<"#";
			}
			if(i == y && j == x){
				cout<<"0";
			}else if(i == FruitY && j == FruitX){
				cout<<"+";
			}else{
				bool print = false;
				for(int k = 0; k<nTail;k++){
					if(tailX[k] == j && tailY[k] == i){
						cout<<"o";
						print = true;
					}
					}
				if(!print){
					cout<<" ";	
				}
			}
			if(j == width-1){
				cout<<"#";
			}
		}
		cout<<endl;
	}
	for(int i = 0; i<width+2; i++){
		cout<<"#";
	}
	cout<<endl;
	cout<<"score: "<<score;
}
void Input()
{
	if(_kbhit())
	{
		switch(_getch())
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
				GameOver = true;
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
	for(int i = 1;i<nTail;i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch(dir){
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
	if(x>width || x<0 || y>height || y<0){
		GameOver = true;
	}
	for(int i = 0; i<nTail; i++){
		if(tailX[i] == x && tailY[i] == y){
			GameOver = true;
		}
	}
	if(x == FruitX && y == FruitY){
		nTail++;
		score += 10;
		a = rand() % width;
        b = rand() % height;
		FruitX = a;
	    FruitY = b;
	}
}
int main(){
	Setup();
	while(!GameOver){
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}
