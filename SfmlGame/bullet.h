#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream> 
using namespace sf;
using namespace std;
class bullet
{
public:
	bullet(Texture* texture);
	void Draw(RenderWindow& window);
	void Update(float deltaTime,Vector2f player);

private:
	Texture t;
	float speed;
	bool control;
	vector<RectangleShape> bullets;



};

