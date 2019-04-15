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
	float plafond;
	aluno membro_aluno;
	staff membro_staff;
	short duração;
};

pessoa* criaPessoa(string *pnomes, string *unomes, string cursos, short dura, bool alunoOuNao, bool especialOuNao);
pessoa* criaGrupo(string *pnomes, string *unomes, string*cursos, short n);
void escrevePessoa(pessoa *p);