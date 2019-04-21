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
	int numDepartamentoOuGrupo;
	int tamanho;
	float plafond;
	aluno membro_aluno;
	staff membro_staff;
	int duração;
};

pessoa* criaPessoa(string pnome, string unome, string curso, int dura, int idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao);
pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos, int*reserva, int tamRes);
void escrevePessoa(pessoa *p);
void criaFila(pessoa**fila, int tam);
void preencheFila(pessoa**fila, string* pnomes, string*unomes, string*cursos, int *pos, int*reserva, int tamRes);
void escreveFila(pessoa**fila, int tam);
void alterarPlafond(pessoa**fila);
void procuraEspecial(pessoa**fila, int tam);
void testaGrupoDep(int*num, int*reserva, int tam);