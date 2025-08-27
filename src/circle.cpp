#include "circle.hpp"

void Circle::render(sf::RenderWindow* window, std::int32_t delta) {
	_circle.setPosition({position.x, position.y});
	_circle.setRadius(size.x); // i just dont want to do ellipse ok
	_circle.setOrigin({size.x, size.x});
	
	window->draw(_circle);
}