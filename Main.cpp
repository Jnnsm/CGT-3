#include <iostream>
#include <GL/glut.h>
#include "Objeto.h"
#include "Funcoes.h"

using namespace std;

int __WIDTH = 600, __HEIGHT = 600;

int main(int argc, char **argv) {
	// Le o objeto 
	Objeto dr("DragonEye.obj");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(__WIDTH, __HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Trabalho 3");

	initialize();
	glutDisplayFunc(display);
	glEnable(GL_CULL_FACE);

	glutMainLoop();


	return 0;
}
