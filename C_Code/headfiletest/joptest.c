#include <stdio.h>
#include <Windows.h>
 
//将光标移动到控制台的(x,y)坐标点处
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 
int main()
{
    gotoxy(50,15);//将光标移动到控制台的(50,15)处
    printf("Hello World\n");
    system("pause");
    return 0;
}