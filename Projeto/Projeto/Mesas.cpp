#include"Mesas.h"
#include"Pessoas.h"
#include <locale>
#include<iostream>
#include<string>
using namespace std;

bool listaVaziaCantina(LLMesas*ll) {
	if (ll->primeira != NULL) {
		return false;
	}
	return true;
}

void insereFimMesas(LLMesas* ll, LLMesas::mesa *m) {
	m->seguinte = NULL;
	if (!listaVaziaCantina(ll)) {
		ll->ultima->seguinte = m;
		ll->ultima = m;
		return;
	}
	ll->primeira = m;
	ll->ultima = m;
	return;
}

void criaCantina(LLMesas*ll) {//vai gerar o tamanho da cantina e criar mesas at� este tamanho ser atingido
	int *TCANTINA = new int(rand() % 21 + 30);
	int t = 0;
	int i = 1;
	bool cria = false;
	while (t < *TCANTINA) {
		cria = true;
		int *TMESA = new int(rand() % 4 + 2);
		t += *TMESA;
		if (*TCANTINA - t <= 1 && *TCANTINA != t) {//quando isto acontece, nenhuma mesa poder� preencher o �ltimo espa�o ou j� ultrapassamos o tamanho da cantina, por isso faz-se um "reset", n�o se cria a mesa e gera-se outro tamanho de mesa
			t -= *TMESA;
			cria = false;
		}
		if (cria) {
			LLMesas::mesa*m = new LLMesas::mesa();
			LLPessoas*sentados = new LLPessoas;
			sentados->primeira = NULL;
			sentados->iterator = NULL;
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
			if (ll->iterator->sentados->iterator->membro_aluno.num > 0) {
				if (!ll->iterator->sentados->iterator->membro_aluno.especialOuNao) {
					cout << "\t" << ll->iterator->sentados->iterator->ultNome << ", Estudante, Grupo " << ll->iterator->sentados->iterator->numDepartamentoOuGrupo << ", " << ll->iterator->sentados->iterator->membro_aluno.curso << ", " << ll->iterator->sentados->iterator->membro_aluno.num << " (ciclos restantes: " << ll->iterator->sentados->iterator->dura��o << ")" << endl;
				}
				else {
					cout << "\t" << ll->iterator->sentados->iterator->ultNome << ", Estudante (especial), Grupo " << ll->iterator->sentados->iterator->numDepartamentoOuGrupo << ", " << ll->iterator->sentados->iterator->membro_aluno.curso << ", " << ll->iterator->sentados->iterator->membro_aluno.num << " (ciclos restantes: " << ll->iterator->sentados->iterator->dura��o << ")" << endl;
				}
			}
			else {
				cout << "\t" << ll->iterator->sentados->iterator->ultNome << ", Staff, Departamento " << ll->iterator->sentados->iterator->numDepartamentoOuGrupo << ", " << ll->iterator->sentados->iterator->membro_staff.numFuncionario << " (ciclos restantes: " << ll->iterator->sentados->iterator->dura��o << ")" << endl;
			}
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



void preencheCantina(LLMesas *cantina, LLPessoas*fila, LLRefei��es*r) {//vai passar as pessoas da fila para a cantina
	string *cursoSenta = new string;
	LLPessoas::pessoa*move = new LLPessoas::pessoa();
	int ind = 0;
	int vagas = 0;
	bool para = false;
	int *vagasP = new int;
	int tamFila = comprimento(fila);
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		vagas += (cantina->iterator->capacidade - cantina->iterator->numSentados);
		cantina->iterator = cantina->iterator->seguinte;
	}
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		para = false;
		if (cantina->iterator->numSentados == 0) {//no caso de n�o haver pessoas na mesa acrescenta-se uma pessoa � mesa
			if (ind < tamFila) {
				move = consultaPessoa(fila, ind);
				vagasPossiveis(vagasP, move, cantina, vagas);
				while (ind < tamFila && *vagasP < move->tamanhoGrupo) {
					ind += move->tamanhoGrupo;
					if (ind < tamFila) {
						move = consultaPessoa(fila, ind);
						vagasPossiveis(vagasP, move, cantina, vagas);
					}
				}
			}
			if (ind < tamFila) {
				move = removePessoaMeio(fila, ind);
				inserirInicioPessoas(cantina->iterator->sentados, move);
				(cantina->iterator->numSentados)++;
				(vagas)--;
				tamFila--;
			}
		}
		if (cantina->iterator->numSentados < cantina->iterator->capacidade && cantina->iterator->numSentados > 0) {//se a mesa n�o estiver cheia
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL && !para) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
					*cursoSenta = cantina->iterator->sentados->iterator->membro_aluno.curso;
					para = true;
				}
				else {
					*cursoSenta = "n�oconta";
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			int numSentados = cantina->iterator->numSentados;
			for (int i = numSentados; i < cantina->iterator->capacidade; i++) {
				if (ind < tamFila) {
					move = consultaPessoa(fila, ind);
					vagasPossiveis(vagasP, move, cantina, vagas);
					while (ind < tamFila && *vagasP < move->tamanhoGrupo) {
						ind += move->tamanhoGrupo;
						if (ind < tamFila) {
							move = consultaPessoa(fila, ind);
							vagasPossiveis(vagasP, move, cantina, vagas);
						}
					}
				}
				if (ind < tamFila) {
					if (*cursoSenta != "n�oconta") {//no caso de ter pelo menos um aluno sentado
						if (move->membro_aluno.num > 0) {
							if (move->membro_aluno.curso == *cursoSenta) {//verifica se a pessoa que est� para entrar na mesa, tendo em conta as restri��es
								move = removePessoaMeio(fila, ind);
								insereFimPessoas(cantina->iterator->sentados, move);
								(cantina->iterator->numSentados)++;
								(vagas)--;
								tamFila--;
							}
							else {
								i = 100;
							}
						}
						else {// se for de staff pode entrar livremente
							move = removePessoaMeio(fila, ind);
							insereFimPessoas(cantina->iterator->sentados, move);
							(cantina->iterator->numSentados)++;
							(vagas)--;
							tamFila--;
						}
					}
					else {//no caso de s� estar staff sentado na mesa
						move = removePessoaMeio(fila, ind);
						if (move->membro_aluno.num > 0) {
							*cursoSenta = move->membro_aluno.curso;
						}
						insereFimPessoas(cantina->iterator->sentados, move);
						(cantina->iterator->numSentados)++;
						(vagas)--;
						tamFila--;
					}
				}
			}
		}
		vagas -= (cantina->iterator->capacidade - cantina->iterator->numSentados);
		cantina->iterator = cantina->iterator->seguinte;
	}
	move = nullptr;
	delete move, cursoSenta;
}

