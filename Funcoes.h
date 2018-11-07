#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/glut.h>
#include <vector>
#include "Objeto.h"

extern Objeto dr;

GLfloat vertices[8][3] = { {-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},
{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0} };

//cor de cada face do cubo
GLfloat colors[6][3] = { {0.0,0.5,0.0} , {1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
{0.0,0.0,1.0} , {1.0,0.0,1.0} };

GLdouble viewer[] = { 3.0, 3.0, 3.0 };

void quad(int a, int b, int c, int d, int ncolor) {
	glColor3fv(colors[ncolor]);
	
	/*glBegin(GL_QUADS);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	*/
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

	//colorcube();

	glColor3f(1,1,1);
	for (int i = 0; i < dr.f.size(); i++) {
	glBegin(GL_TRIANGLES);
		int a, b, c;
		a = dr.f.at(i).primeiro.primeiro - 1;
		b = dr.f.at(i).segundo.primeiro - 1;
		c = dr.f.at(i).terceiro.primeiro - 1;

		glVertex3f(dr.v.at(a).primeiro, dr.v.at(a).segundo, dr.v.at(a).terceiro);
		glVertex3f(dr.v.at(b).primeiro, dr.v.at(b).segundo, dr.v.at(b).terceiro);
		glVertex3f(dr.v.at(c).primeiro, dr.v.at(c).segundo, dr.v.at(c).terceiro);
	
	glEnd();
	}

	glFlush();
}

void initialize() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(144, 1, 2, 20);
	glMatrixMode(GL_MODELVIEW);
}
#endif