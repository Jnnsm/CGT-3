#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/glut.h>
#include <vector>
#include "Objeto.h"

extern Objeto dr;

extern int rotatex, rotatey;

GLdouble viewer[] = { 3.0, 3.0, 3.0 };

void keyboard(unsigned char key, int x, int y) {
	
	switch (key) {
		case 'a':
			rotatex--;
			break;
		case 'd':
			rotatex++;
			break;
		case 's':
			rotatey--;
			break;
		case 'w':
			rotatey++;
			break;
	}
	
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2],
		0.0, 0.0, 0.0,                           
		0.0, 1.0, 0.0);     

	glRotatef(rotatex, 0, 1, 0);
	glRotatef(rotatey, 1, 0, 0);

	glColor3f(0,1,1);
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