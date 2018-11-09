#include <iostream>
#include <GL/glut.h>
#include "Objeto.h"
#include "Funcoes.h"

using namespace std;

vector<Objeto> objs;
double __WIDTH = 800, __HEIGHT = 600;

void createObj(string fileName) {
	Objeto dr;
	dr.initialize(fileName);
	objs.push_back(dr);
}

int main(int argc, char **argv) {
	thread t(createObj, ("DragonEye.obj"));
	thread t2(createObj, ("Teapot.obj"));
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glutInitWindowSize(__WIDTH, __HEIGHT);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Trabalho 3");

	initialize();

	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);

	t.join();
	t2.join();

	glutMainLoop();


	return 0;
}
