#include<iostream>
#include<string>
#include<fstream>
#include "Ficheiros.h"
#include"Pessoas.h"
#include"Mesas.h"
#include"Refeição.h"
using namespace std;

void guardaFicheiros(string* Lista, string nome_ficheiro) {//vai ler um ficheiro com nome "nome_ficheiro" e guardar as linhas que lê no array Lista fornecida nos argumentos
	fstream file(nome_ficheiro, ios::in);
	string *line = new string();
	int *i = new int(0);
	if (file.is_open()) {
		while (getline(file, *line)) {
			Lista[(*i)++] = *line;
		}
	}
	file.close();
	delete i, line;
}

int numLinhas(string nome_ficheiro) {//vai contar o nº de linhas de um ficheiro fornecido, para os vetores que guardarem strings não desperdiçarem memória
	fstream ficheiro(nome_ficheiro, ios::in);
	int *conta = new int(0);
	if (ficheiro.is_open()) {
		string aux;
		while (getline(ficheiro, aux)) {
			(*conta)++;
		}
		ficheiro.close();
		return (*conta);
	}
	else {
		return -1;
	}
}

void limpaLLPessoas(LLPessoas*ll) {
	while (ll->primeira != NULL) {
		LLPessoas::pessoa*apagador = ll->primeira;
		ll->primeira = ll->primeira->seguinte;
		delete apagador;
	}
	ll->primeira = NULL;
	ll->iterator = NULL;
	ll->ultima = NULL;
}

void gravaPessoaRemovidos(LLPessoas::pessoa * p) {//vai gravar uma pessoa que foi removida no ficheiro. Cada dado fica numa linha individual para ser mais fácil o carregamento do ficheiro
	fstream ficheiro("Pessoas removidas.txt", ios::out | ios::app);
	if (ficheiro.is_open()) {
		if (p->membro_aluno.num > 0) {
			if (!p->membro_aluno.especialOuNao) {
				ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->duração << endl << p->plafond << endl << p->tamanhoGrupo << endl;
			}
			else {
				ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante Especial" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->duração << endl << p->plafond << endl << p->tamanhoGrupo << endl;
			}
		}
		else {
			ficheiro << p->priNome << endl << p->ultNome << endl << "Staff" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_staff.numFuncionario) << endl << p->duração << endl << p->plafond << endl << p->tamanhoGrupo << endl;
		}
	}
	ficheiro.close();
}

void gravaLLPessoas(LLPessoas * ll, const char*NomeDoFicheiro) {//grava a fila de pessoas no ficheiro
	fstream ficheiro(NomeDoFicheiro, ios::out);
	ll->iterator = ll->primeira;
	if (ficheiro.is_open()) {
		while (ll->iterator != NULL) {
			if (ll->iterator->membro_aluno.num > 0) {
				if (!ll->iterator->membro_aluno.especialOuNao) {
					ficheiro << ll->iterator->priNome << endl << ll->iterator->ultNome << endl << "Estudante" << endl << ll->iterator->numDepartamentoOuGrupo << endl << ll->iterator->membro_aluno.curso << endl << to_string(ll->iterator->membro_aluno.num) << endl << ll->iterator->duração << endl << ll->iterator->plafond << endl << ll->iterator->tamanhoGrupo << endl;
				}
				else {
					ficheiro << ll->iterator->priNome << endl << ll->iterator->ultNome << endl << "Estudante Especial" << endl << ll->iterator->numDepartamentoOuGrupo << endl << ll->iterator->membro_aluno.curso << endl << to_string(ll->iterator->membro_aluno.num) << endl << ll->iterator->duração << endl << ll->iterator->plafond << endl << ll->iterator->tamanhoGrupo << endl;
				}
			}
			else {
				ficheiro << ll->iterator->priNome << endl << ll->iterator->ultNome << endl << "Staff" << endl << ll->iterator->numDepartamentoOuGrupo << endl << ll->iterator->membro_aluno.curso << endl << to_string(ll->iterator->membro_staff.numFuncionario) << endl << ll->iterator->duração << endl << ll->iterator->plafond << endl << ll->iterator->tamanhoGrupo << endl;
			}
			ll->iterator = ll->iterator->seguinte;
		}
	}
	ficheiro.close();
}

