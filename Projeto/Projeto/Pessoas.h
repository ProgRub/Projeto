#pragma once
#include <string>
#include "Refeição.h"
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

struct nóRemovidos {
	LLPessoas::pessoa* removida;
	nóRemovidos*esquerda;
	nóRemovidos*direita;
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
void limpaReserva(LLReserva*ll);
bool listaVaziaPessoas(LLPessoas*ll);
void inserirInicioPessoas(LLPessoas* ll, LLPessoas::pessoa *p);
void insereFimPessoas(LLPessoas* ll, LLPessoas::pessoa *p);
void insereMeioPessoas(LLPessoas*ll, LLPessoas::pessoa*p, int pos);
LLPessoas::pessoa* removePessoaInicio(LLPessoas*fila);
LLPessoas::pessoa* removePessoaFim(LLPessoas*fila);
LLPessoas::pessoa* removePessoaMeio(LLPessoas*fila, int pos);
LLPessoas::pessoa* consultaPessoa(LLPessoas*fila, int pos);
LLPessoas::pessoa* criaPessoa(string pnome, string unome, string curso, int dura, int idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao);
void preencheFila(LLPessoas*fila, string* pnomes, string*unomes, string*cursos, LLReserva*reserva, bool primeiraVez);
void escreveFila(LLPessoas* fila);
bool listaVaziaReserva(LLReserva*ll);
void insereFimReserva(LLReserva* ll, int num);
void testaGrupoDep(int*num, LLReserva*reserva);
nóRemovidos * novoNó(LLPessoas::pessoa*p);
nóRemovidos* adicionaArvoreRemovidos(nóRemovidos*raiz, LLPessoas::pessoa*p);
int contaNosArvore(nóRemovidos*raiz);
void guardaArvoreVetor(nóRemovidos * raiz, int *pos, LLPessoas::pessoa**guardar);
void limpaArvore(nóRemovidos * raiz);
void imprimeArvoreInfixa(nóRemovidos * raiz);
nóRemovidos* removeSemDinheiro(LLPessoas*fila, LLRefeições *r, nóRemovidos*arvoreRemovidos);
nóRemovidos* removeSemDinheiroPessoa(LLPessoas*fila, nóRemovidos*arvoreRemovidos, int numDepGrupo, int posiPessoa);
nóRemovidos* removeSemDinheiroGrupo(LLPessoas*fila, nóRemovidos*arvoreRemovidos, int numDepGrupo);
void alterarPlafond(LLPessoas*fila);
int contaPessoasFila(LLPessoas*fila);
int contaAcabados(LLPessoas*acabados);
void mergeSortAlfabeticamenteUltNome(LLPessoas::pessoa**sistema, int tam);
void mergeUltNome(LLPessoas::pessoa**left, LLPessoas::pessoa**right, LLPessoas::pessoa**sistema, int n_left, int n_right, int tam);