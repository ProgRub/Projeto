#pragma once
#include <string>
#include "Pessoas.h"
using namespace std;
struct mesa
{
	int tamanho;
	int numMesa;
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
mesa criaMesas(short *vtamMesas);
short* criaCantina();