void gravaRefeicoes(LLRefeições * ref) {
	fstream ficheiro("Refeicoes.txt", ios::out);
	LLRefeições::refeição*itera = ref->primeira;
	if (ficheiro.is_open()) {
		while (itera != NULL) {
			ficheiro << itera->entrada << endl << itera->pratoMain << endl << itera->custo << endl;
			itera = itera->seguinte;
		}
	}
	ficheiro.close();
}

void gravaCantina(LLMesas* cantina) {//grava a cantina de pessoas no ficheiro
	fstream ficheiro("Cantina.txt", ios::out);
	cantina->iterator = cantina->primeira;
	if (ficheiro.is_open()) {
		while (cantina->iterator != NULL) {
			ficheiro << cantina->iterator->numMesa << "\t" << cantina->iterator->capacidade << "\t" << cantina->iterator->numSentados << endl;
			cantina->iterator->sentados->iterator = cantina->iterator->sentados->primeira;
			while (cantina->iterator->sentados->iterator != NULL) {
				if (cantina->iterator->sentados->iterator->membro_aluno.num > 0) {
					if (!cantina->iterator->sentados->iterator->membro_aluno.especialOuNao) {
						ficheiro << cantina->iterator->sentados->iterator->priNome << endl << cantina->iterator->sentados->iterator->ultNome << endl << "Estudante" << endl << cantina->iterator->sentados->iterator->numDepartamentoOuGrupo << endl << cantina->iterator->sentados->iterator->membro_aluno.curso << endl << to_string(cantina->iterator->sentados->iterator->membro_aluno.num) << endl << cantina->iterator->sentados->iterator->duração << endl << cantina->iterator->sentados->iterator->plafond << endl << cantina->iterator->sentados->iterator->tamanhoGrupo << endl;
					}
					else {
						ficheiro << cantina->iterator->sentados->iterator->priNome << endl << cantina->iterator->sentados->iterator->ultNome << endl << "Estudante Especial" << endl << cantina->iterator->sentados->iterator->numDepartamentoOuGrupo << endl << cantina->iterator->sentados->iterator->membro_aluno.curso << endl << to_string(cantina->iterator->sentados->iterator->membro_aluno.num) << endl << cantina->iterator->sentados->iterator->duração << endl << cantina->iterator->sentados->iterator->plafond << endl << cantina->iterator->sentados->iterator->tamanhoGrupo << endl;
					}
				}
				else {
					ficheiro << cantina->iterator->sentados->iterator->priNome << endl << cantina->iterator->sentados->iterator->ultNome << endl << "Staff" << endl << cantina->iterator->sentados->iterator->numDepartamentoOuGrupo << endl << cantina->iterator->sentados->iterator->membro_aluno.curso << endl << to_string(cantina->iterator->sentados->iterator->membro_staff.numFuncionario) << endl << cantina->iterator->sentados->iterator->duração << endl << cantina->iterator->sentados->iterator->plafond << endl << cantina->iterator->sentados->iterator->tamanhoGrupo << endl;
				}
				cantina->iterator->sentados->iterator = cantina->iterator->sentados->iterator->seguinte;
			}
			cantina->iterator = cantina->iterator->seguinte;
		}
	}
	ficheiro.close();
	return;
}

