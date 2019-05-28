#include "Refei��o.h"
#include<iostream>
#include<locale>
#include<string>
using namespace std;

void novaMeal(LLRefei��es *pratos) {//vai receber os dados do utilizador para uma nova refei��o
	LLRefei��es::refei��o *meal = new LLRefei��es::refei��o();
	cout << "***** REFEI��O NOVA *****" << endl << "A cantina EDA necessita de uma nova refei��o" << endl << "\t1. Introduza a entrada:" << endl;
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o pre�o:" << endl;
	cin >> meal->custo;
	insereFimRefei��es(pratos, meal);
}

bool listaVaziaRefei��es(LLRefei��es*ll) {
	if (ll->primeira != NULL) {
		return false;
	}
	return true;
}

void insereFimRefei��es(LLRefei��es* ll, LLRefei��es::refei��o *r) {
	r->seguinte = NULL;
	if (!listaVaziaRefei��es(ll)) {
		ll->atual->seguinte = r;
		ll->atual = r;
		return;
	}
	ll->primeira = r;
	ll->atual = r;
	return;
}


void escreveMeal(LLRefei��es*ll) {//escreve a refei��o atual
	cout << "Refei��o atual:\n\tEntrada: " << ll->atual->entrada << "\n\tPrato Principal: " << ll->atual->pratoMain << "\n\tCusto:" << ll->atual->custo << " EUR" << endl << endl;
}

void escreveTodasRefei��es(LLRefei��es*ll) {
	LLRefei��es::refei��o*itera = ll->primeira;
	int i = 1;
	while (itera != NULL) {
		cout << i++ << "� refei��o:\n\tEntrada: " << itera->entrada << "\n\tPrato Principal: " << itera->pratoMain << "\n\tCusto:" << itera->custo << " EUR" << endl << endl;
		itera = itera->seguinte;
	}
	delete itera;
}