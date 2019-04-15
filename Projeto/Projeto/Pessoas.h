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
		short numFuncionario;
		short numDepartamento;
	};
	string priNome;
	string ultNome;
	float plafond;
	pessoa* grupo;
	aluno *membro_aluno;
	staff *membro_staff;
	short duração;
};

pessoa* criaPessoas(string* pnomes, string* unomes, string* cursos);