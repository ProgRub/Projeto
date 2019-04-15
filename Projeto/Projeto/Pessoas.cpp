#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void criaPessoa(string* pnomes , string* unomes , string* cursos ) {
	pessoa* p = new pessoa();
	float *PLAF = new float(rand() % 100 + 1);
	short *RETIRAPNOME = new short(rand() % numLinhas("primeiro_nome.txt"));
	short *RETIRAUNOME = new short(rand() % numLinhas("ultimo_nome.txt"));
	short *RETIRACURSO = new short(rand() % numLinhas("cursos.txt"));
	short *ALUNOouSTAFF = new short(rand() % 2 + 1);
	p->priNome = pnomes[*RETIRAPNOME];
	p->ultNome = unomes[*RETIRAUNOME];
	p->plafond = *PLAF;
	if (*ALUNOouSTAFF == 1) {
		pessoa::aluno *a = new pessoa::aluno();
		int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
		short *PROBESP = new short(rand() % 100 + 1);
		p->membro_aluno = a;
		p->membro_aluno->curso = cursos[*RETIRACURSO];
		p->membro_aluno->num = *NUMALUNO;
		if (*PROBESP >= 15 && *PROBESP <= 19) {
			p->membro_aluno->especialOuNao = true;
		}
		else {
			p->membro_aluno->especialOuNao = false;
		}
	}
	else {
		pessoa::staff*s = new pessoa::staff();
		short *GRUPOIDDEPART = new short(rand() % 401 + 100);
		int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
		p->membro_staff = s;
		p->membro_staff->numDepartamento = *GRUPOIDDEPART;
		p->membro_staff->numFuncionario = *NUMSTAFF;
	}
}