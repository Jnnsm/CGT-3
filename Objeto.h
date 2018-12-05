#ifndef OBJETO_H__
#define OBJETO_H__

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;

/* Implementa��o de uma fun��o split para dividir umas string */

vector<string> split(string a, string b) {

	string buff{ "" };
	vector<string> v;

	for (auto n : a)
		for (auto m : b) {
			if (n != m && n != '\n') buff += n;
			else if (n == m && buff != "") { v.push_back(buff); buff = ""; }
		}
	
	if (buff != "") v.push_back(buff);

	return v;
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

	Duo() {

	}
	Duo(T p, T s) {
		altera(p, s);
	}

	void altera(T p, T s) {
		data[0] = p;
		data[1] = s;
	}

};

/* Classe para vari�veis triplas */

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

/* Classe para vari�veis quadruplas */

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
	/* Vari�veis relacionadas com o objeto */
	Quad<double> rgba;
	Trio<double> translate;
	Quad<double> rotate;
	Trio<double> scale;
	bool visible;

	/* Vari�veis relacionadas com a textura */
	unsigned char * img;
	int width, height, channels;
	GLuint t;

	/* Vari�veis relacionadas com o arquivo */
	string name;
	string mtl;
	string texImage;

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
		rgba.altera(0, 0, 0, 1);
		t = 0;
		texImage = "";
		width = height = channels = 0;
		img = (unsigned char *)"";
		mtl = "";
		//stbi_image_free(img);
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

	void getImageFromMtl() {
		fstream file;
		string line;
		vector<string> aux;
		file.open(mtl.c_str(), fstream::in | fstream::binary);
		
		if (!file.good())
			throw 1;

		while (file >> line) {
			if (line == "map_Kd") {
				getline(file, line);
				aux = split(line, " ");
				texImage = aux.at(aux.size() - 1);
				cout << texImage << endl;
			}
		}
		
		img = stbi_load(texImage.c_str(), &width, &height, &channels, 0);

		glGenTextures(1, &t);
		glBindTexture(GL_TEXTURE_2D, t);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, img);
	}

	void read(string fileName) {

		/* Vari�veis para auxilio do preenchimento */
		fstream file;
		string line;
		vector<string> aux;


		/* Vari�veis que guardam os valores do arquivo enquanto s�o lidas */

		Trio<double> Taux(0, 0, 0);
		Duo<double> Daux(0, 0);
		Trio<Trio<double>> TDaux(Trio<double>(0, 0, 0), Trio<double>(0, 0, 0), Trio<double>(0, 0, 0));
		string linePiece = "";
		stringstream ssPiece;

		file.open(fileName.c_str(), fstream::in | fstream::binary);

		/* Checa se o arquivo existe de fato */
		if (!file.good())
			throw 1;
		while (file >> line) {
			if (line == "mtllib") {
				file >> line;
				mtl = split(line, " ").at(0);
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

				int i = 0, j = 0;
				TDaux.altera(Trio<double>(0, 0, 0), Trio<double>(0, 0, 0), Trio<double>(0, 0, 0));
				while (i < 3 && file >> line) {

					ssPiece.str("");
					ssPiece.clear();
					ssPiece.str((line + "/"));
					j = 0;
					while (j < 3 && getline(ssPiece, linePiece, '/')) {
						istringstream(linePiece) >> TDaux.data[i].data[j];
						if (TDaux.data[i].data[j] < 0)
							TDaux.data[i].data[j] = v.size() + TDaux.data[i].data[j];
						j++;
					}
					i++;

				}
				f.push_back(TDaux);
			}
			else
				getline(file, line);
		}
		file.close();

		if(mtl != "")
			getImageFromMtl();
	}


	~Objeto() {
		eraseData();
	}

};



#endif