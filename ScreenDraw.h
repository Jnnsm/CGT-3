#ifndef DRAW_H__
#define DRAW_H__

#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "Objeto.h"

extern int poly,
deltaTime,
frameCounter,
averageTime;
/* Limpa a tela */
void resetView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

/* Desenha os eixos XYZ */
void showBaseScreen() {
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

/* Mostra um muro transparente */
void displayWall() {
	glColor4f(1, 1, 1, 0.5);

	glBegin(viewMode);
	glVertex3f(5, 5, 5);
	glVertex3f(5, -5, 5);
	glVertex3f(-5, -5, 5);
	glEnd();
}
/* Desenha cada objeto na tela */
void showObjects() {

	glEnable(GL_BLEND);

	poly = 0;

	for (vector<Objeto>::iterator o = objs.begin(); o != objs.end(); o++) {
		
		if ((*o).visible) {
			glBindTexture(GL_TEXTURE_2D, (*o).t);
			glEnable(GL_TEXTURE_2D);
			if ((*o).width > 0 && (*o).height > 0 && (*o).img != NULL) {
				
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}

			poly += (*o).f.size();
			glPushMatrix();
			glScalef((*o).scale.data[0], (*o).scale.data[1], (*o).scale.data[2]);
			glTranslatef((*o).translate.data[0], (*o).translate.data[1], (*o).translate.data[2]);
			glRotatef((*o).rotate.data[0], (*o).rotate.data[1], (*o).rotate.data[2], (*o).rotate.data[3]);

			glColor4f((*o).rgba.data[0], (*o).rgba.data[1], (*o).rgba.data[2], (*o).rgba.data[3]);


			for (int i = 0; i < (*o).f.size(); i++) {
				/* Pegamos da face i os 3 vertices que a compoe, dai, desses 3 vertices pegamos 3 coordenadas para representa-los no espa�o */
		
				glBegin(viewMode);

				if ((*o).vn.size() > 0)
					glNormal3f(
						(*o).vn.at((*o).f.at(i).data[0].data[2] - 1).data[0],
						(*o).vn.at((*o).f.at(i).data[0].data[2] - 1).data[1],
						(*o).vn.at((*o).f.at(i).data[0].data[2] - 1).data[2]
					);
				if ((*o).vt.size() > 0) {
					glTexCoord2d(
						(*o).vt.at((*o).f.at(i).data[0].data[1] - 1).data[0],
						1 - (*o).vt.at((*o).f.at(i).data[0].data[1] - 1).data[1]
					);
				}
				glVertex3f(
					(*o).v.at((*o).f.at(i).data[0].data[0] - 1).data[0],
					(*o).v.at((*o).f.at(i).data[0].data[0] - 1).data[1],
					(*o).v.at((*o).f.at(i).data[0].data[0] - 1).data[2]
				);


				if ((*o).vn.size() > 0)
					glNormal3f(
					(*o).vn.at((*o).f.at(i).data[1].data[2] - 1).data[0],
						(*o).vn.at((*o).f.at(i).data[1].data[2] - 1).data[1],
						(*o).vn.at((*o).f.at(i).data[1].data[2] - 1).data[2]
					);
				if ((*o).vt.size() > 0) {
					glTexCoord2d(
						(*o).vt.at((*o).f.at(i).data[1].data[1] - 1).data[0],
						1 - (*o).vt.at((*o).f.at(i).data[1].data[1] - 1).data[1]
					);
				}
				glVertex3f(
					(*o).v.at((*o).f.at(i).data[1].data[0] - 1).data[0],
					(*o).v.at((*o).f.at(i).data[1].data[0] - 1).data[1],
					(*o).v.at((*o).f.at(i).data[1].data[0] - 1).data[2]
				);


				if ((*o).vn.size() > 0)
					glNormal3f(
					(*o).vn.at((*o).f.at(i).data[2].data[2] - 1).data[0],
						(*o).vn.at((*o).f.at(i).data[2].data[2] - 1).data[1],
						(*o).vn.at((*o).f.at(i).data[2].data[2] - 1).data[2]
					);
				if ((*o).vt.size() > 0) {
					glTexCoord2d(
						(*o).vt.at((*o).f.at(i).data[2].data[1] - 1).data[0],
						1 - (*o).vt.at((*o).f.at(i).data[2].data[1] - 1).data[1]
					);
				}
				glVertex3f(
					(*o).v.at((*o).f.at(i).data[2].data[0] - 1).data[0],
					(*o).v.at((*o).f.at(i).data[2].data[0] - 1).data[1],
					(*o).v.at((*o).f.at(i).data[2].data[0] - 1).data[2]
				);
				glEnd();
			}
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
	}
}


/* Define os modos de projecao e modelview a serem seguidos na parte da tela referente a exibi��o dos objetos */
void objectsProjection() {
	//Prepara tela do desenho
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110, aspectRatio, 1, 200);
	glViewport(0, 0, __WIDTH, __HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		viewer[0], viewer[1], viewer[2],
		lookPoint[0], lookPoint[1], lookPoint[2],
		upVector[0], upVector[1], upVector[2]
	);
}

/* Define os modos de proje��o e modelview a serem seguidos na parte da tela referente a exibi��o do menu */
void menuProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 200 * aspectRatio / 4, 0, 200, -2, 2);

	/* Temos uma viewport de tamanho 1/4 da tela que vai da posi��o x = 3/4 (do tamanho total) at� o final*/
	glViewport(__WIDTH - __WIDTH / 4, 0, __WIDTH / 4, __HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/* Chama o necess�rio para mostrar os objetos */
void displayObjects() {

	objectsProjection();
	/* Rotaciona a "camera" */
	glTranslated(viewer[0], viewer[1], viewer[2]);
	glRotated(rotateX, 1, 0, 0);
	glRotated(rotateY, 0, 1, 0);
	glTranslated(-viewer[0], -viewer[1], -viewer[2]);

	/* Mostra os eixos e os objetos */
	showBaseScreen();

	if (lightOne || lightTwo || lightThree)
		lightsOn();

	showObjects();
	displayWall();
}


/* Fun��o feita para desenhar algo do tipo: "Label: *" onde * s�o n caixas*/
void drawBoxAndLabel(double startX, double endX, double startY, double endY, string label, int quantity) {
	glColor4f(0, 0, 0, 1);
	glPushMatrix();

	glTranslated(startX, startY, 0);
	glScaled(0.035, 0.035, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)label.c_str());

	glPopMatrix();

	for (int i = endX - 2; i >= 0 && quantity > 0; i -= 12, quantity--) {
		glRectd(i - 10, startY, i, endY);
	}
}

