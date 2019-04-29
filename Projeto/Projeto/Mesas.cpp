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
	cout << "Refeição atual:\n\tEntrada: " << r->entrada << "\n\tPrato Principal: " << r->pratoMain << "\n\tCusto:" << r->custo << "€" << endl << endl;
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
	string *cursoSenta = new string;
	string *cursoVagas = new string;
	int inicio;
	int ind = 0;
	int vagas = 0;
	int *vagasP = new int;
	for (int a = 0; a < cantina[0]->totalMesas; a++) {
		vagas += (cantina[a]->tamanho - cantina[a]->numSentados);
	}
	for (int k = 0; k < cantina[0]->totalMesas; k++) {
		procuraEspecial(fila, 50);
		removeSemDinheiro(fila, r, pos, removidos, tamRemovidos);
		for (int u = 0; u < cantina[k]->tamanho; u++) {
			nullsNoFimCantina(cantina[k]->sentados, u, cantina[k]->tamanho);//certifica que todos os NULLs estão nos últimos lugares da mesa
		}
		if (cantina[k]->numSentados == 0) {//no caso de não haver pessoas na mesa acrescenta-se uma pessoa à mesa
			if (fila[ind] != NULL) {
				vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
			}
			if (fila[ind] != NULL && *vagasP < fila[ind]->tamanho) {
				while (fila[ind] != NULL && *vagasP < fila[ind]->tamanho) {
					ind += fila[ind]->tamanho;
					if (fila[ind] != NULL) {
						vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
					}
				}
			}
			if (fila[ind] != NULL) {
				cantina[k]->sentados[0] = fila[ind];
				fila[ind] = NULL;
				nullsNoFim(fila, ind, pos);
				(cantina[k]->numSentados)++;
				(vagas)--;
			}
		}
		if (cantina[k]->numSentados != cantina[k]->tamanho && cantina[k]->numSentados != 0) {//se a mesa não estiver cheia
			for (int l = 0; l < cantina[k]->tamanho; l++) {
				if (cantina[k]->sentados[l] != NULL) {
					if (cantina[k]->sentados[l]->membro_aluno.num > 0) {
						*cursoSenta = cantina[k]->sentados[l]->membro_aluno.curso;
						l = cantina[k]->tamanho;
					}
					else {
						*cursoSenta = "nãoconta";
					}
				}
			}
			for (int i = 0; i < cantina[k]->tamanho; i++) {
				if (fila[ind] != NULL) {
					vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
				}
				if (fila[ind] != NULL) {
					if (*vagasP < fila[ind]->tamanho) {
						while (fila[ind] != NULL && *vagasP < fila[ind]->tamanho) {
							ind += fila[ind]->tamanho; 
							if (fila[ind] != NULL) {
								vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
							}
							inicio = ind;
						}
						if (fila[ind] != NULL && *vagasP >= fila[ind]->tamanho) {
							ind = inicio;//para certificar que entram as pessoas certas na cantina
						}
					}
				}
				if (cantina[k]->sentados[i] == NULL) {
					if (fila[ind] != NULL) {
						if (*cursoSenta != "nãoconta") {
							if (fila[ind]->membro_aluno.num > 0) {
								if (fila[ind]->membro_aluno.curso == *cursoSenta) {
									cantina[k]->sentados[i] = fila[ind];
									fila[ind] = NULL;
									nullsNoFim(fila, ind, pos);
									(cantina[k]->numSentados)++;
									(vagas)--;
								}
								else {
									i = 100;
								}
							}
							else {
								if (fila[ind]->membro_staff.numFuncionario > 0) {// se for de staff pode entrar livremente
									cantina[k]->sentados[i] = fila[ind];
									fila[ind] = NULL;
									nullsNoFim(fila, ind, pos);
									(cantina[k]->numSentados)++;
									(vagas)--;
								}
							}
						}
						else {
							cantina[k]->sentados[i] = fila[ind];
							fila[ind] = NULL;
							nullsNoFim(fila, ind, pos);
							(cantina[k]->numSentados)++;
							(vagas)--;
							if (fila[ind + 1] != NULL) {
								if ((fila[ind]->membro_aluno.num > 0 && fila[ind + 1]->membro_aluno.num > 0) && (fila[ind]->membro_aluno.curso != fila[ind + 1]->membro_aluno.curso)) {
									i = 100;
								}
							}
							else {
								i = 100;
							}
						}
					}
					else {
						i = 100;
					}
				}
			}
		}
		vagas -= (cantina[k]->tamanho - cantina[k]->numSentados);
	}
	(*pos)++; //assegura que não se apaga ninguém quando se gera novas pessoas para a fila
	delete cursoSenta, cursoVagas;
}

