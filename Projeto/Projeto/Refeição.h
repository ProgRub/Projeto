#pragma once
#include<iostream>
#include<locale>
#include<string>
using namespace std;

struct LLRefeições {
	struct refeição
	{
		string entrada;
		string pratoMain;
		float custo;
		refeição*seguinte;
	};
	refeição*atual;//ou última
	refeição*primeira;
};

void novaMeal(LLRefeições *pratos);
bool listaVaziaRefeições(LLRefeições*ll);
void insereFimRefeições(LLRefeições* ll, LLRefeições::refeição *r);
void escreveMeal(LLRefeições*ll);
void escreveTodasRefeições(LLRefeições*ll);