void gravaRemovidos(nóRemovidos* raiz) {//grava as pessoas que foram removidas por insuficiência de plafond no ficheiro
	fstream ficheiro("Removidos.txt", ios::out);
	int tam = contaNosArvore(raiz);
	LLPessoas::pessoa**removidos = new LLPessoas::pessoa*[tam];
	int *pos = new int(0);
	guardaArvoreVetor(raiz, pos, removidos);
	*pos = 0;
	if (ficheiro.is_open()) {
		while (*pos < tam) {
			if (removidos[*pos]->membro_aluno.num > 0) {
				if (!removidos[*pos]->membro_aluno.especialOuNao) {
					ficheiro << removidos[*pos]->priNome << endl << removidos[*pos]->ultNome << endl << "Estudante" << endl << removidos[*pos]->numDepartamentoOuGrupo << endl << removidos[*pos]->membro_aluno.curso << endl << to_string(removidos[*pos]->membro_aluno.num) << endl << removidos[*pos]->duração << endl << removidos[*pos]->plafond << endl << removidos[*pos]->tamanhoGrupo << endl;
				}
				else {
					ficheiro << removidos[*pos]->priNome << endl << removidos[*pos]->ultNome << endl << "Estudante Especial" << endl << removidos[*pos]->numDepartamentoOuGrupo << endl << removidos[*pos]->membro_aluno.curso << endl << to_string(removidos[*pos]->membro_aluno.num) << endl << removidos[*pos]->duração << endl << removidos[*pos]->plafond << endl << removidos[*pos]->tamanhoGrupo << endl;
				}
			}
			else {
				ficheiro << removidos[*pos]->priNome << endl << removidos[*pos]->ultNome << endl << "Staff" << endl << removidos[*pos]->numDepartamentoOuGrupo << endl << removidos[*pos]->membro_aluno.curso << endl << to_string(removidos[*pos]->membro_staff.numFuncionario) << endl << removidos[*pos]->duração << endl << removidos[*pos]->plafond << endl << removidos[*pos]->tamanhoGrupo << endl;
			}
			(*pos)++;
		}
	}
	ficheiro.close();
}

void carregaPessoa(string PriNome, string UltNome, string AlunoOuNao, string DepGru, string Curso, string numAluFunc, string duracao, string plaf, string tamGrupo, LLPessoas::pessoa*p, LLReserva*reserva) {//vai carregar um aluno de um ficheiro
	p->priNome = PriNome;
	p->ultNome = UltNome;
	const char*aux1 = DepGru.c_str();//transforma o string em *char
	int numDepGru = atoi(aux1);//transforma o *char em int
	p->numDepartamentoOuGrupo = numDepGru;
	if (listaVaziaReserva(reserva)) {
		insereFimReserva(reserva, numDepGru);
	}
	if (numDepGru != reserva->ultimo->num) {
		insereFimReserva(reserva, numDepGru);
	}
	const char*aux2 = plaf.c_str();
	float plafond = atof(aux2);//transforma o *char em float
	p->plafond = plafond;
	const char*aux3 = duracao.c_str();
	int dura = atoi(aux3);
	p->duração = dura;
	p->membro_aluno.curso = Curso;
	const char*aux5 = tamGrupo.c_str();
	int tamanhoGrupo = atoi(aux5);
	p->tamanhoGrupo = tamanhoGrupo;
	if (AlunoOuNao != "Staff") {
		const char*aux4 = numAluFunc.c_str();
		int numAluno = atoi(aux4);
		p->membro_aluno.num = numAluno;
		if (AlunoOuNao == "Estudante Especial") {
			p->membro_aluno.especialOuNao = true;
		}
		else {
			p->membro_aluno.especialOuNao = false;
		}
		p->membro_staff.numFuncionario = NULL;
	}
	else {
		const char*aux4 = numAluFunc.c_str();
		int numFunc = atoi(aux4);
		p->membro_staff.numFuncionario = numFunc;
		p->membro_aluno.num = NULL;
	}
}

void carregaLLPessoas(LLPessoas* fila, LLReserva*reserva, const char*NomeDoFicheiro) {//vai carregar uma fila de pessoas do ficheiro
	fstream ficheiro(NomeDoFicheiro, ios::in);
	limpaLLPessoas(fila);
	int tamFila = numLinhas(NomeDoFicheiro) / 9;
	if (ficheiro.is_open()) {
		for (int conta = 0; conta < tamFila; conta++) {
			LLPessoas::pessoa*p = new LLPessoas::pessoa;
			string *PriNome = new string;
			string *UltNome = new string;
			string *AlunoouNao = new string;
			string *GrupoDep = new string;
			string *Curso = new string;
			string *numAlunoFunc = new string;
			string *duração = new string;
			string *plafond = new string;
			string *tamGrupo = new string;
			getline(ficheiro, *PriNome);
			getline(ficheiro, *UltNome);
			getline(ficheiro, *AlunoouNao);
			getline(ficheiro, *GrupoDep);
			getline(ficheiro, *Curso);
			getline(ficheiro, *numAlunoFunc);
			getline(ficheiro, *duração);
			getline(ficheiro, *plafond);
			getline(ficheiro, *tamGrupo);
			carregaPessoa(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *duração, *plafond, *tamGrupo, p, reserva);
			insereFimPessoas(fila, p);
			delete PriNome, UltNome, GrupoDep, numAlunoFunc, duração, plafond, tamGrupo, AlunoouNao, Curso;
		}
	}
	ficheiro.close();
}

