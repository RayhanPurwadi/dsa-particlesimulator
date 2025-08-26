#include "kineticbody2d.hpp"
#include "environment.hpp"

void KineticBody2D::process_physics(std::int32_t delta) {
	// gas saving
	if (velocity.x + velocity.y == 0) return;

	float appliedX = velocity.x * MULTIPLIER * delta / SECOND;
	float appliedY = velocity.y * MULTIPLIER * delta / SECOND;
	position.x += appliedX;
	position.y += appliedY;
	
	// Arena as Bounding Box
	ImVec2 arenaSize = env->arenaSize;
	/// X-axis movenet
	bool bounceX = false;
	if (position.x < 0) {
		position.x = 0;
		bounceX = true;
	} else if (position.x > arenaSize.x) {
		position.x = arenaSize.x;
		bounceX = true;
	}
	// Y-axis movement
	bool bounceY = false;
	if (position.y < 0) {
		position.y = 0;
		bounceY = true;
	} else if (position.y > arenaSize.y) {
		position.y = arenaSize.y;
		bounceY = true;
	}
	
	// Reset simulated position
	position.x -= appliedX;
	position.y -= appliedY;
	
	// Apply bounce
	if (bounceX) velocity.x *= -1;
	if (bounceY) velocity.y *= -1;

	// Calculate new uhh
	appliedX = velocity.x * MULTIPLIER * delta / SECOND;
	appliedY = velocity.y * MULTIPLIER * delta / SECOND;
	position.x += appliedX;
	position.y += appliedY;
}

void KineticBody2D::apply_velocity(ImVec2 v) {
	velocity = v;
}