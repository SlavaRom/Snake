#pragma once

class Field {
	int left_x = -6;
	int right_x = 6;
	int bottom_y = -6;
	int top_y = 6;
public:
	void draw() {
		for (int j = left_x; j < right_x+2; j++) {
			glBegin(GL_LINES);
			glVertex2f(left_x, j);
			glVertex2f(right_x+1, j);
			glEnd();
		}
		for (int i = bottom_y; i < top_y+2; i++) {
			glBegin(GL_LINES);
			glVertex2f(i, bottom_y);
			glVertex2f(i, top_y+1);
			glEnd();
		}
	}
	int getLX() const { return left_x; }
	int getRX() const { return right_x; }
	int getBY() const { return bottom_y; }
	int getTY() const { return top_y; }
};