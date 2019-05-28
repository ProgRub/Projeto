#include "Refeição.h"
#include<iostream>
#include<locale>
#include<string>
using namespace std;

void novaMeal(LLRefeições *pratos) {//vai receber os dados do utilizador para uma nova refeição
	LLRefeições::refeição *meal = new LLRefeições::refeição();
	cout << "***** REFEIÇÃO NOVA *****" << endl << "A cantina EDA necessita de uma nova refeição" << endl << "\t1. Introduza a entrada:" << endl;
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o preço:" << endl;
	cin >> meal->custo;
	insereFimRefeições(pratos, meal);
}

bool listaVaziaRefeições(LLRefeições*ll) {
	if (ll->primeira != NULL) {
		return false;
	}
	return true;
}

void insereFimRefeições(LLRefeições* ll, LLRefeições::refeição *r) {
	r->seguinte = NULL;
	if (!listaVaziaRefeições(ll)) {
		ll->atual->seguinte = r;
		ll->atual = r;
		return;
	}
	ll->primeira = r;
	ll->atual = r;
	return;
}


void escreveMeal(LLRefeições*ll) {//escreve a refeição atual
	cout << "Refeição atual:\n\tEntrada: " << ll->atual->entrada << "\n\tPrato Principal: " << ll->atual->pratoMain << "\n\tCusto:" << ll->atual->custo << " EUR" << endl << endl;
}

void escreveTodasRefeições(LLRefeições*ll) {
	LLRefeições::refeição*itera = ll->primeira;
	int i = 1;
	while (itera != NULL) {
		cout << i++ << "ª refeição:\n\tEntrada: " << itera->entrada << "\n\tPrato Principal: " << itera->pratoMain << "\n\tCusto:" << itera->custo << " EUR" << endl << endl;
		itera = itera->seguinte;
	}
	delete itera;
}