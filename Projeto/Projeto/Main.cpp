#include"Mesas.h"
#include"Pessoas.h"
#include"Ficheiros.h"
#include "Refei��o.h"
#include<iostream>
#include<locale>
#include<string>
#include<fstream>
using namespace std;

int main(int argv, char**argc) {
	locale::global(locale(""));
	srand(time(NULL));
	LLPessoas*filaEspera = new LLPessoas;
	filaEspera->primeira = NULL;
	filaEspera->ultima = NULL;
	filaEspera->iterator = NULL;
	LLPessoas*acabados = new LLPessoas;
	acabados->primeira = NULL;
	acabados->ultima = NULL;
	acabados->iterator = NULL;
	n�Removidos*arvoreRemovidos = new n�Removidos;
	arvoreRemovidos = NULL;
	LLMesas*cantina = new LLMesas;
	cantina->primeira = NULL;
	cantina->ultima = NULL;
	cantina->iterator = NULL;
	LLRefei��es*refei��es = new LLRefei��es;
	refei��es->primeira = NULL;
	refei��es->atual = NULL;
	LLReserva*reserva = new LLReserva;
	reserva->primeiro = NULL;
	reserva->ultimo = NULL;
	int opcao1;
	int opcao2;
	int opcao3;
	int opcaoExtra;
	int *premio = new int(rand() % 301 + 200);
	bool restartaOpcao1de9 = true;
	bool *h�Vencedor = new bool(true);
	int *aumenta = new int(0);
	string *PNOMES = new string[numLinhas("primeiro_nome.txt")];
	guardaFicheiros(PNOMES, "primeiro_nome.txt");
	string *UNOMES = new string[numLinhas("ultimo_nome.txt")];
	guardaFicheiros(UNOMES, "ultimo_nome.txt");
	string *CURSOS = new string[numLinhas("cursos.txt")];
	guardaFicheiros(CURSOS, "cursos.txt");
	int contaCiclo = 0;
	if (argv == 6) {
		int *pos = new int(1);
		carregaRefei��es(refei��es, argc[(*pos)++]);
		carregaCantina(cantina, contaCantina(argc[(*pos)]), reserva, argc[(*pos)++]);
		carregaLLPessoas(filaEspera, reserva, argc[(*pos)++]);
		carregaLLPessoas(acabados, reserva, argc[(*pos)++]);
		arvoreRemovidos = carregaRemovidos(arvoreRemovidos, reserva, argc[(*pos)++]);
	}
	else {
		criaCantina(cantina);
		novaMeal(refei��es);
		preencheFila(filaEspera, PNOMES, UNOMES, CURSOS, reserva, true);
	}
	bool sair = false;
	while (!sair) {
		system("CLS");
		char opcao;
		cout << "\t\t\t\t\t Cantina EDA" << endl;
		cout << "Escolha uma opcao:" << endl;
		cout << "(s) Seguinte\t";
		cout << "(e) Emerg�ncia\t";
		cout << "(g) Gravar dados\t";
		cout << "(c) Carregar dados\t";
		cout << "(o) Op��es" << endl << endl;
		cout << "**** Comando: ";
		cin >> opcao;
		cin.ignore(1000, '\n');
		switch (opcao) {
		case 's':
			cout << endl;
			contaCiclo++;
			escreveMeal(refei��es);
			escreveCantina(cantina);
			escreveFila(filaEspera);
			removeDura��o(cantina);
			removeAcabados(cantina, acabados, refei��es);
			arvoreRemovidos = removeSemDinheiro(filaEspera, refei��es, arvoreRemovidos);
			preencheCantina(cantina, filaEspera, refei��es);
			preencheFila(filaEspera, PNOMES, UNOMES, CURSOS, reserva, false);
			if (contaCiclo % 10 == 0) {
				novaMeal(refei��es);
			}
			system("pause");
			break;
		case 'e'://opcao dentro da emergencia para escolher entre grupo ou aluno a abandonar
			cout << endl << "***** EMERG�NCIA *****" << endl;
			cout << "Escolha a op��o:" << endl << "1 - Remover Aluno/Funcion�rio" << endl << "2 - Remover Grupo/departamento" << endl;
			cout << "**** Comando: ";
			cin >> opcao1;
			cin.ignore(1000, '\n');
			switch (opcao1) {
			case 1:
				escreveCantina(cantina);
				retiraEmergPessoa(cantina, acabados, refei��es);
				preencheCantina(cantina, filaEspera, refei��es);
				break;
			case 2:
				escreveCantina(cantina);
				retiraEmergGrupo(cantina, acabados, refei��es);
				preencheCantina(cantina, filaEspera, refei��es);
				break;
			default:
				cout << "Isso n�o � uma op��o." << endl;
			}
			system("pause");
			break;
		case 'g':
			gravaRefeicoes(refei��es);
			gravaCantina(cantina);
			gravaLLPessoas(filaEspera, "Fila.txt");
			gravaLLPessoas(acabados, "Acabados.txt");
			gravaRemovidos(arvoreRemovidos);
			cout << endl << "Gravado com sucesso!" << endl;
			system("pause");
			break;
		case 'c':
			limpaReserva(reserva);
			carregaRefei��es(refei��es, "Refeicoes.txt");
			carregaCantina(cantina, contaCantina("Cantina.txt"), reserva, "Cantina.txt");
			carregaLLPessoas(filaEspera, reserva, "Fila.txt");
			carregaLLPessoas(acabados, reserva, "Acabados.txt");
			arvoreRemovidos = carregaRemovidos(arvoreRemovidos, reserva, "Removidos.txt");
			escreveCantina(cantina);
			escreveFila(filaEspera);
			contaCiclo = 0;
			system("pause");
			break;
		case 'o':
			cout << endl << " Escolha a op��o:" << endl;
			cout << "1 - Mostrar todos os indiv�duos do sistema ordenados alfabeticamente pelo �ltimo nome" << endl;
			cout << "2 - Mostrar todas as mesas ordenadas pelo n�mero de pessoas sentadas" << endl;
			cout << "3 - Mostrar todos os indiv�duos rejeitados por falta de plafond ordenados alfabeticamente pelo primeiro nome" << endl;
			cout << "4 - Alterar o plafond de um indiv�duo que esteja na fila" << endl;
			cout << "5 - Apresenta��o dos indiv�duos de um determinado curso / departamento" << endl;
			cout << "6 - Editar a dura��o da refei��o de um determinado grupo / departamento" << endl;
			cout << "7 - Pesquisa de indiv�duos com base no seu n�mero de funcion�rio / aluno" << endl;
			cout << "8 - Editar nome de um indiv�duo" << endl;
			cout << "9 - Op��es extra" << endl << endl;
			cout << "**** Comando: ";
			cin >> opcao2;
			cin.ignore(1000, '\n');
			switch (opcao2) {
			case 1:
				ordenaAlfabeticamenteUltNome(cantina, filaEspera, acabados);
				break;
			case 2:
				SelectionSortMesasNumSentados(converteLLvetorMesas(cantina), cantina->ultima->numMesa);
				break;
			case 3:
				system("CLS");
				cout << "\t\t\t\t\t Cantina EDA" << endl;
				cout << "Pessoas removidas da fila por falta de plafond ordenadas alfabeticamente pelo primeiro nome:" << endl;
				imprimeArvoreInfixa(arvoreRemovidos);
				break;
			case 4:
				escreveFila(filaEspera);
				alterarPlafond(filaEspera);
				break;
			case 5:
				escreveCantina(cantina);
				escreveFila(filaEspera);
				apresentaCursoOuDep(cantina, filaEspera, CURSOS);
				break;
			case 6:
				escreveCantina(cantina);
				escreveFila(filaEspera);
				editaDura��o(cantina, filaEspera);
				break;
			case 7:
				escreveCantina(cantina);
				escreveFila(filaEspera);
				apresentaIndividuo(cantina, filaEspera);
				break;
			case 8:
				escreveCantina(cantina);
				escreveFila(filaEspera);
				mudaNome(cantina, filaEspera);
				break;
			case 9:
				system("CLS");
				cout << "\t\t\t\t\t Cantina EDA" << endl;
				cout << "\t\t\t\t\t Op��es Extra" << endl;
				cout << "1 - Preencher fila com novas pessoas" << endl;
				cout << "2 - Retirar toda a gente da cantina" << endl;
				cout << "3 - Alterar o curso de um grupo de alunos" << endl;
				cout << "4 - Mostrar todas as refei��es que a cantina teve" << endl;
				cout << "5 - Mostrar pessoa mais rica e mais pobre, juntamente com o plafond m�dio" << endl;
				cout << "6 - Acontecimento de lotaria" << endl << endl;
				cout << "**** Comando: ";
				cin >> opcaoExtra;
				cin.ignore(1000, '\n');
				switch (opcaoExtra) {
				case 1:
					limpaLLPessoas(filaEspera);
					while (restartaOpcao1de9) {
						cout << "Quer encher a fila com 10 grupos ou s� 1?\n\t1.10 grupos;\n\t2.S� 1 grupo." << endl;
						cout << "**** Comando: ";
						cin >> opcao3;
						cin.ignore(1000, '\n');
						switch (opcao3) {
						case 1:
							preencheFila(filaEspera, PNOMES, UNOMES, CURSOS, reserva, true);
							restartaOpcao1de9 = false;
							break;
						case 2:
							preencheFila(filaEspera, PNOMES, UNOMES, CURSOS, reserva, false);
							restartaOpcao1de9 = false;
							break;
						default:
							cout << "Por favor escolha uma das op��es dispon�veis." << endl << endl;
							break;
						}
					}
					restartaOpcao1de9 = true;
					escreveFila(filaEspera);
					break;
				case 2:
					cantina->iterator = cantina->primeira;
					while (cantina->iterator != NULL) {
						limpaLLPessoas(cantina->iterator->sentados);
						cantina->iterator = cantina->iterator->seguinte;
					}
					break;
				case 3:
					escreveCantina(cantina);
					escreveFila(filaEspera);
					mudaCurso(cantina, filaEspera, CURSOS);
					break;
				case 4:
					escreveTodasRefei��es(refei��es);
					break;
				case 5:
					PobreRicoEMedia(cantina, filaEspera);
					break;
				case 6:
					lotaria(cantina, filaEspera, h�Vencedor, premio, aumenta);
					break;
				default:
					cout << "Isso n�o � uma op��o." << endl;
					break;
				}
				break;
			default:
				cout << "Isso n�o � uma op��o." << endl;
				break;
			}
			system("pause");
			break;
		default:
			cout << "Carater n�o v�lido" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}