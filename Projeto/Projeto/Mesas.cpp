#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
using namespace std;

refei��o* novaMeal(bool primeiraVez) {//vai receber os dados do utilizador para uma nova refei��o
	refei��o *meal = new refei��o();
	if (!primeiraVez) {
		system("pause");
		cin.get();
	}
	cout << "***** REFEI��O NOVA *****\nA cantina EDA necessita de uma nova refei��o\n\t1. Introduza a entrada:" << endl;
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o pre�o:" << endl;
	cin >> meal->custo;
	return meal;
}

void escreveMeal(refei��o *r) {//escreve a refei��o atual
	cout << "Refei��o atual:\n\tEntrada: " << r->entrada << "\n\tPrato Principal: " << r->pratoMain << "\n\tCusto:" << r->custo << "�" << endl;
}

mesa** criaCantina() {//vai obter o tamanho da cantina e gerar tamanhos de mesas at� a cantina estar preenchida, tamanhos guardados num vetor
	int *TCANTINA = new int(rand() % 21 + 30);
	int *t = new int();
	int *aux = new int[25];
	int *itera = new int(0);
	while (*t < *TCANTINA) {
		int *TMESA = new int(rand() % 4 + 2);
		*t += *TMESA;
		aux[(*itera)++] = *TMESA;
		if (*TCANTINA - *t <= 1 && *TCANTINA != *t) {//quando isto acontece, nenhuma mesa poder� preencher o �ltimo espa�o ou j� ultrapassamos o tamanho da cantina, por isso faz-se um "reset", "apaga-se" a mesa que provocou isto e tenta-se outra vez
			*t -= *TMESA;
			(*itera)--;
		}
		delete TMESA;
	}
	int *vtamMesas = copiaVetor(aux, *itera);
	mesa** vMes = criaMesas(vtamMesas, *itera);
	delete itera, TCANTINA, t;
	delete[]aux;
	return vMes;
}

mesa** criaMesas(int *vtamMesas, int tam) {//vai criar as mesas da cantina com o vetor que contem os tamanhos das mesas obtidos em criaCantina e retornar um vetor de mesa* que vai ser a cantina
	int itera = 0;
	mesa** vMesas = new mesa*[tam];
	int num = 1;
	while (itera < tam) {
		mesa *m = new mesa();
		m->numMesa = num;
		num++;
		m->tamanho = vtamMesas[itera];
		pessoa **sit = new pessoa*[vtamMesas[itera]];
		for (int i = 0; i < m->tamanho; i++) {
			sit[i] = NULL;
		}
		m->sentados = sit;
		if (itera == 0) {
			m->totalMesas = tam;
		}
		else {
			m->totalMesas = NULL;
		}
		m->numSentados = 0;
		vMesas[itera] = m;
		itera++;
	}
	return vMesas;
}

