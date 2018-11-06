#ifndef OBJETO_H__
#define OBJETO_H__

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Implementação de uma função split para dividir umas string

vector<string> split(string a, string b) {
	string aux = "";
	vector<string> result;

	if (a.size() == 0 || b.size() == 0)
		return result;

	for (int i = 0; i < a.size(); i++) {
		bool add = true;
		for (int j = 0; j < b.size(); j++) {
			if (a[i] == b[j]) {
				add = false;
				break;
			}
		}
		if (!add) {
			if (aux != "")
				result.push_back(aux);
			aux = "";
		}
		else
			aux += a[i];
	}
	if (aux != "")
		result.push_back(aux);
	return result;
}


// Classe para variaveis duplas

template<class T>
class Duo {
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

// Classe para variáveis triplas

template<class T>
class Trio {
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

// Classe para um objeto completo

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
			getine(file, line);
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