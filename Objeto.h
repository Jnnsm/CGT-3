#ifndef OBJETO_H__
#define OBJETO_H__

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template<class T>
class Duo {
	//template<class T>
	friend ostream & operator << (ostream &, const Duo<T>& t) {
		cout << "(" << t.primeiro << ", " << t.segundo << ") ";
		return cout;
	}
public:
	T primeiro;
	T segundo;
	
	Duo(){}
	Duo(T p, T s) {
		primeiro = p;
		segundo = s;
	}

};

template<class T>
ostream & operator << (ostream &cout, const Duo<T>& t) {
	cout << "(" << t.primeiro << ", " << t.segundo << ") ";
	return cout;
}


template<class T>
class Trio {
	//template<class T>
	friend ostream & operator << (ostream &cout, const Trio<T>& t) {
		cout << "(" << t.primeiro << ", " << t.segundo << ", " << t.terceiro << ") ";
		return cout;
	}
public:
	T primeiro;
	T segundo;
	T terceiro;

	Trio() {}
	Trio(T p, T s, T t) {
		primeiro = p;
		segundo = s;
		terceiro = t;
	}
};

template<class T>
ostream & operator << (ostream &cout, const Trio<T>& t) {
	cout << "(" << t.primeiro << ", " << t.segundo << ", " << t.terceiro << ") ";
	return cout;
}

class Objeto {
public:
	string mtl;
	double s;
	Trio<double> *v;
	Duo<double> *vt;
	Trio<Duo<double>> *f;
	
	Objeto() {
		//Não faz nada
	}
	Objeto(string fileName) {
		//Preenche os vetores
		fstream file;
		string line;

		file.open(fileName.c_str(), fstream::in);

		while (!file.eof()) {

		}
	}

	~Objeto() {
		//Deleta os vetores
		delete[]v;
		delete[]vt;
		delete[]f;
	}

};




#endif