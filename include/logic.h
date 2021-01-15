#include <bits/stdc++.h>
#define up (std::pair<int,int>){0,1}
#define down (std::pair<int,int>){0,-1}
#define right (std::pair<int,int>){1,0}
#define left (std::pair<int,int>){-1,0}
#define empty 0
#define head 1
#define segment 2
#define apple 3

typedef std::pair<int,int> direction;
typedef std::pair<int,int> position;

class snake{
public:
	void init(int, int);
	int update();
	void setDirection(std::pair<int,int> dir);
	int getXY(int x, int y);
	void clear();
private:
	std::pair<int,int> movement;
	std::pair<int,int> headPos;
	std::pair<int,int> tailPos;
	int X,Y;
	int* tiles;
	std::pair<int,int> applePos;
	void genApple();
	int length;
};
