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
	int contaCiclo = 0;
	criaFila(fila, 50);
	criaFila(removidos, 100);
	criaFila(acabados, 100);
	criaVetor(reserva, 400);
	mesa **cantina = criaCantina();
	bool sair = false;
	criaFila(fila, 50);
	preencheFila(fila, PNOMES, UNOMES, CURSOS, pos, reserva, 400);
	refeição*r = novaMeal(true);
	while (!sair) {
		system("CLS");
		char opcao;
		cout << "\t\t\t\t\t Cantina EDA\n";
		cout << "Escolha uma opcao:\n";
		cout << "(s) Seguinte\t";
		cout << "(e) Emergência\t";
		cout << "(g) Gravar\t";
		cout << "(c) Carregar dados\t";
		cout << "(o) Opções\t";
		cin >> opcao;
		switch (opcao) {
		case 's':
			cout << "\t\t\t\t\t Cantina EDA\n";
			cout << endl;
			contaCiclo++;
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
			cout << " Escolheu Emergência\n";
			cout << " Escolha a opção:\n1 - Remover Aluno/Funcionário\n2 - Remover Grupo/departamento\n";
			cin >> opcao1;
			switch (opcao1) {
			case (1):
				escreveCantina(cantina);
				escreveFila(fila,50);
				retiraEmergPessoa(cantina, acabados, 100, r);
				preencheCantina(cantina, fila, pos, r, removidos, 100);
				(*pos)--;
				escreveCantina(cantina);
				break;
			case (2):
				escreveCantina(cantina);
				escreveFila(fila, 50);
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
			cout << "Gravado com sucesso!" << endl;
			system("pause");
			break;
		case 'c':
			cout << " Escolheu Carregar Dados\n";
			criaVetor(reserva, 400);
			criaFila(fila, 50);
			carregaRefeição(r);
			cantina = carregaCantina(cantina, contaCantina(), reserva,400);
			carregaFila(fila, 50, pos, reserva, 400);
			escreveMeal(r);
			escreveCantina(cantina);
			escreveFila(fila, 50);
			contaCiclo = 0;
			system("pause");
			break;
		case 'o':
			cout << " Escolheu Opções \n";
			cout << " Escolha a opção:\n1 - Mostrar todos os indivíduos do sistema\n2 - Mostrar todas as mesas\n3 - Mostrar todos os indivíduos rejeitados por falta de plafond\n4 - Alterar o plafond do indivíduo enquanto este está na fila\n5 - Apresentação dos indivíduos de um determinado departamento\n6 - Editar a duração da refeição de um grupo/departamento\n7 - Pesquisa de indivíduos com base no seu id\n8 - Editar nome de um indivíduo\n";
			cin >> opcao2;
			switch (opcao2) {
			case (1):
				ordenaAlfabeticamenteUltNome(cantina, fila, acabados, contaPessoasCantina(cantina), contaPessoasFila(fila), contaAcabados(acabados));
				//mostrar todos os individuos do sistema ordenados alfabeticamente pelo último nome
				break;
			case (2):
				//mostrar todas as mesas
				break;
			case (3):
				//mostrar todos os individos rejeitados por falta de plafond
				break;
			case (4):
				escreveFila(fila, 50);
				alterarPlafond(fila);//alterar o plafond do individuo em espera na fila
				break;
			case (5):
				//apresentaçao dos individuos de determinado curso
				break;
			case (6):
				//editar a duração de uma refeição de um grupo/departamento
				break;
			case (7):
				//pesquisa com base no numero de aluno
				break;
			case (8):
				//editar o nome de um individuo
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