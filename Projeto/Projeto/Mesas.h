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
struct refeição
{
	string entrada;
	string pratoMain;
	float custo;
};

refeição* novaMeal();
string* escreveMeal(refeição *r);
mesa criaMesas(short *vtamMesas);
short* criaCantina();