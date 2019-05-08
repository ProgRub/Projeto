#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include "Refeição.h"
#include<string>
using namespace std;

bool listaVaziaCantina(LLMesas*ll) {
	if (ll->primeira != NULL) {
		return false;
	}
	return true;
}

void insereFimMesas(LLMesas* ll, LLMesas::mesa *m) {
	if (!listaVaziaCantina(ll)) {
		m->seguinte = NULL;
		ll->ultima->seguinte = m;
		ll->ultima = m;
		return;
	}
	ll->primeira = m;
	ll->ultima = m;
	m->seguinte = NULL;
	return;
}

void criaCantina(LLMesas*ll) {//vai obter o tamanho da cantina e gerar tamanhos de mesas até a cantina estar preenchida, tamanhos guardados num vetor
	int *TCANTINA = new int(rand() % 21 + 30);
	int t = 0;
	int i = 1;
	bool cria = false;
	while (t < *TCANTINA) {
		cria = true;
		int *TMESA = new int(rand() % 4 + 2);
		t += *TMESA;
		if (*TCANTINA - t <= 1 && *TCANTINA != t) {//quando isto acontece, nenhuma mesa poderá preencher o último espaço ou já ultrapassamos o tamanho da cantina, por isso faz-se um "reset", "apaga-se" a mesa que provocou isto e tenta-se outra vez
			t -= *TMESA;
			cria = false;
		}
		if (cria) {
			LLMesas::mesa*m = new LLMesas::mesa();
			LLPessoas*sentados = new LLPessoas;
			sentados->primeira = NULL;
			sentados->iterator = sentados->primeira;
			sentados->ultima = NULL;
			m->capacidade = *TMESA;
			m->numMesa = i;
			m->numSentados = 0;
			m->sentados = sentados;
			insereFimMesas(ll, m);
			i++;
		}
		delete TMESA;
	}
}

void escreveCantina(LLMesas*ll) {//vai escrever a cantina como diz no nome
	ll->iterator = ll->primeira;
	while (ll->iterator != NULL) {
		int l = 0;
		cout << "Mesa " << ll->iterator->numMesa << "(CAPACIDADE " << ll->iterator->capacidade << "):" << endl;
		ll->iterator->sentados->iterator = ll->iterator->sentados->primeira;
		while (ll->iterator->sentados->iterator != NULL) {
			escrevePessoaCantina(ll->iterator->sentados->iterator);
			ll->iterator->sentados->iterator = ll->iterator->sentados->iterator->seguinte;
			l++;
		}
		while (l < ll->iterator->capacidade) {
			cout << endl;
			l++;
		}
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		ll->iterator = ll->iterator->seguinte;
	}
}

void inserePessoasMesa(LLMesas::mesa*m, LLPessoas*fila) {
	if (!listaVaziaPessoas(m->sentados)) {
		m->sentados->ultima->seguinte = fila->primeira;
		fila->primeira = fila->primeira->seguinte;
		m->sentados->ultima->seguinte->seguinte = NULL;
		m->sentados->ultima=m->sentados->ultima->seguinte;
		return;
	}
	m->sentados->primeira = fila->primeira;
	fila->primeira = fila->primeira->seguinte;
	m->sentados->primeira->seguinte = NULL;
	m->sentados->ultima = m->sentados->primeira;
	return;
}

