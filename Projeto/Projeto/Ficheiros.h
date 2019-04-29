#pragma once
#include <string>
#include"Pessoas.h"
#include"Mesas.h"
using namespace std;

void guardaFicheiros(string* Lista, string nome);
int numLinhas(string nome_ficheiro);
int* copiaVetor(int* aux, int tamanho);
void criaVetor(int*res, int tamanho);
void gravaPessoaFila(pessoa * p);
void gravaPessoaAcabados(pessoa * p);
void gravaPessoaRemovidos(pessoa * p);
void gravaPessoaCantina(pessoa * p);
void gravaFila(pessoa**fila, int tam);
void gravaAcabados(pessoa ** acabados, int tam);
void gravaRemovidos(pessoa ** removidos, int tam);
void gravaCantina(mesa**cantina);
void gravaRefeição(refeição*r);
void carregaAluno(string PriNome, string UltNome, string EspecialouNao, string DepGru, string Curso, string numAluFunc, string duracao, string plaf, string tamGrupo, pessoa*p, int*reserva, int tamReserva);
void carregaStaff(string PriNome, string UltNome, string DepGru, string numAluFunc, string duracao, string plaf, string tamGrupo, pessoa*p, int*reserva, int tamReserva);
void carregaFila(pessoa**fila, int tam, int*pos, int*reserva, int tamReserva);
void carregaAcabados(pessoa ** acabados, int tam, int*reserva, int tamReserva);
void carregaRemovidos(pessoa ** removidos, int tam, int*reserva, int tamReserva);
mesa** carregaCantina(mesa**canteen, int numMesas, int*reserva, int tamReserva);
void carregaRefeição(refeição*r);
int contaCantina();
void adicionaReservaNum(int*reserva, int num, int tam);