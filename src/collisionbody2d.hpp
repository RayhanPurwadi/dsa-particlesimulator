#ifndef __COLLISIONBODY2D_H
#define __COLLISIONBODY2D_H

#include <vector>

#include "body2d.hpp"

enum CollisionShape2D {
	COLLISION_SHAPE_CIRCLE,
	COLLISION_SHAPE_RECTANGLE,
};

class CollisionBody2D : public Body2D {
	protected:
	CollisionShape2D collision_shape;
	std::vector<ImVec2> collision_polygon;

	public:
	CollisionBody2D() : Body2D() {};
	void add_collision_point(ImVec2 v);
};

#endif
