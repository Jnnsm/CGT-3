#include <iostream>
#include <GL/freeglut.h>
#include <time.h>
#include "Objeto.h"
#include "Funcoes.h"

using namespace std;

/* Vector com v�rios objetos a serem desenhados */
vector<Objeto> objs;
double __WIDTH = 800, __HEIGHT = 600;

int main(int argc, char **argv) {
	srand(time(NULL));

	/* Cria 2 objetos que s�o carregados de maneira paralela */
	Trio<double> aux((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX));
	thread t(createObj, ("Dragon.obj"), aux);

	aux.altera((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX));
	thread t2(createObj, ("Teapot.obj"), aux);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(__WIDTH, __HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Trabalho 3");

	initialize();

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	/* Ativa suaviza��es, canal alfa e teste de profundidade */
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	/* Antes de dar um passo no loop espera as thread t e t2 terminarem */
	t.join();
	t2.join();

	glutMainLoop();


	return 0;
}
