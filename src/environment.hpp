#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>
#include <cstdint>

#include "particle.hpp"

class Environment {
	public:
	~Environment();
	std::vector<Particle*> particles;
	void render(std::int32_t delta);
};

#endif
