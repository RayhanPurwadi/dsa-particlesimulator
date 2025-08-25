#ifndef __CIRCLE_H
#define __CIRCLE_H

#include <SFML/Graphics.hpp>
#include <imgui.h>

#include "kineticbody2d.hpp"

/**
 * @brief Collision circle thingy lmao
 */
class Circle : public KineticBody2D {
	protected:
	sf::CircleShape _circle;
	public:
	Circle() : KineticBody2D() {};
	void render(sf::RenderWindow* window, std::int32_t delta) override;
};

#endif
