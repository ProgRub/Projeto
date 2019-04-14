#include"Mesas.h"
#include"Pessoas.h"
#include<iostream>
#include<string>
using namespace std;

refei��o* novaMeal() {//vai receber os dados do utilizador para uma nova refei��o
	cout << "***** REFEI��O NOVA *****\nA cantina EDA necessita de uma nova refei��o\n\t1. Introduza a entrada:" << endl;
	refei��o *meal = new refei��o();
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o pre�o:" << endl;
	cin >> meal->custo;
	return meal;
}

string* escreveMeal(refei��o *r) {//escreve a refei��o atual
	string *aux1 = new string(r->entrada);
	string *aux2 = new string(r->pratoMain);
	string *aux3 = new string(to_string (r->custo));
	cout << "Refei��o atual:\n\tEntrada: " << *aux1 << "\n\tPrato Principal: " << *aux2 << "\n\tCusto:" << *aux3 << "�\n";
	string *FIM = new string[7];
	FIM[0] = "Refei��o atual:\n\tEntrada: ";
	FIM[1] = *aux1;
	FIM[2] = "\n\tPrato Principal: ";
	FIM[3] = *aux2;
	FIM[4] = "\n\tCusto:";
	FIM[5] = *aux3;
	FIM[6] = "�\n";
	return FIM;
}

mesa criaMesas(short *vtm) {//vai criar as mesas da cantina com o vetor que contem os tamanhos das mesas obtidos em criaCantina
	mesa *m = new mesa();
	return *m;
}

short* criaCantina() {//vai obter o tamanho da cantina e gerar tamanhos de mesas at� a cantina estar preenchida, tamanhos guardados num vetor
	short *TCANTINA = new short(rand() % 21 + 30);
	short *t = new short();
	short *vtmesas = new short[25];
	short *itera = new short(0);
	while (*t < *TCANTINA) {
		short *TMESA = new short(rand() % 4 + 2);
		*t += *TMESA;
		vtmesas[(*itera)++] = *TMESA;
		if (*TCANTINA - *t <= 1 && *TCANTINA != *t) {//quando isto acontece, nenhuma mesa poder� preencher o �ltimo espa�o ou j� ultrapassamos o tamanho da cantina, por isso faz-se um "reset", "apaga-se" a mesa que provocou isto e tenta-se outra vez
			*t -= *TMESA;
			(*itera)--;
		}
		delete TMESA;
	}
	for (*itera; *itera < 25; (*itera)++) {
		vtmesas[*itera] = 0;
	}
	delete itera, TCANTINA, t;
	return vtmesas;
}