#pragma once
#include <string>
#include "Pessoas.h"
using namespace std;
struct mesa
{
	short numMesa;
	short tamanho;
	pessoa**sentados;
	short numSentados;
	short totalMesas;

};
struct refei��o
{
	string entrada;
	string pratoMain;
	float custo;
};

refei��o* novaMeal();
string* escreveMeal(refei��o *r);
mesa** criaMesas(short *vtamMesas, short pos);
mesa** criaCantina();
void escreveMesa(mesa *m);
void preencheMesa(mesa *m, pessoa**fila, short *k);
void testeMesas(mesa *m, pessoa *p, short it);
void preencheCantina(mesa**cantina, pessoa**fila);
void escreveCantina(mesa**cantina);
void nullsNoFim(pessoa**fila, short beg,short end);
void removePessoa(pessoa **fila, refei��o *r);
void removeDura��o(mesa **cantina);