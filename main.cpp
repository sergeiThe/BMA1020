#include <iostream>
#include <string>
#include <vector>
// #include "SpawningBall.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <random>
#include <cstdlib>

using namespace std;


struct Vec2
{
	float x;
	float y;
};


// Random

float random() {
	static std::random_device rnddev;
	static std::mt19937 gen(rnddev());
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	return dist(gen);
}

Vec2 radialAcc(float speed, float ang)
{
	Vec2 acc = {
		cos(ang) * -speed,
		sin(ang) * -speed
	};

	return acc;
}




// Constants
const float a = 10.0f;
const float pi = 3.14f;
const Vec2 gravity = { 0.0f, 8.0f };
const Vec2 drag = { -100.0f, 0.0f };


class SpawningBall
{
public:
	sf::CircleShape ball;
	sf::Color color;
	float radius;
	float distFromCenter;

	Vec2 totalAcc;
	Vec2 pos;

	float initSpeed;
	Vec2 initVel;
	float timeSinceSpawn;

	float velAng;

	void initVariables(float x, float y, float speed, float ang, Vec2 acc)
	{
		this->color = sf::Color::Green;
		this->radius = 10.f;
		this->distFromCenter = 100.0f;
		this->timeSinceSpawn = 0;
		// Total acceleration
		this->totalAcc = acc;
		this->velAng = ang;
		// Spawn position
		pos = { x, y };
		// Spawn velocity - cos * speed and sin * speed
		initSpeed = speed; // random(30.0f, 60.0f);
		initVel = {
			cos(ang) * initSpeed,
			sin(ang) * initSpeed
		};

		ball.setFillColor(color);
		ball.setRadius(radius);
		ball.setOrigin(radius, radius);
	}


	SpawningBall(float x, float y, float speed, float ang, Vec2 acc)
	{
		initVariables(x, y, speed, ang, acc);
	}

};




// Main program
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Week 9");
	window.setFramerateLimit(60);

	float x_center = 800.0f / 2;
	float y_center = 800.0f / 2;

	// Creating balls
	vector<SpawningBall*> balls;

	sf::Clock clock;
	clock.restart();
	float t = 0;

	int round = 1;

	// Game loop
	while (window.isOpen())
	{
		sf::Event e;
		

		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}

			if (e.key.code == sf::Keyboard::Space && e.type == e.KeyReleased)
			{
				round++;
				if (round == 4)
					round = 1;
			}
		}
		// Time
		float dt = clock.restart().asSeconds();
		t += dt;
		// srand(t);
		// dt/60 is time spent on one frame

		

		// Updating

		window.clear();
		// 1. Add 1 ball at a time

		if (round == 1)
			balls.push_back(new SpawningBall(x_center, y_center, random() * 8 + 1, -(random() * pi/3 + pi/3), gravity));
		if (round == 2)
			balls.push_back(new SpawningBall(x_center, y_center, random() * 8 + 1, -(random() * pi / 3 + pi / 3), {gravity.x + drag.x, gravity.y + drag.y}));
		if (round == 3)
		{
			
			float velAng = random() * 2 * pi;
			balls.push_back(new SpawningBall(x_center + 100.f*cos(velAng), y_center + 100.f * sin(velAng), 8.0f, velAng, { -cos(velAng) * 10.0f,-sin(velAng) * 10.0f }));
		}
		
		

		// 2. Update the balls' pos
		for (int i = 0; i < balls.size(); i++)
		{ 
			balls[i]->timeSinceSpawn += dt;
			balls[i]->pos.x = balls[i]->pos.x + balls[i]->totalAcc.x / 2 * balls[i]->timeSinceSpawn
				* balls[i]->timeSinceSpawn + balls[i]->initVel.x 
				* balls[i]->timeSinceSpawn;
			balls[i]->pos.y = balls[i]->pos.y + balls[i]->totalAcc.y / 2 * balls[i]->timeSinceSpawn
				* balls[i]->timeSinceSpawn + balls[i]->initVel.y
				* balls[i]->timeSinceSpawn;


			// cout << balls.size() << endl;
			// 3. Delete balls out of screen

			if (round == 1 || round == 2)
			{
				if ((balls[i]->pos.x + balls[i]->radius) < 0 ||
					(balls[i]->pos.x - balls[i]->radius) > window.getSize().x ||
					(balls[i]->pos.y - balls[i]->radius) > window.getSize().y)
				{
					delete balls[i];
					balls.erase(balls.begin() + i);
				}
			}
			else if (round == 3)
			{
				if (balls[i]->velAng >= 0 && balls[i]->velAng < pi)
				{
					if (balls[i]->pos.y < 400.0f)
					{
						delete balls[i];
						balls.erase(balls.begin() + i);
					}
				}
				else
				{
					if (balls[i]->pos.y > 400.0f)
					{
						delete balls[i];
						balls.erase(balls.begin() + i);
					}
				}
			}
		}
			
		// Drawing
		for (int i = 0; i < balls.size(); i++)
		{
			balls[i]->ball.setPosition(balls[i]->pos.x, balls[i]->pos.y);
			window.draw(balls[i]->ball);
		}

		window.display();

	}

	return 0;
}