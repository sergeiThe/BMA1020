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


struct Pos2d
{
	float x;
	float y;
};

struct Vel2d
{
	float x;
	float y;
};

struct Acc2d
{
	float x;
	float y;
};

// Random

float random(float min, float max) {
	 std::random_device rnddev;
	 std::mt19937 gen(rnddev());
	 std::uniform_real_distribution<float> dist(min, max);

	return dist(gen);
}




// Constants
const float a = 10.0f;
const float pi = 3.14f;
const Acc2d acc = { 0.0f, 120.0f };

class SpawningBall
{
public:
	sf::CircleShape ball;
	sf::Color color;
	float radius;
	float distFromCenter;

	Pos2d pos;

	float initSpeed;
	Vel2d initVel;

	void initVariables(float x, float y, float speed, float ang)
	{
		this->color = sf::Color::Magenta;
		this->radius = 20.f;
		this->distFromCenter = 0;

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


	SpawningBall(float x, float y, float speed, float ang)
	{
		initVariables(x, y, speed, ang);
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
		}
		// Time
		float dt = clock.restart().asSeconds();
		t += dt;
		srand(t);
		// dt/60 is time spent on one frame

		// Updating

		// 1. Add 1 ball
		balls.push_back(new SpawningBall(x_center, y_center, static_cast<float>(rand() % 5) + 20.0f, random(0.0f, 2.0f * pi)));
		
		// 2. Update the balls' pos
		for (int i = 0; i < balls.size(); i++)
		{
		
			balls[i]->pos.x += balls[i]->initVel.x * dt;
			balls[i]->pos.y += acc.y * dt * dt + balls[i]->initVel.y * dt;
			

			// 3. Delete balls out of screen
			if ((balls[i]->pos.x + balls[i]->radius) < 0 ||
				(balls[i]->pos.x - balls[i]->radius) > window.getSize().x ||
				(balls[i]->pos.y + balls[i]->radius) < 0 ||
				(balls[i]->pos.y - balls[i]->radius) > window.getSize().y)
			{
				balls.erase(balls.begin() + i);
			}

		}

		window.clear();

		// Drawing
		for (int i = 0; i < balls.size(); i++)
		{
			balls[i]->ball.setPosition(balls[i]->pos.x, balls[i]->pos.y);
			window.draw(balls[i]->ball);
		}

		// Rendering
		window.display();

	}

	return 0;
}