#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

pessoa* criaPessoa(string pnome, string unome, string curso, short dura, short idOuDepart,  float plafond ,bool alunoOuNao, bool especialOuNao) {
	pessoa *p = new pessoa;
	p->priNome = pnome;
	p->ultNome = unome;
	p->plafond = plafond;
	p->duração = dura;
	p->numDepartamentoOuGrupo = idOuDepart;
	if (alunoOuNao) {
		p->membro_aluno.curso = curso;
		int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
		p->membro_aluno.num = *NUMALUNO;
		p->membro_aluno.especialOuNao = especialOuNao;
		p->membro_staff.numFuncionario = NULL;
		delete NUMALUNO;
	}
	else {
		p->membro_aluno.num = NULL;
		p->membro_aluno.especialOuNao = NULL;
		int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
		p->membro_staff.numFuncionario = *NUMSTAFF;
		delete NUMSTAFF;
	}
	return p;
}

pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos) {
	short *RETIRACURSO = new short(rand() % 19);
	short *DURAÇÃOMEAL = new short(rand() % 4 + 2);
	bool *ALUNOOUNAO = new bool(rand() % 2);
	short *PROBESP = new short(rand() % 100 + 1);
	if (*PROBESP > 15 && *PROBESP <= 20) {
		short *GRUPOIDDEPART = new short(rand() % 401 + 100);
		short *RETIRAPNOME = new short(rand() % 44);
		short *RETIRAUNOME = new short(rand() % 97);
		float *PLAF = new float(rand() % 100 + 1);
		pessoa *p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURAÇÃOMEAL, *GRUPOIDDEPART, *PLAF, true, true);
		pessoa**l = new pessoa*[1];
		p->tamanho = 1;
		l[0] = p;
		delete GRUPOIDDEPART, RETIRAPNOME, RETIRAUNOME, PLAF;
		return l;
	}
	else {
		short *TAMANHO = new short(rand() % 10 + 1);
		short *itera = new short(0);
		short *GRUPOIDDEPART = new short(rand() % 401 + 100);
		pessoa*p = new pessoa;
		pessoa**l = new pessoa*[*TAMANHO];
		for (*itera; *itera < *TAMANHO; (*itera)++) {
			short *RETIRAPNOME = new short(rand() % 44);
			short *RETIRAUNOME = new short(rand() % 97);
			float *PLAF = new float(rand() % 100 + 1);
			pessoa*p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURAÇÃOMEAL, *GRUPOIDDEPART, *PLAF, *ALUNOOUNAO, false);
			if (*itera == 0) {
				p->tamanho = *TAMANHO;
			}
			l[*itera] = p;
			delete RETIRAPNOME, RETIRAUNOME, PLAF;
		}
		delete itera,TAMANHO,GRUPOIDDEPART;
		return l;
	}
	delete RETIRACURSO, PROBESP,DURAÇÃOMEAL,ALUNOOUNAO;
}

void escrevePessoa(pessoa *p) {
	if (p == NULL) {
		cout << "-----NULL-----\n";
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << "€\n";
			}
			else {
				cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << "€\n";
			}
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << ", duração " << p->duração << ", " << p->plafond << "€\n";
		}
	}
}

void criaFila(pessoa**fila, short tam) {
	short i = 0;
	for (short i = 0; i < tam; i++) {
		fila[i] = NULL;
	}
}

pessoa** preencheFila(pessoa**fila, string* pnomes, string*unomes, string*cursos) {
	short*i = new short(0);
	short*j = new short(0);
	pessoa**g = criaGrupo(pnomes, unomes, cursos);
	short*tam = new short(g[0]->tamanho);
	while(*i<50) {
		if (*j < *tam) {
			fila[(*i)] = g[(*j)];
			(*j)++;
			(*i)++;
		}
		else  {
			g=criaGrupo(pnomes, unomes, cursos);
			*tam = g[0]->tamanho;
			*j = 0;
		}
	}
	delete i, j;
	return fila;
}

void escreveFila(pessoa**fila, short tam) {
	short*i = new short(0);
	while (*i < tam) {
		cout << *i + 1 << ". ";
		escrevePessoa(fila[(*i)]);
		(*i)++;
	}
}


/*
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
}*/