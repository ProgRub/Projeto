#pragma once
#include <string>
using namespace std;

void guardaFicheiros(string* Lista, string nome);
short numLinhas(string nome_ficheiro);
void escreveFicheiro(string *output,short tamanho, bool primeiraVez);
short* copiaVetor(short* aux, short tamanho);