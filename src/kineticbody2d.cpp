#include "kineticbody2d.hpp"
#include "environment.hpp"

void KineticBody2D::process_physics(std::int32_t delta) {
	// gas saving
	if (velocity.x + velocity.y == 0) return;

	float appliedX = velocity.x * env->timeScale * delta / SECOND;
	float appliedY = velocity.y * env->timeScale * delta / SECOND;
	position.x += appliedX;
	position.y += appliedY;
}

void KineticBody2D::apply_velocity(ImVec2 v) {
	velocity = v;
}