#include "collisionbody2d.hpp"

void CollisionBody2D::add_collision_point(ImVec2 v) {
	collision_polygon.emplace_back(v);
}