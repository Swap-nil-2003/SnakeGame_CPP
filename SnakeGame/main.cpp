#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x,y,foodX,foodY,score;
int tailX[100],tailY[100];
int ntail;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup()
{
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    foodX = rand()%width;
    foodY = rand()%height;
    score=0;
}
void Draw()
{
    system("cls");
    for(int i=0;i<width+2;i++)
        cout << "#";
    cout << endl;

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout << "#";   

            if(i==y && j==x)
                cout << "0";
            else if(i== foodY && j== foodX)
                cout << "F";
            else
            {
                bool print = false;
                for(int k=0;k<ntail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                 if(!print)
                        cout << " ";
            }

            if(j == width-1)
                cout << "#";
        }
        cout << endl;
    }

    for(int i=0;i<width+2;i++)
        cout << "#";
     cout << endl;
     cout << "Score: " << score << endl;
    
}

void Input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'l':
                dir=LEFT;
                break;
            case 'r':
                dir=RIGHT;
                break;
            case 'u':
                dir=UP;
                break;
            case 'd':
                dir=DOWN;
                break;
            case 'x':
                gameOver=true;
                break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2x,prev2y;
    tailX[0]=x; tailY[0]=y;
    for(int i=1; i< ntail;i++)
    {
        prev2x = tailX[i];
        prev2y = tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2x;
        prevY=prev2y;
    }

    switch(dir)
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
        default: 
            break;
    }
    if(x<0 || x > width || y<0 || y > height)
        gameOver=true;
    for(int i=0;i<ntail;i++)
        if(tailX[i]== x && tailY[i]==y)
            gameOver=true;
    if(x==foodX && y==foodY)
    {
        score+=5;
        foodX = rand()%width;
        foodY = rand()%height;
        ntail++;
    }
}

int main()
{
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}