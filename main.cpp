#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({500, 500}), "Particle Simulator :: Rayhan - 5024241032");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.display();
	}

	return 0;
}