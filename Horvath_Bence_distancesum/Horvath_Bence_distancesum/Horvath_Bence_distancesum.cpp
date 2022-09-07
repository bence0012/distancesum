#include "Map.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int height, width;
    cin >> height;
    cin >> width;
    string mapIn="";
    string temp;
    cin.get();
    for (int i = 0; i < height; i++) {
         getline(cin, temp);
         mapIn+=temp;
    }

    Map *map = new Map(height,width,mapIn);
    cout <<map->Dijkstra();
  
}

