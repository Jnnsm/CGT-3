#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/freeglut.h>
#include <vector>
#include "Objeto.h"

/* TODO:
*	Controle de Transparência;
*	Controle de centro de câmera (em qual objeto ou na origem);
*	Menu com Scrolling
*	Alterar nome das variáveis
*/


extern vector<Objeto> objs;
extern double __WIDTH, __HEIGHT;

int poly = 0,
	deltaTime = 0;

int menuPos = 0;
int rotatex = 0, rotatey = 0;

double aspectRatio = 1.0f * __WIDTH / __HEIGHT;
GLdouble viewer[] = { 3.0, 3.0, 6.0 };

string nameBox = "";

bool typing = false;

/* Função para carregar objeto */
void createObj(string fileName, Trio<double> color) {
	Objeto dr;

	dr.initialize(fileName, color);

	objs.push_back(dr);
}

#endif

/* Define os comandos do teclado				 */
/* i - k = comandos que movem o "menu"			 */
/* w - a - s - d = comandos que movem os objetos */

void keyboard(unsigned char key, int x, int y) {	
	if (typing) {
		if (key == 13) {
			typing = false;
			Trio<double> aux((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX));
			createObj(nameBox, aux);
			nameBox = "";
			return;
		}
		else if (key == 8) {
			if(nameBox.size() > 0)
				nameBox.pop_back();
		}
		else
			nameBox += key;
	}
	else {
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
	}
	
	glutPostRedisplay();
}

/* Defne os cliques do mouse */
void mouse(int button, int state, int x, int y) {
	if (x >= 3 * __WIDTH / 4) {
		
		if (button == GLUT_LEFT_BUTTON) {
			
			if (state == GLUT_DOWN) {
				double xf, yf;
				xf = (200 * aspectRatio) * (x - 3 * __WIDTH / 4) / __WIDTH;
				yf = (200) * (__HEIGHT - y) / __HEIGHT;

				/* Checa se ele está clicando na caixa de importação */
				if (xf >= 20.0f / 3 && yf >= 180 && xf <= 60 && yf <= 188) {
					typing = true;
				}
				else if (typing){
					typing = false;
				}

			}
		}
	}
	else {

	}

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
	poly = 0;
	int timeStart = glutGet(GLUT_ELAPSED_TIME);
	for (vector<Objeto>::iterator o = objs.begin(); o != objs.end(); o++){


		poly += (*o).f.size();
		glPushMatrix();

			glRotatef(rotatex, 0, 1, 0);
			glRotatef(rotatey, 1, 0, 0);

			glColor4f((*o).cor.primeiro, (*o).cor.segundo, (*o).cor.terceiro, (*o).alpha);
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < (*o).f.size(); i++) {
				/* Pegamos da face i os 3 vertices que a compoe, dai, desses 3 vertices pegamos 3 coordenadas para representa-los no espaço */
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
	deltaTime = glutGet(GLUT_ELAPSED_TIME) - timeStart;
}

/* Limpa a tela */
void resetView() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

}

/* Define os modos de projeção e modelview a serem seguidos na parte da tela referente a exibição dos objetos */
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
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
}

