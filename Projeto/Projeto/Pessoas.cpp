#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*void  criaGrupo(string *pnomes, string *unomes, string *cursos, short ngrupo) {
	//pessoa::grupo *g = new pessoa::grupo();
	short *TAMANHO = new short(rand() % 10 + 1);
	pessoa * l = new pessoa[*TAMANHO];
	short *ALUNOouSTAFF = new short(1);
	short *i = new short(0);
	pessoa* p = new pessoa();
	float *PLAF = new float(rand() % 100 + 1);
	short *DURAÇÃOMEAL = new short(rand() % 4 + 2);
	p->plafond = *PLAF;
	p->duração = *DURAÇÃOMEAL;
	short *RETIRACURSO = new short(rand() % 19);
		short *RETIRAPNOME = new short(rand() % 44);
		short *RETIRAUNOME = new short(rand() % 97);
		criaAluno(p, pnomes[*RETIRAPNOME], pnomes[*RETIRAUNOME], pnomes[*RETIRACURSO]);
		l[(*i)++] = *p;
		delete RETIRAPNOME, RETIRAUNOME;
	delete PLAF, DURAÇÃOMEAL, RETIRACURSO, p;
		pessoa* p = new pessoa();
		float *PLAF = new float(rand() % 100 + 1);
		short *DURAÇÃOMEAL = new short(rand() % 4 + 2);
		p->plafond = *PLAF;
		p->duração = *DURAÇÃOMEAL;
		while (*i < *TAMANHO) {
			short *RETIRAPNOME = new short(rand() % 44);
			short *RETIRAUNOME = new short(rand() % 97);
			criaStaff(p, pnomes[*RETIRAPNOME], pnomes[*RETIRAUNOME]);
			l[(*i)++] = *p;
			delete RETIRAPNOME, RETIRAUNOME;
		}
		delete PLAF, DURAÇÃOMEAL, p;
}*/
/*
void criaAluno(pessoa * p,string pnome, string unome, string curso) {
	int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
	short *PROBESP = new short(rand() % 100 + 1);
	p->priNome = pnome;
	p->ultNome = unome;
	p->membro_aluno->curso = curso;
	p->membro_aluno->num = *NUMALUNO;
	if (*PROBESP >= 15 && *PROBESP <= 19) {
		p->membro_aluno->especialOuNao = true;
	}
	else {
		p->membro_aluno->especialOuNao = false;
	}
}

void  criaStaff(pessoa * p, string pnome, string unome) {
	short *GRUPOIDDEPART = new short(rand() % 401 + 100);
	int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
	p->membro_staff->numDepartamento = *GRUPOIDDEPART;
	p->membro_staff->numFuncionario = *NUMSTAFF;
}

void  escrevePessoa(pessoa * p) {
	if (!p->alunoOuNao) {
		cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->membro_staff->numDepartamento << ", " << p->membro_staff->numFuncionario << ", duração " << p->duração << ", " << p->plafond << "\n";
	}
	else {
		if (!p->membro_aluno->especialOuNao) {
			cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->gru->num << ", " << p->membro_aluno->num << ", duração " << p->duração << ", " << p->plafond << "\n";
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->gru->num << " (especial), " << p->membro_aluno->num << ", duração " << p->duração << ", " << p->plafond << "\n";
		}
	}
}*/