nóRemovidos* carregaRemovidos(nóRemovidos* arvoreRemovidos, LLReserva*reserva, const char*NomeDoFicheiro) {//vai carregar as pessoas que foram removidas porque não tinham plafond suficiente do ficheiro
	fstream ficheiro(NomeDoFicheiro, ios::in);
	int numRemovidos = numLinhas(NomeDoFicheiro) / 9;
	limpaArvore(arvoreRemovidos);
	arvoreRemovidos = NULL;
	if (ficheiro.is_open()) {
		for (int conta = 0; conta < numRemovidos; conta++) {
			LLPessoas::pessoa*p = new LLPessoas::pessoa;
			string *PriNome = new string;
			string *UltNome = new string;
			string *AlunoouNao = new string;
			string *GrupoDep = new string;
			string *Curso = new string;
			string *numAlunoFunc = new string;
			string *duração = new string;
			string *plafond = new string;
			string *tamGrupo = new string;
			getline(ficheiro, *PriNome);
			getline(ficheiro, *UltNome);
			getline(ficheiro, *AlunoouNao);
			getline(ficheiro, *GrupoDep);
			getline(ficheiro, *Curso);
			getline(ficheiro, *numAlunoFunc);
			getline(ficheiro, *duração);
			getline(ficheiro, *plafond);
			getline(ficheiro, *tamGrupo);
			carregaPessoa(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *duração, *plafond, *tamGrupo, p, reserva);
			arvoreRemovidos = adicionaArvoreRemovidos(arvoreRemovidos, p);
			delete PriNome, UltNome, GrupoDep, numAlunoFunc, duração, plafond, tamGrupo, AlunoouNao, Curso;
		}
	}
	ficheiro.close();
	return arvoreRemovidos;
}

void limpaCantina(LLMesas*cantina) {
	while (cantina->primeira != NULL) {
		limpaLLPessoas(cantina->primeira->sentados);
		LLMesas::mesa*apagador = new LLMesas::mesa();
		apagador = cantina->primeira;
		cantina->primeira = cantina->primeira->seguinte;
		delete apagador;
	}
	cantina->primeira = NULL;
	cantina->iterator = NULL;
	cantina->ultima = NULL;
}