void preencheCantina(LLMesas *cantina, LLPessoas*fila, LLRefeições*r, LLPessoas*removidos) {//vai passar as pessoas da fila para a cantina
	string *cursoSenta = new string;
	int inicio;
	int ind = 0;
	int vagas = 0;
	int tamFila = comprimento(fila);
	int *vagasP = new int;
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		vagas += (cantina->iterator->capacidade - cantina->iterator->numSentados);
		cantina->iterator = cantina->iterator->seguinte;
	}
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		removeSemDinheiro(fila, r, pos, removidos, tamRemovidos);
		if (cantina->iterator->numSentados == 0) {//no caso de não haver pessoas na mesa acrescenta-se uma pessoa à mesa
			/*if (ind < 50 && fila[ind] != NULL) {
				vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
			}
			if (ind < 50 && fila[ind] != NULL && *vagasP < fila[ind]->tamanho) {
				while (ind < 50 && fila[ind] != NULL && *vagasP < fila[ind]->tamanho) {
					ind += fila[ind]->tamanho;
					if (ind < 50 && fila[ind] != NULL) {
						vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
					}
				}
			}*/
			if(fila->primeira!=NULL){
				inserePessoasMesa(cantina->iterator, fila);
				(cantina->iterator->numSentados)++;
			(vagas)--;
			}
		}
		if (cantina->iterator->numSentados != cantina->iterator->capacidade && cantina->iterator->numSentados != 0) {//se a mesa não estiver cheia
			int l = 0;
			/*while (cantina->iterator->sentados->iterator != NULL && l < cantina->iterator->capacidade) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
					*cursoSenta = cantina->iterator->sentados->iterator->membro_aluno.curso;
					l = cantina->iterator->capacidade;
				}
				else {
					*cursoSenta = "nãoconta";
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
				l++;
			}*/
			for (int i = 1; i < cantina->iterator->capacidade; i++) {/*
			//	if (ind < 50 && fila[ind] != NULL) {
			//		vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
			//	}
			//	if (ind < 50 && fila[ind] != NULL) {
			//		if (ind < 50 && *vagasP < fila[ind]->tamanho) {
			//			while (ind < 50 && fila[ind] != NULL && *vagasP < fila[ind]->tamanho ) {
			//				ind += fila[ind]->tamanho;
			//				if (ind < 50 && fila[ind] != NULL) {
			//					vagasPossiveis(vagasP, fila[ind], cantina, k, vagas);
			//				}
			//				inicio = ind;
			//			}
			//			if (ind < 50 && fila[ind] != NULL && *vagasP >= fila[ind]->tamanho) {
			//				ind = inicio;//para certificar que entram as pessoas certas na cantina
			//			}
			//		}
			//	}*/
			//	//if (*cursoSenta != "nãoconta") {
			//	//	if (fila->primeira->membro_aluno.num > 0) {
			//	//		if (fila->primeira->membro_aluno.curso == *cursoSenta) {
				if (fila->primeira != NULL) {
					inserePessoasMesa(cantina->iterator, fila);
					(cantina->iterator->numSentados)++;
				}
			//	(vagas)--;
				//		}
				//		else {
				//			i = 100;
				//		}
				//	}
				//	else {
				//		if (fila->primeira->membro_staff.numFuncionario > 0) {// se for de staff pode entrar livremente
				//			cantina->iterator->sentados->iterator = fila->primeira;
				//			fila->primeira = fila->primeira->seguinte;
				//			cantina->iterator->sentados->iterator->seguinte = NULL;
				//			(cantina->iterator->numSentados)++;
				//			(vagas)--;
				//		}
				//	}
				//}
				//else {
				//	if (fila->primeira->membro_aluno.num > 0) {
				//		*cursoSenta = fila->primeira->membro_aluno.curso;
				//	}
				//	cantina->iterator->sentados->iterator = fila->primeira;
				//	fila->primeira = fila->primeira->seguinte;
				//	cantina->iterator->sentados->iterator->seguinte = NULL;
				//	(cantina->iterator->numSentados)++;
				//	(vagas)--;
			}
		}
		vagas -= (cantina->iterator->capacidade - cantina->iterator->numSentados);
		cantina->iterator = cantina->iterator->seguinte;
	} //assegura que não se apaga ninguém quando se gera novas pessoas para a fila
	delete cursoSenta;
}
	/*
	void removeDuração(mesa **cantina) {//como o nome indica, com cada ciclo remove 1 à duração
		for (int i = 0; i < cantina[0]->totalMesas; i++) {
			if (cantina[i]->numSentados > 0) {
				for (int j = 0; j < cantina[i]->tamanho; j++) {
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
		cout << "Escreva o número de aluno / funcionário da pessoa que tem de sair" << endl;
		cin >> n;
		for (i; i < cantina[0]->totalMesas; i++) {
			for (j = 0; j < cantina[i]->tamanho; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
						if (cantina[i]->sentados[j]->membro_aluno.num == n) {
							adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver definição da função
							(cantina[i]->numSentados)--;
							cantina[i]->sentados[j] = NULL;
							removeu = true;
							break;
						}
					}
					else if (cantina[i]->sentados[j]->membro_staff.numFuncionario > 0) {
						if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
							adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);
							(cantina[i]->numSentados)--;
							cantina[i]->sentados[j] = NULL;
							removeu = true;
							break;
						}
					}
				}
			}
			if (removeu) {
				i = cantina[0]->totalMesas;
			}
		}
		if (i == cantina[0]->totalMesas && !removeu) {
			cout << "Essa pessoa não está na cantina." << endl;
		}
	}

	void retiraEmergGrupo(mesa **cantina, pessoa**acabados, int tamAcabados, refeição *r) {//função para os casos de emergência, neste caso retirar um grupo em caso de emergência
		int n;
		int i = 0;
		bool removeu = false;
		cout << "Escreva o número de grupo / departamento das pessoas que tem que sair" << endl;
		cin >> n;
		for (i = 0; i < cantina[0]->totalMesas; i++) {
			for (int j = 0; j < cantina[i]->tamanho; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == n) {
						adicionaVetorAcabados(acabados, cantina[i]->sentados[j], tamAcabados, r);//ver definição da função
						(cantina[i]->numSentados)--;
						cantina[i]->sentados[j] = NULL;
						removeu = true;
					}
				}
			}
		}
		if (i == cantina[0]->totalMesas && !removeu) {
			cout << "Esse grupo / departamento não está na cantina" << endl;
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
		cout << "\t\t\t\t\t Cantina EDA" << endl;
		cout << "Pessoas que estão na fila, estão na cantina e que já terminaram a sua refeição, ordenadas alfabeticamente pelo último nome:" << endl << endl;
		escreveOpções(sistema, total);
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
	}*/

	void removeSemDinheiro(LLPessoas*fila, LLRefeições *r, LLPessoas*removidos) { // averigua se o aluno/funcionário possui Plafond necessário para pagar pela refeição
		int i = 0;
		bool háPessoa = false;
		int indiOuGrupo;
		int num = 0;
		while (i < 50) {
			if (fila[i] != NULL) {
				if (fila[i]->membro_aluno.num > 0) {
					if (fila[i]->plafond < r->custo) {
						cout << "***** ATENÇÃO *****" << endl << "O aluno com o número " << fila[i]->membro_aluno.num << " não possui plafond suficiente para iniciar a refeição." << endl;
						cout << "\t1.Remover aluno da entrada" << endl << "\t2.Remover grupo da entrada" << endl << endl;
						num = fila[i]->numDepartamentoOuGrupo;
						háPessoa = true;
						break;
					}
				}
				else {
					if (fila[i]->plafond < r->custo) {
						cout << "***** ATENÇÃO *****\nO elemento de staff com o número " << fila[i]->membro_staff.numFuncionario << " não possui plafond suficiente para iniciar a refeição." << endl;
						cout << "\t1.Remover funcionário da entrada" << endl << "\t2.Remover grupo da entrada" << endl << endl;
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

	void removeSemDinheiroPessoa(LLPessoas*fila, LLPessoas*removidos, int posiPessoa, int numDepGrupo) {
		adicionaVetorRemovidos(removidos, fila[posiPessoa], tamRemovidos);
		fila[posiPessoa] = NULL;
		nullsNoFim(fila, posiPessoa, pos);
		int s = 0;
		int conta = 0; //esta variável será para ajustar o tamanho do grupo depois de ser removida a pessoa
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
				if (fila[s]->numDepartamentoOuGrupo == numDepGrupo) {//reajusta o tamanho do grupo tendo em conta que saiu uma pessoa
					fila[s]->tamanho = conta;
					conta--;
				}
			}
			else {
				s = 50;
			}
		}
	}

	void removeSemDinheiroGrupo(LLPessoas*fila, LLPessoas*removidos, int numDepGrupo) {
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
	/*
	void vagasPossiveis(int*vagasPossiveis, pessoa*p, mesa**cantina, int k, int vagas) { //verifica quantas vagas na cantina a pessoa para entrar pode realmente ocupar com as restrições em termos de cursos
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
		delete cursoVagas;
	}

	void mudaNome(mesa**cantina, pessoa**fila, int tamFila) {
		int PriOuUltOuAmbos;
		int n;
		bool háPessoaCantina = false;
		bool háPessoaFila = false;
		int mesaPessoa;
		int posição;
		bool restarta = true;
		cout << endl << "Escreva o número de aluno / funcionário do indivíduo ao qual deseja alterar o nome" << endl;
		cout << "**** Comando: ";
		cin >> n;
		for (int i = 0; i < cantina[0]->totalMesas; i++) {
			for (int j = 0; j < cantina[i]->tamanho; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					if (cantina[i]->sentados[j]->membro_aluno.num > 0) {
						if (cantina[i]->sentados[j]->membro_aluno.num == n) {
							háPessoaCantina = true;
							posição = j;
							break;
						}
					}
					else {
						if (cantina[i]->sentados[j]->membro_staff.numFuncionario == n) {
							háPessoaCantina = true;
							posição = j;
							break;
						}
					}
				}
			}
			if (háPessoaCantina) {
				mesaPessoa = i;
				i = cantina[0]->totalMesas;
			}
		}
		if (!háPessoaCantina) {
			for (int u = 0; u < tamFila; u++) {
				if (fila[u] != NULL) {
					if (fila[u]->membro_aluno.num > 0) {
						if (fila[u]->membro_aluno.num == n) {
							háPessoaFila = true;
							posição = u;
							break;
						}
					}
					else {
						if (fila[u]->membro_staff.numFuncionario == n) {
							háPessoaFila = true;
							posição = u;
							break;
						}
					}
				}
			}
		}
		if (háPessoaFila || háPessoaCantina) {
			cout << endl << "Deseja alterar" << endl << "\t1. O primeiro nome" << endl << "\t2. O último nome" << endl << "\t3. Ambos os nomes do indivíduo" << endl;
			cout << "**** Comando: ";
			cin >> PriOuUltOuAmbos;
			while (restarta) {
				switch (PriOuUltOuAmbos)
				{
				case 1:
					if (háPessoaCantina) {
						cout << endl << "Escreva o novo primeiro nome do indivíduo" << endl << "Novo primeiro nome: ";
						cin.get();
						getline(cin, cantina[mesaPessoa]->sentados[posição]->priNome);
					}
					else {
						cout << endl << "Escreva o novo primeiro nome do indivíduo" << endl << "Novo primeiro nome: ";
						cin.get();
						getline(cin, fila[posição]->priNome);
					}
					restarta = false;
					break;
				case 2:
					if (háPessoaCantina) {
						cout << endl << "Escreva o novo último nome do indivíduo" << endl << "Novo último nome: ";
						cin.get();
						getline(cin, cantina[mesaPessoa]->sentados[posição]->ultNome);
					}
					else {
						cout << endl << "Escreva o novo último nome do indivíduo" << endl << "Novo último nome: ";
						cin.get();
						getline(cin, fila[posição]->ultNome);
					}
					restarta = false;
					break;
				case 3:
					if (háPessoaCantina) {
						cout << endl << "Escreva o novo primeiro nome do indivíduo" << endl << "Novo primeiro nome: ";
						cin.get();
						getline(cin, cantina[mesaPessoa]->sentados[posição]->priNome);
						cout << endl << "Escreva o novo último nome do indivíduo" << endl << "Novo último nome: ";
						cin.get();
						getline(cin, cantina[mesaPessoa]->sentados[posição]->ultNome);
					}
					else {
						cout << endl << "Escreva o novo primeiro nome do indivíduo" << endl << "Novo primeiro nome: ";
						cin.get();
						getline(cin, fila[posição]->priNome);
						cout << endl << "Escreva o novo último nome do indivíduo" << endl << "Novo último nome: ";
						cin.get();
						getline(cin, fila[posição]->ultNome);
					}
					restarta = false;
					break;
				default:
					cout << "Isso não é uma das opções" << endl;
					break;
				}
			}
		}
		else {
			cout << "Essa pessoa não se encontra nem na cantina nem na fila de espera." << endl;
		}
	}

	void editaDuração(mesa** cantina, pessoa**fila, int tamFila) {
		int num;
		int novaDuração;
		bool tentaOutraVez = true;
		bool háGrupoCantina = false;
		bool háGrupoFila = false;
		cout << "Escreva o número do grupo / departamento ao qual deseja alterar a duração de refeição" << endl << "**** Comando: ";
		cin >> num;
		while (tentaOutraVez) {
			cout << endl << "Escreva a nova duração de refeição dos elementos do grupo / departamento" << endl << "**** Comando: ";
			cin >> novaDuração;
			if (novaDuração <= 0) {
				cout << "A nova duração tem que ser maior que 0!" << endl << endl;
			}
			else {
				tentaOutraVez = false;
			}
		}
		for (int i = 0; i < cantina[0]->totalMesas; i++) {
			for (int j = 0; j < cantina[i]->tamanho; j++) {
				if (cantina[i]->sentados[j] != NULL) {
					if (cantina[i]->sentados[j]->numDepartamentoOuGrupo == num) {
						cantina[i]->sentados[j]->duração = novaDuração;
						háGrupoCantina = true;
					}
				}
			}
		}
		if (!háGrupoCantina) {
			for (int u = 0; u < tamFila; u++) {
				if (fila[u] != NULL) {
					if (fila[u]->numDepartamentoOuGrupo == num) {
						fila[u]->duração = novaDuração;
						háGrupoFila = true;
					}
				}
			}
		}
		if (!háGrupoCantina && !háGrupoFila) {
			cout << "Esse grupo / departamento não está nem na cantina nem na fila" << endl;
		}
	}

	void retiraTodaAGenteCantina(mesa**cantina) {
		bool again = true;
		for (int k = 0; k < cantina[0]->totalMesas; k++) {
			for (int j = 0; j < cantina[k]->tamanho; j++) {
				if (cantina[k]->sentados[j] != NULL) {
					cantina[k]->sentados[j] = NULL;
				}
			}
			cantina[k]->numSentados = 0;
		}
	}*/