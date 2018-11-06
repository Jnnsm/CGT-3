#ifndef OBJETO_H__
#define OBJETO_H__

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
		cout << "(" << t.primeiro << ", " << t.segundo << ")";
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
	cout << "(" << t.primeiro << ", " << t.segundo << ")";
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
	bool s;
	vector<Trio<double>> v;
	vector<Trio<double>> vn;
	vector<Duo<double>> vt;
	vector<Trio<Duo<double>>> f;
	
	Objeto() {
		//Nao faz nada
	}
	Objeto(string fileName) {
		//Preenche os vetores


		// Variáveis para auxilio do preenchimento
		fstream file;
		string line;
		vector<string> aux;

		// Variáveis que guardam os valores do arquivo enquanto são lidas

		Trio<double> Taux;
		Duo<double> Daux;
		Trio<Duo<double>> TDaux;

		file.open(fileName.c_str(), fstream::in);

		while (!file.eof()) {
			getline(file, line);
			if (line[0] != '#') {
				aux = split(line, " ");
				if (aux.empty())
					break;
				else if (aux.at(0) == "usemtl" || aux.at(0) == "mtllib")
					mtl = split(aux.at(1),"()").at(0);
				else {
					if (aux.at(0) == "s") {
						if (aux.at(1) == "0" || aux.at(1) == "off")
							s = false;
						else
							s = true;
					}
					else {
						if (aux.at(0) == "v") {
							istringstream(aux.at(1)) >> Taux.primeiro;
							istringstream(aux.at(2)) >> Taux.segundo;
							istringstream(aux.at(3)) >> Taux.terceiro;
							v.push_back(Taux);
						}
						else if (aux.at(0) == "vn") {
							istringstream(aux.at(1)) >> Taux.primeiro;
							istringstream(aux.at(2)) >> Taux.segundo;
							istringstream(aux.at(3)) >> Taux.terceiro;
							vn.push_back(Taux);
						}
						else if (aux.at(0) == "vt") {
							istringstream(aux.at(1)) >> Daux.primeiro;
							istringstream(aux.at(2)) >> Daux.segundo;
							vt.push_back(Daux);
						}
						else if (aux.at(0) == "f") {
							istringstream(split(aux.at(1),"/").at(0)) >> TDaux.primeiro.primeiro;
							istringstream(split(aux.at(1), "/").at(1)) >> TDaux.primeiro.segundo;

							istringstream(split(aux.at(2), "/").at(0)) >> TDaux.segundo.primeiro;
							istringstream(split(aux.at(2), "/").at(1)) >> TDaux.segundo.segundo;

							istringstream(split(aux.at(3), "/").at(0)) >> TDaux.terceiro.primeiro;
							istringstream(split(aux.at(3), "/").at(1)) >> TDaux.terceiro.segundo;

							f.push_back(TDaux);
						}
					}
				}
			}
		}
	}

	~Objeto() {
		//Não faz nada
	}

};




#endif