#include "bullet.h"
#include <math.h>

bullet::bullet(Texture* texture)
{
	t = *texture;
	speed = 120.0f;
}

void bullet::Update(float deltaTime, Vector2f player)
{
	Vector2f movement(0.0f, 0.0f);
	movement.y -= speed * deltaTime*2;
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		RectangleShape bulet;
		bulet.setTexture(&t);
		bulet.setSize(Vector2f((t.getSize().x / 2), (t.getSize().y / 2)));
		bulet.setOrigin(t.getSize().x / 4, t.getSize().y / 4);
		bulet.setPosition(Vector2f(player.x,player.y-45.0f));
		bullets.push_back(bulet);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].move(movement);
	}	
}

void bullet::Draw(RenderWindow& window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].getPosition().x < -50.0f
			|| bullets[i].getPosition().x > window.getSize().x
			|| bullets[i].getPosition().y < -50.0f
			|| bullets[i].getPosition().y > window.getSize().y)
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			window.draw(bullets[i]);
		}
	}
	
}

