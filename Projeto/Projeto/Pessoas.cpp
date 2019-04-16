#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

pessoa* criaPessoa(string *pnomes, string *unomes, string curso, short dura, bool alunoOuNao, bool especialOuNao) {
	pessoa *p = new pessoa;
	int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
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
		p->membro_aluno.especialOuNao = especialOuNao;
	}
	else {
		p->membro_staff.numFuncionario = *NUMSTAFF;
	}
	delete RETIRAPNOME, RETIRAUNOME, PLAF, NUMSTAFF;
	return p;
}

pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos) {
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
	if (*esp) {
		pessoa **k = new pessoa*[1];
		pessoa *p = criaPessoa(pnomes, unomes, cursos[*RETIRACURSO], *DURAÇÃOMEAL, true, *esp);
		short *GRUPOIDDEPART = new short(rand() % 401 + 100);
		p->numDepartamentoOuGrupo = *GRUPOIDDEPART;
		p->tamanho = 1;
		k[0] = p;
		delete p;
		return k;
	}
	else {
		short *TAMANHO = new short(rand() % 10 + 1);
		pessoa **l = new pessoa*[*TAMANHO];
		short *itera = new short(0);
		short *GRUPOIDDEPART = new short(rand() % 401 + 100);
		for (*itera; *itera < *TAMANHO; (*itera)++) {
			pessoa*p = criaPessoa(pnomes, unomes, cursos[*RETIRACURSO], *DURAÇÃOMEAL, *alea, *esp);
			p->numDepartamentoOuGrupo = *GRUPOIDDEPART;
			if (*itera == 0) {
				p->tamanho = *TAMANHO;
			}
			l[*itera] = p;
			escrevePessoa(l[*itera]);
			escrevePessoa(l[0]);
		}
		delete TAMANHO, itera;
		return l;
	}
	delete RETIRACURSO, esp;
}

void escrevePessoa(pessoa *p) {
	if (p->membro_aluno.num > 0) {
		if (!p->membro_aluno.especialOuNao) {
			cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << "€\n";
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num<< ", duração " << p->duração << ", " << p->plafond << "€\n";
		}
	}
	else {
		cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << ", duração " << p->duração << ", " << p->plafond << "€\n";
	}
}
/*
void escrevePessoa(pessoa p) {
	if ((&p)->membro_aluno.num > 0) {
		if (!(&p)->membro_aluno.especialOuNao) {
			cout << (&p)->priNome << " " << (&p)->ultNome << ", Estudante, Grupo " << (&p)->numDepartamentoOuGrupo << ", " << (&p)->membro_aluno.curso << ", " << (&p)->membro_aluno.num << ", duração " << (&p)->duração << ", " << (&p)->plafond << "€\n";
		}
		else {
			cout << (&p)->priNome << " " << (&p)->ultNome << ", Estudante (especial), Grupo " << (&p)->numDepartamentoOuGrupo << ", " << (&p)->membro_aluno.curso << ", " << (&p)->membro_aluno.num << ", duração " << (&p)->duração << ", " << (&p)->plafond << "€\n";
		}
	}
	else {
		cout << (&p)->priNome << " " << (&p)->ultNome << ", Staff, Departamento " << (&p)->numDepartamentoOuGrupo << ", " << (&p)->membro_staff.numFuncionario << ", duração " << (&p)->duração << ", " << (&p)->plafond << "€\n";
	}
}*/

pessoa** preencheFila(pessoa**fila, string* pnomes, string*unomes, string*cursos) {
	short*i = new short(0);
	short*j = new short(0);
	pessoa**g = criaGrupo(pnomes, unomes, cursos);
	short*tam = new short(g[0]->tamanho);
	while(*i<50) {
		if (*j < *tam) {
			fila[(*i)] = g[(*j)];
			(*j)++;
		}
		else {
			g = criaGrupo(pnomes, unomes, cursos);
			*tam = g[0]->tamanho;
			*j = 0;
		}
		(*i)++;
	}
	delete i, j;
	return fila;
}

void escreveFila(pessoa**fila) {
	short*i = new short(0);
	while (*i < 50) {
		escrevePessoa(fila[(*i)]);
		(*i)++;
	}
}

void alterarPlafond(int n, pessoa**fila) {
	short i = 0;
	if (fila->membro_aluno.num > 0) {
		cout << "Plafond inicial: " << fila->plafond << "€" << endl;
		cout << "Insira um novo plafond: ";
		cin >> fila->plafond;
		cout << "Plafond atual: " << fila->plafond << "€" << endl;
		cout << fila->membro_aluno.num;
	}
	else {
		cout << "Plafond inicial: " << fila->plafond << "€" << endl;
		cout << "Insira um novo plafond: ";
		cin >> fila->plafond;
		cout << "Plafond atual: " << fila->plafond << "€" << endl;
		cout << fila->membro_staff.numFuncionario;
	}
}