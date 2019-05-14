#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int comprimento(LLPessoas* ll) {
	int conta = 0;
	ll->iterator = ll->primeira;
	while (ll->iterator != NULL)//enquanto não chegar ao fim da LL
	{
		conta++;
		ll->iterator = ll->iterator->seguinte; //vai para o nodo seguinte
	}
	return conta;
}

bool listaVaziaPessoas(LLPessoas*ll) {
	if (ll->primeira != NULL) {
		return false;
	}
	return true;
}

void inserirInicioPessoas(LLPessoas* ll, LLPessoas::pessoa *p) {
	if (!listaVaziaPessoas(ll)) {
		p->seguinte = ll->primeira;
		ll->primeira = p;
		return;
	}
	p->seguinte = NULL;
	ll->primeira = p;
	ll->ultima = ll->primeira;
	return;
}

void insereFimPessoas(LLPessoas* ll, LLPessoas::pessoa *p) {
	if (!listaVaziaPessoas(ll)) {
		p->seguinte = NULL;
		ll->ultima->seguinte = p;
		ll->ultima = p;
		return;
	}
	ll->primeira = p;
	ll->ultima = ll->primeira;
	p->seguinte = NULL;
	return;
}

LLPessoas::pessoa* criaPessoa (string pnome, string unome, string curso, int dura, int idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao) {// vai criar uma pessoa
	LLPessoas::pessoa *p = new LLPessoas::pessoa();
	p->priNome = pnome;
	p->ultNome = unome;
	p->plafond = plafond;
	p->duração = dura;
	p->numDepartamentoOuGrupo = idOuDepart;
	if (alunoOuNao) {// se alunoOuNao é true vai criar um aluno
		p->membro_aluno.curso = curso;
		int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
		p->membro_aluno.num = *NUMALUNO;
		p->membro_aluno.especialOuNao = especialOuNao;
		p->membro_staff.numFuncionario = NULL;
		delete NUMALUNO;
	}
	else {// senão cria um funcionário de staff
		p->membro_aluno.curso = "\0";
		p->membro_aluno.num = NULL;
		p->membro_aluno.especialOuNao = NULL;
		int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
		p->membro_staff.numFuncionario = *NUMSTAFF;
		delete NUMSTAFF;
	}
	return p;
}

void escrevePessoaFila(LLPessoas::pessoa *p) {//como o nome indica escreve a pessoa que recebe como argumento
	if (p == NULL) {
		cout << endl;
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << p->priNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << " EUR" << endl;
			}
			else {
				cout << p->priNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << " EUR" << endl;
			}
		}
		else {
			cout << p->priNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << ", duração " << p->duração << ", " << p->plafond << " EUR" << endl;
		}
	}
}

void escrevePessoaCompleta(LLPessoas::pessoa *p) {//como o nome indica escreve a pessoa que recebe como argumento
	if (p == NULL) {
		cout << endl;
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << " EUR" << endl;
			}
			else {
				cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << " EUR" << endl;
			}
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << ", duração " << p->duração << ", " << p->plafond << " EUR" << endl;
		}
	}
}

void escrevePessoaCantina(LLPessoas::pessoa *p) {//como o nome indica escreve a pessoa que recebe como argumento
	if (p == NULL) {
		cout << endl;
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << "\t" << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << " (ciclos restantes: " << p->duração << ")" << endl;
			}
			else {
				cout << "\t" << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << " (ciclos restantes: " << p->duração << ")" << endl;
			}
		}
		else {
			cout << "\t" << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << " (ciclos restantes: " << p->duração << ")" << endl;
		}
	}
}


void preencheFila(LLPessoas*fila, string* pnomes, string*unomes, string*cursos, LLReserva*reserva) {//vai preencher a fila, gerando um grupo de pessoas para os lugares vazios
	int j = 0;
	while (j < 3) {
		int *RETIRACURSO = new int(rand() % 19);
		int *DURAÇÃOMEAL = new int(rand() % 4 + 2);
		bool *ALUNOOUNAO = new bool(rand() % 2);
		int *GRUPOIDDEPART = new int(rand() % 401 + 100);
		testaGrupoDep(GRUPOIDDEPART, reserva);//vai testar o número de grupo pois devem ser identificadores únicos
		int *PROBESP = new int(rand() % 100 + 1);
		if (*PROBESP > 15 && *PROBESP <= 20) {//no caso de se criar um aluno especial
			int *RETIRAPNOME = new int(rand() % 44);
			int *RETIRAUNOME = new int(rand() % 97);
			float *PLAF = new float(rand() % 10000 + 1);
			*PLAF /= 100;
			LLPessoas::pessoa *p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURAÇÃOMEAL, *GRUPOIDDEPART, *PLAF, true, true);
			p->tamanhoGrupo = 1;
			inserirInicioPessoas(fila, p);
			delete  RETIRAPNOME, RETIRAUNOME, PLAF;
		}
		else {
			int *TAMANHO = new int(rand() % 10 + 1);//tamanho do grupo
			int i = 0;
			for (i; i < *TAMANHO; i++) {
				int *RETIRAPNOME = new int(rand() % 44);
				int *RETIRAUNOME = new int(rand() % 97);
				float *PLAF = new float(rand() % 10000 + 1);
				*PLAF /= 100;
				LLPessoas::pessoa *p = new LLPessoas::pessoa;
				p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURAÇÃOMEAL, *GRUPOIDDEPART, *PLAF, *ALUNOOUNAO, false);
				p->tamanhoGrupo = *TAMANHO - i;
				insereFimPessoas(fila, p);
				delete RETIRAPNOME, RETIRAUNOME, PLAF;
			}
			delete TAMANHO;
		}
		delete RETIRACURSO, PROBESP, DURAÇÃOMEAL, GRUPOIDDEPART, ALUNOOUNAO;
		if (fila->ultima->tamanhoGrupo == 1) {
			j++;
		}
	}
}
void escreveFila(LLPessoas*fila) {//como o nome indica escreve um vetor de pessoa*
	cout << endl << "FILA DE ESPERA:" << endl;
	int i = 1;
	fila->iterator = fila->primeira;
	while (fila->iterator !=NULL) {
		cout << i++ << ". ";
		escrevePessoaFila(fila->iterator);
		fila->iterator = fila->iterator->seguinte;
	}
}

