#ifndef INPUT_H__
#define INPUT_H__
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "Funcoes.h"
#include "Objeto.h"

extern vector<Objeto> objs;
extern double __WIDTH, __HEIGHT;
extern double aspectRatio;

extern int menuPos;

extern GLfloat viewer[], lookPoint[], upVector[];
extern const GLfloat worldUp[];

extern GLint viewMode;

extern bool dragX, dragY;

extern double initialX, initialY, previousX, previousY;
extern GLdouble yaw, pitch;

extern string nameBox, valueBox;

extern short clickedObj, typingField;

void VectorialProd(const GLfloat* v1, const GLfloat* v2, GLfloat* u){
	u[0] = (v1[1] * v2[2]) - (v2[1] * v1[2]);
	u[1] = -((v1[0] * v2[2]) - (v2[0] * v1[2]));
	u[2] = (v1[0] * v2[1]) - (v2[0] * v1[1]);
}

GLdouble VecNorm(const GLfloat* v1){
	return sqrt(pow(v1[0], 2) + pow(v1[1], 2) + pow(v1[2], 2));
}

/* Define os comandos do teclado					 */
/* i - k = comandos que movem o "menu"				 */
/* w - a - s - d = comandos que movem os objetos	 */
/* 1 - 2 - 3 = acende as luzes da cena               */
/* x - y = ativa o movimento da camera em certo eixo */
/* v = muda o view mode                              */

