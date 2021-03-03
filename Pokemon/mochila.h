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


class Mochila{
	public:
		
		int getmoedas();
		int getimpulso_atk();
		int getimpulso_vida();
		int getimpulso_nivel();
		int getkraxas(int PMX,int PMY);
		Mochila();
		void gravarFich(FILE*f);
		void carregarFich(FILE*f);
		
		void setmoedas(int m);
		void addmoeda();
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





