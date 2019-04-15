#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

grupo * criaGrupo(string *pnomes, string *unomes, string *cursos, short ngrupo) {
	grupo *g = new grupo();
	short *TAMANHO = new short(rand() % 10 + 1);
	pessoa * l = new pessoa[*TAMANHO];
	short *ALUNOouSTAFF = new short(rand() % 2 + 1);
	short *i = new short(0);
	if (*ALUNOouSTAFF == 1) {
		pessoa* p = new pessoa();
		float *PLAF = new float(rand() % 100 + 1);
		short *DURA��OMEAL = new short(rand() % 4 + 2);
		p->plafond = *PLAF;
		p->dura��o = *DURA��OMEAL;
		short *RETIRACURSO = new short(rand() % numLinhas("cursos.txt"));
		while (*i < *TAMANHO) {
			short *RETIRAPNOME = new short(rand() % numLinhas("primeiro_nome.txt"));
			short *RETIRAUNOME = new short(rand() % numLinhas("ultimo_nome.txt"));
			criaAluno(p, pnomes[*RETIRAPNOME], pnomes[*RETIRAUNOME], pnomes[*RETIRACURSO]);
			l[*i] = *p;
			delete RETIRAPNOME, RETIRAUNOME;
		}
		delete PLAF, DURA��OMEAL, RETIRACURSO, p;
	}
	else {
		pessoa* p = new pessoa();
		float *PLAF = new float(rand() % 100 + 1);
		short *DURA��OMEAL = new short(rand() % 4 + 2);
		p->plafond = *PLAF;
		p->dura��o = *DURA��OMEAL;
		while (*i < *TAMANHO) {
			short *RETIRAPNOME = new short(rand() % numLinhas("primeiro_nome.txt"));
			short *RETIRAUNOME = new short(rand() % numLinhas("ultimo_nome.txt"));
			criaStaff(p, pnomes[*RETIRAPNOME], pnomes[*RETIRAUNOME]);
			l[*i] = *p;
			delete RETIRAPNOME, RETIRAUNOME;
		}
		delete PLAF, DURA��OMEAL, p;
	}
	g->num = ngrupo;
	g->tam = *TAMANHO;
	g->lista = l;
	return g;
}

pessoa * criaAluno(pessoa * p,string pnome, string unome, string curso) {
	pessoa::aluno *a = new pessoa::aluno();
	int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
	short *PROBESP = new short(rand() % 100 + 1);
	p->membro_aluno = a;
	p->membro_aluno->curso = curso;
	p->membro_aluno->num = *NUMALUNO;
	if (*PROBESP >= 15 && *PROBESP <= 19) {
		p->membro_aluno->especialOuNao = true;
	}
	else {
		p->membro_aluno->especialOuNao = false;
	}
	return p;
}

pessoa * criaStaff(pessoa * p, string pnome, string unome) {
	pessoa::staff*s = new pessoa::staff();
	short *GRUPOIDDEPART = new short(rand() % 401 + 100);
	int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
	cout << *NUMSTAFF << endl;
	p->membro_staff = s;
	p->membro_staff->numDepartamento = *GRUPOIDDEPART;
	p->membro_staff->numFuncionario = *NUMSTAFF;
	return p;
}