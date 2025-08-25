#include "particle.hpp"

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
	apply_velocity({direction.x * speed, direction.y * speed});
	KineticBody2D::process_physics(delta);
}