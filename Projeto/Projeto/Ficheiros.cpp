#include<iostream>
#include<string>
#include<fstream>
#include "Ficheiros.h"
#include"Pessoas.h"
#include"Mesas.h"
using namespace std;

void guardaFicheiros(string* Lista, string nome_ficheiro) {//vai ler um ficheiro com nome "nome_ficheiro" e guardar as linhas que l� no array Lista fornecida nos argumentos
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

int numLinhas(string nome_ficheiro) {//vai contar o n� de linhas de um ficheiro fornecido, para os vetores que guardarem strings n�o desperdi�arem mem�ria
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

int* copiaVetor(int* aux, int tamanho) {// esta fun��o evitar� a exist�ncia de arrays com espa�os vazios
	int *vetor = new int[tamanho];
	for (int*i = new int(0); *i < tamanho; (*i)++) {
		vetor[*i] = aux[*i];
	}
	return vetor;
}

void criaVetor(int*res, int tamanho) {//cria o vetor que vai guardar os n�meros de grupo/departamento
	int i = 0;
	for (int i = 0; i < tamanho; i++) {
		res[i] = NULL;
	}
}

void gravaPessoaFila(pessoa * p){//vai gravar uma pessoa da fila no ficheiro. Cada dado fica numa linha individual para ser mais f�cil o carregamento do ficheiro
	fstream ficheiro("Fila da cantina.txt", ios::out | ios::app);
	if (ficheiro.is_open()) {
		if (p == NULL) {
			ficheiro << "-----NULL-----" << endl;
		}
		else {
			if (p->membro_aluno.num > 0) {
				if (!p->membro_aluno.especialOuNao) {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
				else {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante Especial" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
			}
			else {
				ficheiro << p->priNome << endl << p->ultNome << endl << "Staff" << endl << p->numDepartamentoOuGrupo << endl << to_string(p->membro_staff.numFuncionario) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
			}
		}
	}
	ficheiro.close();
}

void gravaPessoaAcabados(pessoa * p) {//vai gravar uma pessoa que acabou a refei��o no ficheiro . Cada dado fica numa linha individual para ser mais f�cil o carregamento do ficheiro
	fstream ficheiro("Pessoas que acabaram.txt", ios::out | ios::app);
	if (ficheiro.is_open()) {
		if (p == NULL) {
			ficheiro << "-----NULL-----" << endl;
		}
		else {
			if (p->membro_aluno.num > 0) {
				if (!p->membro_aluno.especialOuNao) {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
				else {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante Especial" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
			}
			else {
				ficheiro << p->priNome << endl << p->ultNome << endl << "Staff" << endl << p->numDepartamentoOuGrupo << endl << to_string(p->membro_staff.numFuncionario) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
			}
		}
	}
	ficheiro.close();
}

void gravaPessoaRemovidos(pessoa * p) {//vai gravar uma pessoa que foi removida no ficheiro. Cada dado fica numa linha individual para ser mais f�cil o carregamento do ficheiro
	fstream ficheiro("Pessoas removidas.txt", ios::out | ios::app);
	if (ficheiro.is_open()) {
		if (p == NULL) {
			ficheiro << "-----NULL-----" << endl;
		}
		else {
			if (p->membro_aluno.num > 0) {
				if (!p->membro_aluno.especialOuNao) {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
				else {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante Especial" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
			}
			else {
				ficheiro << p->priNome << endl << p->ultNome << endl << "Staff" << endl << p->numDepartamentoOuGrupo << endl << to_string(p->membro_staff.numFuncionario) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
			}
		}
	}
	ficheiro.close();
}

void gravaPessoaCantina(pessoa * p) {//vai gravar uma pessoa da cantina no ficheiro. Cada dado fica numa linha individual para ser mais f�cil o carregamento do ficheiro
	fstream ficheiro("Cantina.txt", ios::out | ios::app);
	if (ficheiro.is_open()) {
		if (p == NULL) {
			ficheiro << "-----NULL-----" << endl;
		}
		else {
			if (p->membro_aluno.num > 0) {
				if (!p->membro_aluno.especialOuNao) {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string (p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
				else {
					ficheiro << p->priNome << endl << p->ultNome << endl << "Estudante Especial" << endl << p->numDepartamentoOuGrupo << endl << p->membro_aluno.curso << endl << to_string(p->membro_aluno.num) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
				}
			}
			else {
				ficheiro << p->priNome << endl << p->ultNome << endl << "Staff" << endl << p->numDepartamentoOuGrupo << endl << to_string(p->membro_staff.numFuncionario) << endl << p->dura��o << endl << p->plafond << endl << p->tamanho << endl;
			}
		}
	}
	ficheiro.close();
}

void gravaFila(pessoa ** fila, int tam){//grava a fila de pessoas no ficheiro
	fstream ficheiro("Fila da cantina.txt", ios::out); 
	if (ficheiro.is_open()) {
		int i = 0;
		while (i < tam) {
			gravaPessoaFila(fila[i]);
			i++;
		}
	}
	ficheiro.close();
}

void gravaAcabados(pessoa ** acabados, int tam) {//grava as pessoas que acabaram no ficheiro
	fstream ficheiro("Pessoas que acabaram.txt", ios::out);
	if (ficheiro.is_open()) {
		int i = 0;
		while (i < tam) {
			gravaPessoaAcabados(acabados[i]);
			i++;
		}
	}
	ficheiro.close();
}

void gravaRemovidos(pessoa ** removidos, int tam) {//grava as pessoas que foram removidas por insufici�ncia de plafond no ficheiro
	fstream ficheiro("Pessoas removidas.txt", ios::out);
	if (ficheiro.is_open()) {
		int i = 0;
		while (i < tam) {
			gravaPessoaRemovidos(removidos[i]);
			i++;
		}
	}
	ficheiro.close();
}

void gravaCantina(mesa ** cantina){//grava a cantina de pessoas no ficheiro
	fstream ficheiro("Cantina.txt", ios::out);
	if (ficheiro.is_open()) {
		ficheiro << "\0";//limpa o ficheiro
	}
	ficheiro.close();
	fstream file("Cantina.txt", ios::out | ios::app);
	if (file.is_open()) {
		int tam = cantina[0]->totalMesas;
		for (int i = 0; i < tam; i++) {
			file << cantina[i]->numMesa << "\t" << cantina[i]->tamanho << "\t" << cantina[i]->numSentados << endl;
			int auxmesa = cantina[i]->tamanho;
			for (int j = 0; j < auxmesa; j++) {
				gravaPessoaCantina(cantina[i]->sentados[j]);
			}
		}
	}
	file.close();
}

void gravaRefei��o(refei��o * r){//guarda a refei��o da cantina num ficheiro
	fstream ficheiro("Refei��o da cantina.txt", ios::out);
	if (ficheiro.is_open()) {
		ficheiro << "Refei��o atual:" << endl << r->entrada << endl<< r->pratoMain << endl << r->custo << "�" << endl;
	}
	ficheiro.close();
}

void carregaAluno(string PriNome, string UltNome, string EspecialouNao,string DepGru, string Curso, string numAluFunc, string duracao, string plaf, string tamGrupo, pessoa*p, int*reserva, int tamReserva){//vai carregar um aluno de um ficheiro
	p->priNome = PriNome;
	p->ultNome = UltNome;
	const char*aux1 = DepGru.c_str();//transforma o string em *char
	int numDepGru = atoi(aux1);//transforma o *char em int
	adicionaReservaNum(reserva, numDepGru, tamReserva);
	p->numDepartamentoOuGrupo = numDepGru;
	const char*aux2 = plaf.c_str();
	float plafond = atof(aux2);
	p->plafond = plafond;//transforma o *char em float
	const char*aux3 = duracao.c_str();
	int dura = atoi(aux3);
	p->dura��o = dura;
	p->membro_aluno.curso = Curso;
	const char*aux4 = numAluFunc.c_str();
	int numAluno = atoi(aux4);
	p->membro_aluno.num = numAluno;
	const char*aux5 = tamGrupo.c_str();
	int tamanhoGrupo = atoi(aux5);
	p->tamanho = tamanhoGrupo;
	if (EspecialouNao == "Estudante Especial") {
		p->membro_aluno.especialOuNao = true;
	}
	else {
		p->membro_aluno.especialOuNao = false;
	}
	p->membro_staff.numFuncionario = NULL;
}

void carregaStaff(string PriNome, string UltNome, string DepGru, string numAluFunc, string duracao, string plaf, string tamGrupo, pessoa*p, int*reserva, int tamReserva) {// vai carregar um funcion�rio de staff do ficheiro
	p->priNome = PriNome;
	p->ultNome = UltNome;
	const char*aux1 = DepGru.c_str();
	int numDepGru =atoi(aux1);
	p->numDepartamentoOuGrupo = numDepGru;
	adicionaReservaNum(reserva, numDepGru, tamReserva);
	const char*aux2 = plaf.c_str();
	float plafond = atof(aux2);
	p->plafond = plafond;
	const char*aux3 = duracao.c_str();
	int dura = atoi(aux3);
	p->dura��o = dura;
	const char*aux4 = numAluFunc.c_str();
	int numFunc = atoi(aux4);
	p->membro_staff.numFuncionario = numFunc;
	const char*aux5 = tamGrupo.c_str();
	int tamanhoGrupo = atoi(aux5);
	p->tamanho = tamanhoGrupo;
	p->membro_aluno.num = NULL;
	p->membro_aluno.curso = "\0";
	p->membro_aluno.especialOuNao = NULL;
}

void carregaFila(pessoa ** fila, int tam, int*pos, int*reserva, int tamReserva) {//vai carregar uma fila de pessoas do ficheiro
	fstream ficheiro("Fila da cantina.txt", ios::in);
	if (ficheiro.is_open()) {
		*pos = 0;
		for (int j = 0; j < tam; j++) {
			pessoa*p = new pessoa;
			string *PriNome=new string;
			string *UltNome = new string;
			string *AlunoouNao = new string;
			string *GrupoDep = new string;
			string *Curso = new string;
			string *numAlunoFunc = new string;
			string *dura��o = new string;
			string *plafond = new string;
			string *tamGrupo = new string;
			getline(ficheiro, *PriNome);
			if (*PriNome != "-----NULL-----") {//verifica se est� a guardar pessoas e n�o lugares vazios da fila
				getline(ficheiro, *UltNome);
				getline(ficheiro, *AlunoouNao);
				if (*AlunoouNao != "Staff") {
					getline(ficheiro, *GrupoDep);
					getline(ficheiro, *Curso);
					getline(ficheiro, *numAlunoFunc);
					getline(ficheiro, *dura��o);
					getline(ficheiro, *plafond);
					getline(ficheiro, *tamGrupo);
					carregaAluno(*PriNome,* UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva,tamReserva);
				}
				else {
					getline(ficheiro, *GrupoDep);
					getline(ficheiro, *numAlunoFunc);
					getline(ficheiro, *dura��o);
					getline(ficheiro, *plafond);
					getline(ficheiro, *tamGrupo);
					carregaStaff(*PriNome, *UltNome, *GrupoDep, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
				}
				fila[j] = p;
				(*pos)++;
			}
			else {
				fila[j] = NULL;
			}
			delete PriNome, UltNome, GrupoDep, numAlunoFunc, dura��o, plafond, tamGrupo, AlunoouNao, Curso;
		}
	}
	if (*pos >= 50) {//certifica que est� dentro dos �ndices poss�veis para n�o encontrar erros
		(*pos)--;
	}
	ficheiro.close();
}

void carregaAcabados(pessoa ** acabados, int tam, int*reserva, int tamReserva) {//vai carregar as pessoas  que acabaram do ficheiro
	fstream ficheiro("Pessoas que acabaram.txt", ios::in);
	if (ficheiro.is_open()) {
		for (int j = 0; j < tam; j++) {
			pessoa*p = new pessoa;
			string *PriNome = new string;
			string *UltNome = new string;
			string *AlunoouNao = new string;
			string *GrupoDep = new string;
			string *Curso = new string;
			string *numAlunoFunc = new string;
			string *dura��o = new string;
			string *plafond = new string;
			string *tamGrupo = new string;
			getline(ficheiro, *PriNome);
			if (*PriNome != "-----NULL-----") {//verifica se est� a guardar pessoas e n�o lugares vazios da fila
				getline(ficheiro, *UltNome);
				getline(ficheiro, *AlunoouNao);
				if (*AlunoouNao != "Staff") {
					getline(ficheiro, *GrupoDep);
					getline(ficheiro, *Curso);
					getline(ficheiro, *numAlunoFunc);
					getline(ficheiro, *dura��o);
					getline(ficheiro, *plafond);
					getline(ficheiro, *tamGrupo);
					carregaAluno(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
				}
				else {
					getline(ficheiro, *GrupoDep);
					getline(ficheiro, *numAlunoFunc);
					getline(ficheiro, *dura��o);
					getline(ficheiro, *plafond);
					getline(ficheiro, *tamGrupo);
					carregaStaff(*PriNome, *UltNome, *GrupoDep, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
				}
				acabados[j] = p;
			}
			else {
				acabados[j] = NULL;
			}
			delete PriNome, UltNome, GrupoDep, numAlunoFunc, dura��o, plafond, tamGrupo, AlunoouNao, Curso;
		}
	}
	ficheiro.close();
}

void carregaRemovidos(pessoa ** removidos, int tam, int*reserva, int tamReserva) {//vai carregar as pessoas que foram removidas porque n�o tinham plafond suficiente do ficheiro
	fstream ficheiro("Pessoas removidas.txt", ios::in);
	if (ficheiro.is_open()) {
		for (int j = 0; j < tam; j++) {
			pessoa*p = new pessoa;
			string *PriNome = new string;
			string *UltNome = new string;
			string *AlunoouNao = new string;
			string *GrupoDep = new string;
			string *Curso = new string;
			string *numAlunoFunc = new string;
			string *dura��o = new string;
			string *plafond = new string;
			string *tamGrupo = new string;
			getline(ficheiro, *PriNome);
			if (*PriNome != "-----NULL-----") {//verifica se est� a guardar pessoas e n�o lugares vazios da fila
				getline(ficheiro, *UltNome);
				getline(ficheiro, *AlunoouNao);
				if (*AlunoouNao != "Staff") {
					getline(ficheiro, *GrupoDep);
					getline(ficheiro, *Curso);
					getline(ficheiro, *numAlunoFunc);
					getline(ficheiro, *dura��o);
					getline(ficheiro, *plafond);
					getline(ficheiro, *tamGrupo);
					carregaAluno(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
				}
				else {
					getline(ficheiro, *GrupoDep);
					getline(ficheiro, *numAlunoFunc);
					getline(ficheiro, *dura��o);
					getline(ficheiro, *plafond);
					getline(ficheiro, *tamGrupo);
					carregaStaff(*PriNome, *UltNome, *GrupoDep, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
				}
				removidos[j] = p;
			}
			else {
				removidos[j] = NULL;
			}
			delete PriNome, UltNome, GrupoDep, numAlunoFunc, dura��o, plafond, tamGrupo, AlunoouNao, Curso;
		}
	}
	ficheiro.close();
}

mesa** carregaCantina(mesa ** canteen, int numMesas, int*reserva, int tamReserva){//carrega uma cantina do ficheiro
	fstream ficheiro("Cantina.txt", ios::in); 
	delete canteen;
	mesa**cantina = new mesa*[contaCantina()];
	int i = 0;
	if (ficheiro.is_open()) {
		string testa;
		while(getline(ficheiro,testa)) {
			const char*aux = testa.c_str();
			if (i < 9) {
				if (aux[1] == '\t') {//neste caso sabe-se que est� numa linha com o n�mero da mesa e a sua capacidade
					mesa*m = new mesa;
					const char*aux1 = &aux[2];
					int cap = atoi(aux1);
					const char*aux2 = &aux[4];
					int numSenta = atoi(aux2);
					i++;
					m->numMesa = i;
					m->tamanho = cap;
					m->numSentados = numSenta;
					pessoa**sit = new pessoa*[cap];
					for (int j = 0; j < cap; j++) {
						pessoa*p = new pessoa;
						string* PriNome = new string;
						string *UltNome = new string;
						string *AlunoouNao = new string;
						string *GrupoDep = new string;
						string *Curso = new string;
						string *numAlunoFunc = new string;
						string *dura��o = new string;
						string *plafond = new string;
						string *tamGrupo = new string;
						getline(ficheiro, *PriNome);
						if (*PriNome != "-----NULL-----") {
							getline(ficheiro, *UltNome);
							getline(ficheiro, *AlunoouNao);
							if (*AlunoouNao != "Staff") {
								getline(ficheiro, *GrupoDep);
								getline(ficheiro, *Curso);
								getline(ficheiro, *numAlunoFunc);
								getline(ficheiro, *dura��o);
								getline(ficheiro, *plafond);
								getline(ficheiro, *tamGrupo);
								carregaAluno(*PriNome, *UltNome, *AlunoouNao ,*GrupoDep, *Curso, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
							}
							else{
								getline(ficheiro, *GrupoDep);
								getline(ficheiro, *numAlunoFunc);
								getline(ficheiro, *dura��o);
								getline(ficheiro,* plafond);
								getline(ficheiro, *tamGrupo);
								carregaStaff(*PriNome, *UltNome, *GrupoDep,* numAlunoFunc, *dura��o, *plafond,* tamGrupo, p, reserva,tamReserva);
							}
							sit[j] = p;
						}
						else {
							sit[j] = NULL;
						}
						delete PriNome, UltNome, GrupoDep, numAlunoFunc, dura��o, plafond, tamGrupo, AlunoouNao, Curso;
					}
					if (i == 1) {
						m->totalMesas = numMesas;
					}
					else {
						m->totalMesas = NULL;
					}
					m->sentados = sit;
					cantina[i - 1] = m;
				}
			}
			else {
				if (aux[2] == '\t') {//neste caso sabe-se que est� numa linha com o n�mero da mesa e a sua capacidade
					mesa*m = new mesa;
					const char*aux3 = &aux[3];
					int cap = atoi(aux3);
					const char*aux4 = &aux[5];
					int numSenta = atoi(aux4);
					i++;
					m->numMesa = i;
					m->tamanho = cap;
					m->numSentados = numSenta;
					pessoa**sit = new pessoa*[cap];
					for (int j = 0; j < cap; j++) {
						pessoa*p = new pessoa;
						string *PriNome = new string;
						string *UltNome = new string;
						string *AlunoouNao = new string;
						string *GrupoDep = new string;
						string *Curso = new string;
						string *numAlunoFunc = new string;
						string *dura��o = new string;
						string *plafond = new string;
						string *tamGrupo = new string;
						getline(ficheiro, *PriNome);
						if (*PriNome != "-----NULL-----") {
							getline(ficheiro, *UltNome);
							getline(ficheiro, *AlunoouNao);
							if (*AlunoouNao != "Staff") {
								getline(ficheiro, *GrupoDep);
								getline(ficheiro, *Curso);
								getline(ficheiro, *numAlunoFunc);
								getline(ficheiro, *dura��o);
								getline(ficheiro, *plafond);
								getline(ficheiro, *tamGrupo);
								carregaAluno(*PriNome, *UltNome, *AlunoouNao, *GrupoDep, *Curso, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
							}
							else {
								getline(ficheiro, *GrupoDep);
								getline(ficheiro, *numAlunoFunc);
								getline(ficheiro, *dura��o);
								getline(ficheiro, *plafond);
								getline(ficheiro, *tamGrupo);
								carregaStaff(*PriNome, *UltNome, *GrupoDep, *numAlunoFunc, *dura��o, *plafond, *tamGrupo, p, reserva, tamReserva);
							}
							sit[j] = p;
						}
						else {
							sit[j] = NULL;
						}
						delete PriNome, UltNome, GrupoDep, numAlunoFunc, dura��o, plafond, tamGrupo, AlunoouNao, Curso;
					}
					m->totalMesas = NULL;
					m->sentados = sit;
					cantina[i - 1] = m;
				}
			}
		}
	}
	ficheiro.close();
	return cantina;
}

void carregaRefei��o(refei��o * r){//carrega uma refei��o do ficheiro
	fstream ficheiro("Refei��o da cantina.txt", ios::in);
	if (ficheiro.is_open()) {
		string *discarda=new string;
		getline(ficheiro, *discarda);
		string *entrada=new string;
		getline(ficheiro, *entrada);
		r->entrada = *entrada;
		string *pratoPrincipal= new string;
		getline(ficheiro, *pratoPrincipal);
		r->pratoMain = *pratoPrincipal;
		string *aux= new string;
		getline(ficheiro, *aux, '�');
		const char*aux2 = (*aux).c_str();
		float custo = atof(aux2);
		r->custo = custo;
		delete discarda, entrada, pratoPrincipal, aux;
	}
}

int contaCantina() {//conta o n�mero de mesas na cantina guardada no ficheiro
	fstream ficheiro("Cantina.txt", ios::in);
	int numMesas = 0;
	if (ficheiro.is_open()) {
		string aux;
		while (getline(ficheiro, aux)) {			
			const char*aux2 = aux.c_str();
			if (aux2[1]=='\t' || aux2[2]=='\t') {
				numMesas++;
			}
		}
	}
	ficheiro.close();
	return numMesas;
}

void adicionaReservaNum(int*reserva, int num, int tam) {//adiciona um n�mero � reserva
	for (int p = 0; p < tam; p++) {
		if (num == reserva[p]) {
			break;
		}
		else if (reserva[p] == NULL) {
			reserva[p] = num;
			p = tam;
		}
	}
}