void preencheCantina(mesa**cantina, pessoa**fila, int *pos, refei��o*r, pessoa**removidos, int tamRemovidos) {//vai passar as pessoas da fila para a cantina
	int j = 0;
	int tam = cantina[0]->totalMesas;
	string curso;
	string cursoSenta;
	int mesmogrupo = 1;
	int vagas = 0;
	int ind = 0;
	for (int conta = 0; conta < tam; conta++) {
		vagas += (cantina[conta]->tamanho - cantina[conta]->numSentados);
	}
	for (int k = 0; k < tam; k++) {
		if (cantina[k]->numSentados == 0) {//no caso de n�o haver pessoas na mesa
			procuraEspecial(fila, 50);
			int tammesa = cantina[k]->tamanho;
			removeSemDinheiro(fila, r, pos, removidos, tamRemovidos, tammesa);
			int sentados = cantina[k]->numSentados;
			int mesmocurso = 1;
			if (fila[ind]->membro_aluno.num > 0) {
				curso = fila[ind]->membro_aluno.curso;
			}
			else {
				curso = "n�oconta";//se a pessoa para entrar for de staff n�o h� restri��es
			}
			for (j = 1; j < tammesa; j++) {
				if (curso != "n�oconta") {//para confirmar que n�o se sentam pessoas de cursos diferentes na mesma mesa
					if (fila[j]->membro_aluno.num > 0) {
						if (fila[j]->membro_aluno.curso == curso) {
							mesmocurso++;
						}
						else {
							j = tammesa;
						}
					}
					else {
						mesmocurso++;
					}
				}
				else {
					if ((fila[j]->membro_aluno.num > 0 && fila[j + 1]->membro_aluno.num > 0) && (fila[j]->membro_aluno.curso != fila[j + 1]->membro_aluno.curso)) {
						j = tammesa;
					}
					mesmocurso++;
				}
			}
			if (mesmocurso <= tammesa) {
				for (j = 0; j < mesmocurso; j++) {
					cantina[k]->sentados[j] = fila[ind];
					fila[ind] = NULL;
					nullsNoFim(fila, ind, pos);
					vagas--;
					sentados++;
				}
				cantina[k]->numSentados = sentados;//atualiza o n�mero de pessoas sentadas na mesa
			}
		}
		else {// no caso de j� haver gente na mesa, procedimento � quase igual
			for (int u = 0; u < cantina[k]->tamanho; u++) {
				nullsNoFimCantina(cantina[k]->sentados, 0, cantina[k]->tamanho);
			}
			procuraEspecial(fila, 50);
			int tamanhoMesa = cantina[k]->tamanho;
			int numSentados = cantina[k]->numSentados;
			removeSemDinheiro(fila, r, pos, removidos, tamRemovidos, tamanhoMesa - numSentados);
			int mesmocurso;
			int y = 0;
			if (numSentados != tamanhoMesa) {
				for (int l = 0; l < numSentados; l++) {
					if (cantina[k]->sentados[l] != NULL) {
						if (cantina[k]->sentados[l]->membro_aluno.num > 0) {
							cursoSenta = cantina[k]->sentados[l]->membro_aluno.curso;
							l = numSentados;
						}
						else {
							cursoSenta = "n�oconta";
						}
					}
				}
				for (int p = 0; p < tamanhoMesa - numSentados; p++) {
					mesmocurso = 0;
					if (cursoSenta != "n�oconta") {
						if (fila[ind]->membro_aluno.num > 0) {
							if (fila[ind]->membro_aluno.curso == cursoSenta) {
								mesmocurso++;
							}
							else {
								p = tamanhoMesa;
							}
						}
						else {
							if ((fila[p]->membro_aluno.num > 0 && fila[p + 1]->membro_aluno.num > 0) && (fila[p]->membro_aluno.curso != fila[p + 1]->membro_aluno.curso)) {
								p = tamanhoMesa;
							}
							else if ((fila[p]->membro_aluno.num > 0 && fila[p + 1]->membro_aluno.num > 0) && (fila[j]->membro_aluno.curso == fila[p + 1]->membro_aluno.curso)) {
								mesmocurso++;
							}
							while ((fila[y]->membro_staff.numFuncionario > 0 && y < tamanhoMesa - numSentados)) {// se for de staff pode entrar livremente
								mesmocurso++;
								y++;
							}
						}
					}
					else {
						if (fila[p]->membro_aluno.especialOuNao) {
							mesmocurso++;
							y++;
						}
						else if ((fila[p]->membro_aluno.num > 0 && fila[p + 1]->membro_aluno.num > 0) && (fila[p]->membro_aluno.curso != fila[p + 1]->membro_aluno.curso)) {
							p = tamanhoMesa;
						}
						else if ((fila[p]->membro_aluno.num > 0 && fila[p + 1]->membro_aluno.num > 0) && (fila[p]->membro_aluno.curso == fila[p + 1]->membro_aluno.curso)) {
							while (((fila[p]->membro_aluno.num > 0 && fila[p + 1]->membro_aluno.num > 0) && (fila[p]->membro_aluno.curso == fila[p + 1]->membro_aluno.curso)) && y < tamanhoMesa - numSentados) {
								mesmocurso++;
								y++;
							}
						}
						while (fila[y]->membro_staff.numFuncionario > 0 && y < tamanhoMesa - numSentados) {// se for de staff pode entrar livremente
							mesmocurso++;
							y++;
						}
					}
					if (mesmocurso != 0) {
						for (int i = 0; i <= mesmocurso; i++) {
							if (cantina[k]->sentados[i] == NULL) {
								cantina[k]->sentados[i] = fila[ind];
								fila[ind] = NULL;
								nullsNoFim(fila, ind, pos);
								vagas--;
								numSentados++;
							}
						}
						cantina[k]->numSentados = numSentados;
					}
				}
			}
		}
	}
	(*pos)++; //assegura que n�o se apaga ningu�m quando se gera novas pessoas para a fila
}

