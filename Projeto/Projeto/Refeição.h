#pragma once
#include<iostream>
#include<locale>
#include<string>
using namespace std;

struct LLRefei��es {
	struct refei��o
	{
		string entrada;
		string pratoMain;
		float custo;
		refei��o*seguinte;
	};
	refei��o*atual;//ou �ltima
	refei��o*primeira;
};

void novaMeal(LLRefei��es *pratos);
bool listaVaziaRefei��es(LLRefei��es*ll);
void insereFimRefei��es(LLRefei��es* ll, LLRefei��es::refei��o *r);
void escreveMeal(LLRefei��es*ll);
void escreveTodasRefei��es(LLRefei��es*ll);