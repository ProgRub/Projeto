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

pessoa** criaGrupo(string *pnomes, string *unomes, string*cursos, int*reserva, int tamRes) {//vai criar um grupo de pessoas, que devem ter o mesmo nº de grupo, se for staff, o mesmo nº de departamento
	int *RETIRACURSO = new int(rand() % 19);
	int *DURAÇÃOMEAL = new int(rand() % 4 + 2);
	bool *ALUNOOUNAO = new bool(rand() % 2);
	int *GRUPOIDDEPART = new int(rand() % 401 + 100);
	testaGrupoDep(GRUPOIDDEPART, reserva, tamRes);//vai testar o número de grupo pois devem ser identificadores únicos
	int *PROBESP = new int(rand() % 100 + 1);
	if (*PROBESP > 15 && *PROBESP <= 20) {//no caso de se criar um aluno especial
		int *RETIRAPNOME = new int(rand() % 44);
		int *RETIRAUNOME = new int(rand() % 97);
		float *PLAF = new float(rand() % 100 + 1);
		pessoa *p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURAÇÃOMEAL, *GRUPOIDDEPART, *PLAF, true, true);
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
			pessoa*p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURAÇÃOMEAL, *GRUPOIDDEPART, *PLAF, *ALUNOOUNAO, false);
			p->tamanho = *TAMANHO - i;
			l[i] = p;
			delete RETIRAPNOME, RETIRAUNOME, PLAF;
		}
		delete TAMANHO, GRUPOIDDEPART;
		return l;
	}
	delete RETIRACURSO, PROBESP, DURAÇÃOMEAL, ALUNOOUNAO;
}

void escrevePessoaFila(pessoa *p) {//como o nome indica escreve a pessoa que recebe como argumento
	if (p == NULL) {
		cout << endl;
	}
	else {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << "€" << endl;
			}
			else {
				cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << ", duração " << p->duração << ", " << p->plafond << "€" << endl;
			}
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << ", duração " << p->duração << ", " << p->plafond << "€" << endl;
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
				cout << p->priNome << " " << p->ultNome << ", Estudante, Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << " (ciclos restantes: " << p->duração << ")" << endl;
			}
			else {
				cout << p->priNome << " " << p->ultNome << ", Estudante (especial), Grupo " << p->numDepartamentoOuGrupo << ", " << p->membro_aluno.curso << ", " << p->membro_aluno.num << " (ciclos restantes: " << p->duração << ")" << endl;
			}
		}
		else {
			cout << p->priNome << " " << p->ultNome << ", Staff, Departamento " << p->numDepartamentoOuGrupo << ", " << p->membro_staff.numFuncionario << " (ciclos restantes: " << p->duração << ")" << endl;
		}
	}
}

void criaFila(pessoa**fila, int tam) {//vai por todos os lugares num vetor de pessoa* como NULL para ser mais fácil o manuseamento do vetor
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
	(*pos)--;//a posição final não pode ser maior do que o indice permite
}

void escreveFila(pessoa**fila, int tam) {//como o nome indica escreve um vetor de pessoa*
	int i = 0;
	while (i < tam) {
		cout << i + 1 << ". ";
		escrevePessoaFila(fila[i]);
		i++;
	}
}

void alterarPlafond(pessoa**fila) {// opção 4, altera o plafond de uma pessoa na fila de espera pelo número de aluno ou de funcionário
	int n;
	cout << "Insira um número de aluno/funcionário: " << endl;
	cin >> n;
	int i = 0;
	for (i; i < 50; i++) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->membro_aluno.num == n) {
					cout << "Plafond inicial: " << fila[i]->plafond << "€" << endl;
					cout << "Insira um novo plafond: ";
					cin >> fila[i]->plafond;
					cout << "Plafond atual: " << fila[i]->plafond << "€" << endl;
					break;
				}
			}
			else if (fila[i]->membro_staff.numFuncionario > 0) {
				if (fila[i]->membro_staff.numFuncionario == n) {
					cout << "Plafond inicial: " << fila[i]->plafond << "€" << endl;
					cout << "Insira um novo plafond: ";
					cin >> fila[i]->plafond;
					cout << "Plafond atual: " << fila[i]->plafond << "€" << endl;
					break;
				}
			}
		}
		else {
			i = 49;
		}
	}
	if (i == 50) {
		cout << "Não válido" << endl;
	}
}

void procuraEspecial(pessoa**fila,int tam) {// vai percorrer a fila para ver se há estudantes especiais
	int j;
	int aconteceu = 0;
	for (int i = 0; i < tam; i++) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.especialOuNao) {//se há estudante especial este passa para a primeira posição da fila porque tem prioridade
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

void testaGrupoDep(int * num, int * reserva, int tam){// vê se o número de grupo ou departamento é único
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
	mergeSortAlfabeticamentePriNome(removidos, pessoasRemovidos);//usa-se uma adaptação do mergeSort pois é um dos mais eficientes algoritmos de ordenação
	system("CLS");
	cout << "Pessoas que estiveram na fila, mas não tinham dinheiro suficiente e foram removidos, ordenadas pelo primeiro nome:" << endl << endl;
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