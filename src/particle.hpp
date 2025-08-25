#ifndef __PARTICLE_H
#define __PARTICLE_H

#include "kineticbody2d.hpp"

class Particle : public KineticBody2D {
	public:
	Particle() : KineticBody2D() {};
	virtual void render(std::int32_t delta) override;
};

#endif
