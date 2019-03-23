//后端
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <cstring>
#include <cmath>
#include "map.hpp"
#define MAPN 0
using namespace std;
char ch;//玩家输入
int px,py,health;
int z_count;
class Zombie {
    public:
        int id,x,y;
        bool dead;
        void init(int arg_id) {//生成僵尸
            srand((unsigned)time(NULL));
            a:x=rand()%10;
            y=rand()%10;
            id=arg_id;
            if (_map[MAPN][x][y]==' ') {
                _map[MAPN][x][y]='Z';
                dead=false;
            } else
                goto a;
            Sleep(100);
            system("cls");
        }
        void move() {
            int tx,ty;
            //僵尸攻击机制
            if (_map[MAPN][x+1][y]=='I')
                health--;
            if (_map[MAPN][x-1][y]=='I')
                health--;
            if (_map[MAPN][x][y+1]=='I')
                health--;
            if (_map[MAPN][x][y-1]=='I')
                health--;
            srand((short)time(NULL));
            tx=rand()%2;
            ty=rand()%2;
            if (_map[MAPN][x+tx][y+ty]!=' ') {
                tx*=-1;
                ty*=-1;
            }
            if (_map[MAPN][x+tx][y+ty]==' ') {
                _map[MAPN][x][y]=' ';
                x+=tx;
                y+=ty;
                _map[MAPN][x][y]='Z';
                return;
            }
        }
        void close_attack() {//近身攻击
            if (abs(px-x)<=5 && abs(py-y)<=5) {//判断与玩家的距离
                if (px-x<=0) {//在玩家上
                    if (_map[MAPN][x-1][y]==' ') {
                        _map[MAPN][x][y]=' ';
                        x--;
                        _map[MAPN][x][y]='Z';
                    }
                } else {
                    if (_map[MAPN][x+1][y]==' ') {
                        _map[MAPN][x][y]=' ';
                        x++;
                        _map[MAPN][x][y]='Z';
                    }
                }
                if (py-y>=0) {//在玩家左
                    if (_map[MAPN][x][y+1]==' ') {
                        _map[MAPN][x][y]=' ';
                        y++;
                        _map[MAPN][x][y]='Z';
                    }
                } else {
                    if (_map[MAPN][x][y-1]==' ') {
                        _map[MAPN][x][y]=' ';
                        y--;
                        _map[MAPN][x][y]='Z';
                    }
                }
            }
        }
}zombie[10];
bool is_win() {
    for (int i=0;i<=100;i++)
        for (int j=0;j<=100;j++)
            if (_map[MAPN][i][j]=='Z')
                return false;
    return true;
}
void is_dead(int tx,int ty) {
    for (int i=0;i<=9;i++)
        if (zombie[i].x==tx+1 || zombie[i].x==tx-1 || zombie[i].y==ty-1 || zombie[i].y==ty-1)
            zombie[i].dead=true;
}
void count_zombies() {//统计僵尸数量
    z_count=0;
    for (int i=0;i<=MAXN;i++) {//遍历地图每一个点
        for (int j=0;j<=MAXN;j++) {
            if (_map[MAPN][i][j]=='Z')
                z_count++;
        }
    }
}
void move(int lines) {
    //玩家移动
    ch = getch();
    if (ch=='w'||ch=='W') {
        if (_map[MAPN][px-1][py]==' ') {
            _map[MAPN][px][py]=' ';
            px--;
            _map[MAPN][px][py]='I';
        }
    }
    if (ch=='a'||ch=='A') {
        if (_map[MAPN][px][py-1]==' ') {
            _map[MAPN][px][py]=' ';
            py--;
            _map[MAPN][px][py]='I';
        }
    }
    if (ch=='s'||ch=='S') {
        if (_map[MAPN][px+1][py]==' ') {
            _map[MAPN][px][py]=' ';
            px++;
            _map[MAPN][px][py]='I';
        }
    }
    if (ch=='d'||ch=='D') {
        if (_map[MAPN][px][py+1]==' ') {
            _map[MAPN][px][py]=' ';
            py++;
            _map[MAPN][px][py]='I';
        }
    }
    //这块地方是玩家的攻击机制
    if (ch==' ') {
        if (_map[MAPN][px-1][py]=='Z') {
            _map[MAPN][px-1][py]=' ';
            is_dead(px,py);
        }
        if (_map[MAPN][px][py-1]=='Z') {
            _map[MAPN][px][py-1]=' ';
            is_dead(px,py);
        }
        if (_map[MAPN][px+1][py]=='Z') {
            _map[MAPN][px+1][py]=' ';
            is_dead(px,py);
        }
        if (_map[MAPN][px][py+1]=='Z') {
            _map[MAPN][px][py+1]=' ';
            is_dead(px,py);
        }
    }
    system("cls");
    for (int i=0;i<=lines;i++)
        puts(_map[MAPN][i]);
}
void mode1(int lines) {//多线程式（整合）
    HANDLE hConsole;
    SetConsoleTextAttribute(hConsole,7);
    int time=0,num=0;
    cout << "Map Initing..." << endl;
    memcpy(_map,cmap,sizeof(cmap));
    Sleep(100);
    system("cls");
    for (int i=0;i<=9;i++) {
        zombie[i].init(i);
        printf("Zombies Initing: %d/10\n",i+1);
    }
    system("cls");
    cout << "PLayer Initing..." << endl;
    health=20;
    px=3;py=9;
    Sleep(100);
    system("cls");
    cout << "Ready?" << endl;
    Sleep(2000);
    cout << "Go!" << endl;
    Sleep(100);
    system("cls");
    for (int i=0;i<=lines;i++)
        puts(_map[MAPN][i]);
    while(true){//游戏主循环
        if(_kbhit())
			move(13);
		for (int i=0;i<=9;i++)
			if (!zombie[i].dead) {
            	zombie[i].move();
            	zombie[i].close_attack();
            }
		if(time>=10)
		{
			time=0;
			num++;
		}
		system("cls");
		for (int i=0;i<=lines;i++)
            puts(_map[MAPN][i]);
        count_zombies();
		printf("Aline Time: %d\n",num);
		printf("Your Blood: %d\n",health);
		printf("Zombies Amounts: %d\n",z_count);
		Sleep(50);
		time++;
		if (health<=0) {
		    system("color c4");
            printf("you lose!");
            Sleep(2000);
            return;
		}
		if (is_win()) {
            cout << "You Win!";
            Sleep(2000);
            return;
		}
    }
    return;
}
