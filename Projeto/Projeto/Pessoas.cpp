#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

pessoa* criaPessoa(string pnome, string unome, string curso, int dura, int idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao) {// vai criar uma pessoa
	pessoa *p = new pessoa;
	p->priNome = pnome;
	p->ultNome = unome;
	p->plafond = plafond;
	p->dura��o = dura;
	p->numDepartamentoOuGrupo = idOuDepart;
	if (alunoOuNao) {// se alunoOuNao � true vai criar um aluno
		p->membro_aluno.curso = curso;
		int *NUMALUNO = new int((20 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 7 + 12));
		p->membro_aluno.num = *NUMALUNO;
		p->membro_aluno.especialOuNao = especialOuNao;
		p->membro_staff.numFuncionario = NULL;
		delete NUMALUNO;
	}
	else {// sen�o cria um funcion�rio de staff
		p->membro_aluno.curso = "\0";
		p->membro_aluno.num = NULL;
		p->membro_aluno.especialOuNao = NULL;
		int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 31 + 70));
		p->membro_staff.numFuncionario = *NUMSTAFF;
		delete NUMSTAFF;
	}
	return p;
}

pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos, int*reserva, int tamRes) {//vai criar um grupo de pessoas, que devem ter o mesmo n� de grupo, se for staff, o mesmo n� de departamento
	int *RETIRACURSO = new int(rand() % 19);
	int *DURA��OMEAL = new int(rand() % 4 + 2);
	bool *ALUNOOUNAO = new bool(rand() % 2);
	int *GRUPOIDDEPART = new int(rand() % 401 + 100);
	testaGrupoDep(GRUPOIDDEPART, reserva, tamRes);//vai testar o n�mero de grupo pois devem ser identificadores �nicos
	int *PROBESP = new int(rand() % 100 + 1);
	if (*PROBESP > 15 && *PROBESP <= 20) {//no caso de se criar um aluno especial
		int *RETIRAPNOME = new int(rand() % 44);
		int *RETIRAUNOME = new int(rand() % 97);
		float *PLAF = new float(rand() % 100 + 1);
		pessoa *p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURA��OMEAL, *GRUPOIDDEPART, *PLAF, true, true);
		pessoa**l = new pessoa*[1];
		p->tamanho = 1;
		l[0] = p;
		delete GRUPOIDDEPART, RETIRAPNOME, RETIRAUNOME, PLAF;
		return l;
	}
	else {
		int *TAMANHO = new int(rand() % 10 + 1);//tamanho do grupo
		int i = 0;
		pessoa*p = new pessoa;
		pessoa**l = new pessoa*[*TAMANHO];
		for (i; i < *TAMANHO; i++) {
			int *RETIRAPNOME = new int(rand() % 44);
			int *RETIRAUNOME = new int(rand() % 97);
			float *PLAF = new float(rand() % 100 + 1);
			pessoa*p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURA��OMEAL, *GRUPOIDDEPART, *PLAF, *ALUNOOUNAO, false);
			p->tamanho = *TAMANHO - i;
			l[i] = p;
			delete RETIRAPNOME, RETIRAUNOME, PLAF;
		}
		delete TAMANHO, GRUPOIDDEPART;
		return l;
	}
	delete RETIRACURSO, PROBESP, DURA��OMEAL, ALUNOOUNAO;
}

void escrevePessoaFila(pessoa *p) {//como o nome indica escreve a pessoa que recebe como argumento
	if (p == NULL) {
		cout << endl;
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", dura��o " << p->dura��o << ", " << p->plafond << "�" << endl;
			}
			else {
				cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", dura��o " << p->dura��o << ", " << p->plafond << "�" << endl;
			}
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << ", dura��o " << p->dura��o << ", " << p->plafond << "�" << endl;
		}
	}
}

void escrevePessoaCantina(pessoa *p) {//como o nome indica escreve a pessoa que recebe como argumento
	if (p == NULL) {
		cout << endl;
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << " (ciclos restantes: " << p->dura��o << ")" << endl;
			}
			else {
				cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << " (ciclos restantes: " << p->dura��o << ")" << endl;
			}
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << " (ciclos restantes: " << p->dura��o << ")" << endl;
		}
	}
}