void escreveCantina(mesa ** cantina) {//vai escrever a cantina como diz no nome
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		cout << "Mesa " << cantina[i]->numMesa << "(CAPACIDADE " << cantina[i]->tamanho << "):" << endl;
		for (int j = 0; j < cantina[i]->tamanho; j++) {
			escrevePessoaCantina(cantina[i]->sentados[j]);
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
	for (i; i < cantina[0]->totalMesas; i++) {
		if (cantina[i]->numSentados > 0) {
			for (j = 0; j < cantina[i]->numSentados; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					(cantina[i]->sentados[j]->duração)--;
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
	cout << "Escolha um número para sair" << endl;
	cin >> n;
	for (i; i < cantina[0]->totalMesas; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
					if (cantina[i]->sentados[j]->membro_aluno.num == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver definição da função
						(cantina[i]->numSentados)--;
						cantina[i]->sentados[j] = NULL;
						nullsNoFimCantina(cantina[i]->sentados, j, cantina[i]->tamanho);//mete os NULLs nas últimas posições da mesa
						removeu = true;
					}
				}
				else if (cantina[i]->sentados[j]->membro_staff.numFuncionario > 0) {
					if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
						(cantina[i]->numSentados)--;
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
	if (i == cantina[0]->totalMesas && !removeu) {
		cout << "Não válido" << endl;
	}
}

void retiraEmergGrupo(mesa **cantina, pessoa**acabados, int tamAcabados, refeição *r) {//função para os casos de emergência, neste caso retirar um grupo em caso de emergência
	int n;
	int i = 0;
	int j;
	bool removeu = false;
	cout << "Escolha um grupo para sair" << endl;
	cin >> n;
	for (i; i < cantina[0]->totalMesas; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == n) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver definição da função
					(cantina[i]->numSentados)--;
					cantina[i]->sentados[j] = NULL;
					removeu = true;
					nullsNoFimCantina(cantina[i]->sentados, j, cantina[i]->tamanho);//mete os NULLs nas últimas posições da mesa
				}
			}
		}
	}
	if (i == cantina[0]->totalMesas && !removeu) {
		cout << "Não válido" << endl;
	}
}

void removeAcabados(mesa **cantina, pessoa** acabados, int tamAcabados, refeição*r) {
	int i = 0;
	int j;
	for (i; i < cantina[0]->totalMesas; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->duração == 0) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
					(cantina[i]->numSentados)--;
					cantina[i]->sentados[j] = NULL;
				}
			}
		}
		nullsNoFimCantina(cantina[i]->sentados, 0, cantina[i]->tamanho);
	}
}

void adicionaVetorAcabados(pessoa**acabados, pessoa*p, int tam, refeição*r) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refeição quer tiveram que sair de emergência
	for (int i = 0; i < tam; i++) {
		if (acabados[i] == NULL) {
			p->plafond -= r->custo;//cobra a refeição aos que saem da cantina
			acabados[i] = p;
			i = tam;
		}
	}
}

