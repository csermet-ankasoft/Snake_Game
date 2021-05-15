#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream> 
using namespace sf;
using namespace std;
class Bait
{
public:
	Bait(float size/*,Color& color*/, Texture &temptexture2);
	void Draw(RenderWindow& window);
	vector<float> Collision();
	RectangleShape baitbody;
	void BaitRandom(int psize, int mapsize);


private:	
	bool control;
};

