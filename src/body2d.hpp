#ifndef __BODY2D_H
#define __BODY2D_H

class Body2D {
	public:
	float x, y;
	virtual void render() = 0;
};

#endif
