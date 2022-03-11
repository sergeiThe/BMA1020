#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

float a = 10.0f;
float pi = 3.14f;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Week 9");

	// Spawning circular area
	sf::CircleShape spawningArea;
	spawningArea.setRadius(10);
	spawningArea.setOrigin(10, 10);
	spawningArea.setPosition(800.0f / 2, 800.0f / 2);


	// Creating balls
	
	int amountBalls = 50;
	vector <float> velocities(50);
	vector <sf::CircleShape> circles(50);





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

		// Changing variables



		window.clear();
		// Update here



		window.display();

	}

	return 0;
}