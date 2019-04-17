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

pessoa* criaPessoa(string pnome, string unome, string curso, short dura, short idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao);
pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos);
void escrevePessoa(pessoa *p); 
void criaFila(pessoa**fila, short tam);
pessoa** preencheFila(pessoa**fila, string* pnomes, string*unomes, string*cursos);
void escreveFila(pessoa**fila, short tam);
void alterarPlafond(pessoa**fila);
//void removePobres(pessoa *fila, refeição *r);
//void ordenaAlfabeto(mesa* cantina, pessoa* fila);