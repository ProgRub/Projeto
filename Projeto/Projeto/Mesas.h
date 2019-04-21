#pragma once
#include <string>
#include "Pessoas.h"
using namespace std;
struct mesa
{
	int numMesa;
	int tamanho;
	pessoa** sentados;
	int numSentados;
	int totalMesas;

};
struct refeição
{
	string entrada;
	string pratoMain;
	float custo;
};

refeição* novaMeal(bool primeiraVez);
void escreveMeal(refeição *r);
mesa** criaMesas(int *vtamMesas, int pos);
mesa** criaCantina();
void preencheCantina(mesa**cantina, pessoa**fila, int *pos, refeição*r, pessoa**removidos, int tamRemovidos);
void escreveCantina(mesa**cantina);
void nullsNoFim(pessoa**fila, int beg, int *end);
void nullsNoFimCantina(pessoa**sentados, int beg, int end);
void removeDuração(mesa **cantina);
void retiraEmergPessoa(mesa **cantina, pessoa**removidos, int tamAcabados, refeição *r);
void retiraEmergGrupo(mesa **cantina, pessoa**removidos, int tamAcabados, refeição *r);
void removeDuração(mesa **cantina);
void removeAcabados(mesa **cantina, pessoa** removidos, int tamAcabados, refeição*r);
void adicionaVetorAcabados(pessoa**removidos, pessoa*p, int tam, refeição*r);
void ordenaAlfabeticamenteUltNome(mesa**cantina, pessoa**fila, pessoa**acabados, int pessoasNaCantina, int pessoasNaFila, int pessoasAcabados);
int contaPessoasCantina(mesa**cantina);
int contaPessoasFila(pessoa**fila);
int contaAcabados(pessoa**acabados);
void mergeSortAlfabeticamenteUltNome(pessoa**sistema, int m);
void merge(pessoa**left, pessoa**right, pessoa**sistema, int n_left, int n_right, int m);
void adicionaVetorRemovidos(pessoa**removidos, pessoa*p, int tam);
void removeSemDinheiro(pessoa**fila, refeição *r, int*pos, pessoa**removidos, int tamRemovidos, int tamEntrada);
void removeSemDinheiroPessoa(pessoa**fila, int*pos, pessoa**removidos, int tamRemovidos, int posiPessoa);
void removeSemDinheiroGrupo(pessoa**fila, int*pos, pessoa**removidos, int tamRemovidos, int numDepGrupo);