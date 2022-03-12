#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
// Position 2d
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

// Randomizer
float rand(float min, float max) {
	 std::random_device rnddev;
	 std::mt19937 gen(rnddev());
	std::uniform_real_distribution<float> dist(min, max);

	return dist(gen);
}

using namespace std;

// Constants
const float a = 10.0f;
const float pi = 3.14f;
const Acc2d acc = { 0.0f, 60.0f };

// Main program
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Week 9");

	// Spawning circular area
	sf::CircleShape spawningArea;
	spawningArea.setRadius(10);
	spawningArea.setOrigin(10, 10);
	spawningArea.setFillColor(sf::Color::Magenta);
	float x_center = 800.0f / 2;
	float y_center = 800.0f / 2;

	sf::CircleShape testball;
	testball.setFillColor(sf::Color::Red);
	testball.setRadius(100.f);
	testball.setOrigin(100.f, 100.f);

	// Creating balls
	
	int amountBalls = 50;
	vector <Vel2d> spawnVelocities(amountBalls);
	vector <Pos2d> spawnPositions(amountBalls);
	vector <sf::CircleShape> circles(amountBalls);

	for (int i = 0; i < amountBalls; i++)
	{
		circles[i].setFillColor(sf::Color::Green);
		circles[i].setRadius(20.f);
		circles[i].setOrigin(20.f, 20.f);
	}

	// Spawning
	float distance = 100.0f;
	for (int i = 0; i < amountBalls; i++)
	{
		float randomAng = rand(0.0f, 2.0f * pi);
		float randomSpeed = rand(20.0f, 50.0f);
		

		// Initial position
		spawnPositions.at(i) = {
			x_center + distance * cos(randomAng),
			y_center + distance * sin(randomAng)
		};
		circles.at(i).setPosition(spawnPositions.at(i).x, spawnPositions.at(i).y);
		// Initial velocity
		spawnVelocities[i] = {
			cos(randomAng) * randomSpeed,
			sin(randomAng) * randomSpeed
		};
	}
	

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

		// Changing variables
		spawningArea.setPosition(x_center, y_center);

		// Position
		for (int i = 0; i < amountBalls; i++)
		{
			// pos_x = v_x_spawn * t
			// pos_y = acc_y/2 * t^2 + v_y_spawn * t + pos_y_spawn

			float pos_x = spawnVelocities[i].x * t + spawnPositions[i].x;
			float pos_y = acc.y/2 * t * t + spawnVelocities[i].y * t + spawnPositions[i].y;



			circles.at(i).setPosition(pos_x, pos_y);
		}

		window.clear();

		window.draw(spawningArea);
		for (int i = 0; i < amountBalls; i++)
		{
			
			window.draw(circles.at(i));
		}

		window.draw(testball);
		// window.draw(spawningArea);
		window.display();

	}

	return 0;
}