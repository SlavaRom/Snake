#pragma once

class Cell {
protected:
	float x, y, w, h;
public:
	Cell() {
		x = y = w = h = 0;
	}
	Cell(const float& x, const float& y, const float& w, const float& h) {
		updatePosition(x, y);
		this->w = w;
		this->h = h;
	}
	Cell(const float& x, const float& y) {
		updatePosition(x, y);
	}
	Cell(const Cell& cell) {
		updatePosition(cell);
		this->w = cell.w;
		this->h = cell.h;
	}
	Cell(const Cell* cell) {
		updatePosition(*cell);
		this->w = cell->w;
		this->h = cell->h;
	}
	
	void updatePosition(const float& x, const float& y) {
		this->x = x;
		this->y = y;
	}
	void updatePosition(const Cell& cell) {
		this->x = cell.x;
		this->y = cell.y;
	}
	void draw() {
		glRectf(this->x, this->y, this->x + 1, this->y + 1);
	}
	void add(const float& x, const float& y) {
		this->x += x;
		this->y += y;
	}
	float getX() const { return x; }
	float getY() const { return y; }
	void setX(const float& X) { x = X; }
	void setY(const float& Y) { y = Y; }
};
