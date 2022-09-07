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
				startPosX = i;
				startPosY = j;
			}
			x++;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Point * vertex =new Point();
			vertex->posX = i;
			vertex->posY = j;
			vertex->value = -1;
			vertices.push_back(vertex);
			if (this->map[i][j]!='X'&& this->map[i][j] != '-' && this->map[i][j]!='T')
			{
				endpoints.push_back(vertex);
			}
			
		}
	}

	for (int i = 0; i < width * height; i++) {
	Point *vertex = vertices.at(i);
	int k = 1;
		
		for (int j = 0; j < 2; j++) {
			
			if (IsSteppable(vertex->posX, vertex->posY, vertex->posX+k, vertex->posY))
			{	
				vertex->neighbours.push_back(VertexAt(vertex->posX+k, vertex->posY));
			}
			if (IsSteppable(vertex->posX, vertex->posY, vertex->posX, vertex->posY + k))
			{
					vertex->neighbours.push_back(VertexAt(vertex->posX, vertex->posY + k));
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
	return d;
}

int Map::Dijkstra() {
	int step = 0;
	VertexAt(startPosX,startPosY)->value = 0;
	
	for (auto neighbour : VertexAt(startPosX, startPosY)->neighbours)
	{
		neighbour->value = step +1;
	}
	
	step++;
	int x;
	while (!vertices.empty())
	{
		x = 0;
		for (Point* vertex : vertices)
		{
			
			if (step == vertex->value) {
				x++;
			
				for (auto neighbour : vertex->neighbours)
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

	int sum = 0;
	for (auto point : endpoints)
		if(point->value>0)
			sum += point->value - 1;
		return sum;
}

Point* Map::VertexAt(int posX, int posY) {
	return vertices.at(posX * width + posY);
}

Map::~Map() {
		for (int i = 0; i < height; ++i)
			delete map[i];
		delete map;
		while (!vertices.empty()) {
			delete vertices.back();
			vertices.pop_back();
		}
		endpoints.clear();
}