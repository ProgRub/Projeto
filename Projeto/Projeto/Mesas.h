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
struct refei��o
{
	string entrada;
	string pratoMain;
	float custo;
};

refei��o* novaMeal();
string* escreveMeal(refei��o *r);
mesa* criaMesas(short *vtamMesas);
short* criaCantina();
void guardaVetorMesas(mesa* m, mesa* vetor, short tam);