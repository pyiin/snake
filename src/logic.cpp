#include <bits/stdc++.h>
#include "logic.h"
#define empty 0
#define head 1
#define segment 2
#define apple 3
#define OUT(a,b) (a<0 || a>=b)

std::pair<int,int> operator+(std::pair<int,int> a, std::pair<int,int> b){
	return (std::pair<int,int>){a.first+b.first, a.second+b.second};
}

void snake::init(int x, int y){
	tiles = new int[x*y];
	for(int i =0; i<x*y;i++)
		tiles[i] = 0;
	X = x, Y = y, length = 3;
	headPos = std::make_pair(x>>1, y>>1);
	tailPos = std::make_pair(x>>1, (y>>1)-2);
	movement = {0,1};
	tiles[((y>>1)-1) * X + (x>>1)] = segment | (movement.first+1)<<3 | (movement.second+1)<<5;
	tiles[((y>>1)-2) * X + (x>>1)] = segment | (movement.first+1)<<3 | (movement.second+1)<<5;
	tiles[(y>>1) * X + (x>>1)] = head;
	genApple();
}
void snake::genApple(){
	int t = rand()%(X*Y-length);
	int i=0;
	while(t>0)
		t -= (tiles[i++] == empty);
	tiles[i] = apple;
}
int snake::update(){
	if(OUT(headPos.first + movement.first, X) || OUT(headPos.second + movement.second,Y))
		return 0;
	tiles[headPos.second * X + headPos.first] = segment | (movement.first+1)<<3 | (movement.second+1)<<5;
	headPos = headPos + movement;
	auto t = tiles[headPos.second * X + headPos.first] & 3;
	if(t == segment)
		return 0;
	tiles[headPos.second * X + headPos.first] = head;
	if(t != apple){
		auto dir = tiles[tailPos.second * X + tailPos.first] >> 3;
		tiles[tailPos.second * X + tailPos.first] = empty;
		tailPos = tailPos + std::make_pair((dir&3)-1, ((dir&12)>>2)-1);
	}
	else{
		length++;
		genApple();
	}
	return 1;
}
void snake::setDirection(std::pair<int,int> dir){
	if(movement + dir != (std::pair<int,int>){0,0})
		movement = dir;
}
int snake::getXY(int x, int y){
	return tiles[y * X + x]&7;
}
void snake::clear(){
	delete[] tiles;
}
