#pragma once
#include <string>
using namespace std;
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
	short numDepartamentoOuGrupo;
	short tamanho;
	float plafond;
	aluno membro_aluno;
	staff membro_staff;
	short duração;
};

pessoa* criaPessoa(string *pnomes, string *unomes, string cursos, short dura, bool alunoOuNao, bool especialOuNao); 
pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos);
void escrevePessoa(pessoa *p); 
pessoa** preencheFila(pessoa**fila, string* pnomes, string*unomes, string*cursos);
void escreveFila(pessoa**fila);
void alterarPlafond(int n, pessoa**fila);
void removePobres(pessoa *fila, refeição *r);
void ordenaAlfabeto(mesa* cantina, pessoa* fila);