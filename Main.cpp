#include <iostream>
#include <GL/glut.h>
#include "Objeto.h"
#include "Funcoes.h"

using namespace std;

Objeto dr;
int __WIDTH = 600, __HEIGHT = 600;
int rotatex = 0, rotatey = 0;

void createObj(string fileName) {
	dr.initialize(fileName);
}

int main(int argc, char **argv) {
	thread t(createObj, ("Dragon.obj"));
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glutInitWindowSize(__WIDTH, __HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Trabalho 3");

	initialize();
	
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	t.join();
	glutMainLoop();


	return 0;
}
