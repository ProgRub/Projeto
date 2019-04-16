#pragma once
#include <string>
#include "Pessoas.h"
using namespace std;
struct mesa
{
	short numMesa;
	short tamanho;
	pessoa**sentados;
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
void guardaVetorMesas(mesa* m, mesa** vetor, short tam);
void escreveMesa(mesa *m);
void preencheMesa(mesa *m, pessoa**fila);
void testeMesas(mesa *m, pessoa *p);