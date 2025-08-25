#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>

#include "particle.hpp"

class Environment {
	public:
	std::vector<Particle> particles;
	void render();
};

#endif