void escreveCantina(mesa ** cantina) {//vai escrever a cantina como diz no nome
	int tam = cantina[0]->totalMesas;
	for (int i = 0; i < tam; i++) {
		cout << "Mesa " << cantina[i]->numMesa << "(CAPACIDADE " << cantina[i]->tamanho << "):" << endl;
		int auxmesa = cantina[i]->tamanho;
		for (int j = 0; j < auxmesa; j++) {
			escrevePessoa(cantina[i]->sentados[j]);
		}
		cout << endl;
	}
}

void nullsNoFim(pessoa**fila, int beg, int *end) {//quando se passa uma pessoa da fila para a cantina, o NULL no lugar dessa pessoa tem de ser mandado para o fim, ou para a primeira posi��o onde est� um NULL, para evitar swaps desnecess�rios
	for (beg; beg <= (*end - 1); beg++) {
		swap(fila[beg], fila[beg + 1]);
	}
	(*end)--;//evita swaps desnecess�rios 
}

void nullsNoFimCantina(pessoa**sentados, int beg, int end) {//mesma coisa que a vers�o anterior, s� que pondo os NULLs gerados de retirar as pessoas que acabam da mesa nas �ltimas posi��es da mesa, para ser mais f�cil aceder �s pessoas sentadas na mesa
	for (beg; beg <= (end - 2); beg++) {
		if (sentados[beg] == NULL) {
			swap(sentados[beg], sentados[beg + 1]);
		}
	}

}

void removeDura��o(mesa **cantina) {//como o nome indica, com cada ciclo remove 1 � dura��o
	int i = 0;
	int j;
	int tam = cantina[0]->totalMesas;
	for (i; i < tam; i++) {
		if (cantina[i]->numSentados > 0) {
			for (j = 0; j < cantina[i]->numSentados; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					cantina[i]->sentados[j]->dura��o--;
				}
			}
		}
	}
}

void retiraEmergPessoa(mesa **cantina, pessoa**acabados, int tamAcabados, refei��o *r) {//fun��o para os casos de emerg�ncia, neste caso retirar uma pessoa em caso de emerg�ncia
	int n;
	int i = 0;
	int j;
	bool removeu = false;
	int *tam = new int(cantina[0]->totalMesas);
	cout << "Emerg�ncia, escolha um n�mero pra sair" << endl;
	cin >> n;
	for (i; i < *tam; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
					if (cantina[i]->sentados[j]->membro_aluno.num == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver defini��o da fun��o
						cantina[i]->numSentados--;
						cantina[i]->sentados[j] = NULL;
						nullsNoFimCantina(cantina[i]->sentados, j, cantina[i]->tamanho);//mete os NULLs nas �ltimas posi��es da mesa
						removeu = true;
					}
				}
				else if (cantina[i]->sentados[j]->membro_staff.numFuncionario > 0) {
					if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
						cantina[i]->numSentados--;
						cantina[i]->sentados[j] = NULL;
						nullsNoFimCantina(cantina[i]->sentados, j, cantina[i]->tamanho);//mete os NULLs nas �ltimas posi��es da mesa
						removeu = true;
					}
				}
			}
			else {
				j = cantina[i]->tamanho;
			}
		}
	}
	if (i == *tam && !removeu) {
		cout << "N�o v�lido" << endl;
	}
}

void retiraEmergGrupo(mesa **cantina, pessoa**acabados, int tamAcabados, refei��o *r) {//fun��o para os casos de emerg�ncia, neste caso retirar um grupo em caso de emerg�ncia
	int n;
	int i = 0;
	int j;
	int *tam = new int(cantina[0]->totalMesas);
	bool removeu = false;
	cout << "Emerg�ncia, escolha um grupo pra sair" << endl;
	cin >> n;
	for (i; i < *tam; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == n) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver defini��o da fun��o
					cantina[i]->numSentados--;
					cantina[i]->sentados[j] = NULL;
					removeu = true;
				}
			}
		}
		nullsNoFimCantina(cantina[i]->sentados, 0, cantina[i]->tamanho);//mete os NULLs nas �ltimas posi��es da mesa
	}
	if (i == *tam && !removeu) {
		cout << "N�o v�lido" << endl;
	}
}

