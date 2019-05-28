#include"Pessoas.h"
#include "Refei��o.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int comprimento(LLPessoas* ll) {
	int conta = 0;
	ll->iterator = ll->primeira;
	while (ll->iterator != NULL)//enquanto n�o chegar ao fim da LL
	{
		conta++;
		ll->iterator = ll->iterator->seguinte; //vai para o nodo seguinte
	}
	return conta;
}

void limpaReserva(LLReserva*ll) {
	while (ll->primeiro != NULL) {
		LLReserva::item*apagador = ll->primeiro;
		ll->primeiro = ll->primeiro->seguinte;
		delete apagador;
	}
	ll->primeiro = NULL;
	ll->ultimo = NULL;
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

void insereMeioPessoas(LLPessoas*ll, LLPessoas::pessoa*p, int pos) {
	int tamanho = comprimento(ll);
	if (pos == 0) {
		inserirInicioPessoas(ll, p);
		return;
	}
	else if (pos == tamanho) {
		insereFimPessoas(ll, p);
		return;
	}
	else if (pos > tamanho) {
		return;
	}
	else {
		ll->iterator = ll->primeira;
		int pos_count = 0;
		while (ll->iterator->seguinte != NULL && pos_count < pos - 1) {
			ll->iterator = ll->iterator->seguinte;
			pos_count++;
		}
		p->seguinte = ll->iterator->seguinte;
		ll->iterator->seguinte = p;
		return;
	}
}

LLPessoas::pessoa* removePessoaInicio(LLPessoas*fila) {
	LLPessoas::pessoa* aux = new LLPessoas::pessoa();
	aux = fila->primeira;
	fila->primeira = fila->primeira->seguinte;
	fila->iterator = fila->primeira;
	return aux;
}

LLPessoas::pessoa* removePessoaFim(LLPessoas*fila) {
	fila->iterator = fila->primeira;
	while (fila->iterator->seguinte->seguinte != NULL) {
		fila->iterator = fila->iterator->seguinte;
	}
	LLPessoas::pessoa* aux = new LLPessoas::pessoa();
	fila->ultima = fila->iterator;
	aux = fila->iterator->seguinte;
	fila->iterator->seguinte = NULL;
	return aux;
}

LLPessoas::pessoa* removePessoaMeio(LLPessoas*fila, int pos) {
	int tamanho = comprimento(fila);
	LLPessoas::pessoa*aux = new LLPessoas::pessoa();
	if (pos == 0) {
		aux = removePessoaInicio(fila);
		return aux;
	}
	else if (pos == tamanho - 1) {
		aux = removePessoaFim(fila);
		return aux;
	}
	else if (pos >= tamanho) {
		cout << "Erro fim de lista " << pos << tamanho << endl;
		return nullptr;
	}
	else {
		fila->iterator = fila->primeira;
		int pos_count = 1;
		while (fila->iterator->seguinte != NULL && pos != pos_count) {
			fila->iterator = fila->iterator->seguinte;
			pos_count++;
		}
		aux = fila->iterator->seguinte;
		fila->iterator->seguinte = fila->iterator->seguinte->seguinte;
		fila->iterator = fila->iterator->seguinte;
		return aux;
	}
}

LLPessoas::pessoa* consultaPessoa(LLPessoas*fila, int pos) {
	int tamanho = comprimento(fila);
	if (pos == 0) {
		return fila->primeira;
	}
	else if (pos == tamanho - 1) {
		return fila->ultima;
	}
	else if (pos >= tamanho) {
		cout << "Erro fim de lista " << pos << tamanho << endl;
		return nullptr;
	}
	else {
		fila->iterator = fila->primeira->seguinte;
		int pos_count = 1;
		while (fila->iterator != NULL && pos != pos_count) {
			fila->iterator = fila->iterator->seguinte;
			pos_count++;
		}
		return fila->iterator;
	}
}

LLPessoas::pessoa* criaPessoa(string pnome, string unome, string curso, int dura, int idOuDepart, float plafond, bool alunoOuNao, bool especialOuNao) {// vai criar uma pessoa
	LLPessoas::pessoa *p = new LLPessoas::pessoa();
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
		int *NUMSTAFF = new int((19 * 100000) + ((rand() % 999 + 1) * 100) + (rand() % 30 + 70));
		p->membro_staff.numFuncionario = *NUMSTAFF;
		delete NUMSTAFF;
	}
	return p;
}

