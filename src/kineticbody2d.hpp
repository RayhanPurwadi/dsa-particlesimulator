#ifndef __KINETICBODY2D_H
#define __KINETICBODY2D_H

#include "collisionbody2d.hpp"

class Environment;

class KineticBody2D : public CollisionBody2D {
	public:
	ImVec2 velocity;
	Environment* env;
	bool physicsEnabled = true;

	KineticBody2D() : CollisionBody2D() {};
	virtual void process_physics(std::int32_t delta);
	void apply_velocity(ImVec2 v);
};

#endif