void removeDura��o(LLMesas*cantina) {//como o nome indica, com cada ciclo remove 1 � dura��o
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		if (cantina->iterator->numSentados > 0) {
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				(cantina->iterator->sentados->iterator->dura��o)--;
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
}


void retiraEmergPessoa(LLMesas*cantina, LLPessoas*acabados, LLRefei��es *r) {//fun��o para os casos de emerg�ncia, neste caso retirar uma pessoa em caso de emerg�ncia
	int num;
	int pos = 0;
	LLPessoas::pessoa*retirada = new LLPessoas::pessoa();
	cout << "Escreva o n�mero de aluno / funcion�rio da pessoa que tem de sair" << endl;
	cin >> num;
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		pos = 0;
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num == num) {
					retirada = removePessoaMeio(cantina->iterator->sentados, pos);
					retirada->dura��o = 0;
					insereFimPessoasAcabadas(acabados, retirada, r);
					(cantina->iterator->numSentados)--;
					retirada = nullptr;
					delete retirada;
					return;
				}
				else {
					pos++;
					cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
				}
			}
			else if (cantina->iterator->sentados->iterator->membro_staff.numFuncionario > 0) {
				if (cantina->iterator->sentados->iterator->membro_staff.numFuncionario == num) {
					retirada = removePessoaMeio(cantina->iterator->sentados, pos);
					retirada->dura��o = 0;
					insereFimPessoasAcabadas(acabados, retirada, r);
					(cantina->iterator->numSentados)--;
					retirada = nullptr;
					delete retirada;
					return;
				}
				else {
					pos++;
					cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
				}
			}
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	cout << "Essa pessoa n�o est� na cantina." << endl;
}

