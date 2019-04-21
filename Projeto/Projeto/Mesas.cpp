#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<string>
using namespace std;

refeição* novaMeal(bool primeiraVez) {//vai receber os dados do utilizador para uma nova refeição
	refeição *meal = new refeição();
	if (!primeiraVez) {
		system("pause");
		cin.get();
	}
	cout << "***** REFEIÇÃO NOVA *****\nA cantina EDA necessita de uma nova refeição\n\t1. Introduza a entrada:" << endl;
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o preço:" << endl;
	cin >> meal->custo;
	return meal;
}

void escreveMeal(refeição *r) {//escreve a refeição atual
	cout << "Refeição atual:\n\tEntrada: " << r->entrada << "\n\tPrato Principal: " << r->pratoMain << "\n\tCusto:" << r->custo << "€" << endl;
}

mesa** criaCantina() {//vai obter o tamanho da cantina e gerar tamanhos de mesas até a cantina estar preenchida, tamanhos guardados num vetor
	int *TCANTINA = new int(rand() % 21 + 30);
	int *t = new int();
	int *aux = new int[25];
	int *itera = new int(0);
	while (*t < *TCANTINA) {
		int *TMESA = new int(rand() % 4 + 2);
		*t += *TMESA;
		aux[(*itera)++] = *TMESA;
		if (*TCANTINA - *t <= 1 && *TCANTINA != *t) {//quando isto acontece, nenhuma mesa poderá preencher o último espaço ou já ultrapassamos o tamanho da cantina, por isso faz-se um "reset", "apaga-se" a mesa que provocou isto e tenta-se outra vez
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

void preencheCantina(mesa**cantina, pessoa**fila, int *pos, refeição*r, pessoa**removidos, int tamRemovidos) {//vai passar as pessoas da fila para a cantina
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
		if (cantina[k]->numSentados == 0) {//no caso de não haver pessoas na mesa
			procuraEspecial(fila, 50);
			int tammesa = cantina[k]->tamanho;
			removeSemDinheiro(fila, r, pos, removidos, tamRemovidos, tammesa);
			int sentados = cantina[k]->numSentados;
			int mesmocurso = 1;
			if (fila[ind]->membro_aluno.num > 0) {
				curso = fila[ind]->membro_aluno.curso;
			}
			else {
				curso = "nãoconta";//se a pessoa para entrar for de staff não há restrições
			}
			for (j = 1; j < tammesa; j++) {
				if (curso != "nãoconta") {//para confirmar que não se sentam pessoas de cursos diferentes na mesma mesa
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
				cantina[k]->numSentados = sentados;//atualiza o número de pessoas sentadas na mesa
			}
		}
		else {// no caso de já haver gente na mesa, procedimento é quase igual
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
							cursoSenta = "nãoconta";
						}
					}
				}
				for (int p = 0; p < tamanhoMesa - numSentados; p++) {
					mesmocurso = 0;
					if (cursoSenta != "nãoconta") {
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
	(*pos)++; //assegura que não se apaga ninguém quando se gera novas pessoas para a fila
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

void nullsNoFim(pessoa**fila, int beg, int *end) {//quando se passa uma pessoa da fila para a cantina, o NULL no lugar dessa pessoa tem de ser mandado para o fim, ou para a primeira posição onde está um NULL, para evitar swaps desnecessários
	for (beg; beg <= (*end - 1); beg++) {
		swap(fila[beg], fila[beg + 1]);
	}
	(*end)--;//evita swaps desnecessários 
}

void nullsNoFimCantina(pessoa**sentados, int beg, int end) {//mesma coisa que a versão anterior, só que pondo os NULLs gerados de retirar as pessoas que acabam da mesa nas últimas posições da mesa, para ser mais fácil aceder às pessoas sentadas na mesa
	for (beg; beg <= (end - 2); beg++) {
		if (sentados[beg] == NULL) {
			swap(sentados[beg], sentados[beg + 1]);
		}
	}

}

void removeDuração(mesa **cantina) {//como o nome indica, com cada ciclo remove 1 à duração
	int i = 0;
	int j;
	int tam = cantina[0]->totalMesas;
	for (i; i < tam; i++) {
		if (cantina[i]->numSentados > 0) {
			for (j = 0; j < cantina[i]->numSentados; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					cantina[i]->sentados[j]->duração--;
				}
			}
		}
	}
}

void retiraEmergPessoa(mesa **cantina, pessoa**acabados, int tamAcabados, refeição *r) {//função para os casos de emergência, neste caso retirar uma pessoa em caso de emergência
	int n;
	int i = 0;
	int j;
	bool removeu = false;
	int *tam = new int(cantina[0]->totalMesas);
	cout << "Emergência, escolha um número pra sair" << endl;
	cin >> n;
	for (i; i < *tam; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
					if (cantina[i]->sentados[j]->membro_aluno.num == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver definição da função
						cantina[i]->numSentados--;
						cantina[i]->sentados[j] = NULL;
						nullsNoFimCantina(cantina[i]->sentados, j, cantina[i]->tamanho);//mete os NULLs nas últimas posições da mesa
						removeu = true;
					}
				}
				else if (cantina[i]->sentados[j]->membro_staff.numFuncionario > 0) {
					if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
						cantina[i]->numSentados--;
						cantina[i]->sentados[j] = NULL;
						nullsNoFimCantina(cantina[i]->sentados, j, cantina[i]->tamanho);//mete os NULLs nas últimas posições da mesa
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
		cout << "Não válido" << endl;
	}
}

void retiraEmergGrupo(mesa **cantina, pessoa**acabados, int tamAcabados, refeição *r) {//função para os casos de emergência, neste caso retirar um grupo em caso de emergência
	int n;
	int i = 0;
	int j;
	int *tam = new int(cantina[0]->totalMesas);
	bool removeu = false;
	cout << "Emergência, escolha um grupo pra sair" << endl;
	cin >> n;
	for (i; i < *tam; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == n) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver definição da função
					cantina[i]->numSentados--;
					cantina[i]->sentados[j] = NULL;
					removeu = true;
				}
			}
		}
		nullsNoFimCantina(cantina[i]->sentados, 0, cantina[i]->tamanho);//mete os NULLs nas últimas posições da mesa
	}
	if (i == *tam && !removeu) {
		cout << "Não válido" << endl;
	}
}

