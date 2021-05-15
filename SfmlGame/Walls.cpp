#include "Walls.h"

Walls::Walls(int psize, int mapsize)
{
	this->psize = psize;
	this->mapsize = mapsize;
}


Vector2f Walls::Random()
{
	float x, y;
	x = (int)((rand() % mapsize)*psize + psize / 2);
	y = (int)((rand() % (mapsize - 2))*psize + psize / 2 + psize * 2);
	walls[wallindex].setPosition(x, y);
	wallindex++;
}



void Walls::wallcreate()
{
	RectangleShape walltemp;
	walltemp.setSize(Vector2f(size, size));
	walltemp.setOrigin(walltemp.getSize().x / 2, walltemp.getSize().y / 2);
	walltemp.setPosition(Random());
	walltemp.setFillColor(Color(125,145,175));
	walls.push_back(walltemp);
}


void Walls::Draw(RenderWindow& window)
{
	for (int i = 0; i < walls.size(); i++)
	{
		window.draw(walls[i]);
	}
}