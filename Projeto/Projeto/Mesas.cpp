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
	cout << "***** REFEI��O NOVA *****"<< endl << "A cantina EDA necessita de uma nova refei��o" << endl << "\t1. Introduza a entrada:" << endl;
	getline(cin, meal->entrada);
	cout << "\t2. Introduza o prato principal:" << endl;
	getline(cin, meal->pratoMain);
	cout << "\t3. Introduza o pre�o:" << endl;
	cin >> meal->custo;
	return meal;
}

void escreveMeal(refei��o *r) {//escreve a refei��o atual
	cout << "Refei��o atual:\n\tEntrada: " << r->entrada << "\n\tPrato Principal: " << r->pratoMain << "\n\tCusto:" << r->custo << " EUR" << endl << endl;
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
		if (cantina[k]->numSentados == 0) {//no caso de n�o haver pessoas na mesa acrescenta-se uma pessoa � mesa
			if (fila[ind] != NULL) {
				vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
			}
			if (fila[ind] != NULL && *vagasP < fila[ind]->tamanho && ind < 50) {
				while (fila[ind] != NULL && *vagasP < fila[ind]->tamanho && ind < 50) {
					ind += fila[ind]->tamanho;
					if (fila[ind] != NULL && ind < 50) {
						vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
					}
				}
			}
			if (fila[ind] != NULL && ind < 50) {
				cantina[k]->sentados[0] = fila[ind];
				fila[ind] = NULL;
				nullsNoFim(fila, ind, pos);
				(cantina[k]->numSentados)++;
				(vagas)--;
			}
		}
		if (cantina[k]->numSentados != cantina[k]->tamanho && cantina[k]->numSentados != 0) {//se a mesa n�o estiver cheia
			for (int l = 0; l < cantina[k]->tamanho; l++) {
				if (cantina[k]->sentados[l] != NULL) {
					if (cantina[k]->sentados[l]->membro_aluno.num > 0) {
						*cursoSenta = cantina[k]->sentados[l]->membro_aluno.curso;
						l = cantina[k]->tamanho;
					}
					else {
						*cursoSenta = "n�oconta";
					}
				}
			}
			for (int i = 0; i < cantina[k]->tamanho; i++) {
				if (fila[ind] != NULL && ind < 50) {
					vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
				}
				if (fila[ind] != NULL && ind < 50) {
					if (*vagasP < fila[ind]->tamanho && ind < 50) {
						while (fila[ind] != NULL && *vagasP < fila[ind]->tamanho && ind < 50) {
							ind += fila[ind]->tamanho; 
							if (fila[ind] != NULL && ind < 50) {
								vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
							}
							inicio = ind;
						}
						if (fila[ind] != NULL && *vagasP >= fila[ind]->tamanho && ind < 50) {
							ind = inicio;//para certificar que entram as pessoas certas na cantina
						}
					}
				}
				if (cantina[k]->sentados[i] == NULL) {
					if (fila[ind] != NULL && ind < 50) {
						if (*cursoSenta != "n�oconta") {
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
							if (fila[ind]->membro_aluno.num > 0) {
								*cursoSenta = fila[ind]->membro_aluno.curso;
							}
							cantina[k]->sentados[i] = fila[ind];
							fila[ind] = NULL;
							nullsNoFim(fila, ind, pos);
							(cantina[k]->numSentados)++;
							(vagas)--;
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
	(*pos)++; //assegura que n�o se apaga ningu�m quando se gera novas pessoas para a fila
	delete cursoSenta, cursoVagas;
}

void escreveCantina(mesa ** cantina) {//vai escrever a cantina como diz no nome
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		cout << "Mesa " << cantina[i]->numMesa << "(CAPACIDADE " << cantina[i]->tamanho << "):" << endl;
		for (int j = 0; j < cantina[i]->tamanho; j++) {
			escrevePessoaCantina(cantina[i]->sentados[j]);
		}
		cout << "---------------------------------------------------------------------------------------------------" << endl;
	}
}

void nullsNoFim(pessoa**fila, int beg, int *end) {//quando se passa uma pessoa da fila para a cantina, o NULL no lugar dessa pessoa tem de ser mandado para o fim, ou para a primeira posi��o onde est� um NULL, para evitar swaps desnecess�rios
	for (beg; beg <= (*end - 1); beg++) {
		swap(fila[beg], fila[beg + 1]);
	}
	(*end)--;//evita swaps desnecess�rios 
}

void removeDura��o(mesa **cantina) {//como o nome indica, com cada ciclo remove 1 � dura��o
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		if (cantina[i]->numSentados > 0) {
			for (int j = 0; j < cantina[i]->tamanho; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					(cantina[i]->sentados[j]->dura��o)--;
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
	cout << "Escolha um n�mero para sair" << endl;
	cin >> n;
	for (i; i < cantina[0]->totalMesas; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
					if (cantina[i]->sentados[j]->membro_aluno.num == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver defini��o da fun��o
						(cantina[i]->numSentados)--;
						cantina[i]->sentados[j] = NULL;
						removeu = true;
					}
				}
				else if (cantina[i]->sentados[j]->membro_staff.numFuncionario > 0) {
					if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
						(cantina[i]->numSentados)--;
						cantina[i]->sentados[j] = NULL;
						removeu = true;
					}
				}
			}
		}
	}
	if (i == cantina[0]->totalMesas && !removeu) {
		cout << "N�o v�lido" << endl;
	}
}

void retiraEmergGrupo(mesa **cantina, pessoa**acabados, int tamAcabados, refei��o *r) {//fun��o para os casos de emerg�ncia, neste caso retirar um grupo em caso de emerg�ncia
	int n; 
	int i = 0;
	bool removeu = false;
	cout << "Escolha um grupo para sair" << endl;
	cin >> n;
	for (i = 0; i < cantina[0]->totalMesas; i++) {
		for (int j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == n) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver defini��o da fun��o
					(cantina[i]->numSentados)--;
					cantina[i]->sentados[j] = NULL;
					removeu = true;
				}
			}
		}
	}
	if (i == cantina[0]->totalMesas && !removeu) {
		cout << "N�o v�lido" << endl;
	}
}

