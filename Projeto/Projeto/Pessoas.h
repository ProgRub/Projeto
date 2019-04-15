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
	aluno *membro_aluno;
	staff *membro_staff;
};