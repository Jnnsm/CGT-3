#ifndef OBJETO_H__
#define OBJETO_H__

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>

using namespace std;

/* Implementação de uma função split para dividir umas string */ 

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


/* Classe para variaveis duplas */

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

	void altera(T p, T s) {
		primeiro = p;
		segundo = s;
	}

};

template<class T>
ostream & operator << (ostream &cout, const Duo<T>& t) {
	cout << "(" << t.primeiro << ", " << t.segundo << ")";
	return cout;
}

/* Classe para variáveis triplas */

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

	void altera(T p, T s, T t) {
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

/* Classe para um objeto completo */

class Objeto {
public:
	/* Variáveis relacionadas com o objeto */
	Trio<double> cor;
	double transparencia;

	/* Variáveis relacionadas com o arquivo */
	string mtl;
	bool s;
	vector<Trio<double>> v;
	vector<Trio<double>> vn;
	vector<Duo<double>> vt;
	vector<Trio<Duo<double>>> f;
	
	Objeto() {
		/* Nao faz nada */
	}
	Objeto(string fileName) {
		/* Preenche os vetores */ 
		read(fileName);
		/* Randomiza a cor e coloca o objeto sólido */
	}

	/* Limpa o objeto */
	void eraseData() {
		mtl = "";
		s = false;

		v.clear();
		vn.clear();
		vt.clear();
		f.clear();

	}

	/* Preenche o objeto */
	void initialize(string fileName) {
		eraseData();
		read(fileName);
	}

	/* Lê do arquivo o objeto */
	void read(string fileName) {
		// Variáveis para auxilio do preenchimento
		fstream file;
		string line;
		vector<string> aux;

		// Variáveis que guardam os valores do arquivo enquanto são lidas

		Trio<double> Taux;
		Duo<double> Daux;
		Trio<Duo<double>> TDaux;

		file.open(fileName.c_str(), fstream::in | fstream::binary);
		
		while (getline(file, line, ' ')) {
			if (line[0] == '#')
				getline(file, line);
			else {
				if (line == "usemtl" || line == "mtllib") {
					getline(file, line);
					mtl = split(line, "()").at(0);
				}
				else {
					if (line[0] == 's') {
						getline(file, line);
						if (line == "0" || line == "off")
							s = false;
						else
							s = true;
					}
					else {
						if (line == "v") {
							getline(file, line, ' ');
							istringstream(line) >> Taux.primeiro;
							getline(file, line, ' ');
							istringstream(line) >> Taux.segundo;
							getline(file, line);
							istringstream(line) >> Taux.terceiro;
							v.push_back(Taux);
						}
						else if (line == "vn") {
							getline(file, line, ' ');
							istringstream(line) >> Taux.primeiro;
							getline(file, line, ' ');
							istringstream(line) >> Taux.segundo;
							getline(file, line);
							istringstream(line) >> Taux.terceiro;
							vn.push_back(Taux);
						}
						else if (line == "vt") {
							getline(file, line, ' ');
							istringstream(line) >> Daux.primeiro;
							getline(file, line);
							istringstream(line) >> Daux.segundo;
							vt.push_back(Daux);
						}
						else if (line == "f") {
							getline(file, line, '/');
							istringstream(line) >> TDaux.primeiro.primeiro;
							getline(file, line, ' ');
							istringstream(line) >> TDaux.primeiro.segundo;

							getline(file, line, '/');
							istringstream(line) >> TDaux.segundo.primeiro;
							getline(file, line, ' ');
							istringstream(line) >> TDaux.segundo.segundo;

							getline(file, line, '/');
							istringstream(line) >> TDaux.terceiro.primeiro;
							getline(file, line);
							istringstream(line) >> TDaux.terceiro.segundo;

							f.push_back(TDaux);
						}
					}
				}
			}
		}
		file.close();
	}

	~Objeto() {
		/* Não faz nada */
	}

};




#endif