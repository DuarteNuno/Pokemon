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

class Pokemon{
	public:
		int numero;
		int tipo;
		char nome[20];
		Pokemon(int p);
		Pokemon();
		
		int getvida();
		int getnivel();
		int getxp();
		int getataque_basico();
		int getataque_alternativo1();
		int getataque_alternativo2();
		int getataque_especial();
		int getenergia();
		void setvida();
		void setvida(int a);
		void setnivel(int n);
		void setxp(int x);
		void setataque_basico(int t);
		void setataque_alternativo1(int t );
		void setataque_alternativo2(int t);
		void setataque_especial(int t);
		void setenergia();
		void gravarFich(FILE*f);
	
	private:
		int vida;
		int nivel;
		int xp;
		int ataque_basico;
		int ataque_alternativo1;
		int ataque_alternativo2;
		int ataque_especial;
		int energia;
		
};


class Mochila{
	public:
		
		int getmoedas();
		int getimpulso_atk();
		int getimpulso_vida();
		int getimpulso_nivel();
		int getkraxas(int PMX,int PMY);
		Mochila();
		void gravarFich(FILE*f);
		
		void setmoedas(int m);
		void setimpulso_nivel(int in);
		void setimpulso_atk(int a);
		void setimpulso_vida(int v);
		void setkraxa(int PMX , int PMY,int v);
		int kraxa[3][3];//um para cada mapa

		
				
	private:
		int Kraxa[3][3];
		int moedas;
		int impulso_atk;
		int impulso_vida;
		int impulso_nivel;
		
};


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
		void addPokemon(int pk);
		void trocaPokemon(int pk);
		void gravarFich(FILE*f);
		void gravar(int slot);	
		void carregar(int slot);
	};
	



