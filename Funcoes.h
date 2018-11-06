#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/glut.h>

GLfloat vertices[8][3] = { {-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},
{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0} };

//cor de cada face do cubo
GLfloat colors[6][3] = { {0.0,0.5,0.0} , {1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
{0.0,0.0,1.0} , {1.0,0.0,1.0} };

GLdouble viewer[] = { 3.0, 3.0, 3.0 };

void quad(int a, int b, int c, int d, int ncolor) {
	glColor3fv(colors[ncolor]);
	glBegin(GL_QUADS);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube() {
	quad(0, 3, 2, 1, 0);
	quad(2, 3, 7, 6, 1);
	quad(0, 4, 7, 3, 2);
	quad(1, 2, 6, 5, 3);
	quad(4, 5, 6, 7, 4);
	quad(0, 1, 5, 4, 5);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2],
		0.0, 0.0, 0.0,                           
		0.0, 1.0, 0.0);                         

	colorcube();

	glFlush();
}

void initialize() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(70, 1, 2, 20);
	glMatrixMode(GL_MODELVIEW);
}
#endif