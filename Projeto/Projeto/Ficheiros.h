#pragma once
#include <string>
#include"Refeição.h"
#include"Mesas.h"
#include"Pessoas.h"
using namespace std;

void guardaFicheiros(string* Lista, string nome);
int numLinhas(string nome_ficheiro);
void limpaLLPessoas(LLPessoas*ll);
void gravaPessoaRemovidos(LLPessoas::pessoa * p);
void gravaLLPessoas(LLPessoas * ll, const char*NomeDoFicheiro);
void gravaRefeicoes(LLRefeições * ref);
void gravaCantina(LLMesas* cantina);
void gravaRemovidos(nóRemovidos* raiz);
void carregaPessoa(string PriNome, string UltNome, string AlunoOuNao, string DepGru, string Curso, string numAluFunc, string duracao, string plaf, string tamGrupo, LLPessoas::pessoa*p, LLReserva*reserva);
void carregaLLPessoas(LLPessoas* fila, LLReserva*reserva, const char*NomeDoFicheiro);
nóRemovidos* carregaRemovidos(nóRemovidos* arvoreRemovidos, LLReserva*reserva, const char*NomeDoFicheiro);
void limpaCantina(LLMesas*cantina);
void carregaCantina(LLMesas* cantina, int numMesas, LLReserva*reserva, const char*NomeDoFicheiro);
void limpaRefeições(LLRefeições*r);
void carregaRefeições(LLRefeições * r, const char*NomeDoFicheiro);
int contaCantina(const char*NomeDoFicheiro);