#pragma once
#include <string>
using namespace std;


struct LLPessoas {
	struct pessoa
	{
		struct aluno
		{
			int num;
			string curso;
			bool especialOuNao;

		};
		struct staff
		{
			int numFuncionario;
		};
		string priNome;
		string ultNome;
		int numDepartamentoOuGrupo;
		int tamanhoGrupo;
		float plafond;
		aluno membro_aluno;
		staff membro_staff;
		int duração;
		pessoa*seguinte;
	};
	pessoa*primeira;
	pessoa*iterator;
	pessoa*ultima;
};

struct LLReserva {
	struct item {
		int num;
		item*seguinte;
	};
	item*primeiro;
	item*ultimo;
};

int comprimento(LLPessoas* ll);
bool listaVaziaPessoas(LLPessoas*ll);
void inserirInicioPessoas(LLPessoas* ll, LLPessoas::pessoa *p);
void insereFimPessoas(LLPessoas* ll, LLPessoas::pessoa *p);
LLPessoas::pessoa* criaPessoa(string pnome, string unome, string curso, int dura, int idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao);
void escrevePessoaFila(LLPessoas::pessoa *p);
void escrevePessoaCompleta(LLPessoas::pessoa *p);
void escrevePessoaCantina(LLPessoas::pessoa *p);
void preencheFila(LLPessoas*fila, string* pnomes, string*unomes, string*cursos, LLReserva*reserva);
void escreveFila(LLPessoas* fila);
bool listaVaziaReserva(LLReserva*ll);
void insereFimReserva(LLReserva* ll, int num);
void testaGrupoDep(int*num, LLReserva*reserva);/*
void escreveOpções(pessoa**v, int tam);
void alterarPlafond(pessoa**fila);
void ordenaAlfabeticamentePriNome(pessoa**removidos, int pessoasRemovidos);
int contaRemovidos(pessoa**removidos);
void mergeSortAlfabeticamentePriNome(pessoa**sistema, int tam);
void mergeRemovidos(pessoa**left, pessoa**right, pessoa**sistema, int n_left, int n_right, int tam); */