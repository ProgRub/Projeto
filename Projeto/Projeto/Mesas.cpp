#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
using namespace std;

refeição* novaMeal() {//vai receber os dados do utilizador para uma nova refeição
	cout << "***** REFEIÇÃO NOVA *****\nA cantina EDA necessita de uma nova refeição\n\t1. Introduza a entrada:" << endl;
	refeição *meal = new refeição();
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o preço:" << endl;
	cin >> meal->custo;
	return meal;
}

string* escreveMeal(refeição *r) {//escreve a refeição atual, retorna um array de strings para guardar-se para a possível gravação de dados
	string *aux1 = new string(r->entrada);
	string *aux2 = new string(r->pratoMain);
	cout << "Refeição atual:\n\tEntrada: " << *aux1 << "\n\tPrato Principal: " << *aux2 << "\n\tCusto:" << r->custo << "€\n";
	string *FIM = new string[7];
	FIM[0] = "Refeição atual:\n\tEntrada: ";
	FIM[1] = *aux1;
	FIM[2] = "\n\tPrato Principal: ";
	FIM[3] = *aux2;
	FIM[4] = "\n\tCusto:";
	FIM[5] = to_string(r->custo);
	FIM[6] = "€\n";
	delete aux1, aux2;
	return FIM;
}

mesa** criaCantina() {//vai obter o tamanho da cantina e gerar tamanhos de mesas até a cantina estar preenchida, tamanhos guardados num vetor
	short *TCANTINA = new short(rand() % 21 + 30);
	short *t = new short();
	short *aux = new short[25];
	short *itera = new short(0);
	while (*t < *TCANTINA) {
		short *TMESA = new short(rand() % 4 + 2);
		*t += *TMESA;
		aux[(*itera)++] = *TMESA;
		if (*TCANTINA - *t <= 1 && *TCANTINA != *t) {//quando isto acontece, nenhuma mesa poderá preencher o último espaço ou já ultrapassamos o tamanho da cantina, por isso faz-se um "reset", "apaga-se" a mesa que provocou isto e tenta-se outra vez
			*t -= *TMESA;
			(*itera)--;
		}
		delete TMESA;
	}
	short *vtamMesas = copiaVetor(aux, *itera);
	mesa** vMes= criaMesas(vtamMesas, *itera);
	delete itera, TCANTINA, t;
	delete[]aux;
	return vMes;
}

mesa** criaMesas(short *vtamMesas, short tam) {//vai criar as mesas da cantina com o vetor que contem os tamanhos das mesas obtidos em criaCantina
	short *itera = new short(0);
	mesa** vMesas = new mesa*[tam];
	short *num = new short(1);
	while (*itera < tam) {
		mesa *m = new mesa();
		m->numMesa = *num;
		(*num)++;
		m->tamanho = vtamMesas[*itera];
		pessoa **sit = new pessoa*[vtamMesas[*itera]];
		for (int i = 0; i < m->tamanho; i++) {
			sit[i] = NULL;
		}
		m->sentados = sit;
		if (*itera == 0) {
			m->totalMesas = tam;
		}
		m->numSentados = 0;
		vMesas[*itera] = m;
		(*itera)++;
	}
	return vMesas;
}

void escreveMesa(mesa *m) {
	cout << "Mesa " << m->numMesa << "(CAPACIDADE " << m->tamanho << "):\n";
	short*i = new short(0);
	while (*i < m->numSentados) {
		escrevePessoa(m->sentados[*i]);
		(*i)++;
	}
}

void preencheMesa(mesa *m, pessoa**fila, short *k) {
	short*i = new short(0);
	short*j = new short(0);
	while (*i < m->tamanho) {
		if (*i > 1) {
			testeMesas(m, fila[*j], *i);
		}
		m->sentados[*i] = fila[*j];
		(*i)++;
		m->numSentados = *i;
		fila[*j]=NULL;
		(*j)++;
	}
	short l = 0;
	while(l < m->tamanho) {
		nullsNoFim(fila, 0, *k);
		(*k)--;
		l++;
	}
}

void preencheCantina(mesa**cantina, pessoa**fila) {
	short i = 0;
	short*k = new short(49);
	short *tam = new short(cantina[0]->totalMesas);
	while (i <*tam ) {
		preencheMesa(cantina[i], fila, k);
		i++;
	}
}
void escreveCantina(mesa ** cantina)
{
	short *i = new short(0);
	while (*i < cantina[0]->totalMesas) {
		escreveMesa(cantina[*i]);
		(*i)++;
	}
}

void nullsNoFim(pessoa**fila, short beg ,short end) {
	for (beg; beg <= (end-1); beg++) {
		swap(fila[beg], fila[beg+1]);
	}
}
void testeMesas(mesa *m, pessoa *p, short it) { //verifica as mesas pra ver se tem cursos diferentes
	short i = it-1;
	string *curso = new string(m->sentados[i]->membro_aluno.curso);
	bool funciona = false;
	while (i < m->numSentados) {
		if(m->sentados[i]!=NULL){
			if (*curso == p->membro_aluno.curso) {
				funciona = true;
			}
			cout << funciona << endl;
			i++;
		}
		else {
			i = m->numSentados;
		}
	}
}

void removePessoa(pessoa **fila, refeição *r) { // averigua se o aluno/funcionário possui Plafond necessário
	short i = 0;
	while (i < 50) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->plafond < r->custo) {
					cout << "O aluno com o número " << fila[i]->membro_aluno.num << " não possui plafond suficiente. " << endl;
				}
			}
			else {
				if (fila[i]->plafond < r->custo) {
					cout << "O elemento de staff com o número " << fila[i]->membro_staff.numFuncionario << " não possui plafond suficiente. " << endl;
				}
			}
			i++;
		}
		else {
			break;
		}
	}
}

void removeDuração(mesa **cantina) {
	short i = 0;
	short j;
	short *tam = new short(cantina[0]->totalMesas);
	for (i; i < *tam; i++) {
		for (j = 0; j < cantina[i]->numSentados; j++) {
			if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
				cantina[i]->sentados[j]->duração--;
			}
			else if (cantina[i]->sentados[j]->membro_staff.numFuncionario > 0) {
				cantina[i]->sentados[j]->duração--;
			}
		}
	}
}
/*
void removePobres(pessoa *fila, refeição *r) { // averigua se o aluno/funcionário possui Plafond necessário
	short i = 0;
	while (i < 50) {
		if (fila[i].membro_aluno.num > 0) {
			if (fila[i].plafond < r->custo) {
				cout << "O aluno com o número " << fila[i].membro_aluno.num << " não possui plafond suficiente. " << endl;
			}
		}
		else {
			if (fila[i].plafond < r->custo) {
				cout << "O elemento de staff com o número " << fila[i].membro_staff.numFuncionario << " não possui plafond suficiente. " << endl;
			}
		}
		i++;
	}
}

void ordenaAlfabeto(mesa* cantina, pessoa* fila) {
	short y = 0;
	short i = 0;
	short p = 0;
	string max;
	if (cantina[y].sentados[i].ultNome < cantina[y].sentados[i++].ultNome) {
		max = cantina[y].sentados[i++].ultNome;
		cout << max;
		p++;
	}
	else {
		i++;
		p++;
	}
}*/

