#include "enemy.h"


enemy::enemy(Texture* texture)
{
	Texture t = *texture;
	enemybody.setSize(Vector2f((t.getSize().x / 2), (t.getSize().y / 2)));
	enemybody.setTexture(texture);
	enemybody.setRotation(180.0f);
	enemybody.setOrigin(t.getSize().x / 4, t.getSize().y / 4);
	enemybody.setPosition(700, 200);
	speed = 40.0f;
}

void enemy::Update(float deltaTime)
{
	/*
	Vector2f movement(0.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		movement.x += speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		movement.x -= speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		movement.y -= speed * deltaTime;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		movement.y += speed * deltaTime;
	}
	playerbody.move(movement);
	*/
}

void enemy::Draw(RenderWindow& window)
{
	window.draw(enemybody);
}
