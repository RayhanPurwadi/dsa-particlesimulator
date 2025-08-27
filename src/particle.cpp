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
sf::Color determine_color(size_t mass) {
	RGBRotate r(clamp(190 + (mass / 10)));
	return r.apply(sf::Color(130, 25, 200)); // balance red and blue to make purple, put some gren
}
#undef clamp

void Particle::render(sf::RenderWindow* window, ::int32_t delta) {
    if (!haveINeverEverDoThis) {
        _circle.setFillColor(determine_color(mass));
        haveINeverEverDoThis = true;
    }
    Circle::render(window, delta);
}

void Particle::process_physics(std::int32_t delta) {
    // Save old position
    float oldX = position.x;
    float oldY = position.y;

    KineticBody2D::process_physics(delta);

    ImVec2 arenaSize = env->arenaSize;
    float radius = size.x;

    // Move particle
    float appliedX = velocity.x * env->timeScale * delta / SECOND;
    float appliedY = velocity.y * env->timeScale * delta / SECOND;
    position.x += appliedX;
    position.y += appliedY;

    // Arena bounds collision (for top-left origin, size.x is radius)
    if (position.x - radius < 0) {
        position.x = radius;
        velocity.x = -velocity.x;
    } else if (position.x + radius > arenaSize.x) {
        position.x = arenaSize.x - radius;
        velocity.x = -velocity.x;
    }
    if (position.y - radius < 0) {
        position.y = radius;
        velocity.y = -velocity.y;
    } else if (position.y + radius > arenaSize.y) {
        position.y = arenaSize.y - radius;
        velocity.y = -velocity.y;
    }

    ImVec2 totalAcc = {0, 0};
    for (Particle *other : env->particles) {
        if (other == this) continue;

        double oRad = other->size.x;
        ImVec2 oPos = other->position;

        double dx = position.x - oPos.x;
        double dy = position.y - oPos.y;
        double dist = sqrt(dx*dx + dy*dy);

        float minDist = radius + oRad;
        float overlap = minDist - dist;
        float nx = dx / dist;
        float ny = dy / dist;

        // Particle-particle collision for n-body sim
        if (env->nBodyMode && dist < minDist && dist > 0) {
            float m1 = mass;
            float m2 = other->mass;

            float v1n = velocity.x * nx + velocity.y * ny;
            float v2n = other->velocity.x * nx + other->velocity.y * ny;

            const float restitution = 0.8f;

            float v1nNew = (v1n * (m1 - m2) + 2 * m2 * v2n) / (m1 + m2);
            float v2nNew = (v2n * (m2 - m1) + 2 * m1 * v1n) / (m1 + m2);

            v1nNew *= restitution;
            v2nNew *= restitution;

            float tx = -ny;
            float ty = nx;
            float v1t = velocity.x * tx + velocity.y * ty;
            float v2t = other->velocity.x * tx + other->velocity.y * ty;

            velocity.x = v1nNew * nx + v1t * tx;
            velocity.y = v1nNew * ny + v1t * ty;
            other->velocity.x = v2nNew * nx + v2t * tx;
            other->velocity.y = v2nNew * ny + v2t * ty;

            float totalMass = m1 + m2;
            float move1 = (m2 / totalMass) * overlap;
            float move2 = (m1 / totalMass) * overlap;
            position.x += nx * (move1/2);
            position.y += ny * (move1/2);
            other->position.x -= nx * (move2/2);
            other->position.y -= ny * (move2/2);
        } else if (!env->nBodyMode && dist < minDist && dist > 0) {
            // Particle-particle collision for non n-body sim
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

        // N-Body simulation
        if (env->nBodyMode && dist > 0) {
#define G_CONSTANT 8e-1
            double epsilon = 1.0f; // Softening factor
            double r = dist;
            double force = (G_CONSTANT * mass * other->mass) / (r * r + epsilon);
            ImVec2 forceV = {
                (oPos.x - position.x) / r,
                (oPos.y - position.y) / r
            };
            totalAcc.x += force * forceV.x / mass;
            totalAcc.y += force * forceV.y / mass;
#undef G_CONSTANT
        }

        // Resolve overlap
        if (dist < minDist && dist > 0) {
            position.x += nx * (overlap/2);
            position.y += ny * (overlap/2);
            other->position.x -= nx * (overlap/2);
            other->position.y -= ny * (overlap/2);
        }

        // clamp speed
        const float MAX_SPEED = env->maxSpeed;
        float speed = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (speed > MAX_SPEED) {
            velocity.x = velocity.x / speed * MAX_SPEED;
            velocity.y = velocity.y / speed * MAX_SPEED;
        }
        float otherSpeed = sqrt(other->velocity.x * other->velocity.x + other->velocity.y * other->velocity.y);
        if (otherSpeed > MAX_SPEED) {
            other->velocity.x = other->velocity.x / otherSpeed * MAX_SPEED;
            other->velocity.y = other->velocity.y / otherSpeed * MAX_SPEED;
        }
    }

    if (env->nBodyMode) {
        velocity.x += totalAcc.x * env->timeScale * delta;
        velocity.y += totalAcc.y * env->timeScale * delta;
    }

    if (env->selectedBall == this) {
        ImVec2 mPos = ImGui::GetMousePos();
        position.x = mPos.x;
        position.y = mPos.y;
    }
}