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

/* Armazenam respectivamente a quantidade de poligonos na tela e o tempo para desenha-los */
int poly = 0,
	deltaTime = 0;

/* Representa o scroll do menu */
int menuPos = 0;

/* Variável teste para rotação */
int rotatex = 0, rotatey = 0;

/* Aspect Rato da tela e posição do observador */
double aspectRatio = 1.0f * __WIDTH / __HEIGHT;
GLdouble viewer[] = { 3.0, 3.0, 6.0 };

/* String digitada na caixa de importação do objeto */
string nameBox = "";

/* Identificadores para saber se o usuário está digitando						*/
/* clickedObj = -1 representa a tela de menu inteira							*/
/* clickedObj >= 0 representa um objeto de "objs"								*/
/* typingField = -1 representa lugar nenhum										*/
/* typingField = 0 representa a caixa de importação caso clickedObj = -1		*/
/* typingField = 0 e <= 10 representam caixas do objeto quanto clickedObj != -1 */
short clickedObj = -1, typingField = -1;

/* Função para carregar objeto */
void createObj(string fileName, Quad<double> color) {
	Objeto dr;

	try {
		dr.initialize(fileName, color);
		objs.push_back(dr);
	}
	catch (int e) {
		cerr << "File does not exist" << endl;
	}
}

#endif

/* Define os comandos do teclado				 */
/* i - k = comandos que movem o "menu"			 */
/* w - a - s - d = comandos que movem os objetos */

void keyboard(unsigned char key, int x, int y) {
	cout << x << " " << y << endl;
	if (clickedObj == -1 && typingField == 0) {
		if (key == 13) {
			clickedObj = -1;
			typingField = -1;
			Quad<double> aux((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), 0.5);
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
	/* Trata rolagem do mouse */
	if (button == 4)
		menuPos++;
	else if (button == 3)
		menuPos--;
	/* Trata parte do menu da tela */
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (x >= 3 * __WIDTH / 4) {
			double xf, yf;
			xf = (200 * aspectRatio) * (x - 3 * __WIDTH / 4) / __WIDTH;
			yf = (200) * (__HEIGHT - y) / __HEIGHT;

			/* Descobre qual caixa o usuário clicou */
			cout << trunc(((yf - 140 + menuPos) / -40)+0.99) << endl;

			/* Checa se ele está clicando na caixa de importação */
			if (xf >= 20.0f / 3 && yf >= 180 && xf <= 60 && yf <= 188) {
				clickedObj = -1;
				typingField = 0;
			}
			else if (clickedObj >= 0 || typingField >= 0) {
				clickedObj = -1;
				typingField = -1;
			}
		}
	}
	/* Trata a parte dos objetos da tela */
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

			glColor4f((*o).rgba.primeiro, (*o).rgba.segundo, (*o).rgba.terceiro, (*o).rgba.quarto);
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

	/* Damos um push na matrix para não precisarmos redefinir o lookAt novamente para posição original */
	
	glPushMatrix();

		gluLookAt(
			0, menuPos, 1,
			0.0, menuPos, 0.0,
			0.0, 1.0, 0.0
		);

		/* Desenha cada quadrado para exemplo da caixa de cada objeto */
		int pos = 0;
		for (int i = 0; i < objs.size(); i++) {
			pos = i * 40;

			/* Desenha apenas se ele estiver a baixo da barra que importa objetos */
			if (180 - pos - 40 - menuPos <= 180) {
				/* Desenha caixa de fundo com a cor do objeto */
				glColor4f(objs.at(i).rgba.primeiro, objs.at(i).rgba.segundo, objs.at(i).rgba.terceiro, 0.7);
				glRectd(20.0f / 3, 180 - pos - 40, 60, 180 - (pos + 5));

				glColor4f(0, 0, 0, 1);

				/* Desenha o nome do objeto */
				glPushMatrix();

				glTranslated(23.0f / 3, 175 - pos - 5, 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(objs.at(i).name).c_str());

				glPopMatrix();

				/* Desenha as caixas relacionadas com translação e seu label */
				glPushMatrix();

				glTranslated(23.0f / 3, 168 - (pos + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"T: ");

				glPopMatrix();


				glRectd(24, 168 - pos, 34, 168 - (pos + 5));
				glRectd(36, 168 - pos, 46, 168 - (pos + 5));
				glRectd(48, 168 - pos, 58, 168 - (pos + 5));

				/* Desenha as caixas relacionadas com rotação e seu label */
				glPushMatrix();

				glTranslated(23.0f / 3, 161 - (pos + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"R: ");

				glPopMatrix();

				glRectd(12, 161 - (pos), 22, 161 - (pos + 5));
				glRectd(24, 161 - (pos), 34, 161 - (pos + 5));
				glRectd(36, 161 - (pos), 46, 161 - (pos + 5));
				glRectd(48, 161 - (pos), 58, 161 - (pos + 5));

				/* Desenha as caixas relacionadas com escala e seu label */
				glPushMatrix();

				glTranslated(23.0f / 3, 154 - (pos + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"E: ");

				glPopMatrix();

				glRectd(24, 154 - pos, 34, 154 - (pos + 5));
				glRectd(36, 154 - pos, 46, 154 - (pos + 5));
				glRectd(48, 154 - pos, 58, 154 - (pos + 5));

				/* Desenha as caixas relacionadas com transparencia e seu label */
				glPushMatrix();

				glTranslated(23.0f / 3, 147 - (pos + 5), 0);
				glScaled(0.035, 0.035, 0);
				glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Alpha: ");

				glPopMatrix();

				glRectd(48, 147 - pos, 58, 147 - (pos + 5));
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
	glRectd(20.0f/3 , 180, 60, 188);
	
	glPushMatrix();
		glColor4d(0, 1, 0, 1);
		glTranslated(23.0f / 3, 182, 0);
		glScaled(0.035, 0.035, 0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)(nameBox + "_").c_str());
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

