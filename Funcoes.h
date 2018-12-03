#ifndef FUNCOES_H__
#define FUNCOES_H__
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
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
GLfloat viewer[] = { 3.0, 3.0, 6.0, 50000000 };
GLfloat lookPoint[] = { 0.0, 0.0, 0.0 };
GLfloat upVector[] = { 0.0, 1.0, 0.0 };

/* Modo de exibição do objeto */
GLint viewMode = GL_TRIANGLES;

/* Movimentação do olho do observador */
bool dragX = false, dragY = false;
double posX, posY, posfX, posfY;
double rotateX = 0, rotateY = 0;

/* String digitada na caixa de importa��o do objeto */
string nameBox = "", valueBox = "";

/* Identificadores para saber se o usu�rio est� digitando						*/
/* clickedObj = -1 representa a tela de menu inteira							*/
/* clickedObj >= 0 representa um objeto de "objs"								*/
/* typingField = -1 representa lugar nenhum										*/
/* typingField = 0 representa a caixa de importa��o caso clickedObj = -1		*/
/* typingField = 0 e <= 10 representam caixas do objeto quanto clickedObj != -1 */
short clickedObj = -1, typingField = -1;

bool lightOne = false, lightTwo = false, lightThree = false;

/* Fun��o para carregar objeto */
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