void criaFila(pessoa**fila, int tam) {//vai por todos os lugares num vetor de pessoa* como NULL para ser mais f�cil o manuseamento do vetor
	int i = 0;
	for (int i = 0; i < tam; i++) {
		fila[i] = NULL;
	}
}

void preencheFila(pessoa**fila, string* pnomes, string*unomes, string*cursos, int *pos,int*reserva, int tamRes) {//vai preencher a fila, gerando um grupo de pessoas para os lugares vazios
	int j = 0;
	pessoa**g = criaGrupo(pnomes, unomes, cursos,reserva,tamRes);
	int subtrai;
	int y = 0;
	while (*pos < 50) {
		if (j < g[0]->tamanho) {
			fila[*pos] = g[j];
			j++;
			(*pos)++;
		}
		else {
			g = criaGrupo(pnomes, unomes, cursos, reserva, tamRes);
			subtrai = 50 - *pos;
			if (g[0]->tamanho > subtrai) {//para evitar problemas quando tivermos a verificar para vagas
				while (y < 50 - *pos) {
					g[y]->tamanho = subtrai;
					y++;
					subtrai--;
				}
			}
			y = 0;
			j = 0;
		}
	}
	(*pos)--;//a posi��o final n�o pode ser maior do que o indice permite
}

void escreveFila(pessoa**fila, int tam) {//como o nome indica escreve um vetor de pessoa*
	int i = 0;
	while (i < tam) {
		cout << i + 1 << ". ";
		escrevePessoaFila(fila[i]);
		i++;
	}
}

void alterarPlafond(pessoa**fila) {// op��o 4, altera o plafond de uma pessoa na fila de espera pelo n�mero de aluno ou de funcion�rio
	int n;
	cout << "Insira um n�mero de aluno/funcion�rio: " << endl;
	cin >> n;
	int i = 0;
	for (i; i < 50; i++) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->membro_aluno.num == n) {
					cout << "Plafond inicial: " << fila[i]->plafond << "�" << endl;
					cout << "Insira um novo plafond: ";
					cin >> fila[i]->plafond;
					cout << "Plafond atual: " << fila[i]->plafond << "�" << endl;
					break;
				}
			}
			else if (fila[i]->membro_staff.numFuncionario > 0) {
				if (fila[i]->membro_staff.numFuncionario == n) {
					cout << "Plafond inicial: " << fila[i]->plafond << "�" << endl;
					cout << "Insira um novo plafond: ";
					cin >> fila[i]->plafond;
					cout << "Plafond atual: " << fila[i]->plafond << "�" << endl;
					break;
				}
			}
		}
		else {
			i = 49;
		}
	}
	if (i == 50) {
		cout << "N�o v�lido" << endl;
	}
}

void procuraEspecial(pessoa**fila,int tam) {// vai percorrer a fila para ver se h� estudantes especiais
	int j;
	int aconteceu = 0;
	for (int i = 0; i < tam; i++) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.especialOuNao) {//se h� estudante especial este passa para a primeira posi��o da fila porque tem prioridade
				j = i;
				for (j; j > aconteceu; j--) {
					swap(fila[j - 1], fila[j]);
				}
				aconteceu++;
			}
		}
		else {
			break;
		}
	}
}

void testaGrupoDep(int * num, int * reserva, int tam){// v� se o n�mero de grupo ou departamento � �nico
	for (int i = 0; i < tam; i++) {
		if (reserva[i] != NULL) {
			if (reserva[i] == *num) {
				*num= (rand() % 401 + 100);
			}
		}
		else {
			reserva[i] = *num;
			i = 100;
		}
	}
}

void ordenaAlfabeticamentePriNome(pessoa ** removidos, int pessoasRemovidos){
	mergeSortAlfabeticamentePriNome(removidos, pessoasRemovidos);//usa-se uma adapta��o do mergeSort pois � um dos mais eficientes algoritmos de ordena��o
	system("CLS");
	cout << "Pessoas que estiveram na fila, mas n�o tinham dinheiro suficiente e foram removidos, ordenadas pelo primeiro nome:" << endl << endl;
	escreveFila(removidos, pessoasRemovidos);
}

int contaRemovidos(pessoa ** removidos){
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

void mergeSortAlfabeticamentePriNome(pessoa ** removidos, int tam){
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

void mergeRemovidos(pessoa ** left, pessoa ** right, pessoa ** removidos, int n_left, int n_right, int tam){
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
}