#include "kineticbody2d.hpp"

void KineticBody2D::process_physics(std::int32_t delta) {
	// gas saving
	if (velocity.x + velocity.y == 0) return;

	position.x += velocity.x * MULTIPLIER * delta / SECOND;
	position.y += velocity.y * MULTIPLIER * delta / SECOND;
}

void KineticBody2D::apply_velocity(ImVec2 v) {
	velocity = v;
}