void keyboard(unsigned char key, int x, int y) {
	/* Quer digitar o nome de um novo objeto */
	if (clickedObj == -1 && typingField == 0) {
		/* Apertou enter para inserir o objeto */
		if (key == 13) {
			clickedObj = -1;
			typingField = -1;
			Quad<double> aux((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), 0.5);
			createObj(nameBox, aux);
			nameBox = "";
			return;
		}
		/* Apertou backspace */
		else if (key == 8) {
			if (nameBox.size() > 0)
				nameBox.pop_back();
		}
		else
			nameBox += key;
	}
	/* Pressionou delete */
	else if (clickedObj >= 0 && key == 127 && typingField == -1) {
		objs.erase(objs.begin() + clickedObj);
		clickedObj = -1;
	}
	else if (clickedObj >= 0 && typingField >= 0) {
		if (key == 13) {

			stringstream ss;
			ss << valueBox;
			valueBox = "";
			switch (typingField) {
				/* Translate */
			case 0:
				ss >> objs.at(clickedObj).translate.data[0];
				break;
			case 1:
				ss >> objs.at(clickedObj).translate.data[1];
				break;
			case 2:
				ss >> objs.at(clickedObj).translate.data[2];
				break;
				/* Rotate */
			case 3:
				ss >> objs.at(clickedObj).rotate.data[0];
				break;
			case 4:
				ss >> objs.at(clickedObj).rotate.data[1];
				break;
			case 5:
				ss >> objs.at(clickedObj).rotate.data[2];
				break;
			case 6:
				ss >> objs.at(clickedObj).rotate.data[3];
				break;
				/* Scale */
			case 7:
				ss >> objs.at(clickedObj).scale.data[0];
				break;
			case 8:
				ss >> objs.at(clickedObj).scale.data[1];
				break;
			case 9:
				ss >> objs.at(clickedObj).scale.data[2];
				break;
				/* Alpha */
			case 10:
				ss >> objs.at(clickedObj).rgba.data[3];
				break;
			}
			return;
		}
		/* Apertou backspace */
		else if (key == 8) {
			if (valueBox.size() > 0)
				valueBox.pop_back();
		}
		else
			valueBox += key;

	}
	else {
		GLfloat n[] = { 0.0, 0.0, 0.0 };
		GLfloat u[] = { 0.0, 0.0, 0.0 };
		GLdouble norm;
		GLdouble speed = 0.1;
		switch (key) {
		case '1':
			lightOne = !lightOne;
			if (lightOne)
				glEnable(GL_LIGHT0);
			else
				glDisable(GL_LIGHT0);
			break;
		case '2':
			lightTwo = !lightTwo;
			if (lightTwo)
				glEnable(GL_LIGHT1);
			else
				glDisable(GL_LIGHT1);
			break;
		case '3':
			lightThree = !lightThree;
			if (lightThree)
				glEnable(GL_LIGHT2);
			else
				glDisable(GL_LIGHT2);
			break;
		case 'v':
			if (viewMode == GL_TRIANGLES)
				viewMode = GL_LINE_LOOP;
			else
				viewMode = GL_TRIANGLES;
			break;
		case 'i':
			menuPos--;
			break;
		case 'k':
			menuPos++;
			break;
		case 'a': case 'A':
			if (key == 'A')
				speed *= 5;
			//Calcula o produto vetorial para achar o vetor u perpendicular a n e v
			n[0] = lookPoint[0] - viewer[0]; n[1] = lookPoint[1] - viewer[1]; n[2] = lookPoint[2] - viewer[2];

			u[0] = (upVector[1] * n[2]) - (n[1] * upVector[2]);
			u[1] = -((upVector[0] * n[2]) - (n[0] * upVector[2]));
			u[2] = (upVector[0] * n[1]) - (n[0] * upVector[1]);
			//Calcula a norma de u e o torna unit�rio
			norm = sqrt(pow(u[0], 2) + pow(u[1], 2) + pow(u[2], 2));
			u[0] = u[0] / norm;
			u[1] = u[1] / norm;
			u[2] = u[2] / norm;

			viewer[0] = viewer[0] + (u[0] * speed);
			viewer[1] = viewer[1] + (u[1] * speed);
			viewer[2] = viewer[2] + (u[2] * speed);

			lookPoint[0] = lookPoint[0] + (u[0] * speed);
			lookPoint[1] = lookPoint[1] + (u[1] * speed);
			lookPoint[2] = lookPoint[2] + (u[2] * speed);

			gluLookAt(
				viewer[0], viewer[1], viewer[2],
				lookPoint[0], lookPoint[1], lookPoint[2],
				upVector[0], upVector[1], upVector[2]
			);
			break;
		case 'd': case 'D':
			if (key == 'D')
				speed *= 5;
			//Calcula o produto vetorial para achar o vetor u perpendicular a n e v
			n[0] = lookPoint[0] - viewer[0]; n[1] = lookPoint[1] - viewer[1]; n[2] = lookPoint[2] - viewer[2];

			VectorialProd(upVector, n, u);

			//Calcula a norma de u e o torna unit�rio
			norm = VecNorm(u);
			u[0] = u[0] / norm;
			u[1] = u[1] / norm;
			u[2] = u[2] / norm;

			viewer[0] = viewer[0] - (u[0] * speed);
			viewer[1] = viewer[1] - (u[1] * speed);
			viewer[2] = viewer[2] - (u[2] * speed);

			lookPoint[0] = lookPoint[0] - (u[0] * speed);
			lookPoint[1] = lookPoint[1] - (u[1] * speed);
			lookPoint[2] = lookPoint[2] - (u[2] * speed);

			gluLookAt(
				viewer[0], viewer[1], viewer[2],
				lookPoint[0], lookPoint[1], lookPoint[2],
				upVector[0], upVector[1], upVector[2]
			);
			break;
		case 's': case 'S':
			if (key == 'S')
				speed *= 5;
			//Calcula o vetor n
			n[0] = lookPoint[0] - viewer[0]; n[1] = lookPoint[1] - viewer[1]; n[2] = lookPoint[2] - viewer[2];

			//Calcula a norma de n e o torna unit�rio
			norm = sqrt(pow(n[0], 2) + pow(n[1], 2) + pow(n[2], 2));
			n[0] = -n[0] / norm;
			n[1] = -n[1] / norm;
			n[2] = -n[2] / norm;

			viewer[0] = viewer[0] + (n[0] * speed);
			viewer[1] = viewer[1] + (n[1] * speed);
			viewer[2] = viewer[2] + (n[2] * speed);

			lookPoint[0] = lookPoint[0] + (n[0] * speed);
			lookPoint[1] = lookPoint[1] + (n[1] * speed);
			lookPoint[2] = lookPoint[2] + (n[2] * speed);

			gluLookAt(
				viewer[0], viewer[1], viewer[2],
				lookPoint[0], lookPoint[1], lookPoint[2],
				upVector[0], upVector[1], upVector[2]
			);

			break;
		case 'w': case 'W':
			if (key == 'W')
				speed *= 5;
			//Calcula o vetor n
			n[0] = lookPoint[0] - viewer[0]; n[1] = lookPoint[1] - viewer[1]; n[2] = lookPoint[2] - viewer[2];

			//Calcula a norma de n e o torna unit�rio
			norm = VecNorm(n);
			n[0] = -n[0] / norm;
			n[1] = -n[1] / norm;
			n[2] = -n[2] / norm;

			viewer[0] = viewer[0] - (n[0] * speed);
			viewer[1] = viewer[1] - (n[1] * speed);
			viewer[2] = viewer[2] - (n[2] * speed);

			lookPoint[0] = lookPoint[0] - (n[0] * speed);
			lookPoint[1] = lookPoint[1] - (n[1] * speed);
			lookPoint[2] = lookPoint[2] - (n[2] * speed);

			gluLookAt(
				viewer[0], viewer[1], viewer[2],
				lookPoint[0], lookPoint[1], lookPoint[2],
				upVector[0], upVector[1], upVector[2]
			);

			break;
		}
	}
	glutPostRedisplay();
}
/* Calcula o arrastar do mouse */
void clickedMouse(int x, int y) {
	yaw -= (previousX - x) / 100;
	if(pitch + (previousY - y) / 100 >= -3.14/2 && pitch + (previousY - y) / 100 <= 3.14/2)
		pitch += (previousY - y) / 100;
	cout << pitch << endl;
	previousX = x;
	previousY = y;

	lookPoint[0] = cos(pitch) * cos(yaw) + (viewer[0] );
	lookPoint[1] = sin(pitch) + (viewer[1] );
	lookPoint[2] = cos(pitch) * sin(yaw) + (viewer[2] );

	GLfloat aux[] = { lookPoint[0] - viewer[0], lookPoint[1] - viewer[1], lookPoint[2] - viewer[2] };

	GLfloat aux2[3];
	VectorialProd(worldUp, aux, aux2);

	VectorialProd(aux, aux2, upVector);

	upVector[0] = upVector[0] / VecNorm(upVector);
	upVector[1] = upVector[1] / VecNorm(upVector);
	upVector[2] = upVector[2] / VecNorm(upVector);
}

