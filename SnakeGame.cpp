//
//  SnakeGame.cpp
//  
//
//  Created by Prabhat Kadam on 14/02/19.
//

#include <iostream>
#include<vector>
#include<time.h>
#include<conio.h>
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int const r=20,c=40;
char board[r][c];

struct Snake
{
    int x,y;
    char val;
};

struct Food
{
    int x,y;
    char val;
};

void move();

void printBoard()
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<board[i][j];
        }
        cout<<endl;
        
    }
}


Food f;
vector<Snake> s;

void generateFood()  //set random food on board
{
    srand(time(NULL));
    do
    {
        f.y=(rand()%(c-2))+1;
        f.x=(rand()%(r-2))+1;
        //cout<<f.x;
    }
    while(board[f.x][f.y]=='H' || board[f.x][f.y]=='T' || board[f.x][f.y]=='#');
    board[f.x][f.y]='F';
}

void initSnake()
{
    Snake t;
    t.x=5;
    t.y=7;
    t.val='H';
    s.push_back(t);
    
    t.x=5;
    t.y=6;
    t.val='#';
    s.push_back(t);
    
    t.x=5;
    t.y=5;
    t.val='#';
    s.push_back(t);
    
    t.x=5;
    t.y=4;
    t.val='T';
    s.push_back(t);
    
    for(int i=0;i<s.size();i++)
    {
        board[s[i].x][s[i].y]=s[i].val;
    }
}


void setSnake()  //set snake on board
{
    for(int i=0;i<s.size();i++)
    {
        board[s[i].x][s[i].y]=s[i].val;
    }
}

void moveRight()
{
    int x1=s[s.size()-1].x,y1=s[s.size()-1].y;
    
    if((s[0].y%(c-2)+1)==s[1].y)          //dont let it go back
    {
        move();
        return;
    }

    for(int i=s.size()-1;i>=1;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        //
    }
    
    //s[0].y+=1;
    s[0].y=s[0].y%(c-2)+1;
    if(s[0].x==f.x && s[0].y==f.y)
    {
        Snake t;
        t.x=x1;
        t.y=y1;
        t.val='T';
        s[s.size()-1].val='#';
        s.push_back(t);
        generateFood();
    }
    else board[x1][y1]=' ';
    
    
}

void moveUp()
{
    int x1=s[s.size()-1].x,y1=s[s.size()-1].y;
    
    int t=s[0].x-1;           //dont let it go back
    t=((r-2)+t-1)%(r-2)+1;
    if(t==s[1].x)
    {
        move();
        return;
    }                 //
    
    for(int i=s.size()-1;i>=1;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        //
    }
    s[0].x-=1;
    s[0].x=((r-2)+s[0].x-1)%(r-2)+1;    //   n-2-> 2 values excluded  i = (i - 1 + N) % N
    if(s[0].x==f.x && s[0].y==f.y)
    {
        Snake t;
        t.x=x1;
        t.y=y1;
        t.val='T';
        s[s.size()-1].val='#';
        s.push_back(t);
        generateFood();
    }
    else board[x1][y1]=' ';
}

void moveLeft()
{
    int x1=s[s.size()-1].x,y1=s[s.size()-1].y;
    
    int t=s[0].y-1;             //dont let it go back
    t=((c-2)+t-1)%(c-2)+1;
    if(t==s[1].y)
    {
        move();
        return;
    }
    
    for(int i=s.size()-1;i>=1;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        //
    }
    s[0].y-=1;
    s[0].y=((c-2)+s[0].y-1)%(c-2)+1;    //   n-2-> 2 values excluded  i = (i - 1 + N) % N
    if(s[0].x==f.x && s[0].y==f.y)
    {
        Snake t;
        t.x=x1;
        t.y=y1;
        t.val='T';
        s[s.size()-1].val='#';
        s.push_back(t);
        generateFood();
    }
    else board[x1][y1]=' ';
}

void moveDown()
{
    int x1=s[s.size()-1].x,y1=s[s.size()-1].y;
    
    if((s[0].x%(r-2)+1)==s[1].x)          //dont let it go back
    {
        move();
        return;
    }
    
    for(int i=s.size()-1;i>=1;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
        //
    }
   // s[0].x+=1;
    s[0].x=s[0].x%(r-2)+1;
    if(s[0].x==f.x && s[0].y==f.y)
    {
        Snake t;
        t.x=x1;
        t.y=y1;
        t.val='T';
        s[s.size()-1].val='#';
        s.push_back(t);
        generateFood();
    }
    else board[x1][y1]=' ';
}

char ch;

void move()   //set required snake and print baord
{
    if(kbhit())
    {
        ch=getch();
    }
        //cin>>ch;
    if(ch=='d')
        moveRight();
    else if(ch=='w')
        moveUp();
    else if(ch=='s')
        moveDown();
    else if(ch=='a')
        moveLeft();
    setSnake();
    printBoard();
}


void init()   //initialise board border snake and food
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(i==0||i==(r-1)||j==0||j==(c-1))
                board[i][j]='*';
            else board[i][j]=' ';
        }
    }
    initSnake();
    generateFood();
    //setSnake();
}


int main()
{
    init();
    //char ch;
    printBoard();
    while(board[s[0].x][s[0].y]!='#' && board[s[0].x][s[0].y]!='T')
    {
        move();
        Sleep(70);
        //for(int k=0;k<10000;k++);
        system("cls");
    }
    cout<<endl<<endl<<"GAME OVER"<<endl<<"\nYour Score: "<<s.size()<<endl;
    return 0;
}

