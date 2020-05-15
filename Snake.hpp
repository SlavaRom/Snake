#pragma once

class Snake : public list<Cell*>{
public:
	Snake() : list() {}
	void draw() {
		for (list<Cell*>::iterator iter = this->begin(); iter != this->end(); iter++) {
			(*iter)->draw();
		}
	}
	void updatePosition(const float& x, const float& y) {
		this->front()->add(x, y);
	}
	void setHeadPosition(const float& x, const float& y) {
		this->front()->updatePosition(x, y);
	}
	/*Раскомментировать строки "return false;" для запрета вхождения змейки в стену*/
	bool checkConstraints(const Field* field) {
		int p = 0;
		if (this->size() > 2) {
			for (list<Cell*>::iterator iter = this->begin(); iter != this->end(); iter++) {
				if (p == 0) { iter++; p++; }
				if ((this->front()->getX() == (*iter)->getX()) && (this->front()->getY() == (*iter)->getY())) {
					return false;
				}
			}
		}
		if (this->front()->getY() > field->getTY()) {
			setHeadPosition(this->front()->getX(), -6);
			//return false;
		}
		if (this->front()->getY() < field->getBY()) {
			setHeadPosition(this->front()->getX(), 6);
			//return false;
		}
		if (this->front()->getX() > field->getRX()) {
			setHeadPosition(-6, this->front()->getY());
			//return false;
		}
		if (this->front()->getX() < field->getLX()) {
			setHeadPosition(6, this->front()->getY());
			//return false;
		}
		return true;
	}
	void eatApple(Apple* apple) {
		if (this->front()->getX() == apple->getX() && this->front()->getY() == apple->getY()) {
			this->push_back(new Cell(this->back()));
			apple->updateRandomly();
		}
	}
	int getTextedSize_int() {
		return (this->size() - 1);
	}
	void update() {
		for (list<Cell*>::iterator iter = this->end(), prev = this->end();;) {
			if (prev != this->end()) {
				Cell* pElem = *prev;
				Cell* cElem = *iter;
				pElem->setX(cElem->getX());
				pElem->setY(cElem->getY());
			}
			prev = iter;
			if (iter == this->begin())
				break;
			iter--;
		}
	}
};