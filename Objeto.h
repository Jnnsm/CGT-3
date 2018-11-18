#ifndef OBJETO_H__
#define OBJETO_H__

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <time.h>

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
		cout << "(" << t.data[0] << ", " << t.data[1] << ")";
		return cout;
	}
public:
	T data[2];
	
	Duo(){

	}
	Duo(T p, T s) {
		altera(p,s);
	}

	void altera(T p, T s) {
		data[0] = p;
		data[1] = s;
	}

};

/* Classe para variáveis triplas */

template<class T>
class Trio {
	friend ostream & operator << (ostream &cout, const Trio<T>& t) {
		cout << "(" << t.data[0] << ", " << t.data[1] << ", " << t.data[2] << ") ";
		return cout;
	}
public:
	T data[3];

	Trio() {

	}
	Trio(T p, T s, T t) {
		altera(p, s, t);
	}

	void altera(T p, T s, T t) {
		data[0] = p;
		data[1] = s;
		data[2] = t;
	}

};

/* Classe para variáveis quadruplas */

template<class T>
class Quad {
	friend ostream & operator << (ostream &cout, const Quad<T>& t) {
		cout << "(" << t.data[0] << ", " << t.data[1] << ", " << t.data[2] << ", " << t.data[3] << ") ";
		return cout;
	}
public:
	T data[4];

	Quad() {

	}
	Quad(T p, T s, T t, T q) {
		altera(p, s, t, q);
	}

	void altera(T p, T s, T t, T q) {
		data[0] = p;
		data[1] = s;
		data[2] = t;
		data[3] = q;
	}

};


/* Classe para um objeto completo */

class Objeto {
public:
	/* Variáveis relacionadas com o objeto */
	Quad<double> rgba;
	Trio<double> translate;
	Quad<double> rotate;
	Trio<double> scale;
	bool visible;

	/* Variáveis relacionadas com o arquivo */
	string name;
	string mtl;
	bool s;
	vector<Trio<double>> v;
	vector<Trio<double>> vn;
	vector<Duo<double>> vt;
	vector<Trio<Trio<double>>> f;
	
	Objeto() {
		/* Nao faz nada */
	}
	Objeto(string fileName) {
		initialize(fileName);
	}
	Objeto(string fileName, Quad<double> rgba) {
		initialize(fileName, rgba);
	}

	/* Limpa o objeto */
	void eraseData() {

		visible = true;
		translate.altera(0, 0, 0);
		rotate.altera(0, 0, 0, 0);
		scale.altera(1, 1, 1);

		name = "";
		rgba.altera(0,0,0,1);

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
		name = fileName;
		read(fileName);
	}

	/* Preenche o objeto e adiciona cor */
	void initialize(string fileName, Quad<double> rgba) {

		eraseData();
		name = fileName;
		read(fileName);

		this->rgba.altera(rgba.data[0], rgba.data[1], rgba.data[2], rgba.data[3]);
	}

	void read(string fileName) {

		/* Variáveis para auxilio do preenchimento */
		fstream file;
		string line;
		vector<string> aux;

		/* Variáveis que guardam os valores do arquivo enquanto são lidas */

		Trio<double> Taux(0, 0, 0);
		Duo<double> Daux(0, 0);
		Trio<Trio<double>> TDaux(Trio<double>(0, 0, 0), Trio<double>(0, 0, 0), Trio<double>(0, 0, 0));

		file.open(fileName.c_str(), fstream::in | fstream::binary);

		/* Checa se o arquivo existe de fato */
		if (!file.good())
			throw 1;

		while (file >> line) {
			if (line == "usemtl" || line == "mtllib") {
				getline(file, line);
				mtl = split(line, "()").at(0);
			}

			else if (line == "s") {
				getline(file, line);
				if (line == "0" || line == "off")
					s = false;
				else
					s = true;
			}
			else if (line == "v") {
				for (int i = 0; i < 3; i++) {
					file >> line;
					istringstream(line) >> Taux.data[i];
				}
				v.push_back(Taux);
			}
			else if (line == "vn") {
				for (int i = 0; i < 3; i++) {
					file >> line;
					istringstream(line) >> Taux.data[i];
				}
				vn.push_back(Taux);
			}
			else if (line == "vt") {
				for (int i = 0; i < 2; i++) {
					file >> line;
					istringstream(line) >> Daux.data[i];
				}
				vt.push_back(Daux);
			}
			else if (line == "f") {
				getline(file, line, '/');
				istringstream(line) >> TDaux.data[0].data[0];
				getline(file, line, ' ');
				istringstream(line) >> TDaux.data[0].data[1];

				getline(file, line, '/');
				istringstream(line) >> TDaux.data[1].data[0];
				getline(file, line, ' ');
				istringstream(line) >> TDaux.data[1].data[1];

				getline(file, line, '/');
				istringstream(line) >> TDaux.data[2].data[0];
				getline(file, line);
				istringstream(line) >> TDaux.data[2].data[1];
				
				f.push_back(TDaux);
			}
			else
				getline(file, line);
		}
		file.close();
	}


	~Objeto() {
		eraseData();
	}

};




#endif