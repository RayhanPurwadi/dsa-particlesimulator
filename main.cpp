#include <SFML/Graphics.hpp>
#include <optional>

int main() {
	sf::RenderWindow window(sf::VideoMode({500, 500}), "Particle Simulator :: Rayhan - 5024241032");
	
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}