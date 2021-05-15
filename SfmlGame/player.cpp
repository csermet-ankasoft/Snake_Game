#include "player.h"
#include "Bait.h"
using namespace sf;
using namespace std;

player::player(float size, float positionx, float positiony,Color color, vector<float> windowssize)
{
	this->size = size;
	this->windowssize = windowssize;
	this->color = color;
	speed = size;
	head = playerbodymake(Vector2f(positionx+speed, positiony));
	head.setFillColor(Color(70, 120, 240));
	playerbody.push_back(playerbodymake(Vector2f(head.getPosition().x - speed, head.getPosition().y)));
	movementold.push_back(Vector2f(speed, 0.0f));
	playerbody.push_back(playerbodymake(Vector2f(head.getPosition().x - speed*2, head.getPosition().y)));
	movementold.push_back(Vector2f(speed, 0.0f));
}

RectangleShape player::playerbodymake(Vector2f position)
{
	RectangleShape playerbodytemp;
	playerbodytemp.setSize(Vector2f(size, size));
	playerbodytemp.setOrigin(playerbodytemp.getSize().x / 2, playerbodytemp.getSize().y / 2);
	playerbodytemp.setPosition(position);
	playerbodytemp.setFillColor(color);
	return playerbodytemp;
}

void player::upgrade()
{
	playerbody.push_back(playerbodymake(playerbody[playerbody.size() - 1].getPosition()));
	movementold.push_back(Vector2f(0.0f, 0.0f));
}

void player::EventFunction(Event event)
{
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::D && LastMove != MoveDirection::Left && LastMove != MoveDirection::Right /*Keyboard::isKeyPressed(Keyboard::D)*/)
		{
			move = MoveDirection::Right;
		}
		else if (event.key.code == Keyboard::A && LastMove != MoveDirection::Right && LastMove != MoveDirection::Left)
		{
			move = MoveDirection::Left;
		}
		else if (event.key.code == Keyboard::W && LastMove != MoveDirection::Down && LastMove != MoveDirection::Up)
		{
			move = MoveDirection::Up;
		}
		else if (event.key.code == Keyboard::S && LastMove != MoveDirection::Up && LastMove != MoveDirection::Down)
		{
			move = MoveDirection::Down;
		}
	}
}

player::Collision player::CollisionDetection(RectangleShape bait, float close)
{
	float Deltax = abs(bait.getPosition().x - head.getPosition().x);
	float Intersectionx = Deltax - (bait.getSize().x / 2 + head.getSize().x / 2);
	float Deltay = abs(bait.getPosition().y - head.getPosition().y);
	float Intersectiony = Deltay - (bait.getSize().y / 2 + head.getSize().y / 2);
	if (Intersectionx < close && Intersectiony < close)
	{
		return  Collision::bait;
	}	
	return  Collision::Nope;
}

player::Collision player::CollisionDetection(Vector2f movement)
{
	Collision col;
	if (head.getPosition().x + movement.x - head.getSize().x / 2 < 0
		|| head.getPosition().x + movement.x + head.getSize().x / 2 > windowssize[0]
		|| head.getPosition().y + movement.y - head.getSize().y / 2 < size * 2
		|| head.getPosition().y + movement.y + head.getSize().y / 2 > windowssize[1]
		)
	{
		return Collision::Side;
	}
	return  Collision::Nope;
}


player::Collision player::Update(float& deltaTime)
{	
	if (deltaTime > 100)
	{
		deltaTime = -5;
		Vector2f movement(0.0f, 0.0f);
		if (move == MoveDirection::Right)
		{
			LastMove = MoveDirection::Right;
			movement.x += speed;
		}
		else if (move == MoveDirection::Left)
		{
			LastMove = MoveDirection::Left;
			movement.x -= speed;
		}
		else if (move == MoveDirection::Up)
		{
			LastMove = MoveDirection::Up;
			movement.y -= speed;
		}
		else if (move == MoveDirection::Down)
		{
			LastMove = MoveDirection::Down;
			movement.y += speed;
		}
		if (CollisionDetection(movement) == Collision::Side)
		{
			return Collision::Side;
		}
		if (move != MoveDirection::n)
		{
			head.move(movement);
			/*
			playerbody[0].move(movementold[0]);
			movementold[0] = movement;
			playerbody[1].move(movementold[1]);
			movementold[1] = movement;
			*/
			for (int i = 0; i < playerbody.size(); i++)
			{
				playerbody[i].move(movementold[i]);
			}
			for (int i = playerbody.size()-1; i > 0; i--)
			{
				movementold[i] = movementold[i-1];
			}
			movementold[0] = movement;
			
		}		
	}
	return Collision::Nope;	
}

void player::Draw(RenderWindow& window)
{	
	for (int i = 0; i < playerbody.size(); i++)
	{
		window.draw(playerbody[i]);
	}
	window.draw(head);
}
