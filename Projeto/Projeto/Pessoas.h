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
	short duração;
};

/*struct grupo {
	short num;
	pessoa *lista;
	short tam;
};
grupo *gru;

void criaGrupo(string *pnomes, string *unomes, string *cursos, short ngrupo);
void criaAluno(pessoa *p, string pnome, string unome, string curso);
void  criaStaff(pessoa *p, string pnome, string unome);/*
void  escrevePessoa(pessoa * p);*/