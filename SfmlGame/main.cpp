#include <SFML/Graphics.hpp>
#include <string> 
#include <iostream>
#include <time.h>
#include "player.h"
#include "Bait.h"
#include "bullet.h"

using namespace sf;
using namespace std;
//RectangleShape *head = nullptr;
//vector<RectangleShape*> body;
//---------------------------------------Start Variables----------------------------------------------

float psize = 30.0f, deltaTime = -1, baitsize = 25.0f, mapsize = 21.0f; //Mapsize tek sayý ver çünkü player konumu hatalý oluyor.

//---------------------------------------Start Variables----------------------------------------------

bool baitcheck(Bait bait,player snake/*,Wall wall*/)
{
	Vector2f baitp = bait.baitbody.getPosition();
	if (baitp == snake.head.getPosition())
	{
		return true;
	}
	for (int i = 0; i < snake.playerbody.size(); i++)
	{
		if (baitp == snake.playerbody[i].getPosition())
		{
			return true;
		}
	}
	return false;
}

bool eatselfcheck(player snake)
{
	for (int i = 0; i < snake.playerbody.size(); i++)
	{
		if (snake.head.getPosition() == snake.playerbody[i].getPosition())
		{
			return false;
		}
	}
	return true;
}


int main()
{
	//---------------------------------------START Settings--------------------------------------	
	srand(time(NULL));
	ContextSettings settings;
	settings.antialiasingLevel = 16;
	RenderWindow window(VideoMode(psize*mapsize, psize*mapsize), "Railgun", Style::Close, settings);
	window.setFramerateLimit(144);
	//---------------------------------------START Settings--------------------------------------
	//---------------------------------------Variables-------------------------------------------	
	Clock clock;
	Texture temptexture,baittexture;
	bool GamePause = true;
	vector<float> windowssize;	
	windowssize.push_back(window.getSize().x);
	windowssize.push_back((window.getSize().y));
	RectangleShape upside;
	upside.setSize(Vector2f(window.getSize().x, psize *2));
	upside.setFillColor(Color(140, 140, 200));
	RectangleShape GameOver;
	temptexture.loadFromFile("GameOver.png");
	GameOver.setTexture(&temptexture);
	GameOver.setSize(Vector2f(temptexture.getSize().x/2,temptexture.getSize().y/2));
	GameOver.setOrigin(Vector2f(GameOver.getSize().x / 2, GameOver.getSize().y / 2));
	GameOver.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	//---------------------------------------Variables-------------------------------------------
	//---------------------------------------Class----------------------------------------------
	player::Collision col = player::Collision::Nope;
	player snake(psize, psize*mapsize / 2, psize*mapsize / 2, Color(100, 100, 100), windowssize);
	player snake2 = snake;
	baittexture.loadFromFile("food.png");
	Bait bait(baitsize,baittexture);
	do
		bait.BaitRandom(psize, mapsize);
	while (baitcheck(bait,snake));

	//bait.Position(window.getSize().x, window.getSize().y,size);
	//---------------------------------------Class----------------------------------------------
	//---------------------------------------LOOP----------------------------------------------	
	vector<Bait*> x;						//TEST
	for (int i = 0; i < 20000; i++)
	{
		Bait *z = new Bait(baitsize,temptexture);
		do
			z->BaitRandom(psize, mapsize);
		while (baitcheck(*z, snake));
		x.push_back(z);
	}
	while (window.isOpen())
	{		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed)
			{
				snake.EventFunction(event);
			}
		}
		if (GamePause == true)
		{
			window.clear();
			window.draw(upside);	
			GamePause = snake.Update(deltaTime) != player::Collision::Side;
			if (GamePause == true)
			{
				GamePause = eatselfcheck(snake);
			}
			if (deltaTime == -5)
			{
				clock.restart().asSeconds();
			}
			deltaTime = clock.getElapsedTime().asMilliseconds();
			snake.Draw(window);
			bait.Draw(window);
			for (int i = 0; i < 20000; i++)						//TEST
			{
				x[i]->Draw(window);
			}
			window.display();
			if (snake.CollisionDetection(bait.baitbody, 0.0f) == player::Collision::bait)
			{
				do
					bait.BaitRandom(psize, mapsize);
				while (baitcheck(bait, snake));
				snake.upgrade();
			}
		}
		else
		{
			//window.clear();  //FULL CLEAR GAME OVER
			window.draw(GameOver);
			window.display();
			if (event.key.code == Keyboard::R)
			{
				snake = snake2;
				GamePause = true;
				do
					bait.BaitRandom(psize, mapsize);
				while (baitcheck(bait, snake));
			}
		}



		/*
		deltaTime = clock.restart().asSeconds();
		user1.Update(deltaTime * 10);
		//enemys.Update(deltaTime * 10);
		bullets.Update(deltaTime * 10, user1.playerbody.getPosition());
		window.clear();
		user1.Draw(window);
		enemys.Draw(window);
		bullets.Draw(window);
		window.display();
		*/
		/*
		for (CircleShape *x : sekiller)
		{
			window.draw(*x);
		}
		if (active)
		{
			active->setRadius(radius);
			active->setPosition(Vector2f(x, y));
			active->setFillColor(Color::Blue);
			active->setOutlineColor(Color::Red);
			active->setOutlineThickness(5);
			window.draw(*active);
		}
		*/
	}
	return 0;
}