void removeAcabados(mesa **cantina, pessoa** acabados, int tamAcabados, refei��o*r) {
	int i = 0;
	int j;
	int tam = cantina[0]->totalMesas;
	for (i; i < tam; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->dura��o == 0) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
					cantina[i]->numSentados--;
					cantina[i]->sentados[j] = NULL;
				}
			}
		}
		nullsNoFimCantina(cantina[i]->sentados, 0, cantina[i]->tamanho);
	}
}

void adicionaVetorAcabados(pessoa**acabados,pessoa*p, int tam, refei��o*r) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refei��o quer tiveram que sair de emerg�ncia
	for (int i =0; i < tam; i++) {
		if (acabados[i] == NULL) {
			p->plafond -= r->custo;//cobra a refei��o aos que saem da cantina
			acabados[i] = p;
			i = tam;
		}
	}
}

void ordenaAlfabeticamenteUltNome(mesa**cantina, pessoa**fila, pessoa**acabados, int pessoasNaCantina, int pessoasNaFila, int pessoasAcabados) {//op��o 1, ordena alfabeticamente todas as pessoas que passaram pelo sistema pelos seus �ltimos nomes
	int total = pessoasNaCantina + pessoasNaFila + pessoasAcabados;//n� de pessoas no sistema
	pessoa**sistema = new pessoa*[total];
	criaFila(sistema, total);
	int i = 0;
	int x = 0;
	int y = 0;
	while (i < total) {
		for (int k = 0; k < cantina[0]->totalMesas; k++) {
			for (int j = 0; j < cantina[k]->tamanho; j++) {//vai adicionar ao vetor que vai ser ordenado as pessoas da cantina
				if (cantina[k]->sentados[j] != NULL) {
					sistema[i] = cantina[k]->sentados[j];
					i++;
				}
			}
		}
		while (x < pessoasNaFila) {//vai adicionar ao vetor que vai ser ordenado as pessoas da fila
			sistema[i] = fila[x];
			i++;
			x++;
		}
		while (y < pessoasAcabados) {//vai adicionar ao vetor que vai ser ordenado as pessoas que sa�ram da cantina
			sistema[i] = acabados[y];
			i++;
			y++;
		}
	}
	mergeSortAlfabeticamenteUltNome(sistema, total);//usa-se uma adapta��o do mergeSort pois � um dos mais eficientes algoritmos de ordena��o
	system("CLS"); 
	cout << "Pessoas que estiveram na fila, entraram na cantina e j� sa�ram ordenadas alfabeticamente pelo �ltimo nome:" << endl << endl;
	escreveFila(sistema, total);
}

int contaPessoasCantina(mesa**cantina) {//conta as pessoas que est�o na cantina, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		soma += cantina[i]->numSentados;
	}
	return soma;
}

int contaPessoasFila(pessoa**fila) {//conta as pessoas que est�o na fila, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	int i = 0;
	while (i<50) {
		if (fila[i] != NULL) {
			soma++;
			i++;
		}
		else {
			break;
		}
	}
	return soma;
}

int contaAcabados(pessoa**acabados) {//conta as pessoas que sa�ram da cantina, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	int i = 0;
	while (i<100) {
		if (acabados[i] != NULL) {
			soma++;
			i++;
		}
		else { 
			break; 
		}
	}
	return soma;
}

void mergeSortAlfabeticamenteUltNome(pessoa**sistema, int m) {// o merge sort da ordena��o alfab�tica pelo �ltimo nome
	if (m < 2) {
		return;
	}
	int mid = m / 2;
	pessoa **left = new pessoa*[mid];
	pessoa**right = new pessoa*[m - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = sistema[i];
	}
	for (int j = mid; j < m; j++) {
		right[j - mid] = sistema[j];
	}
	mergeSortAlfabeticamenteUltNome(left, mid);
	mergeSortAlfabeticamenteUltNome(right, m - mid);
	merge(left, right, sistema, mid, m - mid, m);
}

void merge(pessoa**left, pessoa**right, pessoa**sistema, int n_left, int n_right, int m) {
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n_left && j < n_right) {
		if (left[i]->ultNome < right[j]->ultNome) {
			sistema[k] = left[i];
			i++;
		}
		else {
			sistema[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < n_left) {
		sistema[k] = left[i];
		k++;
		i++;
	}
	while (j < n_right) {
		sistema[k] = right[j];
		j++;
		k++;
	}
}

void adicionaVetorRemovidos(pessoa**removidos, pessoa*p, int tam) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refei��o quer tiveram que sair de emerg�ncia
	for (int i = 0; i < tam; i++) {
		if (removidos[i] == NULL) {
			removidos[i] = p;
			i = tam;
		}
	}
}

