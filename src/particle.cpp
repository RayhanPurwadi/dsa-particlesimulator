#include "particle.hpp"
#include "environment.hpp"

// This RGBRotate has been adapted from python to c++ from here:
// https://stackoverflow.com/a/8510751
#define clamp(v) (v < 0 ? 0 : (v > 255 ? 255 : v))
#define d2r(d) (d/180.0f * (double)M_PI)
class RGBRotate {
	public:
	double matrix[3][3];
	RGBRotate(double degrees) {
		double cosA = cos(d2r(degrees));
		double sinA = sin(d2r(degrees));

		matrix[0][0] = cosA + (1.0 - cosA) / 3.0;
        matrix[0][2] = 1./3. * (1.0 - cosA) + sqrt(1./3.) * sinA;
        matrix[0][1] = 1./3. * (1.0 - cosA) - sqrt(1./3.) * sinA;
        matrix[1][0] = 1./3. * (1.0 - cosA) + sqrt(1./3.) * sinA;
        matrix[1][1] = cosA + 1./3.*(1.0 - cosA);
        matrix[1][2] = 1./3. * (1.0 - cosA) - sqrt(1./3.) * sinA;
        matrix[2][0] = 1./3. * (1.0 - cosA) - sqrt(1./3.) * sinA;
        matrix[2][1] = 1./3. * (1.0 - cosA) + sqrt(1./3.) * sinA;
        matrix[2][2] = cosA + 1./3. * (1.0 - cosA);
	}
	sf::Color apply(sf::Color c) {
		double r = c.r;
		double g = c.g;
		double b = c.b;

		double rx = r * matrix[0][0] + g * matrix[0][1] + b * matrix[0][2];
        double gx = r * matrix[1][0] + g * matrix[1][1] + b * matrix[1][2];
        double bx = r * matrix[2][0] + g * matrix[2][1] + b * matrix[2][2];

		return {clamp(rx), clamp(gx), clamp(bx)};
	}
};
#undef d2r

#define clamp(v) (v < 190 ? 190 : (v % 361))
sf::Color determine_color(size_t speed) {
	RGBRotate r(clamp(190 + speed));
	return r.apply(sf::Color(130, 25, 200)); // balance red and blue to make purple, put some gren
}
#undef clamp

void Particle::render(sf::RenderWindow* window, ::int32_t delta) {
    if (!haveINeverEverDoThis) {
        _circle.setFillColor(determine_color(speed));
        haveINeverEverDoThis = true;
    }
    Circle::render(window, delta);
}

void Particle::process_physics(std::int32_t delta) {
    // Save old position
    float oldX = position.x;
    float oldY = position.y;

    // Update velocity (direction and speed only used for initialization)
    // If you want to change direction, set velocity = {direction.x * speed, direction.y * speed};
    KineticBody2D::process_physics(delta);

    ImVec2 arenaSize = env->arenaSize;
    float radius = size.x;

    // Move particle
    float appliedX = velocity.x * env->timeScale * delta / SECOND;
    float appliedY = velocity.y * env->timeScale * delta / SECOND;
    position.x += appliedX;
    position.y += appliedY;

    // Arena bounds collision (for top-left origin, size.x is radius)
    if (position.x < 0) {
        position.x = 0;
        velocity.x = fabs(velocity.x);
    } else if (position.x + radius * 2 > arenaSize.x) {
        position.x = arenaSize.x - radius * 2;
        velocity.x = -fabs(velocity.x);
    }
    if (position.y < 0) {
        position.y = 0;
        velocity.y = fabs(velocity.y);
    } else if (position.y + radius * 2 > arenaSize.y) {
        position.y = arenaSize.y - radius * 2;
        velocity.y = -fabs(velocity.y);
    }

    // Particle-particle collision
    for (Particle *other : env->particles) {
        if (other == this) continue;
        float oRad = other->size.x;
        ImVec2 oPos = other->position;
        float dx = position.x - oPos.x;
        float dy = position.y - oPos.y;
        float dist = sqrt(dx*dx + dy*dy);
        float minDist = radius + oRad;
        if (dist < minDist && dist > 0) {
            // Resolve overlap
            float overlap = minDist - dist;
            float nx = dx / dist;
            float ny = dy / dist;
            position.x += nx * (overlap/2);
            position.y += ny * (overlap/2);
            other->position.x -= nx * (overlap/2);
            other->position.y -= ny * (overlap/2);

            // Elastic collision
            float tx = -ny;
            float ty = nx;
            float dpTan1 = velocity.x * tx + velocity.y * ty;
            float dpTan2 = other->velocity.x * tx + other->velocity.y * ty;
            float dpNorm1 = velocity.x * nx + velocity.y * ny;
            float dpNorm2 = other->velocity.x * nx + other->velocity.y * ny;
            // Swap normal components
            float v1n = dpNorm2;
            float v2n = dpNorm1;
            velocity.x = tx * dpTan1 + nx * v1n;
            velocity.y = ty * dpTan1 + ny * v1n;
            other->velocity.x = tx * dpTan2 + nx * v2n;
            other->velocity.y = ty * dpTan2 + ny * v2n;
        }
    }

    // Calculate speed from velocity for color
    speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}