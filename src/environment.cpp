#include "environment.hpp"

void Environment::render(sf::RenderWindow* window, ::int32_t delta) {
	for (auto particle : particles) {
		particle->process_physics(delta);
		particle->render(window, delta);
	}
}

Environment::~Environment() {
	for (auto particle : particles) {
		delete particle;
	}
}

size_t Environment::create_particle(ImVec2 pos, ImVec2 size, ImVec2 initial_velocity) {
	Particle* p = new Particle();
	p->position = pos;
	p->size = size;
	p->velocity = initial_velocity;
	p->env = this;

	particles.emplace_back(p);
	
	return particles.size() - 1;
}