void preencheFila(LLPessoas*fila, string* pnomes, string*unomes, string*cursos, LLReserva*reserva, bool primeiraVez) {//vai preencher a fila, gerando um grupo de pessoas para os lugares vazios
	int max;
	if (primeiraVez) {
		max = 10;
	}
	else {
		max = 1;
	}
	int j = 0;
	int pos = 0;
	while (j < max) {
		int *RETIRACURSO = new int(rand() % 19);
		int *DURA��OMEAL = new int(rand() % 4 + 2);
		bool *ALUNOOUNAO = new bool(rand() % 2);
		int *GRUPOIDDEPART = new int(rand() % 401 + 100);
		testaGrupoDep(GRUPOIDDEPART, reserva);//vai testar o n�mero de grupo pois devem ser identificadores �nicos
		int *PROBESP = new int(rand() % 100 + 1);
		if (*PROBESP > 15 && *PROBESP <= 20) {//no caso de se criar um aluno especial
			fila->iterator = fila->primeira;
			while (fila->iterator != NULL && fila->iterator->membro_aluno.especialOuNao) {
				pos++;
				fila->iterator = fila->iterator->seguinte;
			}
			int *RETIRAPNOME = new int(rand() % 44);
			int *RETIRAUNOME = new int(rand() % 97);
			float *PLAF = new float(rand() % 10000 + 1);
			*PLAF /= 100;
			LLPessoas::pessoa *p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURA��OMEAL, *GRUPOIDDEPART, *PLAF, true, true);
			p->tamanhoGrupo = 1;
			insereMeioPessoas(fila, p, pos);
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
				p = criaPessoa(pnomes[*RETIRAPNOME], unomes[*RETIRAUNOME], cursos[*RETIRACURSO], *DURA��OMEAL, *GRUPOIDDEPART, *PLAF, *ALUNOOUNAO, false);
				p->tamanhoGrupo = *TAMANHO - i;
				insereFimPessoas(fila, p);
				delete RETIRAPNOME, RETIRAUNOME, PLAF;
			}
			delete TAMANHO;
		}
		delete RETIRACURSO, PROBESP, DURA��OMEAL, GRUPOIDDEPART, ALUNOOUNAO;
		if (fila->ultima->tamanhoGrupo == 1) {
			j++;
		}
	}
}
void escreveFila(LLPessoas*fila) {//como o nome indica escreve um vetor de pessoa*
	cout << endl << "FILA DE ESPERA:" << endl;
	int i = 1;
	fila->iterator = fila->primeira;
	while (fila->iterator != NULL) {
		cout << i++ << ". ";
		if (fila->iterator->membro_aluno.num > 0) {
			if (!fila->iterator->membro_aluno.especialOuNao) {
				cout << fila->iterator->priNome << ", Estudante, Grupo " << fila->iterator->numDepartamentoOuGrupo << ", " << fila->iterator->membro_aluno.curso << ", " << fila->iterator->membro_aluno.num << ", dura��o " << fila->iterator->dura��o << ", " << fila->iterator->plafond << " EUR" << endl;
			}
			else {
				cout << fila->iterator->priNome << ", Estudante (especial), Grupo " << fila->iterator->numDepartamentoOuGrupo << ", " << fila->iterator->membro_aluno.curso << ", " << fila->iterator->membro_aluno.num << ", dura��o " << fila->iterator->dura��o << ", " << fila->iterator->plafond << " EUR" << endl;
			}
		}
		else {
			cout << fila->iterator->priNome << ", Staff, Departamento " << fila->iterator->numDepartamentoOuGrupo << ", " << fila->iterator->membro_staff.numFuncionario << ", dura��o " << fila->iterator->dura��o << ", " << fila->iterator->plafond << " EUR" << endl;
		}
		fila->iterator = fila->iterator->seguinte;
	}
	cout << endl;
}

bool listaVaziaReserva(LLReserva*ll) {
	if (ll->primeiro != NULL) {
		return false;
	}
	return true;
}

void insereFimReserva(LLReserva* ll, int num) {
	LLReserva::item*novo = new LLReserva::item();
	novo->num = num;
	novo->seguinte = NULL;
	if (!listaVaziaReserva(ll)) {
		ll->ultimo->seguinte = novo;
		ll->ultimo = novo;
		return;
	}
	ll->primeiro = novo;
	ll->ultimo = novo;
}

