#pragma once
#include <string>
#include "Pessoas.h"
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
void preencheCantina(LLMesas *cantina, LLPessoas*fila, LLRefeições*r);
void removeDuração(LLMesas*cantina);
void retiraEmergPessoa(LLMesas*cantina, LLPessoas*acabados, LLRefeições *r);
void retiraEmergGrupo(LLMesas*cantina, LLPessoas*acabados, LLRefeições *r);
void removeAcabados(LLMesas*cantina, LLPessoas* acabados, LLRefeições*r);
void insereFimPessoasAcabadas(LLPessoas* ll, LLPessoas::pessoa *p, LLRefeições*r);
void ordenaAlfabeticamenteUltNome(LLMesas*cantina, LLPessoas*fila, LLPessoas*acabados);
int contaPessoasCantina(LLMesas*cantina);
void vagasPossiveis(int*vagasPossiveis, LLPessoas::pessoa*p, LLMesas*cantina, int vagas);
void mudaNome(LLMesas*cantina, LLPessoas*fila);
void editaDuração(LLMesas* cantina, LLPessoas*fila);
LLMesas::mesa** converteLLvetorMesas(LLMesas*cantina);
void SelectionSortMesasNumSentados(LLMesas::mesa**cantina, int tam);
void apresentaIndividuo(LLMesas*cantina, LLPessoas*fila);
void apresentaCursoOuDep(LLMesas*cantina, LLPessoas*fila, string *CURSOS);
void mudaCurso(LLMesas*cantina, LLPessoas*fila, string* CURSOS);
void PobreRicoEMedia(LLMesas*cantina, LLPessoas*fila);
void lotaria(LLMesas*cantina, LLPessoas*fila, bool *háVencedor, int*premio, int*aumenta);