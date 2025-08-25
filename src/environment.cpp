#include "environment.hpp"

void Environment::render(sf::RenderWindow* window, ::int32_t delta) {
	for (auto particle : particles) {
		particle->render(window, delta);
	}
}

Environment::~Environment() {
	for (auto particle : particles) {
		delete particle;
	}
}