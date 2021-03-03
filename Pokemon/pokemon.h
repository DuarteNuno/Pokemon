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
		void setvida(int v);
		void ataque(int a);
		void setnivel(int n);
		void setxp(int x);
		void setataque_basico(int t);
		void setataque_alternativo1(int t );
		void setataque_alternativo2(int t);
		void setataque_especial(int t);
		void setenergia(int x);
		void newExperience();
		void gravarFich(FILE*f);
		void carregarFich(FILE*f);

	
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

