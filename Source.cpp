#include <windows.h>
#include <math.h>
#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <glut.h>
#include "GameUtils.hpp"
#include "Cell.hpp"
#include "Apple.hpp"
#include "Field.hpp"
using namespace std;
#include "Snake.hpp"

// ���������� ����������:
  // ������� ������ � ������ ���������� ������� ���� ����������
GLfloat windowWidth = 300;
GLfloat windowHeight = 300;
const int WIDTH = 600;	//������ ���� � ��������
const int HEIGHT = 600;	//������ ���� � ��������
//������� �������� ����
const int left_x = -10;
const int right_x = 10;
const int bottom_y = -10;
const int top_y = 10;
//��� ������
const float delta = 1.0f;

int x = 0;
int y = 0;

bool game = true;	//��������� ����

Snake* snake = new Snake();
Apple* apple = new Apple();
Field* field = new Field();

int score_int = 1;	//������� ����

// ��������� ���������� �������
void SetupRC(void);			//��������� ���������
void ChangeSize(int, int);	//���������� ��� ��������� �������� ����

void glWrite(float x, float y, int *font, string text) {
	int kls = text.size();
	glRasterPos2f(x, y);
	for (int i = 0; i < kls; i++)
		glutBitmapCharacter(font, (int)text[i]);
}

void glEnter2D(void) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(300, 0, 500, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
}

void glLeave2D(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (game) {
		glEnter2D();
		glColor3f(1, 0, 0);
		glWrite(35, 50, (int*)GLUT_BITMAP_8_BY_13, to_string(score_int)); // ������� ����
		glLeave2D();
		glColor3f(0, 1, 0);  //���� �����
		glLineWidth(5.0f);
		// ������� ����
		field->draw();
		//������
		glColor3f(0, 0, 0);
		snake->draw();
		//������
		glColor3f(1, 0, 0);
		apple->draw();
	}
	else {
		glEnter2D();
		glColor3f(1, 0, 0);
		glWrite(200, 250, (int*)GLUT_BITMAP_TIMES_ROMAN_24, "GAMEOVER!");
		glWrite(200, 250 + 24, (int*)GLUT_BITMAP_TIMES_ROMAN_24, "SCORE: " + to_string(score_int));
		glLeave2D();
	}
	glFlush();
	glutSwapBuffers();
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void timer(int = 0) { // ��� ����
	display();
	glutTimerFunc(100, timer, 0);
}

void tick(int = 0) {
	snake->updatePosition(x, y);
	if (!snake->checkConstraints(field)) {
		game = false;
	}
	else {
		snake->eatApple(apple);
		score_int = snake->getTextedSize_int();
		snake->update();
	}
	if (game)glutTimerFunc(200, tick, 1);
}

void keyHandler(int key, int xr, int yr) {
	switch (key) {
	case GLUT_KEY_UP:
		y = delta;
		x = 0;
		break;
	case GLUT_KEY_DOWN:
		y = -delta;
		x = 0;
		break;
	case GLUT_KEY_LEFT:
		x = -delta;
		y = 0;
		break;
	case GLUT_KEY_RIGHT:
		x = delta;
		y = 0;
		break;
	}
}

//**********************************************************
// ����� ����� ����������
void main(int argc, char* argv[]) {
	srand(time(NULL));
	snake->push_back(new Cell(0, 0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Snake");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(ChangeSize);
	timer();
	tick();
	glutSpecialFunc(keyHandler);
	SetupRC();
	glutMainLoop();
}


//**********************************************************
// ��������� ��������� ���������� (������������)
void SetupRC(void)
{
	// ������������� ���� ������� 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

//**********************************************************
// ���������� ����������� GLUT ��� ��������� �������� ����
// ����������.
void ChangeSize(int width, int height)
{
	GLfloat aspectRatio;
	// ������������� ������� �� ����
	if (height == 0)
		height = 1;
	// ������������� ���� ��������� � ��������� ����
	glViewport(0, 0, width, height);
	// ������������� ������� �������������� � ����� �������������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ������������� ������� ����������� (����������� ������)
	// (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)width / (GLfloat)height;
	if (width <= height) {
		windowWidth = 10;
		windowHeight = 10 / aspectRatio;
		glOrtho(left_x, right_x,
			-windowHeight, windowHeight, 1.0, -1.0);
	}
	else {
		windowWidth = 10 * aspectRatio;
		windowHeight = 10;
		glOrtho(-windowWidth, windowWidth,
			bottom_y, top_y, 1.0, -1.0);
	}
	// ��������������� ������� �������������� � �������� ����� ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}