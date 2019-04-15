#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

pessoa* criaPessoa(string *pnomes, string *unomes, string curso, short dura, bool alunoOuNao, bool especialOuNao) {
	pessoa *p = new pessoa();
	int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
	short *GRUPOIDDEPART = new short(rand() % 401 + 100);
	int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
	short *RETIRAPNOME = new short(rand() % 44);
	short *RETIRAUNOME = new short(rand() % 97);
	float *PLAF = new float(rand() % 100 + 1);
	p->priNome = pnomes[*RETIRAPNOME];
	p->ultNome = unomes[*RETIRAUNOME];
	p->plafond = *PLAF;
	p->duração = dura;
	if (alunoOuNao) {
		p->membro_aluno.curso = curso;
		p->membro_aluno.num = *NUMALUNO;
	}
	else {
		p->membro_staff.numDepartamento = *GRUPOIDDEPART;
		p->membro_staff.numFuncionario = *NUMSTAFF;
	}
	delete RETIRAPNOME, RETIRAUNOME, PLAF, NUMSTAFF, GRUPOIDDEPART;
	return p;
}

grupo* criaGrupo(string *pnomes, string *unomes, string*cursos, short n) {
	grupo *g = new grupo();
	g->num = n;
	short *TAMANHO = new short(rand() % 10 + 1);
	pessoa*l = new pessoa[*TAMANHO];
	g->tam = *TAMANHO;
	g->lista = l;
	short *itera = new short(0);
	short *RETIRACURSO = new short(rand() % 19);
	short *DURAÇÃOMEAL = new short(rand() % 4 + 2);
	bool *alea = new bool(rand() % 2);
	short *PROBESP = new short(rand() % 100 + 1);
	bool *esp = new bool();
	if (*PROBESP > 15 && *PROBESP <= 20) {
		*esp = true;
	}
	else {
		*esp = false;
	}
	cout << *esp << endl;
	if (*esp) {
		g->tam = 1;
		pessoa*k = new pessoa[1];
		pessoa*p = criaPessoa(pnomes, unomes, cursos[*RETIRACURSO], *DURAÇÃOMEAL, *alea, *esp);
		k[0] = *p;
		g->lista = k;
		cout << g->lista[*itera].duração << "\t" << g->lista[*itera].membro_aluno.num << "\n";
	}
	else {
		for (*itera; *itera < g->tam; (*itera)++) {
			pessoa*p = criaPessoa(pnomes, unomes, cursos[*RETIRACURSO], *DURAÇÃOMEAL, *alea, *esp);
			g->lista[*itera] = *p;
			cout << g->lista[*itera].duração << "\t" << g->lista[*itera].membro_staff.numFuncionario << "\n";
		}
	}
	delete RETIRACURSO, itera;
	delete TAMANHO;
	return g;
}
/*
void preencherGrupo(string *pnomes, string *unomes, string*cursos, grupo*g) {
	short *itera = new short(0);
	short *RETIRACURSO = new short(rand() % 19);
	short *DURAÇÃOMEAL = new short(rand() % 4 + 2);
	bool *alea = new bool(rand()% 2);
	for (*itera; *itera < g->tam;(*itera)++) {
		pessoa*p = criaPessoa(pnomes, unomes, cursos[*RETIRACURSO], *DURAÇÃOMEAL , *alea, *esp);
		g->lista[*itera] = *p;
		cout << g->lista[*itera].duração << "\t" << g->lista[*itera].membro_staff.numFuncionario<< "\n";
	}
	delete RETIRACURSO, itera;
}
*/
void escrevePessoa(pessoa *p) {

}