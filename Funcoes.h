#ifndef FUNCOES_H__
#define FUNCOES_H__

#include <GL/freeglut.h>
#include <vector>
#include <cmath>

#include "ObjectCreation.h"
#include "SceneLights.h"
#include "ScreenDraw.h"
#include "InputControl.h"
#include "Objeto.h"


extern vector<Objeto> objs;
extern double __WIDTH, __HEIGHT;

/* Armazenam respectivamente a quantidade de poligonos na tela e o tempo para desenha-los */
int poly = 0,
deltaTime = 0,
frameCounter = 0,
averageTime = 0;

double timeCounter = 0;

/* Representa o scroll do menu */
int menuPos = 0;

/* Aspect Rato da tela e posi��o do observador */
double aspectRatio = 1.0f * __WIDTH / __HEIGHT;
GLfloat viewer[] = { 3.0, 3.0, 6.0, 1 };
GLfloat lookPoint[] = { 0.0, 0.0, 0.0 };
GLfloat upVector[] = { 0.0, 1.0, 0.0 };
const GLfloat worldUp[] = { 0.0, 1.0, 0.0 };

/* Modo de exibição do objeto */
GLint viewMode = GL_TRIANGLES;

/* Movimentação do olho do observador */
bool dragX = false, dragY = false;
double posX = 0, posY = 0, posfX = 0, posfY = 0;
double rotateX = 0, rotateY = 0;

/* String digitada na caixa de importa��o do objeto */
string nameBox = "", valueBox = "";

/* Movimento da câmera */
GLdouble yaw=0, pitch=0;

/* Identificadores para saber se o usu�rio est� digitando						*/
/* clickedObj = -1 representa a tela de menu inteira							*/
/* clickedObj >= 0 representa um objeto de "objs"								*/
/* typingField = -1 representa lugar nenhum										*/
/* typingField = 0 representa a caixa de importa��o caso clickedObj = -1		*/
/* typingField = 0 e <= 10 representam caixas do objeto quanto clickedObj != -1 */
short clickedObj = -1, typingField = -1;

bool lightOne = false, lightTwo = false, lightThree = false;

/* Sempre mantem a tela com um aspect definido para n�o distorcer o desenho */
void reshape(int w, int h) {
	if (h == 0)
		h = 1;

	__WIDTH = w;
	__HEIGHT = h;

	aspectRatio = 1.0f * (w) / h;
}

void timer(int) {
	glutPostRedisplay();

	glutTimerFunc(1000.0f / 60, timer, 0);

}

/* Inicializa uma tela vazia apenas com os eixos */
void initialize() {
	
	glClearColor(0, 0, 0, 1);

	/* Faz os desenhos iniciais */
	resetView();
	
	objectsProjection();
	
	showBaseScreen();

	createObj("popotato.obj", Quad<double>(1, 1, 1, 1));
	

	glutSwapBuffers();

	glutTimerFunc(1000.0f / 60, timer, 0);
}

#endif