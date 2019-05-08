#pragma once
#include <string>
#include "Pessoas.h"
#include "Refei��o.h"
using namespace std;

struct LLMesas {
	struct mesa
	{
		int numMesa;
		int capacidade;
		LLPessoas* sentados;
		int numSentados;
		mesa*seguinte;
	};
	mesa*primeira;
	mesa*iterator;
	mesa*ultima;
};

bool listaVaziaCantina(LLMesas*ll);
void insereFimMesas(LLMesas* ll, LLMesas::mesa *m);
void criaCantina(LLMesas*ll);
void escreveCantina(LLMesas*ll);
void inserePessoasMesa(LLMesas::mesa*m, LLPessoas*fila);
void preencheCantina(LLMesas *cantina, LLPessoas*fila, LLRefei��es*r, LLPessoas*removidos);/*
void removeDura��o(mesa **cantina);
void retiraEmergPessoa(mesa **cantina, pessoa**removidos, int tamAcabados, refei��o *r);
void retiraEmergGrupo(mesa **cantina, pessoa**removidos, int tamAcabados, refei��o *r);
void removeDura��o(mesa **cantina);
void removeAcabados(mesa **cantina, pessoa** removidos, int tamAcabados, refei��o*r);
void adicionaVetorAcabados(pessoa**removidos, pessoa*p, int tam, refei��o*r);
void ordenaAlfabeticamenteUltNome(mesa**cantina, pessoa**fila, pessoa**acabados, int pessoasNaCantina, int pessoasNaFila, int pessoasAcabados);
int contaPessoasCantina(mesa**cantina);
int contaPessoasFila(pessoa**fila);
int contaAcabados(pessoa**acabados);
void mergeSortAlfabeticamenteUltNome(pessoa**sistema, int tam);
void mergeUltNome(pessoa**left, pessoa**right, pessoa**sistema, int n_left, int n_right, int tam);
void adicionaVetorRemovidos(pessoa**removidos, pessoa*p, int tam);*/
void removeSemDinheiro(LLPessoas*fila, LLRefei��es *r, LLPessoas*removidos);
void removeSemDinheiroPessoa(LLPessoas*fila, LLPessoas*removidos, int posiPessoa, int numDepGrupo);
void removeSemDinheiroGrupo(LLPessoas*fila, LLPessoas*removidos, int numDepGrupo);/*
void vagasPossiveis(int*vagasPossiveis, pessoa*p, mesa**cantina, int k, int vagas);
void mudaNome(mesa**cantina, pessoa**fila, int tamFila);
void editaDura��o(mesa** cantina, pessoa**fila, int tamFila);
void retiraTodaAGenteCantina(mesa**cantina);*/