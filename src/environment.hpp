#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <imgui.h>
#include <SFML/Graphics.hpp>

class Particle;

class Environment {
	private:
	std::vector<Particle*> _particles;

	public:
	ImVec2 arenaSize;
	~Environment();
	void render(sf::RenderWindow* window, std::int32_t delta);
	size_t create_particle(ImVec2 pos, ImVec2 size, size_t speed, ImVec2 initial_direction);
};

#include "particle.hpp" // dont touch it'll break idk why

#endif
