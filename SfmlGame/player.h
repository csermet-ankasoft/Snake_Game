#pragma once
#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream> 
#include "Bait.h"
using namespace sf;
using namespace std;
class player
{
public:
	player(float size, float positionx, float positiony,Color color, vector<float> windowssize);
	enum Collision { Side, Wall, bait, Nope };
	void Draw(RenderWindow& window);
	Collision Update(float& deltaTime);
	void EventFunction(Event event);
	Collision CollisionDetection(RectangleShape b, float close);
	Collision CollisionDetection(Vector2f movement);
	vector<RectangleShape> playerbody;
	void upgrade();
	RectangleShape head;
	
private:
	RectangleShape playerbodymake(Vector2f position);
	vector<float> windowssize;
	float speed;
	bool control;
	enum MoveDirection { Right, Left, Up, Down,n };
	MoveDirection move = n;
	MoveDirection LastMove = n;
	float size;
	Color color;
	vector<Vector2f> movementold;
};

