#include "Bait.h"
using namespace sf;
using namespace std;


Bait::Bait(float size/*,Color& color*/,Texture &temptexture2)
{
	baitbody.setTexture(&temptexture2);
	baitbody.setSize(Vector2f(size, size));
	baitbody.setOrigin(baitbody.getSize().x / 2, baitbody.getSize().y / 2);
	//baitbody.setFillColor(color);
}

void Bait::BaitRandom(int psize,int mapsize)
{
	float x, y;
	//int windowsizex = psize * mapsize;
	//int windowsizey = psize * mapsize;
	x = (int)((rand() % mapsize)*psize + psize / 2);
	y = (int)((rand() % (mapsize-2))*psize + psize / 2 + psize*2);
	//x = ((int)(rand() % (windowsizex)) / psize)*psize + psize - psize / 2;
	//y = ((int)(rand() % (windowsizey - 2 * psize)) / psize)*psize + 3 * psize - psize / 2;
	baitbody.setPosition(x, y);
}

vector<float> Bait::Collision()
{
	vector<float> p;
	p.push_back(baitbody.getPosition().x);
	p.push_back(baitbody.getPosition().y);
	p.push_back(baitbody.getSize().x);
	return p;
}

void Bait::Draw(RenderWindow& window)
{
	window.draw(baitbody);
}