void carregaCantina(LLMesas* cantina, int numMesas, LLReserva*reserva, const char*NomeDoFicheiro) {//carrega uma cantina do ficheiro
	fstream ficheiro(NomeDoFicheiro, ios::in);
	limpaCantina(cantina);
	int i = 1;
	if (ficheiro.is_open()) {
		string testa;
		while (getline(ficheiro, testa)) {
			const char*aux = testa.c_str();
			if (i < 10) {
				if (aux[1] == '\t') {//neste caso sabe-se que está numa linha com o número da mesa e a sua capacidade
					LLMesas::mesa*m = new LLMesas::mesa();
					const char*aux1 = &aux[2];
					int cap = atoi(aux1);
					const char*aux2 = &aux[4];
					int numSenta = atoi(aux2);
					m->numMesa = i++;
					m->capacidade = cap;
					m->numSentados = numSenta;
					LLPessoas*sentados = new LLPessoas;
					sentados->primeira = NULL;
					sentados->iterator = NULL;
					sentados->ultima = NULL;
					for (int j = 0; j < numSenta; j++) {
						LLPessoas::pessoa*p = new LLPessoas::pessoa();
						string* PriNome = new string;
						string *UltNome = new string;
						string *AlunoouNao = new string;
						string *GrupoDep = new string;
						string *Curso = new string;
						string *numAlunoFunc = new string;
						string *duração = new string;
						string *plafond = new string;
						string *tamGrupo = new string;
						getline(ficheiro, *PriNome);
						getline(ficheiro, *UltNome);
						getline(ficheiro, *AlunoouNao);
						getline(ficheiro, *GrupoDep);
						getline(ficheiro, *Curso);
						getline(ficheiro, *numAlunoFunc);
						getline(ficheiro, *duração);
						getline(ficheiro, *plafond);
						getline(ficheiro, *tamGrupo);
						carregaPessoa(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *duração, *plafond, *tamGrupo, p, reserva);
						insereFimPessoas(sentados, p);
						delete PriNome, UltNome, GrupoDep, numAlunoFunc, duração, plafond, tamGrupo, AlunoouNao, Curso;
					}
					m->sentados = sentados;
					insereFimMesas(cantina, m);
				}
			}
			else {
				if (aux[2] == '\t') {//neste caso sabe-se que está numa linha com o número da mesa e a sua capacidade
					LLMesas::mesa*m = new LLMesas::mesa();
					const char*aux3 = &aux[3];
					int cap = atoi(aux3);
					const char*aux4 = &aux[5];
					int numSenta = atoi(aux4);
					m->numMesa = i++;
					m->capacidade = cap;
					m->numSentados = numSenta;
					LLPessoas*sentados = new LLPessoas;
					sentados->primeira = NULL;
					sentados->iterator = NULL;
					sentados->ultima = NULL;
					for (int j = 0; j < numSenta; j++) {
						LLPessoas::pessoa*p = new LLPessoas::pessoa();
						string *PriNome = new string;
						string *UltNome = new string;
						string *AlunoouNao = new string;
						string *GrupoDep = new string;
						string *Curso = new string;
						string *numAlunoFunc = new string;
						string *duração = new string;
						string *plafond = new string;
						string *tamGrupo = new string;
						getline(ficheiro, *PriNome);
						getline(ficheiro, *UltNome);
						getline(ficheiro, *AlunoouNao);
						getline(ficheiro, *GrupoDep);
						getline(ficheiro, *Curso);
						getline(ficheiro, *numAlunoFunc);
						getline(ficheiro, *duração);
						getline(ficheiro, *plafond);
						getline(ficheiro, *tamGrupo);
						carregaPessoa(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *duração, *plafond, *tamGrupo, p, reserva);
						insereFimPessoas(sentados, p);
					}
					m->sentados = sentados;
					insereFimMesas(cantina, m);
				}
			}
		}
	}
	ficheiro.close();
}

void limpaRefeições(LLRefeições*r) {
	while (r->primeira != NULL) {
		LLRefeições::refeição*apagador = new LLRefeições::refeição();
		apagador = r->primeira;
		r->primeira = r->primeira->seguinte;
		delete apagador;
	}
	r->primeira = NULL;
	r->atual = NULL;
}

void carregaRefeições(LLRefeições * r, const char*NomeDoFicheiro) {//carrega uma refeição do ficheiro
	fstream ficheiro(NomeDoFicheiro, ios::in);
	limpaRefeições(r);
	int numRefeições = numLinhas(NomeDoFicheiro) / 3;
	int conta = 0;
	if (ficheiro.is_open()) {
		while (conta < numRefeições) {
			LLRefeições::refeição*novo = new LLRefeições::refeição();
			string *entrada = new string;
			string *pratoPrincipal = new string;
			string *aux = new string;
			getline(ficheiro, *entrada);
			novo->entrada = *entrada;
			getline(ficheiro, *pratoPrincipal);
			novo->pratoMain = *pratoPrincipal;
			getline(ficheiro, *aux);
			const char*aux2 = (*aux).c_str();
			float custo = atof(aux2);
			novo->custo = custo;
			insereFimRefeições(r, novo);
			delete  entrada, pratoPrincipal, aux;
			conta++;
		}
	}
}

int contaCantina(const char*NomeDoFicheiro) {//conta o número de mesas na cantina guardada no ficheiro
	fstream ficheiro(NomeDoFicheiro, ios::in);
	int numMesas = 0;
	if (ficheiro.is_open()) {
		string aux;
		while (getline(ficheiro, aux)) {
			const char*aux2 = aux.c_str();
			if (aux2[1] == '\t' || aux2[2] == '\t') {
				numMesas++;
			}
		}
	}
	ficheiro.close();
	return numMesas;
}