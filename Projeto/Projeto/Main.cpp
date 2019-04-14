#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<locale>
#include<string>
#include<fstream>
using namespace std;

int main() {
	locale::global(locale(""));
	srand(time(NULL));
	pessoa * fila = new pessoa[50];
	short *DURAÇÃOMEAL = new short(rand() % 4 + 2);
	short *RETIRAPNOME = new short(rand() % 44);
	short *RETIRAUNOME = new short(rand() % 97);
	short *RETIRACURSO = new short(rand() % 19);
	short *CAPGRUPO = new short(rand() % 10 + 1);
	short *GRUPOIDDEPART = new short(rand() % 401 + 100);
	short *PROBESP = new short(rand() % 100 + 1);
	float *PLAF = new float(rand() % 100 + 1);
	cout << "\t\t\t\t\t Cantina EDA\n";
	string *PNOMES = new string[numLinhas("primeiro_nome.txt")];
	guardaFicheiros(PNOMES, "primeiro_nome.txt");
	string *UNOMES = new string[numLinhas("ultimo_nome.txt")];
	guardaFicheiros(UNOMES, "ultimo_nome.txt");
	string *CURSOS = new string[numLinhas("cursos.txt")];
	guardaFicheiros(CURSOS, "cursos.txt");
	criaCantina();
	system("pause");
	return 0;
}