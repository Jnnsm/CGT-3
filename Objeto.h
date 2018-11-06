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
		fstream file;
		string line;
		vector<string> aux;

		double a, b, c;

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
							istringstream(aux.at(1)) >> a;
							istringstream(aux.at(2)) >> b;
							istringstream(aux.at(3)) >> c;
							v.push_back(Trio<double>(a, b, c));
						}
						else if (aux.at(0) == "vn") {
							istringstream(aux.at(1)) >> a;
							istringstream(aux.at(2)) >> b;
							istringstream(aux.at(3)) >> c;
							vn.push_back(Trio<double>(a, b, c));
						}
						else if (aux.at(0) == "vt") {
							istringstream(aux.at(1)) >> a;
							istringstream(aux.at(2)) >> b;
							vt.push_back(Duo<double>(a, b));
						}
						else if (aux.at(0) == "f") {
							Trio<Duo<double>> auxiliar;
							istringstream(split(aux.at(1),"/").at(0)) >> auxiliar.primeiro.primeiro;
							istringstream(split(aux.at(1), "/").at(1)) >> auxiliar.primeiro.segundo;

							istringstream(split(aux.at(2), "/").at(0)) >> auxiliar.segundo.primeiro;
							istringstream(split(aux.at(2), "/").at(1)) >> auxiliar.segundo.segundo;

							istringstream(split(aux.at(3), "/").at(0)) >> auxiliar.terceiro.primeiro;
							istringstream(split(aux.at(3), "/").at(1)) >> auxiliar.terceiro.segundo;

							f.push_back(auxiliar);

							cout << auxiliar << endl;
						}
					}
				}
			}
		}

		cout << v.size() << " " << vn.size() << " " << vt.size() << " " << f.size() << endl;
		
	}

	~Objeto() {
		//Não faz nada
	}

};




#endif