void removeSemDinheiro(pessoa**fila, refei��o *r, int*pos, pessoa**removidos, int tamRemovidos, int tamEntrada) { // averigua se o aluno/funcion�rio possui Plafond necess�rio para pagar pela refei��o
	int i = 0;
	bool h�Pessoa = false;
	int indiOuGrupo;
	int num=0;
	while (i < tamEntrada) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->plafond < r->custo) {
					cout << "O aluno com o n�mero " << fila[i]->membro_aluno.num << " n�o possui plafond suficiente. " << endl;
					cout << "Deseja remover s� a pessoa ou o seu grupo inteiro?\n1.S� a pessoa\n2.O grupo todo" << endl;
					num = fila[i]->numDepartamentoOuGrupo;
					h�Pessoa = true;
					break;
				}
			}
			else {
				if (fila[i]->plafond < r->custo) {
					cout << "O elemento de staff com o n�mero " << fila[i]->membro_staff.numFuncionario << " n�o possui plafond suficiente. " << endl;
					cout << "Deseja remover s� a pessoa ou o seu departamento inteiro?\n1.S� a pessoa\n2.O departamento todo" << endl;
					h�Pessoa = true;
					num = fila[i]->numDepartamentoOuGrupo;
					break;
				}
			}
			i++;
		}
		else {
			i = 50;
		}
	}
	if (h�Pessoa) {
		cin >> indiOuGrupo;
		switch (indiOuGrupo)
		{
		case(1):
			removeSemDinheiroPessoa(fila, pos, removidos, tamRemovidos, i);
			break;
		case(2):
			removeSemDinheiroGrupo(fila, pos, removidos, tamRemovidos, num);
			break;
		default:
			break;
		}
	}
}

void removeSemDinheiroPessoa(pessoa**fila, int*pos, pessoa**removidos, int tamRemovidos, int posiPessoa) {
	adicionaVetorRemovidos(removidos, fila[posiPessoa], tamRemovidos);
	fila[posiPessoa] = NULL;
	nullsNoFim(fila, posiPessoa, pos);
}

void removeSemDinheiroGrupo(pessoa**fila, int*pos, pessoa**removidos, int tamRemovidos, int numDepGrupo) {
	for (int s = 0; fila[s]->numDepartamentoOuGrupo == numDepGrupo; s) {
		adicionaVetorRemovidos(removidos, fila[s], tamRemovidos);
		fila[s] = NULL;
		nullsNoFim(fila, s, pos);
	}
}
/*
	
	int num;
	int d = 10;
	for (int e = 0; e < d; e++) {
		if (fila[e]->membro_aluno.num > 0) {
			if (fila[e]->plafond < r->custo) {
				cout << "O aluno " << fila[e]->priNome << " " << fila[e]->ultNome << " n�o possui plafond suficiente. " << endl;
				cout << "Deseja remover s� a pessoa ou o seu grupo inteiro?\n1.S� a pessoa\n2.O grupo todo" << endl;
				h�Pessoa = true;
				running = true;
				num = fila[e]->numDepartamentoOuGrupo;
			}
		}
		else if (fila[e]->membro_staff.numFuncionario > 0) {
			if (fila[e]->plafond < r->custo) {
				cout << "O elemento de staff " << fila[e]->priNome << " " << fila[e]->ultNome << " n�o possui plafond suficiente. " << endl;
				cout << "Deseja remover s� a pessoa ou o seu departamento inteiro?\n1.S� a pessoa\n2.O departamento todo" << endl;
				h�Pessoa = true;
			}
		}
		if (h�Pessoa) {
			while (running) {
				cin >> indiOuGrupo;
				switch (indiOuGrupo)
				{
				case (1):
					adicionaVetorRemovidos(removidos, fila[e], tamRemovidos, r);
					fila[e] = NULL;
					nullsNoFim(fila, e, pos);
					d--;
					running = false;
					break;
				case (2):
						d--;
					}
					running = false;
					break;
				default:
					cout << "Carater n�o v�lido" << endl;
					break;
				}
			}
		}
	}*/