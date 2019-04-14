#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void guardaFicheiros(string* Lista, string nome_ficheiro) {//vai ler um ficheiro com nome "nome_ficheiro" e guardar as linhas que l� no array Lista fornecida nos argumentos
	fstream file(nome_ficheiro,ios::in);
	string *line = new string();
	short *i = new short(0);
	if (file.is_open()) {
		while (getline(file, *line)) {
			Lista[(*i)++] = *line;
		}
	}
	file.close();
	delete i, line;
}

short numLinhas(string nome_ficheiro) {//vai contar o n� de linhas de um ficheiro fornecido, para os vetores que guardarem strings n�o desperdi�arem mem�ria
	fstream ficheiro(nome_ficheiro,ios::in);
	short *conta = new short(0);
	if (ficheiro.is_open()) {
		string aux;
		while (getline(ficheiro, aux)) {
			(*conta)++;
		}
		ficheiro.close();
		return (*conta);
	}
	else {
		return -1;
	}
}

void escreveFicheiro(string *output,short tamanho, bool primeiraVez) { // vai escrever no ficheiro "cantina.txt" o vetor de strings que recebe como argumento
	if (!primeiraVez) {
		fstream ficheiro("cantina.txt", ios::out | ios::app);
		short*i = new short(0);
		if (ficheiro.is_open()) {
			while (*i < tamanho) {
				ficheiro << output[(*i)++];
			}
		}
		ficheiro.close();
		delete i;
	}
	else {
		fstream ficheiro("cantina.txt", ios::out);
		short*i = new short(0);
		if (ficheiro.is_open()) {
			while (*i < tamanho) {
				ficheiro << output[(*i)++];
			}
		}
		ficheiro.close();
		delete i;
	}
}

short* copiaVetor(short* aux, short tamanho) {
	short *vetor = new short[tamanho];
	for (int*i = new int(0); *i < tamanho; (*i)++) {
		vetor[*i] = aux[*i];
	}
	return vetor;
}