void testaGrupoDep(int * num, LLReserva * reserva) {// v� se o n�mero de grupo ou departamento � �nico
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

n�Removidos * novoN�(LLPessoas::pessoa*p) {
	n�Removidos*novo = new n�Removidos;
	novo->esquerda = NULL;
	novo->direita = NULL;
	novo->removida = p;
	return novo;
}

n�Removidos* adicionaArvoreRemovidos(n�Removidos*raiz, LLPessoas::pessoa*p) {
	if (raiz == NULL) {
		return novoN�(p);
	}
	if (p->priNome <= raiz->removida->priNome) {
		raiz->esquerda = adicionaArvoreRemovidos(raiz->esquerda, p);
	}
	else {
		raiz->direita = adicionaArvoreRemovidos(raiz->direita, p);
	}
	return raiz;
}

int contaNosArvore(n�Removidos*raiz) {
	if (raiz == NULL) {
		return 0;
	}
	return contaNosArvore(raiz->esquerda) + 1 + contaNosArvore(raiz->direita);
}

void guardaArvoreVetor(n�Removidos * raiz, int *pos, LLPessoas::pessoa**guardar) {
	if (raiz == NULL) {
		return;
	}
	guardar[(*pos)++] = raiz->removida;
	guardaArvoreVetor(raiz->esquerda, pos, guardar);
	guardaArvoreVetor(raiz->direita, pos, guardar);
	return;
}

void limpaArvore(n�Removidos * raiz) {
	if (raiz == NULL) {
		return;
	}
	limpaArvore(raiz->esquerda);
	limpaArvore(raiz->direita);
	delete raiz;
}

void imprimeArvoreInfixa(n�Removidos * raiz) {
	if (raiz == NULL) {
		return;
	}
	imprimeArvoreInfixa(raiz->esquerda);
	if (raiz->removida->membro_aluno.num > 0) {
		if (!raiz->removida->membro_aluno.especialOuNao) {
			cout << raiz->removida->priNome << " " << raiz->removida->ultNome << ", Estudante, Grupo " << raiz->removida->numDepartamentoOuGrupo << ", " << raiz->removida->membro_aluno.curso << endl;
		}
		else {
			cout << raiz->removida->priNome << " " << raiz->removida->ultNome << ", Estudante (especial), Grupo " << raiz->removida->numDepartamentoOuGrupo << ", " << raiz->removida->membro_aluno.curso << endl;
		}
	}
	else {
		cout << raiz->removida->priNome << " " << raiz->removida->ultNome << ", Staff, Departamento " << raiz->removida->numDepartamentoOuGrupo << endl;
	}
	imprimeArvoreInfixa(raiz->direita);
}

n�Removidos* removeSemDinheiro(LLPessoas*fila, LLRefei��es *r, n�Removidos*arvoreRemovidos) { // averigua se o aluno/funcion�rio possui Plafond necess�rio para pagar pela refei��o
	int i = 0;
	bool h�Aluno = false;
	bool h�Staff = false;
	bool again = false;
	int indiOuGrupo;
	int num = 0;
	fila->iterator = fila->primeira;
	while (fila->iterator != NULL) {
		if (fila->iterator->membro_aluno.num > 0) {
			if (fila->iterator->plafond < r->atual->custo) {
				cout << "***** ATEN��O *****" << endl << "O aluno com o n�mero " << fila->iterator->membro_aluno.num << " n�o possui plafond suficiente para iniciar a refei��o." << endl;
				cout << "\t1.Remover aluno da entrada" << endl << "\t2.Remover grupo da entrada" << endl << endl;
				num = fila->iterator->numDepartamentoOuGrupo;
				h�Aluno = true;
				again = true;
				break;
			}
		}
		else {
			if (fila->iterator->plafond < r->atual->custo) {
				cout << "***** ATEN��O *****\nO elemento de staff com o n�mero " << fila->iterator->membro_staff.numFuncionario << " n�o possui plafond suficiente para iniciar a refei��o." << endl;
				cout << "\t1.Remover funcion�rio da entrada" << endl << "\t2.Remover grupo da entrada" << endl << endl;
				num = fila->iterator->numDepartamentoOuGrupo;
				h�Staff = true;
				again = true;
				break;
			}
		}
		i++;
		fila->iterator = fila->iterator->seguinte;
	}
	if (h�Aluno || h�Staff) {
		while (again) {
			cout << "**** Comando: ";
			cin >> indiOuGrupo;
			cin.ignore(1000, '\n');
			cout << endl;
			switch (indiOuGrupo)
			{
			case 1:
				arvoreRemovidos = removeSemDinheiroPessoa(fila, arvoreRemovidos, num, i);
				again = false;
				break;
			case 2:
				arvoreRemovidos = removeSemDinheiroGrupo(fila, arvoreRemovidos, num);
				again = false;
				break;
			default:
				cout << "Por favor escolha uma das op��es dispon�veis." << endl;
				if (h�Aluno) {
					cout << "\t1.Remover aluno da entrada" << endl << "\t2.Remover grupo da entrada" << endl << endl;
				}
				else {
					cout << "\t1.Remover funcion�rio da entrada" << endl << "\t2.Remover grupo da entrada" << endl << endl;
				}
				break;
			}
		}
		arvoreRemovidos = removeSemDinheiro(fila, r, arvoreRemovidos);
	}
	return arvoreRemovidos;
}

n�Removidos* removeSemDinheiroPessoa(LLPessoas*fila, n�Removidos*arvoreRemovidos, int numDepGrupo, int posiPessoa) {
	fila->iterator = fila->primeira;
	LLPessoas::pessoa*p = new LLPessoas::pessoa();
	p = removePessoaMeio(fila, posiPessoa);
	arvoreRemovidos = adicionaArvoreRemovidos(arvoreRemovidos, p);
	fila->iterator = fila->primeira;
	int conta = 0; //esta vari�vel ser� para ajustar o tamanho do grupo depois de ser removida a pessoa
	while (fila->iterator != NULL) {
		if (fila->iterator->numDepartamentoOuGrupo == numDepGrupo) {
			conta++;
		}
		fila->iterator = fila->iterator->seguinte;
	}
	fila->iterator = fila->primeira;
	while (fila->iterator != NULL) {
		if (fila->iterator->numDepartamentoOuGrupo == numDepGrupo) {//reajusta o tamanho do grupo tendo em conta que saiu uma pessoa
			fila->iterator->tamanhoGrupo = conta;
			conta--;
		}
		fila->iterator = fila->iterator->seguinte;
	}
	return arvoreRemovidos;
}

n�Removidos* removeSemDinheiroGrupo(LLPessoas*fila, n�Removidos*arvoreRemovidos, int numDepGrupo) {
	int s = 0;
	fila->iterator = fila->primeira;
	while (fila->iterator != NULL) {
		if (fila->iterator->numDepartamentoOuGrupo == numDepGrupo) {
			LLPessoas::pessoa*p = new LLPessoas::pessoa();
			p = removePessoaMeio(fila, s);
			arvoreRemovidos = adicionaArvoreRemovidos(arvoreRemovidos, p);
		}
		else {
			s++;
			fila->iterator = fila->iterator->seguinte;
		}
	}
	return arvoreRemovidos;
}

void alterarPlafond(LLPessoas *ll) {// op��o 4, altera o plafond de uma pessoa na fila de espera pelo n�mero de aluno ou de funcion�rio
	int n;
	cout << "Insira um n�mero de aluno/funcion�rio: " << endl;
	cin >> n;
	int i = 0;
	ll->iterator = ll->primeira;
	while (ll->iterator != NULL) {
		if (ll->iterator->membro_aluno.num > 0) {
			if (ll->iterator->membro_aluno.num == n) {
				cout << "Plafond inicial: " << ll->iterator->plafond << " EUR" << endl;
				cout << "Insira um novo plafond: ";
				cin >> ll->iterator->plafond;
				return;
			}
		}
		else {
			if (ll->iterator->membro_staff.numFuncionario == n) {
				cout << "Plafond inicial: " << ll->iterator->plafond << " EUR" << endl;
				cout << "Insira um novo plafond: ";
				cin >> ll->iterator->plafond;
				return;
			}
		}
		ll->iterator = ll->iterator->seguinte;
	}
	cout << "Ningu�m na fila tem o n�mero de aluno / funcion�rio que inseriu" << endl;
}

int contaPessoasFila(LLPessoas*fila) {//conta as pessoas que est�o na fila, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	fila->iterator = fila->primeira;
	while (fila->iterator != NULL) {
		soma++;
		fila->iterator = fila->iterator->seguinte;
	}
	return soma;
}

int contaAcabados(LLPessoas*acabados) {//conta as pessoas que sa�ram da cantina, para ser usado no ordenaAlfabeticamenteUltNome
	int soma = 0;
	acabados->iterator = acabados->primeira;
	while (acabados->iterator != NULL) {
		soma++;
		acabados->iterator = acabados->iterator->seguinte;
	}
	return soma;
}

void mergeSortAlfabeticamenteUltNome(LLPessoas::pessoa**sistema, int tam) {// o merge sort da ordena��o alfab�tica pelo �ltimo nome
	if (tam < 2) {
		return;
	}
	int mid = tam / 2;
	LLPessoas::pessoa **left = new LLPessoas::pessoa*[mid];
	LLPessoas::pessoa**right = new LLPessoas::pessoa*[tam - mid];
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

void mergeUltNome(LLPessoas::pessoa**left, LLPessoas::pessoa**right, LLPessoas::pessoa**sistema, int n_left, int n_right, int tam) {
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