void ordenaAlfabeticamenteUltNome(mesa**cantina, pessoa**fila, pessoa**acabados, int pessoasNaCantina, int pessoasNaFila, int pessoasAcabados) {//opção 1, ordena alfabeticamente todas as pessoas que passaram pelo sistema pelos seus últimos nomes
	int total = pessoasNaCantina + pessoasNaFila + pessoasAcabados;//nº de pessoas no sistema
	cout << pessoasNaCantina << "\t" << pessoasNaFila << "\t" << pessoasAcabados << endl;
	pessoa**sistema = new pessoa*[total];
	criaFila(sistema, total);
	int i = 0;
	int x = 0;
	int y = 0;
	while (i < total) {
		for (int k = 0; k < cantina[0]->totalMesas; k++) {
			for (int j = 0; j < cantina[k]->numSentados; j++) {//vai adicionar ao vetor que vai ser ordenado as pessoas da cantina
				sistema[i] = cantina[k]->sentados[j];
				i++;
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
	cout << "Pessoas que estiveram na fila, entraram na cantina e já saíram, ordenadas alfabeticamente pelo último nome:" << endl << endl;
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
	while (i < 50) {
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
	while (i < 100) {
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

void mergeSortAlfabeticamenteUltNome(pessoa**sistema, int tam) {// o merge sort da ordenação alfabética pelo último nome
	if (tam < 2) {
		return;
	}
	int mid = tam / 2;
	pessoa **left = new pessoa*[mid];
	pessoa**right = new pessoa*[tam - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = sistema[i];
	}
	for (int j = mid; j < tam; j++) {
		right[j - mid] = sistema[j];
	}
	mergeSortAlfabeticamenteUltNome(left, mid);
	mergeSortAlfabeticamenteUltNome(right, tam - mid);
	mergeUltNome(left, right, sistema, mid, tam - mid, tam);
}

void mergeUltNome(pessoa**left, pessoa**right, pessoa**sistema, int n_left, int n_right, int tam) {
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

void removeSemDinheiro(pessoa**fila, refeição *r, int*pos, pessoa**removidos, int tamRemovidos) { // averigua se o aluno/funcionário possui Plafond necessário para pagar pela refeição
	int i = 0;
	bool háPessoa = false;
	int indiOuGrupo;
	int num = 0;
	while (i < 50) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->plafond < r->custo) {
					cout << "***** ATENÇÃO *****\nO aluno com o número " << fila[i]->membro_aluno.num << " não possui plafond suficiente. " << endl;
					cout << "Deseja remover só a pessoa ou o seu grupo inteiro?\n1.Só a pessoa\n2.O grupo todo" << endl;
					num = fila[i]->numDepartamentoOuGrupo;
					háPessoa = true;
					break;
				}
			}
			else {
				if (fila[i]->plafond < r->custo) {
					cout << "***** ATENÇÃO *****\nO elemento de staff com o número " << fila[i]->membro_staff.numFuncionario << " não possui plafond suficiente. " << endl;
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
			removeSemDinheiroPessoa(fila, pos, removidos, tamRemovidos, i, num);
			break;
		case(2):
			removeSemDinheiroGrupo(fila, pos, removidos, tamRemovidos, num);
			break;
		default:
			break;
		}
	}
}

void removeSemDinheiroPessoa(pessoa**fila, int*pos, pessoa**removidos, int tamRemovidos, int posiPessoa, int numDepGrupo) {
	adicionaVetorRemovidos(removidos, fila[posiPessoa], tamRemovidos);
	fila[posiPessoa] = NULL;
	nullsNoFim(fila, posiPessoa, pos);
	int s = 0;
	int conta = 0;
	while (s < 50) {
		if (fila[s] != NULL) {
			if (fila[s]->numDepartamentoOuGrupo == numDepGrupo) {
				conta++;
			}
			s++;
		}
		else {
			s = 50;
		}
	}
	for (s = 0; s < 50; s++) {
		if (fila[s] != NULL) {
			if (fila[s]->numDepartamentoOuGrupo == numDepGrupo) {
				fila[s]->tamanho = conta;
				conta--;
			}
		}
		else {
			s = 50;
		}
	}
}

void removeSemDinheiroGrupo(pessoa**fila, int*pos, pessoa**removidos, int tamRemovidos, int numDepGrupo) {
	int s = 0;
	while (s < 50) {
		if (fila[s] != NULL) {
			if (fila[s]->numDepartamentoOuGrupo == numDepGrupo) {
				adicionaVetorRemovidos(removidos, fila[s], tamRemovidos);
				fila[s] = NULL;
				nullsNoFim(fila, s, pos);
			}
			else {
				s++;
			}
		}
		else {
			s = 50;
		}
	}
}

void mergeSortMesasNumSentados(mesa ** cantina, int tam) {
	if (tam < 2) {
		return;
	}
	int mid = tam / 2;
	mesa **left = new mesa*[mid];
	mesa**right = new mesa*[tam - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = cantina[i];
	}
	for (int j = mid; j < tam; j++) {
		right[j - mid] = cantina[j];
	}
	mergeSortMesasNumSentados(left, mid);
	mergeSortMesasNumSentados(right, tam - mid);
	mergeMesas(left, right, cantina, mid, tam - mid, tam);
}

void mergeMesas(mesa ** left, mesa ** right, mesa ** cantina, int n_left, int n_right, int tam) {
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n_left && j < n_right) {
		if (left[i]->numSentados < right[j]->numSentados) {
			cantina[k] = left[i];
			i++;
		}
		else {
			cantina[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < n_left) {
		cantina[k] = left[i];
		k++;
		i++;
	}
	while (j < n_right) {
		cantina[k] = right[j];
		j++;
		k++;
	}
}

void reverseOrdenação(mesa**cantina, int tam) {
	if (tam < 2) {
		return;
	}
	int mid = tam / 2;
	mesa **left = new mesa*[mid];
	mesa**right = new mesa*[tam - mid];
	for (int i = 0; i < mid; i++) {
		left[i] = cantina[i];
	}
	for (int j = mid; j < tam; j++) {
		right[j - mid] = cantina[j];
	}
	reverseOrdenação(left, mid);
	reverseOrdenação(right, tam - mid);
	mergeReverseOrdenação(left, right, cantina, mid, tam - mid, tam);
}

void mergeReverseOrdenação(mesa ** left, mesa ** right, mesa ** cantina, int n_left, int n_right, int tam) {
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n_left && j < n_right) {
		if (left[i]->numMesa < right[j]->numMesa) {
			cantina[k] = left[i];
			i++;
		}
		else {
			cantina[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < n_left) {
		cantina[k] = left[i];
		k++;
		i++;
	}
	while (j < n_right) {
		cantina[k] = right[j];
		j++;
		k++;
	}
}

void vagasPossiveis(int*vagasPossiveis, pessoa*p, mesa**cantina, int k, int vagas) {
	*vagasPossiveis = vagas;
	string *cursoVagas = new string;
	if (p != NULL) {
		for (int a = k; a < cantina[0]->totalMesas; a++) {
			if (cantina[a]->numSentados != 0) {
				for (int l = 0; l < cantina[a]->tamanho; l++) {
					if (cantina[a]->sentados[l] != NULL) {
						if (cantina[a]->sentados[l]->membro_aluno.num > 0) {
							*cursoVagas = cantina[a]->sentados[l]->membro_aluno.curso;
							l = cantina[a]->tamanho;
						}
						else {
							*cursoVagas = "nãoconta";
						}
					}
				}
				if (*cursoVagas != "nãoconta") {
					if (p->membro_aluno.num > 0) {
						if (p->membro_aluno.curso != *cursoVagas) {
							*vagasPossiveis -= (cantina[a]->tamanho - cantina[a]->numSentados);
						}
					}
				}
			}
		}
	}
	delete cursoVagas;
}