/* Define os modos de projeção e modelview a serem seguidos na parte da tela referente a exibição do menu */
void menuProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 200 * aspectRatio / 4, 0, 200, -2, 2);

	/* Temos uma viewport de tamanho 1/4 da tela que vai da posição x = 3/4 (do tamanho total) até o final*/
	glViewport(__WIDTH - __WIDTH / 4, 0, __WIDTH / 4, __HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Chama o necessário para mostrar os objetos */
void displayObjects() {

	objectsProjection();
	showBaseScreen();
	showObjects();
}


/* Chama o necessário para construir o menu*/
void displayMenu() {
	
	/* Desativado teste pra checar o que está na frente */
	glDisable(GL_DEPTH_TEST);
	
	/* Fazemos a projeção do menu */
	menuProjection();

	/* Desenhamos o background */
	glColor4f(0.88, 0.88, 0.88, 0.60);
	glRectd(0.0, 0.0, 200 * aspectRatio / 4, 200.0);

	/* Caixa para digitar arquivo */
	glPushMatrix();
		glColor4d(0, 0, 0, 1);
		glTranslated(20.0f / 3, 190, 0);
		glScaled(0.035, 0.035, 0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Nome do arquivo: ");
	glPopMatrix();

	glColor4d(0, 0, 0, 0.8);
	glRectd(20.0f/3 , 180, 60, 188);
	
	glPushMatrix();
		glColor4d(0, 1, 0, 1);
		glTranslated(23.0f / 3, 182, 0);
		glScaled(0.035, 0.035, 0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(nameBox + "_").c_str());
	glPopMatrix();


	/* Damos um push na matrix para não precisarmos redefinir o lookAt novamente para posição original */
	
	glPushMatrix();

		gluLookAt(
			0, menuPos, 1,
			0.0, menuPos, 0.0,
			0.0, 1.0, 0.0
		);

		/* Desenha cada quadrado para exemplo da caixa de cada objeto */
		for (int i = 0; i < objs.size(); i++) {
			glColor4f(objs.at(i).cor.primeiro, objs.at(i).cor.segundo, objs.at(i).cor.terceiro, 0.7);
			glRectd(20.0f/3, 180 - ((i + 1) * 35), 60, 180 - ((i) * 35 + 5));

			glColor4f(0, 0, 0, 1);

			glPushMatrix();

				glTranslated(23.0f / 3, 175 - ((i) * 35 + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(objs.at(i).name).c_str());

			glPopMatrix();

			glPushMatrix();

				glTranslated(23.0f / 3, 168 - ((i) * 35 + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"T: ");

			glPopMatrix();

			
			glRectd(24, 168 - ((i) * 35) ,34, 168 - ((i) * 35 + 5));
			glRectd(36, 168 - ((i) * 35) ,46, 168 - ((i) * 35 + 5));
			glRectd(48, 168 - ((i) * 35) ,58, 168 - ((i) * 35 + 5));

			glPushMatrix();

				glTranslated(23.0f / 3, 161 - ((i) * 35 + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"R: ");

			glPopMatrix();

			glRectd(12, 161 - ((i) * 35), 22, 161 - ((i) * 35 + 5));
			glRectd(24, 161 - ((i) * 35), 34, 161 - ((i) * 35 + 5));
			glRectd(36, 161 - ((i) * 35), 46, 161 - ((i) * 35 + 5));
			glRectd(48, 161 - ((i) * 35), 58, 161 - ((i) * 35 + 5));

			glPushMatrix();

				glTranslated(23.0f / 3, 154 - ((i) * 35 + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"E: ");

			glPopMatrix();

			glRectd(24, 154 - ((i) * 35), 34, 154 - ((i) * 35 + 5));
			glRectd(36, 154 - ((i) * 35), 46, 154 - ((i) * 35 + 5));
			glRectd(48, 154 - ((i) * 35), 58, 154 - ((i) * 35 + 5));

		}

	glPopMatrix();

	/* Escreve a quantidade de tempo para desenhar e a quantidade de poly na parte de baixo da tela */
	glPushMatrix();

		glColor4d(0, 0, 0, 1);
		glTranslated(20.0f/3, 1, 0);
		glScaled(0.035, 0.035, 0);

		stringstream ss;
		ss << deltaTime;
		string time = ss.str() + " ms ";
	
		ss.str("");
		ss << poly;
		time += ss.str() + " poly";

		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)time.c_str());


	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
}

/* Chama as funções necessárias para apagar a tela e desenhar os objetos e o menu. Além disso é a controladora do swapBuffer */
void display() {
	resetView();
	displayObjects();
	displayMenu();

	glutSwapBuffers();
}

/* Sempre mantêm a tela com um aspect definido para não distorcer o desenho */
void reshape(int w, int h){
	if (h == 0)
		h = 1;

	__WIDTH = w;
	__HEIGHT = h;

	aspectRatio = 1.0f * (w) / h;
}

void timer(int) {
	glutPostRedisplay();

	glutTimerFunc(1000.0f/ 60, timer, 0);
}

/* Inicializa uma tela vazia apenas com os eixos */
void initialize() {
	glClearColor(0, 0, 0, 1);
	
	resetView();
	objectsProjection();
	showBaseScreen();

	glutSwapBuffers();

	glutTimerFunc(1000.0f/60, timer, 0);
}