void retiraEmergGrupo(LLMesas*cantina, LLPessoas*acabados, LLRefei��es *r) {//fun��o para os casos de emerg�ncia, neste caso retirar um grupo em caso de emerg�ncia
	int num;
	int i = 0;
	int pos = 0;
	LLPessoas::pessoa*retirada = new LLPessoas::pessoa();
	bool removeu = false;
	cout << "Escreva o n�mero de grupo / departamento das pessoas que tem que sair" << endl;
	cin >> num;
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		pos = 0;
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->numDepartamentoOuGrupo == num) {
				retirada = removePessoaMeio(cantina->iterator->sentados, pos);
				retirada->dura��o = 0;
				insereFimPessoasAcabadas(acabados, retirada, r);
				(cantina->iterator->numSentados)--;
				removeu = true;
			}
			else {
				pos++;
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	if (!removeu) {
		cout << "Esse grupo / departamento n�o est� na cantina." << endl;
	}
	retirada = nullptr;
	delete retirada;
}
void removeAcabados(LLMesas*cantina, LLPessoas* acabados, LLRefei��es*r) {//remove as pessoas que acabaram a sua refei��o e guarda-se numa lista ligada de pessoas
	cantina->iterator = cantina->primeira;
	LLPessoas::pessoa*acabou = new LLPessoas::pessoa();
	int p;
	while (cantina->iterator != NULL) {
		if (cantina->iterator->numSentados > 0) {
			p = 0;
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				if (cantina->iterator->sentados->iterator->dura��o == 0) {
					acabou = removePessoaMeio(cantina->iterator->sentados, p);
					insereFimPessoasAcabadas(acabados, acabou, r);
					(cantina->iterator->numSentados)--;
				}
				else {
					cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
					p++;
				}
			}
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
}

void insereFimPessoasAcabadas(LLPessoas* ll, LLPessoas::pessoa *p, LLRefei��es*r) {
	p->plafond -= r->atual->custo;
	p->seguinte = NULL;
	if (!listaVaziaPessoas(ll)) {
		ll->ultima->seguinte = p;
		ll->ultima = p;
		return;
	}
	ll->primeira = p;
	ll->ultima = ll->primeira;
	return;
}
void ordenaAlfabeticamenteUltNome(LLMesas*cantina, LLPessoas*fila, LLPessoas*acabados) {//ordena alfabeticamente todas as pessoas que passaram pelo sistema pelos seus �ltimos nomes
	int total = contaPessoasCantina(cantina) + contaPessoasFila(fila) + contaAcabados(acabados);//n� de pessoas no sistema
	LLPessoas::pessoa**sistema = new LLPessoas::pessoa*[total];
	int i = 0;
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	acabados->iterator = acabados->primeira;
	while (i < total) {
		while (cantina->iterator != NULL) {
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {//vai adicionar ao vetor que vai ser ordenado as pessoas da cantina
				sistema[i] = cantina->iterator->sentados->iterator;
				i++;
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			cantina->iterator = cantina->iterator->seguinte;
		}
		while (fila->iterator != NULL) {//vai adicionar ao vetor que vai ser ordenado as pessoas da fila
			sistema[i] = fila->iterator;
			i++;
			fila->iterator = fila->iterator->seguinte;
		}
		while (acabados->iterator != NULL) {//vai adicionar ao vetor que vai ser ordenado as pessoas que sa�ram da cantina
			sistema[i] = acabados->iterator;
			i++;
			acabados->iterator = acabados->iterator->seguinte;
		}
	}
	mergeSortAlfabeticamenteUltNome(sistema, total);//usa-se uma adapta��o do mergeSort pois � um dos mais eficientes algoritmos de ordena��o
	system("CLS");
	cout << "\t\t\t\t\t Cantina EDA" << endl;
	cout << "Pessoas que est�o na fila, est�o na cantina e que j� terminaram a sua refei��o, ordenadas alfabeticamente pelo �ltimo nome:" << endl << endl;
	for (i = 0; i < total; i++) {
		if (sistema[i]->membro_aluno.num > 0) {
			if (!sistema[i]->membro_aluno.especialOuNao) {
				if (sistema[i]->dura��o != 0) {
					cout << sistema[i]->priNome << " " << sistema[i]->ultNome << ", Estudante, Grupo " << sistema[i]->numDepartamentoOuGrupo << ", " << sistema[i]->membro_aluno.curso << ", dura��o " << sistema[i]->dura��o << ", " << sistema[i]->plafond << " EUR" << endl;
				}
				else {
					cout << sistema[i]->priNome << " " << sistema[i]->ultNome << ", Estudante, Grupo " << sistema[i]->numDepartamentoOuGrupo << ", " << sistema[i]->membro_aluno.curso << ", acabou a sua refei��o, " << sistema[i]->plafond << " EUR" << endl;
				}
			}
			else {
				if (sistema[i]->dura��o != 0) {
					cout << sistema[i]->priNome << " " << sistema[i]->ultNome << ", Estudante (especial), Grupo " << sistema[i]->numDepartamentoOuGrupo << ", " << sistema[i]->membro_aluno.curso << ", dura��o " << sistema[i]->dura��o << ", " << sistema[i]->plafond << " EUR" << endl;
				}
				else {
					cout << sistema[i]->priNome << " " << sistema[i]->ultNome << ", Estudante (especial), Grupo " << sistema[i]->numDepartamentoOuGrupo << ", " << sistema[i]->membro_aluno.curso << ", acabou a sua refei��o, " << sistema[i]->plafond << " EUR" << endl;
				}
			}
		}
		else {
			if (sistema[i]->dura��o != 0) {
				cout << sistema[i]->priNome << " " << sistema[i]->ultNome << ", Staff, Departamento " << sistema[i]->numDepartamentoOuGrupo << ", dura��o " << sistema[i]->dura��o << ", " << sistema[i]->plafond << " EUR" << endl;
			}
			else {
				cout << sistema[i]->priNome << " " << sistema[i]->ultNome << ", Staff, Departamento " << sistema[i]->numDepartamentoOuGrupo << ", acabou a sua refei��o, " << sistema[i]->plafond << " EUR" << endl;
			}
		}
	}
	delete sistema;
}

int contaPessoasCantina(LLMesas*cantina) {//conta as pessoas que est�o na cantina, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		soma += cantina->iterator->numSentados;
		cantina->iterator = cantina->iterator->seguinte;
	}
	return soma;
}

void vagasPossiveis(int*vagasPossiveis, LLPessoas::pessoa*p, LLMesas*cantina, int vagas) { //verifica quantas vagas na cantina a pessoa para entrar pode realmente ocupar com as restri��es em termos de cursos
	*vagasPossiveis = vagas;
	string *cursoVagas = new string;
	LLMesas::mesa*itera = new LLMesas::mesa();
	itera = cantina->iterator;
	while (itera != NULL) {
		bool para = false;
		if (itera->numSentados > 0) {
			itera->sentados->iterator = itera->sentados->primeira;
			while (itera->sentados->iterator != NULL && !para) {
				if (itera->sentados->iterator->membro_aluno.num > 0) {
					*cursoVagas = itera->sentados->iterator->membro_aluno.curso;
					para = true;
				}
				else {
					*cursoVagas = "n�oconta";
				}
				itera->sentados->iterator = itera->sentados->iterator->seguinte;
			}
			if (*cursoVagas != "n�oconta") {
				if (p->membro_aluno.num > 0) {
					if (p->membro_aluno.curso != *cursoVagas) {
						*vagasPossiveis -= (itera->capacidade - itera->numSentados);
					}
				}
			}
		}
		itera = itera->seguinte;
	}
	delete cursoVagas, itera;
}

void mudaNome(LLMesas*cantina, LLPessoas*fila) {//fun��o que permite a altera��o do primeiro, �ltimo ou ambos os nomes de um dado indiv�duo, identificado pelo seu n�mero
	int PriOuUltOuAmbos;
	int n;
	bool h�PessoaCantina = false;
	bool h�PessoaFila = false;
	bool restarta = true;
	cout << "Escreva o n�mero de aluno / funcion�rio do indiv�duo ao qual deseja alterar o nome" << endl;
	cout << "**** Comando: ";
	cin >> n;
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num == n) {
					h�PessoaCantina = true;
					break;
				}
			}
			else {
				if (cantina->iterator->sentados->iterator->membro_staff.numFuncionario == n) {
					h�PessoaCantina = true;
					break;
				}
			}
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		if (h�PessoaCantina) {
			break;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	if (!h�PessoaCantina) {
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_aluno.num > 0) {
				if (fila->iterator->membro_aluno.num == n) {
					h�PessoaFila = true;
					break;
				}
			}
			else {
				if (fila->iterator->membro_staff.numFuncionario == n) {
					h�PessoaFila = true;
					break;
				}
			}
			fila->iterator = fila->iterator->seguinte;
		}
	}
	if (h�PessoaFila || h�PessoaCantina) {
		while (restarta) {
			cout << endl << "Deseja alterar" << endl << "\t1. O primeiro nome" << endl << "\t2. O �ltimo nome" << endl << "\t3. Ambos os nomes do indiv�duo" << endl;
			cout << "**** Comando: ";
			cin >> PriOuUltOuAmbos;
			cin.ignore(1000, '\n');
			switch (PriOuUltOuAmbos)
			{
			case 1:
				if (h�PessoaCantina) {
					cout << endl << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					getline(cin, cantina->iterator->sentados->iterator->priNome);
				}
				else {
					cout << endl << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					getline(cin, fila->iterator->priNome);
				}
				restarta = false;
				break;
			case 2:
				if (h�PessoaCantina) {
					cout << endl << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					getline(cin, cantina->iterator->sentados->iterator->ultNome);
				}
				else {
					cout << endl << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					getline(cin, fila->iterator->ultNome);
				}
				restarta = false;
				break;
			case 3:
				if (h�PessoaCantina) {
					cout << endl << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					getline(cin, cantina->iterator->sentados->iterator->priNome);
					cout << endl << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					getline(cin, cantina->iterator->sentados->iterator->ultNome);
				}
				else {
					cout << endl << "Escreva o novo primeiro nome do indiv�duo" << endl << "Novo primeiro nome: ";
					getline(cin, fila->iterator->priNome);
					cout << endl << "Escreva o novo �ltimo nome do indiv�duo" << endl << "Novo �ltimo nome: ";
					getline(cin, fila->iterator->ultNome);
				}
				restarta = false;
				break;
			default:
				cout << "Por favor escolha uma das op��es." << endl;
				break;
			}
		}
	}
	else {
		cout << "Essa pessoa n�o se encontra nem na cantina nem na fila de espera." << endl;
	}
}

