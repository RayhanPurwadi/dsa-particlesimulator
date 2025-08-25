#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>
#include <cstdint>

#include "particle.hpp"

class Environment {
	private:
	std::vector<Particle*> _particles;

	public:
	~Environment();
	void render(sf::RenderWindow* window, std::int32_t delta);
	size_t create_particle(ImVec2 pos, ImVec2 size, size_t speed, ImVec2 initial_direction);
};

#endif
