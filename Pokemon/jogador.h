//bibliotecas
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>

using namespace std;

class Jogador {
	friend class Pokemon;
	friend class mochila;
	
	public:
		Mochila m;
		vector<Pokemon> pks;
		char nome[20];
		int pk_act;

		void setposicao(int PMX,int PMY,int x, int y);
		void getposicao(int *PMX,int *PMY,int *x, int *y);
		int posicaoMx;
		int posicaoMy;
		int posicaox;
		int posicaoy;
		Jogador(int PMX,int PMY,int x, int y,int e,char* nj);
		Jogador();
		void addPokemon(Pokemon pkm) ;
		void addPokemon(int pk);
		void updatePokemon(Pokemon PkEsc);
		void trocaPokemon(int pk);
		void gravarFich(FILE*f);
		void carregarFich(FILE*f);
		void gravar(int slot);	
		void carregar(int slot);
	};
	