void editaDura��o(LLMesas* cantina, LLPessoas*fila) {//permite a altera��o da dura��o de um grupo / departamento, identificado pelo n�mero de grupo / departamento
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
			cout << "A nova dura��o tem que ser maior que 0!" << endl << endl;
		}
		else {
			tentaOutraVez = false;
		}
	}
	cantina->iterator = cantina->primeira;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->numDepartamentoOuGrupo == num) {
				cantina->iterator->sentados->iterator->dura��o = novaDura��o;
				h�GrupoCantina = true;
			}
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	fila->iterator = fila->primeira;
	if (!h�GrupoCantina) {
		while (fila->iterator != NULL) {
			if (fila->iterator->numDepartamentoOuGrupo == num) {
				fila->iterator->dura��o = novaDura��o;
				h�GrupoFila = true;
			}
			fila->iterator = fila->iterator->seguinte;
		}
	}
	if (!h�GrupoCantina && !h�GrupoFila) {
		cout << "Esse grupo / departamento n�o est� nem na cantina nem na fila" << endl;
	}
}

LLMesas::mesa** converteLLvetorMesas(LLMesas*cantina) { //converte a lista ligada de mesas (a cantina) num vetor para facilitar a implementa��o do selection sort
	LLMesas::mesa**vetorMesas = new LLMesas::mesa*[cantina->ultima->numMesa];
	cantina->iterator = cantina->primeira;
	int i = 0;
	while (cantina->iterator != NULL) {
		vetorMesas[i++] = cantina->iterator;
		cantina->iterator = cantina->iterator->seguinte;
	}
	return vetorMesas;
}

