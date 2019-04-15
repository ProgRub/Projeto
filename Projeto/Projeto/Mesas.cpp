#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
using namespace std;

refeição* novaMeal() {//vai receber os dados do utilizador para uma nova refeição
	cout << "***** REFEIÇÃO NOVA *****\nA cantina EDA necessita de uma nova refeição\n\t1. Introduza a entrada:" << endl;
	refeição *meal = new refeição();
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o preço:" << endl;
	cin >> meal->custo;
	return meal;
}

string* escreveMeal(refeição *r) {//escreve a refeição atual, retorna um array de strings para guardar-se para a possível gravação de dados
	string *aux1 = new string(r->entrada);
	string *aux2 = new string(r->pratoMain);
	cout << "Refeição atual:\n\tEntrada: " << *aux1 << "\n\tPrato Principal: " << *aux2 << "\n\tCusto:" << r->custo << "€\n";
	string *FIM = new string[7];
	FIM[0] = "Refeição atual:\n\tEntrada: ";
	FIM[1] = *aux1;
	FIM[2] = "\n\tPrato Principal: ";
	FIM[3] = *aux2;
	FIM[4] = "\n\tCusto:";
	FIM[5] = to_string(r->custo);
	FIM[6] = "€\n";
	delete aux1, aux2;
	return FIM;
}

short* criaCantina() {//vai obter o tamanho da cantina e gerar tamanhos de mesas até a cantina estar preenchida, tamanhos guardados num vetor
	short *TCANTINA = new short(rand() % 21 + 30);
	short *t = new short();
	short *aux = new short[25];
	short *itera = new short(0);
	while (*t < *TCANTINA) {
		short *TMESA = new short(rand() % 4 + 2);
		*t += *TMESA;
		aux[(*itera)++] = *TMESA;
		if (*TCANTINA - *t <= 1 && *TCANTINA != *t) {//quando isto acontece, nenhuma mesa poderá preencher o último espaço ou já ultrapassamos o tamanho da cantina, por isso faz-se um "reset", "apaga-se" a mesa que provocou isto e tenta-se outra vez
			*t -= *TMESA;
			(*itera)--;
		}
		delete TMESA;
	}
	short *vtamMesas = copiaVetor(aux, *itera);
	delete itera, TCANTINA, t;
	delete[]aux;
	return vtamMesas;
}

mesa* criaMesas(short *vtamMesas) {//vai criar as mesas da cantina com o vetor que contem os tamanhos das mesas obtidos em criaCantina
	mesa *m = new mesa();
	short *num = new short(1);
	short *itera = new short(0);
	short *n = new short(comprimentoVetor(vtamMesas));
	mesa* vMesas = new mesa[*n];
	while (*itera < *n) {
		m->numMesa = *num;
		m->tamanho = vtamMesas[*itera];
		pessoa *sit = new pessoa[*itera];
		m->sentados = sit;
		guardaVetorMesas(m,vMesas, *n);
		(*itera)++;
	}
	return vMesas;
}

void guardaVetorMesas(mesa* m, mesa* vetor, short tam) {
	short*i = new short(0);
	for (*i; *i < tam; (*i)++) {
		vetor[*i] = *m;
	}
}