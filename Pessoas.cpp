#include"Mesas.h"
#include"Pessoas.h"
#include<iostream>
#include<string>
#include<fstream>
#include "Ficheiros.h"
using namespace std;


void opcoes() {

	char opcao;
	bool sair = false;

	while (!sair) {
		cout << "\nEscolha uma opcao:\n";
		cout << " (s) Seguinte \n";
		cout << " (e) Emerg�ncia \n";
		cout << " (g) Gravar \n";
		cout << " (c) Carregar dados \n";
		cout << " (o) Op��es \n";
		cin >> opcao;
		cout << endl;
		switch (opcao) {
		case ('s'):
			cout << " Escolheu Seguinte \n";
			/*linha para fazer a subtra�ao do ciclo do tempo de cada refeicao na cantina*/
			break;

		case ('e'):
			char opcao1;/*opcao dentro da emergencia para escolher entre grupo ou aluno a abandonar*/
			cout << " Escolheu Emerg�ncia \n";
			cout << " Escolha a op��o:\n1 - Remover Aluno/Funcion�rio\n2 - Remover Grupo/departamento \n";
			cin >> opcao1;

			switch (opcao1) {
			case 1:
				cout << " Insira o n�mero de identifica��o do aluno/funcion�rio \n";
				/*falta o cin do numero de ident da pessoa*/
				/*linha para cobrar a refeicao da pessoa*/
				/*linha para remover a pessoa da cantina*/
				/*linha para inserir novos indiv�duos na cantina para preencher*/
				break;

			case 2:
			
				cout << " Insira o n�mero de identifica��o do grupo \n";
				/*falta o cin do numero de ident do grpo*/
				/*linha para cobrar refeicao*/
				/*linha para reover grpo da cantina*/
				/*linha para inserir novo grupo na cantina para preencher*/
				break;
			}

		case ('g'):
			cout << " Escolheu Gravar \n";
			escreveFicheiro;
			break;

		case ('c'):
			cout << " Escolheu Carregar Dados \n";
			break;

		case ('o'):
			int opcao2 = 0;
			cout << " Escolheu Op��es \n";
			cout << " Escolha a op��o: \n1 - Mostrar todos os indiv�duos do sistema\n2 - Mostrar todas as mesas\n3 - Mostrar todos os indiv�duos rejeitados por falta de plafond\n4 - Alterar o plafond do indiv�duo enquanto este est� na fila\n5 - Apresenta��o dos indiv�duos de um determinado departamento\n6 - Editar a dura��o da refei��o de um grupo/departamento\n7 - Pesquisa de indiv�duos com base no seu id\n8 - Editar nome de um indiv�duo\n ";
			cin >> opcao2;

			switch (opcao2) {
			case 1:
				/*mostrar todos os individuos do sistema*/
				break;

			case 2:
				/*mostrar todas as mesas*/
				break;

			case 3:
				/*mostrar todos os individos rejeitados por falta de plafond*/
				break;

			case 4:
				/*alterar o plafond do individuo em espera na fila*/
				break;

			case 5:
				/*apresenta�ao dos individuos de determinado curso*/
				break;

			case 6:
				/*editar a dura��o de uma refei��o de um grupo/departamento*/
				break;

			case 7:
				/*pesquisa com base no numero de aluno*/
				break;

			case 8:
				/*editar o nome de um individuo*/
				break;

			}




















		}

	}
}	