void SelectionSortMesasNumSentados(LLMesas::mesa**cantina, int tam) {//ordena a cantina pelo n�mero de pessoas sentadas nas mesas, ordem decrescente
	for (int i = 0; i < tam - 1; i++) {
		int min = i;
		for (int j = i + 1; j < tam; j++) {
			if (cantina[j]->numSentados < cantina[min]->numSentados) {
				min = j;
			}
		}
		if (min != i) {
			swap(cantina[i], cantina[min]);
		}
	}
	system("CLS");
	cout << "\t\t\t\t\t Cantina EDA" << endl;
	for (int escreve = 0; escreve < tam; escreve++) {
		int l = 0;
		cout << "Mesa " << cantina[escreve]->numMesa << "(CAPACIDADE " << cantina[escreve]->capacidade << "):" << endl;
		cantina[escreve]->sentados->iterator = cantina[escreve]->sentados->primeira;
		while (cantina[escreve]->sentados->iterator != NULL) {
			if (cantina[escreve]->sentados->iterator->membro_aluno.num > 0) {
				if (!cantina[escreve]->sentados->iterator->membro_aluno.especialOuNao) {
					cout << "\t" << cantina[escreve]->sentados->iterator->ultNome << ", Estudante, Grupo " << cantina[escreve]->sentados->iterator->numDepartamentoOuGrupo << ", " << cantina[escreve]->sentados->iterator->membro_aluno.curso << ", " << cantina[escreve]->sentados->iterator->membro_aluno.num << " (ciclos restantes: " << cantina[escreve]->sentados->iterator->dura��o << ")" << endl;
				}
				else {
					cout << "\t" << cantina[escreve]->sentados->iterator->ultNome << ", Estudante (especial), Grupo " << cantina[escreve]->sentados->iterator->numDepartamentoOuGrupo << ", " << cantina[escreve]->sentados->iterator->membro_aluno.curso << ", " << cantina[escreve]->sentados->iterator->membro_aluno.num << " (ciclos restantes: " << cantina[escreve]->sentados->iterator->dura��o << ")" << endl;
				}
			}
			else {
				cout << "\t" << cantina[escreve]->sentados->iterator->ultNome << ", Staff, Departamento " << cantina[escreve]->sentados->iterator->numDepartamentoOuGrupo << ", " << cantina[escreve]->sentados->iterator->membro_staff.numFuncionario << " (ciclos restantes: " << cantina[escreve]->sentados->iterator->dura��o << ")" << endl;
			}
			cantina[escreve]->sentados->iterator = cantina[escreve]->sentados->iterator->seguinte;
			l++;
		}
		while (l < cantina[escreve]->capacidade) {
			cout << endl;
			l++;
		}
		cout << "---------------------------------------------------------------------------------------------------" << endl;
	}
	delete cantina;
}

void apresentaIndividuo(LLMesas*cantina, LLPessoas*fila) {//apresenta todos os detalhes de um indiv�duo identificado pelo seu n�mero pelo utilizador
	int n;
	cout << endl << "Escreva o n�mero de aluno / funcion�rio do indiv�duo do qual deseja conhecer todos os dados" << endl;
	cout << "**** Comando: ";
	cin >> n;
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num == n) {
					system("CLS");
					cout << "Aqui est� o indiv�duo que pediu" << endl;
					if (!cantina->iterator->sentados->iterator->membro_aluno.especialOuNao) {
						cout << cantina->iterator->sentados->iterator->priNome << " " << cantina->iterator->sentados->iterator->ultNome << ", Estudante, Grupo " << cantina->iterator->sentados->iterator->numDepartamentoOuGrupo << ", " << cantina->iterator->sentados->iterator->membro_aluno.curso << ", " << cantina->iterator->sentados->iterator->membro_aluno.num << ", dura��o " << cantina->iterator->sentados->iterator->dura��o << ", " << cantina->iterator->sentados->iterator->plafond << " EUR" << endl;
					}
					else {
						cout << cantina->iterator->sentados->iterator->priNome << " " << cantina->iterator->sentados->iterator->ultNome << ", Estudante (especial), Grupo " << cantina->iterator->sentados->iterator->numDepartamentoOuGrupo << ", " << cantina->iterator->sentados->iterator->membro_aluno.curso << ", " << cantina->iterator->sentados->iterator->membro_aluno.num << ", dura��o " << cantina->iterator->sentados->iterator->dura��o << ", " << cantina->iterator->sentados->iterator->plafond << " EUR" << endl;
					}
					return;
				}
			}
			else {
				if (cantina->iterator->sentados->iterator->membro_staff.numFuncionario == n) {
					system("CLS");
					cout << "Aqui est� o indiv�duo que pediu" << endl;
					cout << cantina->iterator->sentados->iterator->priNome << " " << cantina->iterator->sentados->iterator->ultNome << ", Staff, Departamento " << cantina->iterator->sentados->iterator->numDepartamentoOuGrupo << ", " << cantina->iterator->sentados->iterator->membro_staff.numFuncionario << ", dura��o " << cantina->iterator->sentados->iterator->dura��o << ", " << cantina->iterator->sentados->iterator->plafond << " EUR" << endl;
					return;
				}
			}
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	while (fila->iterator != NULL) {
		if (fila->iterator->membro_aluno.num > 0) {
			if (fila->iterator->membro_aluno.num == n) {
				system("CLS");
				cout << "Aqui est� o indiv�duo que pediu:" << endl;
				if (!fila->iterator->membro_aluno.especialOuNao) {
					cout << fila->iterator->priNome << " " << fila->iterator->ultNome << ", Estudante, Grupo " << fila->iterator->numDepartamentoOuGrupo << ", " << fila->iterator->membro_aluno.curso << ", " << fila->iterator->membro_aluno.num << ", dura��o " << fila->iterator->dura��o << ", " << fila->iterator->plafond << " EUR" << endl;
				}
				else {
					cout << fila->iterator->priNome << " " << fila->iterator->ultNome << ", Estudante (especial), Grupo " << fila->iterator->numDepartamentoOuGrupo << ", " << fila->iterator->membro_aluno.curso << ", " << fila->iterator->membro_aluno.num << ", dura��o " << fila->iterator->dura��o << ", " << fila->iterator->plafond << " EUR" << endl;
				}
				return;
			}
		}
		else {
			if (fila->iterator->membro_staff.numFuncionario == n) {
				system("CLS");
				cout << "Aqui est� o indiv�duo que pediu:" << endl;
				cout << fila->iterator->priNome << " " << fila->iterator->ultNome << ", Staff, Departamento " << fila->iterator->numDepartamentoOuGrupo << ", " << fila->iterator->membro_staff.numFuncionario << ", dura��o " << fila->iterator->dura��o << ", " << fila->iterator->plafond << " EUR" << endl;
				return;
			}
		}
		fila->iterator = fila->iterator->seguinte;
	}
}