/* Defne os cliques do mouse */
void mouse(int button, int state, int x, int y) {
	
	double xf, yf;
	xf = (200 * aspectRatio) * (x - 3 * __WIDTH / 4) / __WIDTH;
	yf = (200) * (__HEIGHT - y) / __HEIGHT;

	/* Atribuição prévia para clicked mouse*/
	if (state == GLUT_DOWN) {
		previousX = x;
		previousY = y;
	}
	/* Trata rolagem do mouse */
	if (button == 4)
		menuPos++;
	else if (button == 3)
		menuPos--;
	/* Trata parte do menu da tela */
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (x >= 3 * __WIDTH / 4) {

			/* Checa se ele esta clicando na caixa de importacao */
			if (xf >= 20.0f / 3 && yf >= 180 && xf <= 60 && yf <= 188) {
				clickedObj = -1;
				typingField = 0;
			}
			/* Checa se eles esta clicando na caixa de carregar */
			else if (xf >= 20 && yf >= 173 && xf <= 60 && yf <= 179) {
				clickedObj = -1;
				typingField = -1;
				Quad<double> aux((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), 0.5);
				createObj(nameBox, aux);
				nameBox = "";
			}
			/* Se for clicado em alguma caixa de algum objeto*/
			else if (xf >= 20.0f / 3 && xf <= 60 && yf <= 168) {

				/* Calcula pelo ortho e pelo movimento do menu qual objeto foi clicado */
				double aux = ((yf - 133 + menuPos) / -40) + 0.875;

				if (trunc(aux) == trunc(aux + 0.125) && aux < objs.size()) {
					clickedObj = trunc(aux);

					/* Caso a visibilidade do objeto seja alterada */
					if (xf >= 53 && xf <= 58 && yf >= 168 - clickedObj * 40 - 6 - menuPos && yf <= 168 - clickedObj * 40 - 1 - menuPos) {
						objs.at(clickedObj).visible = !objs.at(clickedObj).visible;
						typingField = -1;
					}

					/* Esta na 'caixa' em x que envolve todas as caixas menores de rotacao, translacao, etc... */

					/* Checa em qual coluna esta (da esquerda para a direita) e dentro checa em qual linha */
					else if (xf >= 12 && xf <= 22) {
						if (yf >= 154 - (clickedObj * 40 + 5) - menuPos && yf <= 154 - (clickedObj * 40) - menuPos) {
							typingField = 3;
						}
						else {
							typingField = -1;
						}
					}
					else if (xf >= 24 && xf <= 34) {
						if (yf >= 161 - (clickedObj * 40 + 5) - menuPos && yf <= 161 - (clickedObj * 40) - menuPos) {
							typingField = 0;
						}
						else if (yf >= 154 - (clickedObj * 40 + 5) - menuPos && yf <= 154 - (clickedObj * 40) - menuPos) {
							typingField = 4;
						}
						else if (yf >= 147 - (clickedObj * 40 + 5) - menuPos && yf <= 147 - (clickedObj * 40) - menuPos) {
							typingField = 7;
						}
						else {
							typingField = -1;
						}
					}
					else if (xf >= 36 && xf <= 46) {
						if (yf >= 161 - (clickedObj * 40 + 5) - menuPos && yf <= 161 - (clickedObj * 40) - menuPos) {
							typingField = 1;
						}
						else if (yf >= 154 - (clickedObj * 40 + 5) - menuPos && yf <= 154 - (clickedObj * 40) - menuPos) {
							typingField = 5;
						}
						else if (yf >= 147 - (clickedObj * 40 + 5) - menuPos && yf <= 147 - (clickedObj * 40) - menuPos) {
							typingField = 8;
						}
						else {
							typingField = -1;
						}
					}
					else if (xf >= 48 && xf <= 58) {
						if (yf >= 161 - (clickedObj * 40 + 5) - menuPos && yf <= 161 - (clickedObj * 40) - menuPos) {
							typingField = 2;
						}
						else if (yf >= 154 - (clickedObj * 40 + 5) - menuPos && yf <= 154 - (clickedObj * 40) - menuPos) {
							typingField = 6;
						}
						else if (yf >= 147 - (clickedObj * 40 + 5) - menuPos && yf <= 147 - (clickedObj * 40) - menuPos) {
							typingField = 9;
						}
						else if (yf >= 140 - (clickedObj * 40 + 5) - menuPos && yf <= 140 - (clickedObj * 40) - menuPos) {
							typingField = 10;
						}
						else {
							typingField = -1;
						}
					}
					else {
						typingField = -1;
					}
				}

				else {
					clickedObj = -1;
					typingField = -1;
				}

				valueBox = "";
			}
			/* Se clicou diretamente fora */
			else if (clickedObj >= 0 || typingField >= 0) {
				clickedObj = -1;
				typingField = -1;
			}
		}
		/* Trata a parte dos objetos da tela */
		else {
			clickedObj = -1;
			typingField = -1;

		}
	}
}

#endif