bool listaVaziaReserva(LLReserva*ll) {
	if (ll->primeiro != NULL) {
		return false;
	}
	return true;
}

void insereFimReserva(LLReserva* ll, int num) {
	LLReserva::item*aux = new LLReserva::item();
	aux->num = num;
	if (!listaVaziaReserva(ll)) {
		ll->ultimo->seguinte = aux;
		aux->seguinte = NULL;
		ll->ultimo = aux;
		return;
	}
	ll->primeiro = aux;
	ll->ultimo = aux;
	aux->seguinte = NULL;
}

void testaGrupoDep(int * num, LLReserva * reserva) {// vê se o número de grupo ou departamento é único
	if (!listaVaziaReserva(reserva)) {
		LLReserva::item*itera = new LLReserva::item();
		itera = reserva->primeiro;
		while (itera != NULL) {
			if (itera->num == *num) {
				*num = (rand() % 401 + 100);
				testaGrupoDep(num, reserva);
				return;
			}
			itera = itera->seguinte;
		}
		insereFimReserva(reserva, *num);
		delete itera;
		return;
	}
	insereFimReserva(reserva, *num);
	return;
}


void escreveOpções(LLPessoas*ll) {
	ll->iterator = ll->primeira;
	int i = 1;
	while (ll->iterator!=NULL) {
		cout << i++ << ". ";
		escrevePessoaCompleta(ll->iterator);
		ll->iterator = ll->iterator->seguinte;
	}
}

void alterarPlafond(LLPessoas *ll) {// opção 4, altera o plafond de uma pessoa na fila de espera pelo número de aluno ou de funcionário
	int n;
	cout << endl << "Insira um número de aluno/funcionário: " << endl;
	cin >> n;
	int i = 0;
	bool VerPessoa = false;
	ll->iterator = ll->primeira;
	while (ll->iterator!=NULL) {
			if (ll->iterator->membro_aluno.num > 0) {
				if (ll->iterator->membro_aluno.num == n) {
					cout << "Plafond inicial: " << ll->iterator->plafond << " EUR" << endl;
					cout << "Insira um novo plafond: ";
					cin >> ll->iterator->plafond;
					VerPessoa = true;
					break;
				}
			}
			else if (ll->iterator->membro_staff.numFuncionario > 0) {
				if (ll->iterator->membro_staff.numFuncionario == n) {
					cout << "Plafond inicial: " <<ll->iterator->plafond << " EUR" << endl;
					cout << "Insira um novo plafond: ";
					cin >> ll->iterator->plafond;
					VerPessoa = true;
					break;
				}
			}
			ll->iterator = ll->iterator->seguinte;
	}
	if (!VerPessoa) {
		cout << "Ninguém na fila tem o número de aluno / funcionário que inseriu" << endl;
	}
}
/*
void ordenaAlfabeticamentePriNome(pessoa ** removidos, int pessoasRemovidos) {//vai ordenar alfabeticamente pelo primeiro nome as pessoas que foram removidas da fila de espera porque não tinham dinheiro suficiente para pagar pela refeição
	mergeSortAlfabeticamentePriNome(removidos, pessoasRemovidos);//usa-se uma adaptação do mergeSort pois é um dos mais eficientes algoritmos de ordenação
	system("CLS");
	cout << "\t\t\t\t\t Cantina EDA" << endl;
	cout << "Pessoas que estiveram na fila, mas não tinham dinheiro suficiente e foram removidos, ordenadas pelo primeiro nome:" << endl << endl;
	escreveOpções(removidos, pessoasRemovidos);
}

int contaRemovidos(pessoa ** removidos) {
	int soma = 0;
	int i = 0;
	while (i < 100) {
		if (removidos[i] != NULL) {
			soma++;
			i++;
		}
		else {
			break;
		}
	}
	return soma;
}

void mergeSortAlfabeticamentePriNome(pessoa ** removidos, int tam) {
	if (tam < 2) {
		return;
	}
	int mid = tam / 2;
	pessoa **left = new pessoa*[mid];
	pessoa**right = new pessoa*[tam - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = removidos[i];
	}
	for (int j = mid; j < tam; j++) {
		right[j - mid] = removidos[j];
	}
	mergeSortAlfabeticamentePriNome(left, mid);
	mergeSortAlfabeticamentePriNome(right, tam - mid);
	mergeRemovidos(left, right, removidos, mid, tam - mid, tam);
}

void mergeRemovidos(pessoa ** left, pessoa ** right, pessoa ** removidos, int n_left, int n_right, int tam) {
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n_left && j < n_right) {
		if (left[i]->priNome < right[j]->priNome) {
			removidos[k] = left[i];
			i++;
		}
		else {
			removidos[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < n_left) {
		removidos[k] = left[i];
		k++;
		i++;
	}
	while (j < n_right) {
		removidos[k] = right[j];
		j++;
		k++;
	}
}*/