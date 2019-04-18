#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include<iostream>
#include<locale>
#include<string>
#include<fstream>
using namespace std;

int main() {
	locale::global(locale(""));
	srand(time(NULL));
	pessoa ** fila=new pessoa*[50];
	short *CAPGRUPO = new short(rand() % 10 + 1);
	string *PNOMES = new string[numLinhas("primeiro_nome.txt")];
	guardaFicheiros(PNOMES, "primeiro_nome.txt");
	string *UNOMES = new string[numLinhas("ultimo_nome.txt")];
	guardaFicheiros(UNOMES, "ultimo_nome.txt");
	string *CURSOS = new string[numLinhas("cursos.txt")];
	guardaFicheiros(CURSOS, "cursos.txt");
	short*k = new short(49);
	mesa **c = criaCantina();/*
	preencheMesa(c[0], fila, k);
	cout << endl;
	preencheMesa(c[1], fila, k);
	cout << endl;
	escreveMesa(c[0]);
	cout << endl;
	escreveMesa(c[1]);
	cout << endl;*/
	//escreveFila(fila, 50);
	refeição *r = new refeição;
	r = novaMeal();
	//removePessoa(fila, r);
	bool sair = false;
	criaFila(fila, 50);
	preencheFila(fila, PNOMES, UNOMES, CURSOS);
	preencheCantina(c, fila);
	while (!sair) {
		char opcao;
		cout << "\t\t\t\t\t Cantina EDA\n";
		cout << "\nEscolha uma opcao:\n";
		cout << " (s) Seguinte \n";
		cout << " (e) Emergência \n";
		cout << " (g) Gravar \n";
		cout << " (c) Carregar dados \n";
		cout << " (o) Opções \n";
		cin >> opcao;
		switch (opcao) {
		case 's':
			system("CLS");
			cout << "\t\t\t\t\t Cantina EDA\n";
			cout << endl;
			escreveCantina(c);
			escreveFila(fila, 50);
			//retiraPlafond(c, r); //não  tá assumindo os que acabam como NULL
			//removeDuração(c);
			//removeAcabados(c); tá implementado no retiraPlafond
			//linha para fazer a subtraçao do ciclo do tempo de cada refeicao na cantina
			break;
	
		case 'e':
			int opcao1;//opcao dentro da emergencia para escolher entre grupo ou aluno a abandonar
			cout << " Escolheu Emergência \n";
			cout << " Escolha a opção:\n1 - Remover Aluno/Funcionário\n2 - Remover Grupo/departamento \n";
			cin >> opcao1;
			switch (opcao1) {
			case (1):
				retiraEmerg(c);
				/*removePessoa(fila, r);falta o cin do numero de ident da pessoa
				linha para cobrar a refeicao da pessoa
				linha para remover a pessoa da cantina
				linha para inserir novos indivíduos na cantina para preencher*/
				break;
			case (2):
				retiraGrupo(c);
				//cout << " Insira o número de identificação do grupo \n";
				/*falta o cin do numero de ident do grpo
				linha para cobrar refeicao
				linha para reover grpo da cantina
				linha para inserir novo grupo na cantina para preencher*/
				break;
			}
			break;
			/*
		case 'g':
			cout << " Escolheu Gravar \n";
			escreveFicheiro;
			break;
		case 'c':
			cout << " Escolheu Carregar Dados \n";
			break;*/
		case 'o':
			int opcao2 = 0;
			cout << " Escolheu Opções \n";
			cout << " Escolha a opção: \n1 - Mostrar todos os indivíduos do sistema\n2 - Mostrar todas as mesas\n3 - Mostrar todos os indivíduos rejeitados por falta de plafond\n4 - Alterar o plafond do indivíduo enquanto este está na fila\n5 - Apresentação dos indivíduos de um determinado departamento\n6 - Editar a duração da refeição de um grupo/departamento\n7 - Pesquisa de indivíduos com base no seu id\n8 - Editar nome de um indivíduo\n ";
			cin >> opcao2;
			switch (opcao2) {
			case 1:
				//mostrar todos os individuos do sistema
				break;
			case 2:
				//mostrar todas as mesas
				break;
			case 3:
				//mostrar todos os individos rejeitados por falta de plafond
				break;
			case 4:
				alterarPlafond(fila);//alterar o plafond do individuo em espera na fila
				break;
			case 5:
				//apresentaçao dos individuos de determinado curso
				break;
			case 6:
				//editar a duração de uma refeição de um grupo/departamento
				break;
			case 7:
				//pesquisa com base no numero de aluno
				break;
			case 8:
				//editar o nome de um individuo
				break;
			}
		
		}
	}
	
	system("pause");
	return 0;
}