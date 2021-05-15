#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream> 
using namespace sf;
using namespace std;
class Walls
{
public:	
	Walls(int psize ,int mapsize);
	void Draw(RenderWindow& window);
	void wallcreate();
	Vector2f Random();
	vector<RectangleShape> walls;
	int size;	
private:
	int psize, mapsize;
	int wallindex = 0;
};

