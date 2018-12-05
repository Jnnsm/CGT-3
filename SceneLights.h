#ifndef LIGHTS_H__
#define LIGHTS_H__
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "Objeto.h"

extern vector<Objeto> objs;
extern double __WIDTH, __HEIGHT;
extern double aspectRatio;

extern double timeCounter;

extern int menuPos;

extern GLfloat viewer[], lookPoint[], upVector[];

extern GLint viewMode;

extern bool dragX, dragY;
extern double posX, posY, posfX, posfY;
extern double rotateX, rotateY;

extern string nameBox, valueBox;

extern short clickedObj, typingField;

extern bool lightOne, lightTwo, lightThree;

void lightsOn() {
	GLfloat white_light[] = { 0.2, 0.2, 0.2, 0 };
	GLfloat red_light[] = { 1.0, 0.0, 0.0, 0.0 };
	GLfloat blue_light[] = { 0.0, 0.0, 1.0, 0.0 };

	GLfloat global_position[] = { 0, 1, 0, 0 };
	GLfloat ceiling_position[] = { 0, 5, 0, 1 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* Luz "sol" */
	if (lightOne) {

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);

		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
		glLightfv(GL_LIGHT0, GL_POSITION, global_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
	}
	/* Luz a partir do observador */
	if (lightTwo) {

		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
		glLightfv(GL_LIGHT1, GL_POSITION, viewer);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
		glLightfv(GL_LIGHT1, GL_POSITION, viewer);
		glLightfv(GL_LIGHT1, GL_SPECULAR, blue_light);
	}
	/* Luz de teto */
	if (lightThree) {
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.009);

		glMaterialf(GL_FRONT, GL_SHININESS, 50);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180);
		glLightfv(GL_LIGHT2, GL_POSITION, ceiling_position);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, red_light);
	}
}

void lightsOff() {
	glDisable(GL_LIGHTING);
}


#endif