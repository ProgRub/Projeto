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
	pessoa ** fila = new pessoa*[50];
	pessoa**removidos = new pessoa*[100];
	pessoa**acabados = new pessoa*[100];
	int*reserva = new int[400];
	int opcao1 = 0;
	int opcao2 = 0;
	string *PNOMES = new string[numLinhas("primeiro_nome.txt")];
	guardaFicheiros(PNOMES, "primeiro_nome.txt");
	string *UNOMES = new string[numLinhas("ultimo_nome.txt")];
	guardaFicheiros(UNOMES, "ultimo_nome.txt");
	string *CURSOS = new string[numLinhas("cursos.txt")];
	guardaFicheiros(CURSOS, "cursos.txt");
	int*pos = new int(0);
	int tamCantina;
	int contaCiclo = 0;
	criaFila(fila, 50);
	criaFila(removidos, 100);
	criaFila(acabados, 100);
	criaVetor(reserva, 400);
	mesa **cantina = criaCantina();
	bool sair = false;
	criaFila(fila, 50);
	cout << "\t\t\t\t\t Cantina EDA" << endl;
	refeição*r = novaMeal(true);
	preencheFila(fila, PNOMES, UNOMES, CURSOS, pos, reserva, 400);
	while (!sair) {
		system("CLS");
		char opcao;
		cout << "\t\t\t\t\t Cantina EDA" << endl;
		cout << "Escolha uma opcao:" << endl;
		cout << "(s) Seguinte\t";
		cout << "(e) Emergência\t";
		cout << "(g) Gravar dados\t";
		cout << "(c) Carregar dados\t";
		cout << "(o) Opções" << endl << endl;
		cout << "**** Comando: ";
		cin >> opcao;
		switch (opcao) {
		case 's':
			cout << endl;
			contaCiclo++;
			//escreveCantina(cantina);
			//escreveFila(fila, 50);
			removeDuração(cantina);
			removeAcabados(cantina, acabados, 100, r);
			preencheCantina(cantina, fila, pos, r,removidos,100);
			preencheFila(fila, PNOMES, UNOMES, CURSOS, pos, reserva, 400);
			escreveMeal(r);
			escreveCantina(cantina);
			escreveFila(fila, 50);
			if (contaCiclo % 10 == 0) {
				r = novaMeal(false);
			}
			system("pause");
			break;

		case 'e'://opcao dentro da emergencia para escolher entre grupo ou aluno a abandonar
			cout << "***** EMERGÊNCIA *****" << endl;
			cout << "Escolha a opção:" << endl << "1 - Remover Aluno/Funcionário" << endl <<"2 - Remover Grupo/departamento" << endl;
			cout << "**** Comando: ";
			cin >> opcao1;
			switch (opcao1) {
			case (1):
				escreveCantina(cantina);
				retiraEmergPessoa(cantina, acabados, 100, r);
				preencheCantina(cantina, fila, pos, r, removidos, 100);
				(*pos)--;
				break;
			case (2):
				escreveCantina(cantina);
				retiraEmergGrupo(cantina, acabados, 100, r);
				preencheCantina(cantina, fila, pos, r, removidos, 100);
				(*pos)--;
				break;
			}
			system("pause");
			break;
		case 'g':
			cout << "Escolheu Gravar Dados" << endl;
			gravaRefeição(r);
			gravaCantina(cantina);
			gravaFila(fila, 50);
			gravaAcabados(acabados, 100);
			gravaRemovidos(removidos, 100);
			cout << "Gravado com sucesso!" << endl;
			system("pause");
			break;
		case 'c':
			criaVetor(reserva, 400);
			criaFila(fila, 50);
			criaFila(acabados, 100);
			criaFila(removidos, 100);
			carregaRefeição(r);
			cantina = carregaCantina(cantina, contaCantina(), reserva,400);
			carregaFila(fila, 50, pos, reserva, 400);
			carregaAcabados(acabados, 100, reserva, 400);
			carregaRemovidos(removidos, 100, reserva, 400);
			escreveMeal(r);
			escreveCantina(cantina);
			escreveFila(fila, 50);
			contaCiclo = 0;
			system("pause");
			break;
		case 'o':
			cout << endl<< " Escolha a opção:" << endl;
			cout << "1 - Mostrar todos os indivíduos do sistema ordenados alfabeticamente pelo último nome" << endl;
			//cout << "2 - Mostrar todas as mesas ordenadas pelo número de pessoas sentadas" << endl;
			cout << "3 - Mostrar todos os indivíduos rejeitados por falta de plafond ordenados alfabeticamente pelo primeiro nome" << endl;
			cout << "4 - Alterar o plafond do indivíduo enquanto este está na fila" << endl;
			//cout << "5 - Apresentação dos indivíduos de um determinado curso / departamento" << endl;
			cout << "6 - Editar a duração da refeição de um grupo / departamento" << endl;
			//cout << "7 - Pesquisa de indivíduos com base no seu número de funcionário / aluno" << endl;
			cout << "8 - Editar nome de um indivíduo" << endl << endl;
			cout << "**** Comando: ";
			cin >> opcao2;
			switch (opcao2) {
			case (1):
				ordenaAlfabeticamenteUltNome(cantina, fila, acabados, contaPessoasCantina(cantina), contaPessoasFila(fila), contaAcabados(acabados));
				break;
			case (2):
				break;
			case (3):
				ordenaAlfabeticamentePriNome(removidos, contaRemovidos(removidos));
				break;
			case (4):
				escreveFila(fila, 50);
				alterarPlafond(fila);
				break;
			case (5):
				//apresentaçao dos individuos de determinado curso
				break;
			case (6):
				escreveCantina(cantina);
				escreveFila(fila, 50);
				editaDuração(cantina, fila, 50);
				//editar a duração de uma refeição de um grupo/departamento
				break;
			case (7):
				//pesquisa com base no numero de aluno
				break;
			case (8):
				escreveCantina(cantina);
				escreveFila(fila, 50);
				mudaNome(cantina, fila, 50);
				break;
			}
			system("pause");
			break;
		default:
			cout << "Carater não válido" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}