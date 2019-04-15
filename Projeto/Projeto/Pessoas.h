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
		short numDepartamento;
	};
	string priNome;
	string ultNome;
	float plafond;
	aluno membro_aluno;
	staff membro_staff;
	short duração;
};

struct grupo {
	short num;
	pessoa *lista;
	short tam;
};

pessoa* criaPessoa(string *pnomes, string *unomes, string cursos, short dura, bool alunoOuNao, bool especialOuNao);
grupo* criaGrupo(string *pnomes, string *unomes, string*cursos, short n);
void preencherGrupo(string *pnomes, string *unomes, string*cursos, grupo*g);
void escrevePessoa(pessoa *p);