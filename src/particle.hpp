#ifndef __PARTICLE_H
#define __PARTICLE_H

#include "circle.hpp"

class Particle : public Circle {
	public:
	Particle() : Circle() {};
	virtual void render(sf::RenderWindow* window, std::int32_t delta) override;
};

#endif