void apresentaCursoOuDep(LLMesas * cantina, LLPessoas * fila, string *CURSOS) {//apresenta os indiv�duos de um dado curso ou departamento
	int cursoAProcurar;
	string oCurso = "skip";
	bool restarta = true;
	int i = 0;
	int numDepartamento;
	int op��o;
	int pos = 0;
	int tam = 0;
	cout << "Pretende saber os alunos de um determinado curso ou os funcion�rios de um determinado departamento?\n\t1.Alunos de um determinado curso;\n\t2.Funcion�rios de um determinado departamento." << endl;
	while (restarta) {
		cout << "**** Comando: ";
		cin >> op��o;
		cin.ignore(1000, '\n');
		switch (op��o)
		{
		case 1:
			while (i < 19) {
				cout << i + 1 << ". " << CURSOS[i] << endl;
				i++;
			}
			i = 0;
			cout << endl << "Indique o curso que pretende." << endl;
			cout << "**** Comando: ";
			cin >> cursoAProcurar;
			if (cursoAProcurar <= 19) {
				restarta = false;
				oCurso = CURSOS[cursoAProcurar - 1];
			}
			else {
				cout << "Por favor insira uma op��o aceit�vel." << endl;
				system("pause");
			}
			break;
		case 2:
			cout << "Escreva o n�mero de departamento que pretende." << endl;
			cout << "**** Comando: ";
			cin >> numDepartamento;
			restarta = false;
			break;
		default:
			cout << "Por favor escolha uma das op��es dispon�veis." << endl << endl;
			cout << "Pretende saber os alunos de um determinado curso ou os funcion�rios de um determinado departamento?\n\t1.Alunos de um determinado curso;\n\t2.Funcion�rios de um determinado departamento." << endl;
			break;
		}
	}
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	if (oCurso != "skip") {
		while (cantina->iterator != NULL) {
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				if (cantina->iterator->sentados->iterator->membro_aluno.curso == oCurso) {
					tam++;
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			cantina->iterator = cantina->iterator->seguinte;
		}
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_aluno.curso == oCurso) {
				tam++;
			}
			fila->iterator = fila->iterator->seguinte;
		}
		if (tam == 0) {
			cout << "N�o h� nenhum aluno desse curso na cantina ou na fila." << endl;
			return;
		}
		LLPessoas::pessoa**pessoasAVer = new LLPessoas::pessoa*[tam];
		cantina->iterator = cantina->primeira;
		fila->iterator = fila->primeira;
		while (cantina->iterator != NULL) {
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				if (cantina->iterator->sentados->iterator->membro_aluno.curso == oCurso) {
					pessoasAVer[pos++] = cantina->iterator->sentados->iterator;
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			cantina->iterator = cantina->iterator->seguinte;
		}
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_aluno.curso == oCurso) {
				pessoasAVer[pos++] = fila->iterator;
			}
			fila->iterator = fila->iterator->seguinte;
		}
		cout << "Estes s�o os alunos que est�o a estudar " << oCurso << " que est�o na cantina ou na fila." << endl;
		pos = 0;
		while (pos < tam) {
			if (!pessoasAVer[pos]->membro_aluno.especialOuNao) {
				cout << pessoasAVer[pos]->priNome << " " << pessoasAVer[pos]->ultNome << ", " << pessoasAVer[pos]->membro_aluno.num << ", grupo " << pessoasAVer[pos]->numDepartamentoOuGrupo << ", dura��o " << pessoasAVer[pos]->dura��o << ", " << pessoasAVer[pos]->plafond << " EUR" << endl;
			}
			else {
				cout << pessoasAVer[pos]->priNome << " " << pessoasAVer[pos]->ultNome << ", Estudante Especial, " << pessoasAVer[pos]->membro_aluno.num << ", grupo " << pessoasAVer[pos]->numDepartamentoOuGrupo << ", dura��o " << pessoasAVer[pos]->dura��o << ", " << pessoasAVer[pos]->plafond << " EUR" << endl;
			}
			pos++;
		}
		delete pessoasAVer;
	}
	else {
		while (cantina->iterator != NULL) {
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				if (cantina->iterator->sentados->iterator->membro_staff.numFuncionario > 0) {
					if (cantina->iterator->sentados->iterator->numDepartamentoOuGrupo == numDepartamento) {
						tam++;
					}
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			cantina->iterator = cantina->iterator->seguinte;
		}
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_staff.numFuncionario > 0) {
				if (fila->iterator->numDepartamentoOuGrupo == numDepartamento) {
					tam++;
				}
			}
			fila->iterator = fila->iterator->seguinte;
		}
		if (tam == 0) {
			cout << "N�o h� nenhum funcion�rio com esse n�mero de departamento na cantina ou na fila." << endl;
			return;
		}
		LLPessoas::pessoa**pessoasAVer = new LLPessoas::pessoa*[tam];
		cantina->iterator = cantina->primeira;
		fila->iterator = fila->primeira;
		while (cantina->iterator != NULL) {
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				if (cantina->iterator->sentados->iterator->membro_staff.numFuncionario > 0) {
					if (cantina->iterator->sentados->iterator->numDepartamentoOuGrupo == numDepartamento) {
						pessoasAVer[pos++] = cantina->iterator->sentados->iterator;
					}
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			cantina->iterator = cantina->iterator->seguinte;
		}
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_staff.numFuncionario > 0) {
				if (fila->iterator->numDepartamentoOuGrupo == numDepartamento) {
					pessoasAVer[pos++] = fila->iterator;
				}
			}
			fila->iterator = fila->iterator->seguinte;
		}
		pos = 0;
		cout << "Estes s�o os funcion�rios do departamento " << numDepartamento << " que est�o na cantina ou na fila." << endl;
		while (pos < tam) {
			cout << pessoasAVer[pos]->priNome << " " << pessoasAVer[pos]->ultNome << ", " << pessoasAVer[pos]->membro_staff.numFuncionario << ", dura��o " << pessoasAVer[pos]->dura��o << ", " << pessoasAVer[pos]->plafond << " EUR" << endl;
			pos++;
		}
		delete pessoasAVer;
	}
}

