#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <imgui.h>
#include <SFML/Graphics.hpp>

class Particle;

class Environment {
	public:
	std::vector<Particle*> particles;
	ImVec2 arenaSize;
	float timeScale = 1;
	~Environment();
	void render(sf::RenderWindow* window, std::int32_t delta);
	size_t create_particle(ImVec2 pos, ImVec2 size, ImVec2 initial_velocity);
};

#include "particle.hpp" // dont touch it'll break idk why

#endif