void removeAcabados(mesa **cantina, pessoa** acabados, int tamAcabados, refei��o*r) {
	int i = 0;
	int j;
	for (i; i < cantina[0]->totalMesas; i++) {
		for (j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->dura��o == 0) {
					adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
					(cantina[i]->numSentados)--;
					cantina[i]->sentados[j] = NULL;
				}
			}
		}
	}
}

void adicionaVetorAcabados(pessoa**acabados, pessoa*p, int tam, refei��o*r) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refei��o quer tiveram que sair de emerg�ncia
	for (int i = 0; i < tam; i++) {
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
	cout << "\t\t\t\t\t Cantina EDA" << endl;
	cout << "Pessoas que est�o na fila, est�o na cantina e que j� terminaram a sua refei��o, ordenadas alfabeticamente pelo �ltimo nome:" << endl << endl;
	escreveOp��es(sistema, total);
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

int contaAcabados(pessoa**acabados) {//conta as pessoas que sa�ram da cantina, para ser usado no ordenaAlfabeticamenteUltNome
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

void mergeSortAlfabeticamenteUltNome(pessoa**sistema, int tam) {// o merge sort da ordena��o alfab�tica pelo �ltimo nome
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

void adicionaVetorRemovidos(pessoa**removidos, pessoa*p, int tam) {//adiciona a um vetor as pessoas que saiem da cantina, quer acabaram a refei��o quer tiveram que sair de emerg�ncia
	for (int i = 0; i < tam; i++) {
		if (removidos[i] == NULL) {
			removidos[i] = p;
			i = tam;
		}
	}
}

void removeSemDinheiro(pessoa**fila, refei��o *r, int*pos, pessoa**removidos, int tamRemovidos) { // averigua se o aluno/funcion�rio possui Plafond necess�rio para pagar pela refei��o
	int i = 0;
	bool h�Pessoa = false;
	int indiOuGrupo;
	int num = 0;
	while (i < 50) {
		if (fila[i] != NULL) {
			if (fila[i]->membro_aluno.num > 0) {
				if (fila[i]->plafond < r->custo) {
					cout << "***** ATEN��O *****" << endl << "O aluno com o n�mero " << fila[i]->membro_aluno.num << " n�o possui plafond suficiente para iniciar a refei��o." << endl;
					cout << "\t1.Remover aluno da entrada" << endl << "\t2.Remover grupo da entrada" << endl;
					num = fila[i]->numDepartamentoOuGrupo;
					h�Pessoa = true;
					break;
				}
			}
			else {
				if (fila[i]->plafond < r->custo) {
					cout << "***** ATEN��O *****\nO elemento de staff com o n�mero " << fila[i]->membro_staff.numFuncionario << " n�o possui plafond suficiente para iniciar a refei��o." << endl;
					cout << "\t1.Remover funcion�rio da entrada" << endl << "\t2.Remover grupo da entrada" << endl;
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
		cout << "**** Comando: ";
		cin >> indiOuGrupo;
		cout << endl;
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

mesa** bubbleSortMesasNumSentados (mesa**cantina, int tam) {
	bool trocaOcorreu = true;
	mesa**aux = new mesa*[tam];
	for (int a = 0; a < cantina[0]->totalMesas; a++) {
		aux[a] = cantina[a];
	}
	for (int i = 0; i < tam - 1 && trocaOcorreu; i++)
	{
		trocaOcorreu = false;
		for (int j = tam - 1; j > i; j--)
		{
			if (aux[j]->numSentados < aux[j - 1]->numSentados)
			{
				swap(aux[j], aux[j - 1]);
				trocaOcorreu = true;
			}
		}
	}
	return aux;
}

void vagasPossiveis(int*vagasPossiveis, pessoa*p, mesa**cantina, int k, int vagas) {
	*vagasPossiveis = vagas;
	string *cursoVagas = new string;
	for (int a = k; a < cantina[0]->totalMesas; a++) {
		if (cantina[a]->numSentados != 0) {
			for (int l = 0; l < cantina[a]->tamanho; l++) {
				if (cantina[a]->sentados[l] != NULL) {
					if (cantina[a]->sentados[l]->membro_aluno.num > 0) {
						*cursoVagas = cantina[a]->sentados[l]->membro_aluno.curso;
						l = cantina[a]->tamanho;
					}
					else {
						*cursoVagas = "n�oconta";
					}
				}
			}
			if (*cursoVagas != "n�oconta") {
				if (p->membro_aluno.num > 0) {
					if (p->membro_aluno.curso != *cursoVagas) {
						*vagasPossiveis -= (cantina[a]->tamanho - cantina[a]->numSentados);
					}
				}
			}
		}
	}
	delete cursoVagas;
}

void mudaNome(mesa**cantina, pessoa**fila, int tamFila) {
	int PriOuUltOuAmbos;
	int n;
	bool h�PessoaCantina = false;
	bool h�PessoaFila = false;
	int mesaPessoa;
	int posi��o;
	bool restarta = true;
	cout << endl << "Escreva o n�mero de aluno / funcion�rio do indiv�duo ao qual deseja alterar o nome" << endl;
	cout << "**** Comando: ";
	cin >> n;
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		for (int j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
					if (cantina[i]->sentados[j]->membro_aluno.num == n) {
						h�PessoaCantina = true;
						posi��o = j;
						break;
					}
				}
				else {
					if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
						h�PessoaCantina = true;
						posi��o = j;
						break;
					}
				}
			}
		}
		if (h�PessoaCantina) {
			mesaPessoa = i;
			i = cantina[0]->totalMesas;
		}
	}
	if (!h�PessoaCantina) {
		for (int u = 0; u < tamFila; u++) {
			if (fila[u] != NULL) {
				if (fila[u]->membro_aluno.num > 0) {
					if (fila[u]->membro_aluno.num == n) {
						h�PessoaFila = true;
						posi��o = u;
						break;
					}
				}
				else {
					if (fila[u]->membro_staff.numFuncionario == n) {
						h�PessoaFila = true;
						posi��o = u;
						break;
					}
				}
			}
		}
	}
	if (h�PessoaFila || h�PessoaCantina) {
		cout << endl << "Deseja alterar" << endl << "\t1. O primeiro nome" << endl << "\t2. O �ltimo nome" << endl << "\t3. Ambos os nomes do indiv�duo" << endl;
		cout << "**** Comando: ";
		cin >> PriOuUltOuAmbos;
		while (restarta) {
			switch (PriOuUltOuAmbos)
			{
			case 1:
				if (h�PessoaCantina) {
					cout << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					cin.get();
					getline(cin, cantina[mesaPessoa]->sentados[posi��o]->priNome);
				}
				else {
					cout << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					cin.get();
					getline(cin, fila[posi��o]->priNome);
				}
				restarta = false;
				break;
			case 2:
				if (h�PessoaCantina) {
					cout << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					cin.get();
					getline(cin, cantina[mesaPessoa]->sentados[posi��o]->ultNome);
				}
				else {
					cout << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					cin.get();
					getline(cin, fila[posi��o]->ultNome);
				}
				restarta = false;
				break;
			case 3:
				if (h�PessoaCantina) {
					cout << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					cin.get();
					getline(cin, cantina[mesaPessoa]->sentados[posi��o]->priNome);
					cout << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					cin.get();
					getline(cin, cantina[mesaPessoa]->sentados[posi��o]->ultNome);
				}
				else {
					cout << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					cin.get();
					getline(cin, fila[posi��o]->priNome);
					cout << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					cin.get();
					getline(cin, fila[posi��o]->ultNome);
				}
				restarta = false;
				break;
			default:
				cout << "Isso n�o � uma das op��es" << endl;
				break;
			}
		}
	}
	else {
		cout << "Essa pessoa n�o se encontra nem na cantina nem na fila de espera." << endl;
	}
}

void editaDura��o(mesa** cantina, pessoa**fila, int tamFila) {
	int num; 
	int novaDura��o;
	bool tentaOutraVez = true;
	bool h�GrupoCantina = false;
	bool h�GrupoFila = false;
	cout << "Escreva o n�mero do grupo / departamento ao qual deseja alterar a dura��o de refei��o" << endl << "**** Comando: ";
	cin >> num;
	while (tentaOutraVez) {
		cout << endl << "Escreva a nova dura��o de refei��o dos elementos do grupo / departamento" << endl << "**** Comando: ";
		cin >> novaDura��o;
		if (novaDura��o <= 0) {
			cout << "A nova dura��o tem de ser maior que 0!" << endl << endl;
		}
		else {
			tentaOutraVez = false;
		}
	}
	for (int i = 0; i < cantina[0]->totalMesas; i++) {
		for (int j = 0; j < cantina[i]->tamanho; j++) {
			if (cantina[i]->sentados[j] != NULL) {
				if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == num) {
					cantina[i]->sentados[j]->dura��o = novaDura��o;
					h�GrupoCantina = true;
				}
			}
		}
	}
	if (!h�GrupoCantina) {
		for (int u = 0; u < tamFila; u++) {
			if (fila[u] != NULL) {
				if (fila[u]->numDepartamentoOuGrupo == num) {
					fila[u]->dura��o = novaDura��o;
					h�GrupoFila = true;
				}
			}
		}
	}
	if (!h�GrupoCantina && !h�GrupoFila) {
		cout << "Esse grupo / departamento n�o est� nem na cantina nem na fila" << endl;
	}
}