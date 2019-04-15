#pragma once
#include <string>
#include "Pessoas.h"
using namespace std;
struct mesa
{
	short numMesa;
	short tamanho;
	pessoa *sentados;
};
struct refeição
{
	string entrada;
	string pratoMain;
	float custo;
};

refeição* novaMeal();
string* escreveMeal(refeição *r);
mesa* criaMesas(short *vtamMesas);
short* criaCantina();
void guardaVetorMesas(mesa* m, mesa* vetor, short tam);