void mudaCurso(LLMesas*cantina, LLPessoas*fila, string* CURSOS) {//permite a altera��o de curso de um dado grupo de alunos
	bool h�Grupo = false;
	int numGrupo;
	cout << endl << "Pretende mudar o curso de qual grupo de alunos?" << endl;
	cout << "**** Comando: ";
	cin >> numGrupo;
	cin.ignore(1000, '\n');
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
				if (cantina->iterator->sentados->iterator->numDepartamentoOuGrupo == numGrupo) {
					h�Grupo = true;
				}
			}
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	if (!h�Grupo) {
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_aluno.num > 0) {
				if (fila->iterator->numDepartamentoOuGrupo == numGrupo) {
					h�Grupo = true;
				}
			}
			fila->iterator = fila->iterator->seguinte;
		}
	}
	if (!h�Grupo) {
		cout << "Esse grupo de alunos n�o est� nem na cantina nem na fila." << endl;
		return;
	}
	int cursoAProcurar;
	string oCurso;
	bool restarta = true;
	int i = 0;
	cout << "Cursos poss�veis:" << endl;
	while (i < 19) {
		cout << i + 1 << ". " << CURSOS[i] << endl;
		i++;
	}
	while (restarta) {
		cout << endl << "Indique o novo curso que pretenda que o grupo tenha." << endl;
		cout << "**** Comando: ";
		cin >> cursoAProcurar;
		if (cursoAProcurar <= 19) {
			restarta = false;
			oCurso = CURSOS[cursoAProcurar - 1];
		}
		else {
			cout << "Por favor insira uma op��o aceit�vel." << endl;
			system("pause");
		}
	}
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	h�Grupo = false;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
				if (cantina->iterator->sentados->iterator->numDepartamentoOuGrupo == numGrupo) {
					cantina->iterator->sentados->iterator->membro_aluno.curso = oCurso;
					h�Grupo = true;
				}
			}
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	if (!h�Grupo) {
		while (fila->iterator != NULL) {
			if (fila->iterator->membro_aluno.num > 0) {
				if (fila->iterator->numDepartamentoOuGrupo == numGrupo) {
					fila->iterator->membro_aluno.curso = oCurso;
				}
			}
			fila->iterator = fila->iterator->seguinte;
		}
	}
}

