#ifndef __PARTICLE_H
#define __PARTICLE_H

#include <math.h>

#include "circle.hpp"

class Particle : public Circle {
	public:
	size_t speed;
	ImVec2 velocity;
	bool haveINeverEverDoThis;
	Particle* lastCollided;
	
	Particle() : Circle() {};
	virtual void render(sf::RenderWindow* window, std::int32_t delta) override;
	virtual void process_physics(std::int32_t delta) override;
};

#endif
