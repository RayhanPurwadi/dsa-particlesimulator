#include "circle.hpp"

void Circle::render(sf::RenderWindow* window, std::int32_t delta) {
	window->draw(_circle);
}