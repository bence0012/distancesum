#pragma once
using namespace std;
#include <string>
#include <vector>

typedef enum Direction
{
	Down, Left, Up, Right
};


 struct Point {
	 int posX, posY, value;
	 vector<Point*> neighbours;
 };

class Map
{
public:
	Map(int h, int w, string map);
	~Map();
	bool IsSteppable(int startX, int startY, int destX, int destY);
	void WhatDirection(int startX, int startY, int destX, int destY, Direction& dir);
	int Dijkstra();
	bool CharToBool(char c);
	int ConvertHexaToDec(char c);
	string ConvertDecToBinaryS(int decimal);
	Point* VertexAt(int posX, int posY);
private:

	int height, width;
	int startPosX, startPosY;
	char** map;
	vector<Point*> vertices, endpoints;

};