void PobreRicoEMedia(LLMesas*cantina, LLPessoas*fila) {//apresenta a pessoa mais pobre, mais rica e o plafond m�dio
	LLPessoas::pessoa*pobre = cantina->primeira->sentados->primeira;
	LLPessoas::pessoa*rico = cantina->primeira->sentados->primeira;
	cantina->iterator = cantina->primeira;
	int *naCantina = new int(0);
	while (cantina->iterator != NULL) {
		*naCantina += cantina->iterator->numSentados;
		cantina->iterator = cantina->iterator->seguinte;
	}
	int numPessoas = comprimento(fila) + *naCantina;
	delete naCantina;
	float media = 0;
	cantina->iterator = cantina->primeira;
	fila->iterator = fila->primeira;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (cantina->iterator->sentados->iterator->plafond < pobre->plafond) {
				pobre = cantina->iterator->sentados->iterator;
			}
			else if (cantina->iterator->sentados->iterator->plafond > rico->plafond) {
				rico = cantina->iterator->sentados->iterator;
			}
			media += cantina->iterator->sentados->iterator->plafond;
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	while (fila->iterator != NULL) {
		if (fila->iterator->plafond < pobre->plafond) {
			pobre = fila->iterator;
		}
		else if (fila->iterator->plafond > rico->plafond) {
			rico = fila->iterator;
		}
		media += fila->iterator->plafond;
		fila->iterator = fila->iterator->seguinte;
	}
	cout << media << endl << numPessoas << endl;
	media /= numPessoas;
	system("CLS");
	cout << "\t\t\t\t\t Cantina EDA" << endl;
	if (rico->membro_aluno.num > 0) {
		cout << "A pessoa mais rica � o aluno " << rico->priNome << " " << rico->ultNome << " de n�mero " << rico->membro_aluno.num << " que tem uns impressionantes " << rico->plafond << " euros!" << endl;
	}
	if (rico->membro_staff.numFuncionario > 0) {
		cout << "A pessoa mais rica � o funcion�rio " << rico->priNome << " " << rico->ultNome << " de n�mero " << rico->membro_staff.numFuncionario << " que tem uns impressionantes " << rico->plafond << " euros!" << endl;
	}
	cout << endl << endl;
	if (pobre->membro_aluno.num > 0) {
		cout << "A pessoa mais pobre � o aluno " << pobre->priNome << " " << pobre->ultNome << " de n�mero " << pobre->membro_aluno.num << " que tem uns miser�veis " << pobre->plafond << " euros!" << endl;
	}
	if (pobre->membro_staff.numFuncionario > 0) {
		cout << "A pessoa mais pobre � o funcion�rio " << pobre->priNome << " " << pobre->ultNome << " de n�mero " << pobre->membro_staff.numFuncionario << " que tem uns miser�veis " << pobre->plafond << " euros!" << endl;
	}
	cout << endl << endl;
	cout << "O plafond m�dio �: " << media << "EUR." << endl;
	rico = nullptr;
	pobre = nullptr;
	delete rico, pobre;
}

void lotaria(LLMesas*cantina, LLPessoas*fila, bool *h�Vencedor, int*premio, int*aumenta) {//uma sortuda pessoa ganha o pr�mio, que � adicionado ao seu plafond. Se ningu�m ganha o pr�mio duplica mas a probabilidade de algu�m ganhar tamb�m diminui
	cantina->iterator = cantina->primeira;
	int*naCantina = new int(0);
	while (cantina->iterator != NULL) {
		*naCantina += cantina->iterator->numSentados;
		cantina->iterator = cantina->iterator->seguinte;
	}
	cantina->iterator = cantina->primeira;
	int numPessoas = *naCantina + comprimento(fila);
	int vencedor;
	delete naCantina;
	if (!*h�Vencedor) {
		*premio *= 2;
		(*aumenta)++;
		vencedor = rand() % (numPessoas*(3 + *aumenta));
	}
	if (*h�Vencedor) {
		*premio = rand() % 301 + 200;
		*h�Vencedor = false;
		*aumenta = 0;
		vencedor = rand() % (numPessoas*(3 + *aumenta));
	}
	int i = 0;
	cout << *premio << endl;
	while (cantina->iterator != NULL) {
		cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
		while (cantina->iterator->sentados->iterator != NULL) {
			if (i == vencedor) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
					cout << "O vencedor da lotaria � o aluno " << cantina->iterator->sentados->iterator->priNome << " " << cantina->iterator->sentados->iterator->ultNome << " de n�mero " << cantina->iterator->sentados->iterator->membro_aluno.num << ", que ganhou " << *premio << " euros! Parab�ns!" << endl;
				}
				else {
					cout << "O vencedor da lotaria � o funcion�rio " << cantina->iterator->sentados->iterator->priNome << " " << cantina->iterator->sentados->iterator->ultNome << " de n�mero " << cantina->iterator->sentados->iterator->membro_staff.numFuncionario << ", que ganhou " << *premio << " euros! Parab�ns!" << endl;
				}
				cantina->iterator->sentados->iterator->plafond += *premio;
				*h�Vencedor = true;
				return;
			}
			i++;
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
		}
		cantina->iterator = cantina->iterator->seguinte;
	}
	fila->iterator = fila->primeira;
	while (fila->iterator != NULL) {
		if (i == vencedor) {
			if (fila->iterator->membro_aluno.num > 0) {
				cout << "O vencedor da lotaria � o aluno " << fila->iterator->priNome << " " << fila->iterator->ultNome << " de n�mero " << fila->iterator->membro_aluno.num << ", que ganhou " << *premio << " euros! Parab�ns!" << endl;
			}
			else {
				cout << "O vencedor da lotaria � o funcion�rio " << fila->iterator->priNome << " " << fila->iterator->ultNome << " de n�mero " << fila->iterator->membro_staff.numFuncionario << ", que ganhou " << *premio << " euros! Parab�ns!" << endl;
			}
			fila->iterator->plafond += *premio;
			*h�Vencedor = true;
			return;
		}
		i++;
		fila->iterator = fila->iterator->seguinte;
	}
	cout << "Desta vez n�o h� vencedores! O que significa que o pr�mio duplica para a pr�xima lotaria!" << endl;
}