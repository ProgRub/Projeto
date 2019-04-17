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
struct refeição
{
	string entrada;
	string pratoMain;
	float custo;
};

refeição* novaMeal();
string* escreveMeal(refeição *r);
mesa** criaMesas(short *vtamMesas, short pos);
mesa** criaCantina();
void escreveMesa(mesa *m);
void preencheMesa(mesa *m, pessoa**fila, short *k);
void testeMesas(mesa *m, pessoa *p, short it);
void preencheCantina(mesa**cantina, pessoa**fila);
void escreveCantina(mesa**cantina);
void nullsNoFim(pessoa**fila, short beg,short end);
void removePessoa(pessoa **fila, refeição *r);
void removeDuração(mesa **cantina);