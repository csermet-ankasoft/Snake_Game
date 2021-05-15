#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream> 
using namespace sf;
using namespace std;
class enemy
{
public:
	enemy(Texture* texture);
	void Draw(RenderWindow& window);
	void Update(float deltaTime);

	RectangleShape enemybody;


private:
	float speed;
	bool control;

};


