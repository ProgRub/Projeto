//
// Created by Filipe Quintal on 2019-03-11.
//
#include <iostream>
#include "LL.h"
using namespace std;

int comprimento(ListaLigada* ll){
	ListaLigada::node*itera= new ListaLigada::node();
	int conta = 0;
	itera = ll->primeiro;
	while (itera != NULL)//enquanto não chegar ao fim da LL
	{
		conta++;
		itera = itera->seguinte; //vai para o nodo seguinte
	}
	return conta;
}

ListaLigada* novaLista(){
	ListaLigada*ll = new ListaLigada;
	ll->primeiro = NULL;
	ll->último = ll->primeiro;
	return ll;
}

bool listaVazia(ListaLigada*ll) {
	if (ll->primeiro != NULL) {
		return false;
	}
	return true;
}

void inserirInicio(ListaLigada* ll, int valor) {
	ListaLigada::node *newNode=new ListaLigada::node();
	newNode->valor = valor;
	if (!listaVazia(ll)) {
		newNode->seguinte = ll->primeiro;
		ll->primeiro = newNode;
		return;
	}
	newNode->seguinte = NULL;
	ll->primeiro = newNode;
	ll->último = ll->primeiro;
	return;
}

void insereFim(ListaLigada* ll, int valor) {
	ListaLigada::node * itera = new ListaLigada::node();
	itera = ll->primeiro;
	while (itera->seguinte != NULL) {
		itera = itera->seguinte;
	}
	ListaLigada::node* novo = new ListaLigada::node();
	novo->valor = valor;
	novo->seguinte = NULL;
	itera->seguinte = novo;
	ll->último = novo;
}

void imprime(ListaLigada* ll) {
	ListaLigada::node* itera = new ListaLigada::node();
	itera = ll->primeiro;
	cout << " Lista " << endl;
	while (itera != NULL) {
		cout << itera->valor << ",";
		itera = itera->seguinte;
	}
}

void insereMeio(ListaLigada* ll, int dados, int pos){
	int tamanho = comprimento(ll);
	cout << "Posição " << pos << " Tamanho " << tamanho;
	if (pos == 0) {
		inserirInicio(ll, dados);
		return;
	}
	else if (pos == tamanho) {
		insereFim(ll, dados);
		return ;
	}
	else if (pos > tamanho) {
		cout << "Erro fim de lista " << pos << tamanho << endl;
		return ;
	}
	else {
		ListaLigada::node* itera = new ListaLigada::node();
		itera = ll->primeiro;
		int pos_count = 0;
		while (itera->seguinte != NULL && pos_count < pos - 1) {
			itera = itera->seguinte;
			pos_count++;
		}
		cout << "Posição a inserir " << pos_count;
		ListaLigada::node* novo = new ListaLigada::node();
		novo->valor = dados;
		novo->seguinte = itera->seguinte;
		itera->seguinte = novo;
		return ;
	}
}

void removerInicio(ListaLigada* ll) {
	ListaLigada::node* aux = new ListaLigada::node();
	aux = ll->primeiro;
	ll->primeiro = ll->primeiro->seguinte;
	delete aux;
}

void removerFim(ListaLigada* ll) {
	ListaLigada::node* itera = new ListaLigada::node();
	itera = ll->primeiro;
	while (itera->seguinte->seguinte != NULL) {
		itera = itera->seguinte;
	}
	ListaLigada::node* aux = new ListaLigada::node();
	ll->último = itera;
	aux = itera->seguinte;
	itera->seguinte = NULL;
	delete aux;
}

void removerPos(ListaLigada* ll, int pos) {
	int tamanho = comprimento(ll);
	if (pos == 0) {
		 removerInicio(ll);
	}
	else if (pos == tamanho-1) {
		removerFim(ll);
		return;
	}
	else if (pos > tamanho) {
		cout << "Erro fim de lista " << pos << tamanho << endl;
		return;
	}
	else {
		ListaLigada::node* itera = new ListaLigada::node();
		itera = ll->primeiro;
		int pos_count = 1;
		while (itera->seguinte != NULL && pos != pos_count) {
			itera = itera->seguinte;
			pos_count++;
		}
		ListaLigada::node* aux = new ListaLigada::node();
		aux = itera->seguinte;
		itera->seguinte = itera->seguinte->seguinte;
		delete aux;
		return;
	}
}