void removeAcabados(mesa **cantina, pessoa** acabados, int tamAcabados, refeição*r) {
	int i = 0;
	int j;
	int tam = cantina[0]->totalMesas;
	for (i; i < tam; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->duração == 0) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
					cantina[i]->numSentados--;
					cantina[i]->sentados[j] = NULL;
				}
			}
		}
		nullsNoFimCantina(cantina[i]->sentados, 0, cantina[i]->tamanho);
	}
}

void adicionaVetorAcabados(pessoa**acabados,pessoa*p, int tam, refeição*r) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refeição quer tiveram que sair de emergência
	for (int i =0; i < tam; i++) {
		if (acabados[i] == NULL) {
			p->plafond -= r->custo;//cobra a refeição aos que saem da cantina
			acabados[i] = p;
			i = tam;
		}
	}
}

void ordenaAlfabeticamenteUltNome(mesa**cantina, pessoa**fila, pessoa**acabados, int pessoasNaCantina, int pessoasNaFila, int pessoasAcabados) {//opção 1, ordena alfabeticamente todas as pessoas que passaram pelo sistema pelos seus últimos nomes
	int total = pessoasNaCantina + pessoasNaFila + pessoasAcabados;//nº de pessoas no sistema
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
		while (y < pessoasAcabados) {//vai adicionar ao vetor que vai ser ordenado as pessoas que saíram da cantina
			sistema[i] = acabados[y];
			i++;
			y++;
		}
	}
	mergeSortAlfabeticamenteUltNome(sistema, total);//usa-se uma adaptação do mergeSort pois é um dos mais eficientes algoritmos de ordenação
	system("CLS"); 
	cout << "Pessoas que estiveram na fila, entraram na cantina e já saíram ordenadas alfabeticamente pelo último nome:" << endl << endl;
	escreveFila(sistema, total);
}

int contaPessoasCantina(mesa**cantina) {//conta as pessoas que estão na cantina, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		soma += cantina[i]->numSentados;
	}
	return soma;
}

int contaPessoasFila(pessoa**fila) {//conta as pessoas que estão na fila, para ser usado no ordenaAlfabeticamenteUltNome
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

int contaAcabados(pessoa**acabados) {//conta as pessoas que saíram da cantina, para ser usado no ordenaAlfabeticamenteUltNome
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

void mergeSortAlfabeticamenteUltNome(pessoa**sistema, int m) {// o merge sort da ordenação alfabética pelo último nome
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

void adicionaVetorRemovidos(pessoa**removidos, pessoa*p, int tam) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refeição quer tiveram que sair de emergência
	for (int i = 0; i < tam; i++) {
		if (removidos[i] == NULL) {
			removidos[i] = p;
			i = tam;
		}
	}
}

void removeSemDinheiro(pessoa**fila, refeição *r, int*pos, pessoa**removidos, int tamRemovidos, int tamEntrada) { // averigua se o aluno/funcionário possui Plafond necessário para pagar pela refeição
	int i = 0;
	bool háPessoa = false;
	int indiOuGrupo;
	int num=0;
	while (i < tamEntrada) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->plafond < r->custo) {
					cout << "O aluno com o número " << fila[i]->membro_aluno.num << " não possui plafond suficiente. " << endl;
					cout << "Deseja remover só a pessoa ou o seu grupo inteiro?\n1.Só a pessoa\n2.O grupo todo" << endl;
					num = fila[i]->numDepartamentoOuGrupo;
					háPessoa = true;
					break;
				}
			}
			else {
				if (fila[i]->plafond < r->custo) {
					cout << "O elemento de staff com o número " << fila[i]->membro_staff.numFuncionario << " não possui plafond suficiente. " << endl;
					cout << "Deseja remover só a pessoa ou o seu departamento inteiro?\n1.Só a pessoa\n2.O departamento todo" << endl;
					háPessoa = true;
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
	if (háPessoa) {
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
				cout << "O aluno " << fila[e]->priNome << " " << fila[e]->ultNome << " não possui plafond suficiente. " << endl;
				cout << "Deseja remover só a pessoa ou o seu grupo inteiro?\n1.Só a pessoa\n2.O grupo todo" << endl;
				háPessoa = true;
				running = true;
				num = fila[e]->numDepartamentoOuGrupo;
			}
		}
		else if (fila[e]->membro_staff.numFuncionario > 0) {
			if (fila[e]->plafond < r->custo) {
				cout << "O elemento de staff " << fila[e]->priNome << " " << fila[e]->ultNome << " não possui plafond suficiente. " << endl;
				cout << "Deseja remover só a pessoa ou o seu departamento inteiro?\n1.Só a pessoa\n2.O departamento todo" << endl;
				háPessoa = true;
			}
		}
		if (háPessoa) {
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
					cout << "Carater não válido" << endl;
					break;
				}
			}
		}
	}*/