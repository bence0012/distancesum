#include "Map.h"
#include <string>
#include <iostream>
#include <bitset>
#include <vector>




Map::Map(int h, int w, string map) :height(h), width(w) {

	this->map = new char*[height];
	for (int i = 0; i < height; ++i){
			this->map[i] = new char[width];

	}
		int x = 0;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				this->map[i][j] = map[x];
				if (map[x] == 'T') {
					startPos.posX = i;
					startPos.posY = j;
				}
				x++;
			}
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Point *v=new Point();
				v->posX = i;
				v->posY = j;
				v->value = -1;
				verticies.push_back(v);
				if (this->map[i][j]!='X'&& this->map[i][j] != '-' && this->map[i][j]!='T')
				{
					endpoints.push_back(v);
				}
				
			}
		}
		//cout << unvisited.size();
		for (int i = 0; i < width * height; i++) {
			Point *p = verticies.at(i);
			int k = 1;
			
			for (int j = 0; j < 2; j++) {
				
				if (IsSteppable(p->posX,p->posY,p->posX+k,p->posY))
				{
					
					p->neighbours.push_back(verticies.at((p->posX+k) * width + p->posY));
				}
				k *= -1;
			}
			for (int j = 2; j < 4; j++) {

				if (IsSteppable(p->posX, p->posY, p->posX, p->posY+k))
				{
					p->neighbours.push_back(verticies.at(p->posX * width + p->posY + k));
				}
				k *= -1;
			}
			
		}
		

}


bool Map::IsSteppable(int startX, int startY, int destX, int destY) {
	if (destX<0 || destX>=height||destY<0||destY>=width)
		return false;
	if (map[startX][startY] != '-' && map[startX][startY] != 'T')
		return false;
	if (map[destX][destY] == 'X')
		return false;
	if (map[destX][destY]=='-')
		return true;

	Direction stepDir;
	string dirBitmap;
	
	WhatDirection(startX, startY, destX, destY, stepDir);
	dirBitmap=ConvertDecToBinaryS(ConvertHexaToDec(map[destX][destY]));
	return CharToBool(dirBitmap[stepDir]);
	
}


void Map::WhatDirection(int startX, int startY, int destX, int destY, Direction& dir){
	if (startX > destX)
		dir = Up;
	else if (startX < destX)
		dir = Down;
	else if (startY < destY)
		dir = Left;
	else
		dir = Right;
}



bool Map::CharToBool(char c) {
	if (c == '1')
		return true;
	else 
		return false;
}



int Map::ConvertHexaToDec(char c) {
	int converted;
	if (c < 58)
		converted = c - '0';
	else
		converted = c - 65 + 9;
	return converted;
	
}

string Map::ConvertDecToBinaryS(int decimal) {
	string d= std::bitset<4>(decimal).to_string();
	//cout << "\n" << d << "\n";
	return d;
}

int Map::Dijkstra() {
	int step = 0;
	verticies.at(startPos.posX * width + startPos.posY)->value = 0;
	
	for (auto neighbour : verticies.at(startPos.posX * width + startPos.posY)->neighbours)
	{
	neighbour->value = step +1;
	}
	
	step++;
	int x;
	while (!verticies.empty())
	{
		x = 0;
		for (Point* var : verticies)
		{
			
			if (step == var->value) {
				x++;
			
				for (auto neighbour : var->neighbours)
				{
					if (neighbour->value>step+1|| neighbour->value<0)
					{
						neighbour->value = step + 1;
					}
				}
			}
		}
		if (x == 0)
			break;
		step++;
	}

	cout << "\n";
	for (auto elem : endpoints) {
		//cout << elem->value << " ";
	}

	for (auto elem : verticies)
	{
		if (elem->value < 10 && elem->value > -1)
			cout << "0";
		cout << elem->value << " ";
	}


	cout << "\n"<< IsSteppable(1,8,1,7) << "\n";
	int sum = 0;
	for (auto elem : endpoints)
		if(elem->value>0)
			sum += elem->value - 1;
		return sum;
	


}
int Map::NumberOfShortestPaths(Point* start) {

	
	
	if (start->value == 0)
	{
		return 1;
	}
	int x = 0;
	for (auto neighbour : start->neighbours) {
		if (neighbour->value < start->value) {
			x += NumberOfShortestPaths(neighbour);
		}
		
	}
	return x;
	
}

Map::~Map() {
		for (int i = 0; i < height; ++i)
			delete map[i];
		delete map;
}