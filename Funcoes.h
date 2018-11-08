#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/glut.h>
#include <vector>
#include "Objeto.h"

extern Objeto dr;

extern int rotatex, rotatey;

GLdouble viewer[] = { 3, 3, 6 };

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

	// xyz
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(15, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 15, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 0, 15);
	glEnd();

	glRotatef(rotatex, 0, 1, 0);
	glRotatef(rotatey, 1, 0, 0);
	
	//Desenha a figura
	glColor3f(1,1,1);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < dr.f.size(); i++) {
			// Pegamos da face i os 3 vertices que a compoe, dai, desses 3 vertices pegamos 3 coordenadas para representa-los no espaço
			glVertex3f(
				dr.v.at( dr.f.at(i).primeiro.primeiro - 1 ).primeiro,
				dr.v.at( dr.f.at(i).primeiro.primeiro - 1 ).segundo,
				dr.v.at( dr.f.at(i).primeiro.primeiro - 1 ).terceiro
			);
			
			glVertex3f(
				dr.v.at( dr.f.at(i).segundo.primeiro - 1 ).primeiro,
				dr.v.at( dr.f.at(i).segundo.primeiro - 1 ).segundo,
				dr.v.at( dr.f.at(i).segundo.primeiro - 1 ).terceiro
			);
			
			glVertex3f(
				dr.v.at( dr.f.at(i).terceiro.primeiro - 1 ).primeiro,
				dr.v.at( dr.f.at(i).terceiro.primeiro - 1 ).segundo,
				dr.v.at( dr.f.at(i).terceiro.primeiro - 1 ).terceiro
			);
	
		
	}
	glEnd();

	glFlush();
}

void timer(int) {
	glutPostRedisplay();

	glutTimerFunc(1000 / 60, timer, 0);
}

void initialize() {
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110, 1, 1, 50);
	glMatrixMode(GL_MODELVIEW);

	//glutTimerFunc(0, timer, 0);
}
#endif