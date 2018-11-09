#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/glut.h>
#include <vector>
#include "Objeto.h"

/* TODO:
*	Controle de Transparência;
*	Controle de centro de câmera (em qual objeto ou na origem);
*/


extern vector<Objeto> objs;
extern double __WIDTH, __HEIGHT;


int rotatex = 0, rotatey = 0;
double aspect_ratio = __WIDTH / __HEIGHT;
GLdouble viewer[] = { 3.0, 3.0, 6.0 };

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

void showBaseScreen() {
	// xyz
	glColor4f(1, 0, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(15, 0, 0);
	glEnd();

	glColor4f(0, 1, 0, 1);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 15, 0);
	glEnd();

	glColor4f(0, 0, 1, 1);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 0, 15);
	glEnd();

}

void showObjects() {

	//Desenha a figura
	glColor4f(1, 0, 0, 0.5);
	Objeto oObj;
	for (vector<Objeto>::iterator o = objs.begin(); o != objs.end(); o++){
		oObj = *o;

		glPushMatrix();

		glRotatef(rotatex, 0, 1, 0);
		glRotatef(rotatey, 1, 0, 0);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < oObj.f.size(); i++) {

			// Pegamos da face i os 3 vertices que a compoe, dai, desses 3 vertices pegamos 3 coordenadas para representa-los no espaço
			glVertex3f(
				oObj.v.at(oObj.f.at(i).primeiro.primeiro - 1).primeiro,
				oObj.v.at(oObj.f.at(i).primeiro.primeiro - 1).segundo,
				oObj.v.at(oObj.f.at(i).primeiro.primeiro - 1).terceiro
			);

			glVertex3f(
				oObj.v.at(oObj.f.at(i).segundo.primeiro - 1).primeiro,
				oObj.v.at(oObj.f.at(i).segundo.primeiro - 1).segundo,
				oObj.v.at(oObj.f.at(i).segundo.primeiro - 1).terceiro
			);

			glVertex3f(
				oObj.v.at(oObj.f.at(i).terceiro.primeiro - 1).primeiro,
				oObj.v.at(oObj.f.at(i).terceiro.primeiro - 1).segundo,
				oObj.v.at(oObj.f.at(i).terceiro.primeiro - 1).terceiro
			);
		}
		glEnd();
		glPopMatrix();
	}
}

void resetView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void objectsProjection() {
	//Prepara tela do desenho
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110, aspect_ratio, 1, 200);
	glViewport(0, 0, __WIDTH, __HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		viewer[0], viewer[1], viewer[2],
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

void menuProjection() {
	//Prepara tela do menu
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100*aspect_ratio);

	glViewport(__WIDTH - __WIDTH / 4, 0, __WIDTH / 4, __HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void displayObjects() {
	//Mostra a tela do desenho
	objectsProjection();
	
	showBaseScreen();
	showObjects();
}



void displayMenu() {
	// Menu
	menuProjection();

	glColor4f(0.88, 0.88, 0.88, 0.60);
	glRectd(0, 0, 100, 200);
}

void display() {

	resetView();
	displayObjects();
	displayMenu();

	glutSwapBuffers();
}

void reshape(int w, int h){
	if (h == 0)
		h = 1;

	__WIDTH = w;
	__HEIGHT = h;

	aspect_ratio = 1.0f * (w) / h;
}


void initialize() {
	glClearColor(0, 0, 0, 1);
	
	resetView();
	objectsProjection();
	showBaseScreen();

	glutSwapBuffers();
}
#endif