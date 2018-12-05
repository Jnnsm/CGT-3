#ifndef CREATION_H__
#define CREATION_H__

#include <iostream>
#include <string>
#include <vector>
#include "Objeto.h"

extern vector<Objeto> objs;

/* Funcao para carregar objeto */
void createObj(string fileName, Quad<double> color) {
	Objeto dr;
	try {
		
		dr.initialize(fileName, color);
		
		objs.push_back(dr);
	}
	catch (int e) {
		cerr << "Algum arquivo est� faltando" << endl;
	}
}

#endif