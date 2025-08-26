#include "environment.hpp"

void Environment::render(sf::RenderWindow* window, ::int32_t delta) {
	for (auto particle : _particles) {
		particle->process_physics(delta);
		particle->render(window, delta);
	}
}

Environment::~Environment() {
	for (auto particle : _particles) {
		delete particle;
	}
}

size_t Environment::create_particle(ImVec2 pos, ImVec2 size, size_t speed, ImVec2 initial_direction) {
	Particle* p = new Particle();
	p->position = pos;
	p->size = size;
	p->speed = speed;
	p->direction = initial_direction;
	p->env = this;

	_particles.emplace_back(p);
	
	return _particles.size() - 1;
}