/* Chama o necess�rio para construir o menu*/
void displayMenu() {

	/* Desativado teste pra checar o que est� na frente */
	glDisable(GL_DEPTH_TEST);

	/* Fazemos a proje��o do menu */
	menuProjection();

	/* Desenhamos o background */
	glColor4f(0.88, 0.88, 0.88, 0.60);
	glRectd(0.0, 0.0, 200 * aspectRatio / 4, 200.0);

	/* Damos um push na matrix para n�o precisarmos redefinir o lookAt novamente para posi��o original */

	glPushMatrix();

	gluLookAt(
		0, menuPos, 1,
		0.0, menuPos, 0.0,
		0.0, 1.0, 0.0
	);

	/* Desenha cada quadrado para caixa de objetos */
	int pos = 0;
	for (int i = 0; i < objs.size(); i++) {
		pos = i * 40;

		/* Desenha apenas se ele estiver a baixo da barra que importa objetos */
		if (173 - pos - 5 - menuPos <= 173) {
			/* Desenha caixa de fundo com a cor do objeto */

			if (clickedObj != i)
				glColor4f(objs.at(i).rgba.data[0], objs.at(i).rgba.data[1], objs.at(i).rgba.data[2], 0.4);
			else {
				glColor4f(objs.at(i).rgba.data[0], objs.at(i).rgba.data[1], objs.at(i).rgba.data[2], 1);
			}
			glRectd(20.0f / 3, 173 - pos - 40, 60, 173 - (pos + 5));

			glColor4f(0, 0, 0, 1);

			/* Desenha o nome do objeto */
			glPushMatrix();

			glTranslated(23.0f / 3, 168 - pos - 5, 0);
			glScaled(0.035, 0.035, 0);
			glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(objs.at(i).name).c_str());

			glPopMatrix();

			/* Desenha a caixa que informa se o objeto está visível */
			if (objs.at(i).visible)
				glColor3f(1, 0, 0);
			else {
				glColor3f(1, 1, 1);
			}
			glRectd(53, 168 - pos - 6, 58, 168 - pos - 1);

			/* Desenha as caixas relacionadas com translacaoo e seu label */

			drawBoxAndLabel(23.0f / 3, 60, 161 - (pos + 5), 161 - pos, "T: ", 3);

			/* Escreve o valor nas caixas */
			stringstream ss;

			glColor4d(1, 1, 1, 1);
			for (int j = 0; j < 3; j++) {
				ss.str("");
				ss << objs.at(i).translate.data[j];
				glPushMatrix();

				glTranslated(60 - 12 * (2 - j) - 12 + 0.7, 161 - pos - 5 + 0.5, 0);
				glScaled(0.035, 0.035, 0);
				if (clickedObj == i && typingField == j)
					glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)valueBox.c_str());
				else
					glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)ss.str().c_str());

				glPopMatrix();
			}

			glColor4d(0, 0, 0, 1);

			/* Desenha as caixas relacionadas com rota��o e seu label */

			drawBoxAndLabel(23.0f / 3, 60, 154 - (pos + 5), 154 - pos, "R: ", 4);

			/* Escreve o valor nas caixas */

			glColor4d(1, 1, 1, 1);
			for (int j = 0; j < 4; j++) {
				ss.str("");
				ss << objs.at(i).rotate.data[j];
				glPushMatrix();

				glTranslated(60 - 12 * (3 - j) - 12 + 0.7, 154 - pos - 5 + 0.5, 0);
				glScaled(0.035, 0.035, 0);
				if (clickedObj == i && typingField - 3 == j)
					glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)valueBox.c_str());
				else
					glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)ss.str().c_str());

				glPopMatrix();
			}

			glColor4d(0, 0, 0, 1);

			/* Desenha as caixas relacionadas com escala e seu label */
			drawBoxAndLabel(23.0f / 3, 60, 147 - (pos + 5), 147 - pos, "E: ", 3);

			/* Escreve o valor nas caixas */

			glColor4d(1, 1, 1, 1);
			for (int j = 0; j < 3; j++) {
				ss.str("");
				ss << objs.at(i).scale.data[j];
				glPushMatrix();

				glTranslated(60 - 12 * (2 - j) - 12 + 0.7, 147 - pos - 5 + 0.5, 0);
				glScaled(0.035, 0.035, 0);

				if (clickedObj == i && typingField - 7 == j)
					glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)valueBox.c_str());
				else
					glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)ss.str().c_str());

				glPopMatrix();
			}

			glColor4d(0, 0, 0, 1);

			/* Desenha as caixas relacionadas com transparencia e seu label */

			drawBoxAndLabel(23.0f / 3, 60, 140 - (pos + 5), 140 - pos, "Alpha: ", 1);

			/* Escreve o valor nas caixas */

			glColor4d(1, 1, 1, 1);
			ss.str("");
			ss << objs.at(i).rgba.data[3];
			glPushMatrix();

			glTranslated(60 - 12 + 0.7, 140 - pos - 5 + 0.5, 0);
			glScaled(0.035, 0.035, 0);
			if (clickedObj == i && typingField == 10)
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)valueBox.c_str());
			else
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)ss.str().c_str());

			glPopMatrix();

			glColor4d(0, 0, 0, 1);
		}
	}

	glPopMatrix();

	/* Caixa para digitar arquivo */
	glPushMatrix();
	glColor4d(0, 0, 0, 1);
	glTranslated(20.0f / 3, 190, 0);
	glScaled(0.035, 0.035, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Nome do arquivo: ");
	glPopMatrix();

	glColor4d(0, 0, 0, 0.8);
	glRectd(20.0f / 3, 180, 60, 188);

	glPushMatrix();
	glColor4d(0, 1, 0, 1);
	glTranslated(23.0f / 3, 182, 0);
	glScaled(0.035, 0.035, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(nameBox + "_").c_str());
	glPopMatrix();

	/* Caixa para carregar o arquivo */

	glColor4d(0, 0, 0, 0.8);
	glRectd(20, 173, 60, 179);

	glPushMatrix();
	glColor4d(0, 1, 0, 1);
	glTranslated(31, 174.5, 0);
	glScaled(0.035, 0.035, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Carregar");
	glPopMatrix();



	/* Escreve a quantidade de tempo para desenhar e a quantidade de poly na parte de baixo da tela */
	glPushMatrix();

	glColor4d(0, 0, 0, 1);
	glTranslated(20.0f / 3, 1, 0);
	glScaled(0.035, 0.035, 0);

	stringstream ss;
	ss << averageTime;
	string time = ss.str() + " ms ";

	ss.str("");
	ss << poly;
	time += ss.str() + " poly";

	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)time.c_str());


	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

/* Chama as fun��es necess�rias para apagar a tela e desenhar os objetos e o menu. Al�m disso � a controladora do swapBuffer */
void display() {

	if (timeCounter == 0) {
		timeCounter = glutGet(GLUT_ELAPSED_TIME) / 1000;
	}
	if (glutGet(GLUT_ELAPSED_TIME) / 1000 - timeCounter >= 1) {
		averageTime = deltaTime / frameCounter;
		deltaTime = frameCounter = 0;
		timeCounter = glutGet(GLUT_ELAPSED_TIME) / 1000;
	}

	int timeStart = glutGet(GLUT_ELAPSED_TIME);

	/* Desenha objetos */
	resetView();

	displayObjects();

	lightsOff();
	displayMenu();

	deltaTime += glutGet(GLUT_ELAPSED_TIME) - timeStart;
	frameCounter++;

	glutSwapBuffers();
}

#endif