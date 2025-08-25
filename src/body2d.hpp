#ifndef __BODY2D_H
#define __BODY2D_H

#include <imgui.h>
#include <cstdint>

class Body2D {
	public:
	ImVec2 position;
	ImVec2 size;
	virtual void render(sf::RenderWindow* window, ::int32_t delta) = 0;
};


#endif
