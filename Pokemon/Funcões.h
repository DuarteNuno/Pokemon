#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <unistd.h>

#define mundox 3
#define mundoy 3
#define mapax 80
#define mapay 30

char MapaDoMundo[mundox][mundoy][mapax][mapay];

using namespace std;

//Menu inicial..........................................
void Menu()
{
	char c;
	int a;
	ifstream Menu("Menu.txt");
	if(!Menu)
	{
		cerr << "Erro a abrir ficheiro" << endl;
	}
	else
	{
		while((c=Menu.get())!=EOF)
		{
			cout << c;
		}
	}
	cout<<endl<<endl<<endl;
	cin>>a;
}

void Logo()
{
	char c;
	int i;
	ifstream origem("Logo.txt");
	if(!origem)
	{
		cerr << "Erro a abrir ficheiro" << endl;
	}
	else
	{
		while((c=origem.get())!=EOF)
		{
			cout << c;
		}
	}
	cout<<endl<<endl<<endl<<endl<<"                               LOADING";
	sleep(1);
	for(i=0;i<3;i++)
	{
		cout<<".";
		sleep(1);
	}
	system("cls");
}
//Abrir fichiro.......................................

void abrir_ficheiro(char M7[30][80])
{
	int j,i;
	ifstream origem;
	origem.open("Mapa 7.txt");
	if(!origem)
	{
		cerr<<"Erro a abir ficheiro"<<endl;
	}
	else
	{
		//Guardar em matriz...
		for(i=0;i<30;i++)
		{
			for(j=0;j<80;j++)
			{
				M7[i][j]=origem.get();
			}
		}
	}
}

void pintar(int Mx,int My)
{
	int i,j;
	char c;
	for(j=0;j<30;j++)
		{
			for(x=0;x<80;x++)
			{
				c=MapaDoMundo[Mx][My][x][j];
				if(c=='1')
				{
					
					c=219;
				}
				else if(c=='2')
				{
					c=178;
				}
				else if(c=='3')
				{
					c=177;
				}
				else if(c=='6')
				{
					c=176;
				}
				else if(c=='7')
				{
					c=64;
				}
				else if(c=='9')
				{
					c='O';
				}
				cout << c;
			}
		}		
	}
	
void movimento(char M7[30][80])
{
	char M[30][80],x;
	int i,j;
	//Criar 2 matriz iguais 
	for(i=0;i<30;i++)
	{
		for(j=0;j<80;j++)
		{
			M[i][j]=M7[i][j];
		}
	}
	//Movimento
	int l=0,c=51,s,k;
	char jogada;
	for(s=0;s<5000;s++)//loop
	{
		cout<<endl<<endl;
		cin>>x;
		if(x=='d' || x=='D')
		{
			//Nao passar pelas paredes
			if(M7[l][c+1]=='6')
			{
				
			}
			else
			{
				M7[l][c+1]=M7[l][c];
				c=c+1;
				M7[l][c-1]=M[l][c-1];
			}
			
		
		}
		else if(x=='a' || x=='A')
		{
			if(M7[l][c-1]=='6')
			{
				
			}
			else
			{
				M7[l][c-1]=M7[l][c];
				c=c-1;
				M7[l][c+1]=M[l][c+1];
			}
			
			
		}
		else if(x=='w' || x=='W')
		{
			if(M7[l-1][c-1]=='6')
			{
				
			}
			else
			{
				M7[l-1][c-1]=M7[l][c];
				l=l-1;
				c=c-1;
				M7[l+1][c+1]=M[l+1][c+1];
			}
			
		}
		else if(x=='s' || x=='S')
		{
			if(M7[l+1][c+1]=='6')
			{
				
			}
			else
			{
				M7[l+1][c+1]=M7[l][c];
				l=l+1;
				c=c+1;
				M7[l-1][c-1]=M[l-1][c-1];
			}
			
		}
		//Colocar posição inicial no valor 'real'
		if(s==0)
		{
			M7[0][51]='1';
		}
		system("cls");
		pintar(M7);
		
	}	
}
//NOVO........................................................................................

FILE *abreficheiro(char *nome,char *mode){
	FILE *f=fopen (nome,mode);
	if (f==NULL)
		exit ( 0 );
	return (f);
}

void PreencheMatriz(FILE* f, int PMX , int PMY){
    int y, x;
    char linha[100];
	for(y = 0 ; y < mapay ; y++){
		fgets(linha,100,f); 
		for(x = 0 ; x < mapax ; x++){
			MapaDoMundo[PMX][PMY][x][y] = linha[x];
		}
	}
}

void showMapaAtivo(int Mx,int My){	
	cout<<"\n\n";
	for(int y=0;y<mapay;y++){
		for(int x=0;x<mapax;x++){
			cout<<MapaDoMundo[Mx][My][x][y];
		}
	cout<<"\n";
	}
}
