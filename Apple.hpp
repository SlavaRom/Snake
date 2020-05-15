#pragma once

class Apple : public Cell{
public:
	Apple() : Cell() {}
	Apple(const float& x, const float& y, const float& w, const float& h) : Cell(x,y,w,h) {}
	Apple(const float& x, const float& y) : Cell(x,y) {}
	void updateRandomly() {
		this->x = random(-6, 6);
		this->y = random(-6, 6);
	}
};