/* Define os comandos do teclado				 */
/* i - k = comandos que movem o "menu"			 */
/* w - a - s - d = comandos que movem os objetos */

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
			if(nameBox.size() > 0)
				nameBox.pop_back();
		}
		else
			nameBox += key;
	}
	/* Pressionou delete */
	else if (clickedObj >= 0 && key == 127 && typingField == -1) {
		objs.erase(objs.begin()+clickedObj);
		clickedObj = -1;
	}
	else if(clickedObj >= 0 && typingField >= 0){
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
		GLdouble n[] = { 0.0, 0.0, 0.0 };
		GLdouble u[] = { 0.0, 0.0, 0.0 };
		GLdouble norm;
		switch (key) {
			case '1':
				lightOne = !lightOne;
				if(lightOne)
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

			case 'x':
				posX = 0;
				dragX = !dragX;
				break;
			case 'y':
				posY = 0;
				dragY = !dragY;
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
			case 'a':
				//Calcula o produto vetorial para achar o vetor u perpendicular a n e v
				n[0] = lookPoint[0]-viewer[0]; n[1] = lookPoint[1]-viewer[1]; n[2] = lookPoint[2]-viewer[2];

				u[0] = (upVector[1]*n[2])-( n[1]*upVector[2]);
				u[1] = -((upVector[0]*n[2])-( n[0]*upVector[2]));
				u[2] = (upVector[0]*n[1])-( n[0]*upVector[1]);
				//Calcula a norma de u e o torna unitário
				norm = sqrt( pow(u[0], 2) + pow(u[1], 2) + pow(u[2], 2) );
				u[0] = u[0]/norm;
				u[1] = u[1]/norm;
				u[2] = u[2]/norm;

				viewer[0] = viewer[0] + (u[0] * 0.1);
				viewer[1] = viewer[1] + (u[1] * 0.1);
				viewer[2] = viewer[2] + (u[2] * 0.1);

				lookPoint[0] = lookPoint[0] + (u[0] * 0.1);
				lookPoint[1] = lookPoint[1] + (u[1] * 0.1);
				lookPoint[2] = lookPoint[2] + (u[2] * 0.1);

				gluLookAt(
					viewer[0], viewer[1], viewer[2],
					lookPoint[0], lookPoint[1], lookPoint[2],
					upVector[0], upVector[1], upVector[2]
				);
				break;
			case 'd':
				//Calcula o produto vetorial para achar o vetor u perpendicular a n e v
				n[0] = lookPoint[0]-viewer[0]; n[1] = lookPoint[1]-viewer[1]; n[2] = lookPoint[2]-viewer[2];

				u[0] = (upVector[1]*n[2])-( n[1]*upVector[2]);
				u[1] = -((upVector[0]*n[2])-( n[0]*upVector[2]));
				u[2] = (upVector[0]*n[1])-( n[0]*upVector[1]);
				//Calcula a norma de u e o torna unitário
				norm = sqrt( pow(u[0], 2) + pow(u[1], 2) + pow(u[2], 2) );
				u[0] = u[0]/norm;
				u[1] = u[1]/norm;
				u[2] = u[2]/norm;

				viewer[0] = viewer[0] - (u[0] * 0.1);
				viewer[1] = viewer[1] - (u[1] * 0.1);
				viewer[2] = viewer[2] - (u[2] * 0.1);

				lookPoint[0] = lookPoint[0] - (u[0] * 0.1);
				lookPoint[1] = lookPoint[1] - (u[1] * 0.1);
				lookPoint[2] = lookPoint[2] - (u[2] * 0.1);

				gluLookAt(
					viewer[0], viewer[1], viewer[2],
					lookPoint[0], lookPoint[1], lookPoint[2],
					upVector[0], upVector[1], upVector[2]
				);
				break;
			case 's':
				//Calcula o vetor n
				n[0] = lookPoint[0]-viewer[0]; n[1] = lookPoint[1]-viewer[1]; n[2] = lookPoint[2]-viewer[2];

				//Calcula a norma de n e o torna unitário
				norm = sqrt( pow(n[0], 2) + pow(n[1], 2) + pow(n[2], 2) );
				n[0] = abs(n[0]/norm);
				n[1] = abs(n[1]/norm);
				n[2] = abs(n[2]/norm);

				viewer[0] = viewer[0] + (n[0] * 0.1);
				viewer[1] = viewer[1] + (n[1] * 0.1);
				viewer[2] = viewer[2] + (n[2] * 0.1);

				lookPoint[0] = lookPoint[0] + (n[0] * 0.1);
				lookPoint[1] = lookPoint[1] + (n[1] * 0.1);
				lookPoint[2] = lookPoint[2] + (n[2] * 0.1);

				gluLookAt(
					viewer[0], viewer[1], viewer[2],
					lookPoint[0], lookPoint[1], lookPoint[2],
					upVector[0], upVector[1], upVector[2]
				);

				break;
			case 'w':
				//Calcula o vetor n
				n[0] = lookPoint[0]-viewer[0]; n[1] = lookPoint[1]-viewer[1]; n[2] = lookPoint[2]-viewer[2];

				//Calcula a norma de n e o torna unitário
				norm = sqrt( pow(n[0], 2) + pow(n[1], 2) + pow(n[2], 2) );
				n[0] = abs(n[0]/norm);
				n[1] = abs(n[1]/norm);
				n[2] = abs(n[2]/norm);

				viewer[0] = viewer[0] - (n[0] * 0.1);
				viewer[1] = viewer[1] - (n[1] * 0.1);
				viewer[2] = viewer[2] - (n[2] * 0.1);

				lookPoint[0] = lookPoint[0] - (n[0] * 0.1);
				lookPoint[1] = lookPoint[1] - (n[1] * 0.1);
				lookPoint[2] = lookPoint[2] - (n[2] * 0.1);

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
void passiveMouse(int x, int y) {
	double xf, yf;
	xf = (200 * aspectRatio) * (x - 3 * __WIDTH / 4) / __WIDTH;
	yf = (200) * (__HEIGHT - y) / __HEIGHT;
	if (dragX) {
		if (xf >= posX) {
			if (xf >= posfX) {
				rotateY += ((xf - posX) / 100);
			}
			else {
				rotateY -= ((xf - posX) / 100);
			}
		}
		else {
			if (xf >= posfX) {
				rotateY -= ((xf - posX) / 100);
			}
			else {
				rotateY += ((xf - posX) / 100);
			}
		}
		posfX = xf;
	}
	if (dragY) {

		if (yf >= posY) {
			if (yf >= posfY) {
				rotateX += ((yf - posY) / 100);
			}
			else {
				rotateX -= ((yf - posY) / 100);
			}
		}
		else {
			if (yf >= posfY) {
				rotateX -= ((yf - posY) / 100);
			}
			else {
				rotateX += ((yf - posY) / 100);
			}
		}
		posfY = yf;
	}
}

/* Defne os cliques do mouse */
void mouse(int button, int state, int x, int y) {
	double xf, yf;
	xf = (200 * aspectRatio) * (x - 3 * __WIDTH / 4) / __WIDTH;
	yf = (200) * (__HEIGHT - y) / __HEIGHT;

	/* Trata rolagem do mouse */
	if (button == 4)
		menuPos++;
	else if (button == 3)
		menuPos--;
	/* Trata parte do menu da tela */
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
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

				//cout << xf << " " << yf << endl;

				/* Calcula pelo ortho e pelo movimento do menu qual objeto foi clicado */
				double aux = ((yf - 133 + menuPos) / -40) + 0.875;

				if (trunc(aux) == trunc(aux + 0.125) && aux < objs.size()) {
					clickedObj = trunc(aux);
				
					/* Caso a visibilidade do objeto seja alterada */
					if (xf>= 53 && xf <= 58 && yf >= 168 - clickedObj*40 - 6 - menuPos && yf <= 168 - clickedObj * 40 - 1 - menuPos) {
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
						if (yf >= 161 - (clickedObj * 40 + 5) - menuPos && yf <= 161 - (clickedObj * 40) - menuPos ) {
							typingField = 0;
						}
						else if (yf >= 154 - (clickedObj * 40 + 5) - menuPos && yf <= 154 - (clickedObj * 40) - menuPos ) {
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
	for (vector<Objeto>::iterator o = objs.begin(); o != objs.end(); o++) {
		if ((*o).visible) {
			poly += (*o).f.size();
			glPushMatrix();

			glScalef((*o).scale.data[0], (*o).scale.data[1], (*o).scale.data[2]);
			glTranslatef((*o).translate.data[0], (*o).translate.data[1], (*o).translate.data[2]);
			glRotatef((*o).rotate.data[0], (*o).rotate.data[1], (*o).rotate.data[2], (*o).rotate.data[3]);

			glColor4f((*o).rgba.data[0], (*o).rgba.data[1], (*o).rgba.data[2], (*o).rgba.data[3]);
			
			
			for (int i = 0; i < (*o).f.size(); i++) {
				
				/* Pegamos da face i os 3 vertices que a compoe, dai, desses 3 vertices pegamos 3 coordenadas para representa-los no espa�o */
				glBegin(viewMode);
				if((*o).vn.size() > 0)
					glNormal3f(
						(*o).vn.at((*o).f.at(i).data[0].data[2] - 1).data[0],
						(*o).vn.at((*o).f.at(i).data[0].data[2] - 1).data[1],
						(*o).vn.at((*o).f.at(i).data[0].data[2] - 1).data[2]
					);
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
				glVertex3f(
					(*o).v.at((*o).f.at(i).data[2].data[0] - 1).data[0],
					(*o).v.at((*o).f.at(i).data[2].data[0] - 1).data[1],
					(*o).v.at((*o).f.at(i).data[2].data[0] - 1).data[2]
				);
				glEnd();
			}
			

			glPopMatrix();
		}
	}
}

/* Limpa a tela */
void resetView() {
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

}

/* Define os modos de proje��o e modelview a serem seguidos na parte da tela referente a exibi��o dos objetos */
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

void lightExample() {
	GLfloat red_light[] = { 1.0, 0.0, 0.0, 0.0 };
	GLfloat blue_light[] = { 0.0, 0.0, 1.0, 0.0 };

	GLfloat position[] = { 0,0,0,1 };
	GLfloat global_position[] = { 0, 1, 0, 0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	if (lightOne) {
		

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);

		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
		glLightfv(GL_LIGHT0, GL_POSITION, global_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, red_light);
	}
	if (lightTwo) {

		glMaterialf(GL_FRONT, GL_SHININESS, 50);
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
	}

	if (lightThree) {

		glMaterialf(GL_FRONT, GL_SHININESS, 50);
		glLightfv(GL_LIGHT2, GL_POSITION, position);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15);
		glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light);
	}

}

void lightsOff() {
	glDisable(GL_LIGHTING);
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
	showObjects();
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
		glRectd(i-10, startY, i, endY);
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
				
				if(clickedObj != i)
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
					
						glTranslated(60 - 12* (2-j) - 12 + 0.7, 161 - pos - 5 + 0.5, 0);
						glScaled(0.035, 0.035, 0);
						if(clickedObj == i && typingField == j)
							glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)valueBox.c_str());
						else
							glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)ss.str().c_str());

					glPopMatrix();
				}

				glColor4d(0,0,0, 1);

				/* Desenha as caixas relacionadas com rota��o e seu label */

				drawBoxAndLabel(23.0f / 3, 60, 154 - (pos + 5), 154 - pos, "R: ", 4);

				/* Escreve o valor nas caixas */

				glColor4d(1, 1, 1, 1);
				for (int j = 0; j < 4; j++) {
					ss.str("");
					ss << objs.at(i).rotate.data[j];
					glPushMatrix();

					glTranslated(60 - 12 * (3-j) - 12 + 0.7, 154 - pos - 5 + 0.5, 0);
					glScaled(0.035, 0.035, 0);
					if (clickedObj == i && typingField-3 == j)
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

					glTranslated(60 - 12 * (2-j) - 12 + 0.7, 147 - pos - 5 + 0.5, 0);
					glScaled(0.035, 0.035, 0);

					if (clickedObj == i && typingField-7 == j)
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
	glRectd(20.0f/3 , 180, 60, 188);
	
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
		glTranslated(31 , 174.5, 0);
		glScaled(0.035, 0.035, 0);
		glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)"Carregar");
	glPopMatrix();



	/* Escreve a quantidade de tempo para desenhar e a quantidade de poly na parte de baixo da tela */
	glPushMatrix();

		glColor4d(0, 0, 0, 1);
		glTranslated(20.0f/3, 1, 0);
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
		timeCounter = glutGet(GLUT_ELAPSED_TIME)/1000;
	}
	if ( glutGet(GLUT_ELAPSED_TIME)/1000 - timeCounter >= 1) {
		averageTime = deltaTime / frameCounter;
		deltaTime = frameCounter = 0;
		timeCounter = glutGet(GLUT_ELAPSED_TIME)/1000;
	}

	int timeStart = glutGet(GLUT_ELAPSED_TIME);
	
	resetView();
	lightExample();
	displayObjects();
	
	lightsOff();
	displayMenu();

	deltaTime += glutGet(GLUT_ELAPSED_TIME) - timeStart;
	frameCounter++;

	glutSwapBuffers();
}

/* Sempre mant�m a tela com um aspect definido para n�o distorcer o desenho */
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


	/* Faz os desenhos iniciais */
	resetView();
	objectsProjection();
	showBaseScreen();

	createObj("Teapot.obj", Quad<double>(1, 1, 1, 1));

	glutSwapBuffers();

	glutTimerFunc(1000.0f/60, timer, 0);
}

#endif