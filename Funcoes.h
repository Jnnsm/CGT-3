#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/glut.h>
#include <vector>
#include "Objeto.h"

/* TODO:
*	Controle de Transpar�ncia;
*	Controle de centro de c�mera (em qual objeto ou na origem);
*	Menu com Scrolling
*	Alterar nome das vari�veis
*/


extern vector<Objeto> objs;
extern double __WIDTH, __HEIGHT;

int menuPos = 0;
int rotatex = 0, rotatey = 0;
double aspect_ratio = __WIDTH / __HEIGHT;
GLdouble viewer[] = { 3.0, 3.0, 6.0 };


/* Define os comandos do teclado				 */
/* i - k = comandos que movem o "menu"			 */
/* w - a - s - d = comandos que movem os objetos */

void keyboard(unsigned char key, int x, int y) {	
	switch (key) {
		case 'i':
			menuPos--;
			break;
		case 'k':
			menuPos++;
			break;
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
/* Desenha cada objeto na tela */
void showObjects() {
	for (vector<Objeto>::iterator o = objs.begin(); o != objs.end(); o++){

		glPushMatrix();

		glRotatef(rotatex, 0, 1, 0);
		glRotatef(rotatey, 1, 0, 0);

		glColor4f((*o).cor.primeiro, (*o).cor.segundo, (*o).cor.terceiro, (*o).alpha);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < (*o).f.size(); i++) {
			/* Pegamos da face i os 3 vertices que a compoe, dai, desses 3 vertices pegamos 3 coordenadas para representa-los no espa�o */
			glVertex3f(
				(*o).v.at((*o).f.at(i).primeiro.primeiro - 1).primeiro,
				(*o).v.at((*o).f.at(i).primeiro.primeiro - 1).segundo,
				(*o).v.at((*o).f.at(i).primeiro.primeiro - 1).terceiro
			);

			glVertex3f(
				(*o).v.at((*o).f.at(i).segundo.primeiro - 1).primeiro,
				(*o).v.at((*o).f.at(i).segundo.primeiro - 1).segundo,
				(*o).v.at((*o).f.at(i).segundo.primeiro - 1).terceiro
			);

			glVertex3f(
				(*o).v.at((*o).f.at(i).terceiro.primeiro - 1).primeiro,
				(*o).v.at((*o).f.at(i).terceiro.primeiro - 1).segundo,
				(*o).v.at((*o).f.at(i).terceiro.primeiro - 1).terceiro
			);
		}
		glEnd();
		glPopMatrix();
	}
}

/* Limpa a tela */
void resetView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

}

/* Define os modos de proje��o e modelview a serem seguidos na parte da tela referente a exibi��o dos objetos */
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

/* Define os modos de proje��o e modelview a serem seguidos na parte da tela referente a exibi��o do menu */
void menuProjection() {
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	glOrtho(0, 100, 0, 200, -2, 2);

	/* Temos uma viewport de tamanho 1/4 da tela que vai da posi��o x = 3/4 (do tamanho total) at� o final*/
	glViewport(__WIDTH - __WIDTH / 4, 0, __WIDTH / 4, __HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Chama o necess�rio para mostrar os objetos */
void displayObjects() {

	objectsProjection();
	showBaseScreen();
	showObjects();
}


/* Chama o necess�rio para construir o menu*/
void displayMenu() {

	/* Desativado teste pra checar o que est� na frente */
	glDisable(GL_DEPTH_TEST);
	
	/* Fazemos a proje��o do menu */
	menuProjection();

	/* Desenhamos o background */
	glColor4f(0.88, 0.88, 0.88, 0.60);
	glRectd(0.0, 0, 100.0, 200.0);

	/* Damos um push na matrix para n�o precisarmos redefinir o lookAt novamente para posi��o original */
	glPushMatrix();

		gluLookAt(
			0, menuPos, 1,
			0.0, menuPos, 0.0,
			0.0, 1.0, 0.0);

		/* Desenha cada quadrado para exemplo da caixa de cada objeto */
		glColor4f(0.5, 0, 0, 0.7);
		for (int i = 0; i < 3; i++) {
			glRectd(10, 200.0 - ((i + 1) * 35 - 5), 90, 200.0 - ((i) * 35));
		}

	glPopMatrix();

	
	glEnable(GL_DEPTH_TEST);
}

/* Chama as fun��es necess�rias para apagar a tela e desenhar os objetos e o menu. Al�m disso � a controladora do swapBuffer */
void display() {

	resetView();
	displayObjects();
	displayMenu();

	glutSwapBuffers();
}

/* Sempre mant�m a tela com um aspect definido para n�o distorcer o desenho */
void reshape(int w, int h){
	if (h == 0)
		h = 1;

	__WIDTH = w;
	__HEIGHT = h;

	aspect_ratio = 1.0f * (w) / h;
}

/* Inicializa uma tela vazia apenas com os eixos */
void initialize() {
	glClearColor(0, 0, 0, 1);
	
	resetView();
	objectsProjection();
	showBaseScreen();

	glutSwapBuffers();
}

/* Fun��o para carregar objeto */
void createObj(string fileName, Trio<double> color) {
	Objeto dr;
	
	dr.initialize(fileName, color);

	objs.push_back(dr);
}

#endif