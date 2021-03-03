//Bibliotecas

#include "pokemon.h"
#include "mochila.h"
#include "jogador.h"
#include <time.h>


//Constantes
#define mundox 3
#define mundoy 3
#define mapax 80
#define mapay 30
#define mapax0 39
#define mapay0 3

#define maty 22
#define matx 40
#define pok 7

#define mat2y 30
#define mat2x 80

#define PRE 0
#define AZU1 1
#define VER1 2
#define AZU2 3
#define MAG 4
#define ROX 5
#define VER2 6
#define CIN1 7
#define CIN2 8
#define AZU3 9
#define VER3 10
#define	AZU4 11
#define VERM 12
#define ROSA 13
#define AMA 14
#define BRA 15

#define passeio ':'
#define relva ','
#define erva '3'
#define pedra '4'
#define agua '5'
#define arvore '6'
#define gym '7'
#define loja 'l'
#define center 'c'
#define CasaInicial '9'
#define parede 'p'
#define entrada 'e'
#define jogador 207
#define Pikachu 'z'

//variaveis globais
Jogador J;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
char Pokemons[pok][maty][matx];
char Inicio[mat2y][mat2x];
char MapaDoMundo[mundox][mundoy][mapax][mapay];//xy do mondo,xy do mapa
int slots[3];

//FUNCOES
FILE *abreficheiro(const char *nome,const char *mode) {
	FILE *f=fopen (nome,mode);
	if (f==NULL)
		exit ( 0 );
	return (f);
}

//posicionar cursor
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
	    GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void sleep(int num) {
	Sleep(num);
}
//cor
void cor(HANDLE h, int fundo, int tinta) {
	SetConsoleTextAttribute(h,  16*fundo + tinta);
}
//escrever no final da consola
void mensagem(const char str[]) {
	gotoxy(39,33);
	cout<<str;
}
void mensagem(char * str, int num) {
	gotoxy(39,33);
	cout<<str<<num;
}

void limparsp() {
	cor(h,PRE,PRE);
	mensagem("                                     ");
}

//guardar para depois

int existeSlot(int slot) {
	if ((slot >= 1) && (slot <= 3))
		return slots[slot-1];
	else
		return false;
}

void MostraCarteira( const char *expr)
{
	cor(h,PRE,BRA);
	gotoxy(mapax0,mapay0+32);
	cout<<"moedas:"<<J.m.getmoedas()<<"  "<<expr<<"       Slots:";
	for (int s=1; s<=3; s++)
		cout << (existeSlot(s)==true?"S":"N");
}

int carregarSlots() {
	// devolve 0 se não encontrou, 1-3 se encontrou apenas um deles, -1 se encontrou mais do que um
	int total_enc=0, slot_enc=0;
	char nomeficheiro[10];
	for (int s=1; s<=3; s++) {
		sprintf(nomeficheiro,"PK_game_s%d.txt",s);
		FILE*f=fopen(nomeficheiro,"r");
		if (f!=NULL) {
			fclose(f);
			slots[s-1]=true;
			total_enc++;
			slot_enc=s;
		} else
		{
			slots[s-1]=false;
		}
	}
	return (total_enc <= 1?slot_enc-1:-1);
}


int procurarSlotVazia() {
	// devolve 0 se não encontrou, 1-3 se encontrou uma vazia
	int total_enc=0, slot_enc=0;

	for (int s=1; s<=3; s++) {
		if (slots[s-1]==false) {
			return(s);
		}
	}
	return (0);
}

int procurarSlotACarregar() {
	// devolve 0 se não encontrou, 1-3 se encontrou apenas uma, -1 se encontrou mais do que uma
	int total_enc=0, slot_enc=0;

	for (int s=1; s<=3; s++) {
		if (slots[s-1]==true) {
			total_enc++;
			slot_enc=s;
			return(s);
		}
	}
	if (total_enc==0)
		return 0;
	else	
		return (total_enc == 1?slot_enc-1:-1);
}

//guardar quando iniciado
void PreencheMatriz2(FILE* f) {
	int y, x;
	char linha[82];
	for(y = 0 ; y < 30 ; y++) {
		gotoxy(mapax0+x,mapay0+y);
		fgets(linha,82,f);
		for(x = 0 ; x < 80 ; x++) {
			Inicio[y][x] = linha[x];
			//cout<<linha[x];
		}
	}
}


void PreenchePokemon(FILE* f, int n) {
	int y, x;
	char linha[43];
	for(y = 0 ; y < 23 ; y++) {
		fgets(linha,43,f);
		for(x = 0 ; x < 42 ; x++) {
			Pokemons[n][y][x] = linha[x];
			//cout<<linha[x];
		}
	}
}

void PreencheMatriz(FILE* f, int PMX , int PMY) {
	int y, x;
	char linha[100];
	for(y = 0 ; y < mapay ; y++) {
		fgets(linha,90,f);
		for(x = 0 ; x < mapax ; x++) {
			MapaDoMundo[PMX][PMY][x][y] = linha[x];
		}
	}
}

//GRAFICOS
//pinta consola de vazio
void Ecravazio() {
	FILE *f=abreficheiro("vazio.txt","r");
	cor(h,PRE,BRA);
	int y, x;
	char linha[100];
	for(y = 0 ; y < mapay ; y++) {
		fgets(linha,90,f);
		for(x = 0 ; x < mapax ; x++) {
			gotoxy(mapax0+x,mapay0+y);
			cout<< linha[x];
		}
	}
	fclose(f);
}

//pinta consola
void mostraconsola() {
	char consola[160][39];
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	FILE*f=abreficheiro("Consola.txt","r");
	int y, x;
	char linha[180];
	for(y = 0 ; y < 39 ; y++) {
		fgets(linha,180,f);
		for(x = 0 ; x < 160; x++) {
			consola[x][y]= linha[x];

			if (consola[x][y]=='#') {
				consola[x][y]=219;
				cor(h,AZU2,AZU1);
			}
			if (consola[x][y]=='@') {
				consola[x][y]=219;
				cor(h,BRA,PRE);
			}
			if (consola[x][y]=='.') {
				consola[x][y]=219;
				cor(h,CIN2,CIN1);
			}
			if (consola[x][y]=='+') {
				consola[x][y]=219;
				cor(h,VER3,VER3);
			}
			if (consola[x][y]=='*') {
				consola[x][y]=219;
				cor(h,CIN1,CIN2);
			}
			if (consola[x][y]==' ') {
				cor(h,PRE,BRA);
			}
			if (consola[x][y]==',') {
				consola[x][y]=219;
				cor(h,CIN1,CIN2);
			}
			cout<<consola[x][y];
		}
	}
}

//pinta J e J anterior
void mostraJogador(int Mx, int My, int Rx_ant,int Ry_ant,int Rx, int Ry) {

	char c;
	// desenha o robot na nova posição
	gotoxy(mapax0+Rx,mapay0+Ry);
	c=jogador;
	cor(h, PRE,BRA);
	cout << c;

	// repõe a posição anterior do mapa
	gotoxy(mapax0+Rx_ant,mapay0+Ry_ant);
	c=MapaDoMundo[Mx][My][Rx_ant][Ry_ant];
	if(c==passeio) {
		c=219;
		cor(h, CIN1,CIN1 );
	} else if(c==relva) {
		c=178;
		cor(h,VER3,VER3);
	} else if(c==Pikachu) {
		c=177;
		cor(h,VER3,PRE);
	} else if(c==erva) {
		c=177;
		cor(h,  VER3, PRE);
	} else if(c==arvore) {
		c=176;
		cor(h, VER1,AZU1);
	} else if(c==gym) {
		c=64;
		cor(h,  MAG, MAG);
	} else if(c==CasaInicial) {
		c='O';
		cor(h,  ROSA,ROSA);
	} else if(c==' ') {
		cor(h,  BRA, BRA);
	} else if(c=='p') {
		cor(h,  CIN2, CIN2);
	} else if(c=='e') {
		cor(h,  BRA, PRE);
	} else if(c=='5') {
		cor(h,AZU2,AZU2);
	} else if(c=='c') {
		cor(h,AMA,AMA);
	} else if(c=='l') {
		cor(h,AMA,VERM);
		c=178;
	} else
		cor(h, PRE, BRA);

	cout << c;
	gotoxy(38,33);
}

//pinta mapa
void mostraMapaAtivo(int Mx,int My,int Rx, int Ry) {

	char c;

	for(int y=0; y<mapay; y++) {
		for(int x=0; x<mapax; x++) {
			gotoxy(mapax0+x,mapay0+y);
			if (x==Rx && y==Ry) {
				c=jogador;
				cor(h, PRE,BRA);
			} else {
				c=MapaDoMundo[Mx][My][x][y];

				if(c==passeio) {
					c=219;
					cor(h, CIN1,CIN1 );
				} else if(c==relva) {
					c=178;
					cor(h,  VER3,VER3);
				} else if(c==Pikachu) {
					c=177;
					cor(h,VER3,PRE);
				} else if(c==erva) {
					c=177;
					cor(h,  VER3, PRE);
				} else if(c==arvore) {
					c=176;
					cor(h, VER1,AZU1);
				} else if(c==gym) {
					c=64;
					cor(h,  MAG, MAG);
				} else if(c==CasaInicial) {
					c='O';
					cor(h,  ROSA,ROSA);
				} else if(c==' ') {
					cor(h,  BRA, BRA);
				} else if(c=='p') {
					cor(h,  CIN2, CIN2);
				} else if(c=='e') {
					cor(h,  BRA, PRE);
				} else if(c=='5') {
					cor(h,AZU2,AZU2);
				} else if(c=='c') {
					cor(h,AMA,AMA);
				} else if(c=='l') {
					cor(h,AMA,VERM);
					c=178;
				} else
					cor(h, PRE, BRA);
			}
			cout << c;
		}
	}
}
void mostraMapaAtivo2() {

	char c;
	for(int y=0; y<30; y++) {
		for(int x=0; x<80; x++) {
			gotoxy(mapax0+x,mapay0+y);
			c=Inicio[y][x];
			if (c=='8') {
				cor(h,PRE,PRE);
				c=219;
			} else if (c=='7') {
				cor(h,PRE,VER1);
				c=219;
			} else if (c=='6') {
				cor(h,PRE,AZU2);
				c=219;
			} else if (c=='5') {
				cor(h,PRE,VERM);
				c=219;
			} else if (c=='4') {
				cor(h,PRE,BRA);
				c=219;
			} else if (c=='3') {
				cor(h,AMA,VERM);
				c=177;
			} else if (c=='1') {
				cor(h,PRE,CIN2);
				c=219;
			} else if (c=='9') {
				cor(h,BRA,VERM);
				c=177;
			} else if (c=='2') {
				cor(h,PRE,AMA);
				c=219;
			} else if (c=='0') {
				cor(h,PRE,MAG);
				c=219;
			} else if (c=='€') {
				cor(h,PRE,AZU1);
				c=219;
			} else if (c=='&') {
				cor(h,BRA,PRE);
				c=219;
			} else {
				cor(h,PRE,BRA);
			}
			cout << c;
		}
	}
}

//Pintar Pokemons
void pintar(char c) {

	if (c=='8') {
		cor(h,PRE,PRE);
		c=219;
	} else if (c=='7') {
		cor(h,PRE,VER1);
		c=219;
	} else if (c=='6') {
		cor(h,PRE,AZU2);
		c=219;
	} else if (c=='5') {
		cor(h,PRE,VERM);
		c=219;
	} else if (c=='4') {
		cor(h,PRE,BRA);
		c=219;
	} else if (c=='3') {
		cor(h,AMA,VERM);
		c=177;
	} else if (c=='1') {
		cor(h,PRE,CIN2);
		c=219;
	} else if (c=='9') {
		cor(h,BRA,VERM);
		c=177;
	} else if (c=='2') {
		cor(h,PRE,AMA);
		c=219;
	} else if (c=='0') {
		cor(h,PRE,MAG);
		c=219;
	} else {
		cor(h,PRE,BRA);
		c=219;
	}
	cout<<c;
}

//Perguntar que pokemon quer usar
Pokemon PKUsar() {
	Ecravazio();
	char H;
	cor(h,PRE,BRA);
	gotoxy(mapax0,mapay0);
	cout<<"QUE POKEMON DESEJA UTILIZAR:";

	int linha = 1;
	vector<Pokemon>::iterator it;
	for (it = J.pks.begin(); it != J.pks.end(); it++) {
		Pokemon pkm= *it;
		gotoxy(mapax0,mapay0+linha);
		cout<<"["<<pkm.numero<<"] -> "<<pkm.nome;
		linha++;
	}

	bool fim = false;
	while (!fim) {
		gotoxy(mapax0,mapay0+30);
		H=getch();
		gotoxy(mapax0,mapay0+30);

		for (it = J.pks.begin(); it != J.pks.end(); it++) {
			Pokemon pkm= *it;

			if (pkm.numero==H-'0') {
				return pkm;
			}
		}
		mensagem(" Pokemon não encontrado. Indique novamente por favor.");
	}
}

//BATALHA........................................................................................
//Matriz batalha(2 pokemons)
void MatBat(int PK1,int PK2) {
	char c;
	int i,j,k=-1;
	for(i=0; i<23; i++) {
		for(j=0; j<80; j++) {
			gotoxy(mapax0+j,mapay0+i);
			if(j<40) {
				c=Pokemons[PK1][i][j];
				pintar(c);
			} else {
				k++;
				c=Pokemons[PK2][i][k];
				pintar(c);
			}
		}
		k=0;
	}

}

//INTRODUCAO-------------------------------------------------------------------------------------------

Jogador intro() {
	Jogador jog;
	int escolha=0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int n;
	char c=219;
	char nomepokemon[80], modo[5];
	char nome_jog[20];

	sprintf(nomepokemon,"logo.txt");
	sprintf(modo,"r");
	FILE *logo = abreficheiro(nomepokemon,"r");
	gotoxy(mapax0,mapay0);
	PreencheMatriz2(abreficheiro(nomepokemon,modo));
	fclose(logo);
	mostraMapaAtivo2();
	sleep(4000);
	sprintf(nomepokemon,"loading.txt");
	sprintf(modo,"r");
	FILE *loading = abreficheiro(nomepokemon,"r");
	PreencheMatriz2(abreficheiro(nomepokemon,modo));
	fclose(loading);
	mostraMapaAtivo2();
	gotoxy(mapax0+37,mapay0+13);
	cor(h,PRE,BRA);
	cout<<"LOADING";
	gotoxy(mapax0+35,mapay0+15);
	cor(h,PRE,CIN2);
	for (int i=0; i<11; i++) {
		cout<<c;
	}
	gotoxy(mapax0+35,mapay0+15);
	cor(h,PRE,BRA);
	for (int i=0; i<11; i++) {
		sleep(500);
		cout<<c;
	}
	gotoxy(mapax0+79,mapay0+29);

	sleep(1500);
	sprintf(nomepokemon,"loading.txt");
	sprintf(modo,"r");
	FILE *loading2 = abreficheiro(nomepokemon,"r");
	PreencheMatriz2(abreficheiro(nomepokemon,modo));
	fclose(loading2);
	mostraMapaAtivo2();
	gotoxy(mapax0+1,mapay0+1);
	cor(h,PRE,BRA);
	cout<<"ESCOLHA A OPCAO:";
	gotoxy(mapax0+1,mapay0+3);
	cout<<"1 - NOVO JOGO";
	gotoxy(mapax0+1,mapay0+5);
	cout<<"2 - CARREGAR JOGO";
	gotoxy(mapax0+1,mapay0+7);
	char opcaoinicio;
	opcaoinicio = getch();
	if(opcaoinicio==49) {
		//NOVO JOGO
		sprintf(nomepokemon,"profoak.txt");
		sprintf(modo,"r");
		FILE *profoak = abreficheiro(nomepokemon,"r");
		PreencheMatriz2(abreficheiro(nomepokemon,modo));
		fclose(profoak);
		mostraMapaAtivo2();
		cor(h,BRA,PRE);
		gotoxy(mapax0+47,mapay0+12);
		sleep(1500);
		cout <<"OLA! SE BEM VINDO AO MUNDO";
		gotoxy(mapax0+47,mapay0+13);
		sleep(1500);
		cout <<"DOS POKEMONS! O MEU NOME E";
		gotoxy(mapax0+47,mapay0+14);
		sleep(1500);
		cout <<"OAK. AS PESSOAS CHAMAM-ME ";
		gotoxy(mapax0+47,mapay0+15);
		sleep(1500);
		cout <<"DE PROFESSOR POKEMON!     ";
		gotoxy(mapax0+47,mapay0+16);
		sleep(1500);
		cout <<"ESTE MUNDO E HABITADO POR ";
		gotoxy(mapax0+47,mapay0+17);
		sleep(1500);
		cout <<"SERES CHAMADOS POKEMONS!  ";
		gotoxy(mapax0+47,mapay0+18);
		sleep(1500);
		cout <<"PARA ALGUMAS PESSOAS, ELES";
		gotoxy(mapax0+0,mapay0+30);
		sleep(2000);
		gotoxy(mapax0+47,mapay0+12);
		cout <<"                          ";
		gotoxy(mapax0+47,mapay0+13);
		cout <<"                          ";
		gotoxy(mapax0+47,mapay0+14);
		cout <<"                          ";
		gotoxy(mapax0+47,mapay0+15);
		cout <<"                          ";
		gotoxy(mapax0+47,mapay0+16);
		cout <<"                          ";
		gotoxy(mapax0+47,mapay0+17);
		cout <<"                          ";
		gotoxy(mapax0+47,mapay0+18);
		cout <<"                          ";
		gotoxy(mapax0+0,mapay0+30);
		gotoxy(mapax0+47,mapay0+12);
		sleep(1500);
		cout <<"SAO APENAS PARA ESTIMACAO.";
		gotoxy(mapax0+47,mapay0+13);
		sleep(1500);
		cout <<"OUTROS USAM OS POKEMONS   ";
		gotoxy(mapax0+47,mapay0+14);
		sleep(1500);
		cout <<"PARA BATALHAS. JA EU...   ";
		gotoxy(mapax0+47,mapay0+15);
		sleep(1500);
		cout <<"EU ESTUDO ESTAS CRIATURAS!";
		gotoxy(mapax0+47,mapay0+16);
		sleep(1500);
		cout <<"QUE FALTA DE MODOS QUE EU ";
		gotoxy(mapax0+47,mapay0+17);
		sleep(1500);
		cout <<"TENHO...  COMO TE CHAMAS? ";
		gotoxy(mapax0+0,mapay0+30);
		sleep(2000);
		sprintf(nomepokemon,"loading.txt");
		sprintf(modo,"r");
		FILE *loading3 = abreficheiro(nomepokemon,"r");
		PreencheMatriz2(abreficheiro(nomepokemon,modo));
		fclose(loading3);
		mostraMapaAtivo2();

		gotoxy(mapax0+1,mapay0+1);
		cor(h,PRE,BRA);
		cout<<"INTRODUZA O SEU NOME (MAX. 10)";
		gotoxy(mapax0+1,mapay0+3);
		gets(nome_jog);
		sprintf(nomepokemon,"profoak.txt");
		sprintf(modo,"r");
		FILE *profoak2 = abreficheiro(nomepokemon,"r");
		PreencheMatriz2(abreficheiro(nomepokemon,modo));
		fclose(profoak2);
		mostraMapaAtivo2();
		cor(h,BRA,PRE);
		gotoxy(mapax0+47,mapay0+12);
		sleep(1500);
		cout <<"OK! ENTAO O TEU NOME E    ";
		gotoxy(mapax0+47,mapay0+13);
		sleep(1500);
		cout <<nome_jog<<"!!";
		gotoxy(mapax0+47,mapay0+14);
		sleep(1500);
		cout <<"DIZ-ME, "<<nome_jog<<", QUE ";
		gotoxy(mapax0+47,mapay0+15);
		sleep(1500);
		cout <<"POKEMON QUERES ESCOLHER?";
		sleep(2000);
		sprintf(nomepokemon,"pokebolas_iniciais.txt");
		sprintf(modo,"r");
		FILE *pokebolas = abreficheiro(nomepokemon,"r");
		PreencheMatriz2(abreficheiro(nomepokemon,modo));
		fclose(pokebolas);
		mostraMapaAtivo2();
		gotoxy(mapax0,mapay0+28);
		cout<<"0 -> Charmander     1 -> Bulbasaur     2->Squirtle                              ";
		gotoxy(mapax0,mapay0+29);
		cout<<"                                                                                ";
		gotoxy(mapax0,mapay0+29);
		escolha=getch()-'0';
		if(escolha==0) {}
		else if(escolha==1) {}
		else if(escolha==2) {}
		else if(escolha==3) {
			sleep(1000);
			sprintf(nomepokemon,"pokebolapikachu.txt");
			sprintf(modo,"r");
			FILE *pokebolapikachu = abreficheiro(nomepokemon,"r");
			PreencheMatriz2(abreficheiro(nomepokemon,modo));
			fclose(pokebolapikachu);
			mostraMapaAtivo2();
			sleep(2000);
		}
		gotoxy(mapax0,mapay0+30);
		system("pause");
		limparsp();
		sprintf(nomepokemon,"profoak.txt");
		sprintf(modo,"r");
		FILE *profoak3 = abreficheiro(nomepokemon,"r");
		PreencheMatriz2(abreficheiro(nomepokemon,modo));
		fclose(profoak3);
		mostraMapaAtivo2();
		cor(h,BRA,PRE);
		gotoxy(mapax0+47,mapay0+12);
		sleep(1500);
		cout <<"EXCELENTE ESCOLA A TUA!   ";
		gotoxy(mapax0+47,mapay0+13);
		sleep(1500);
		cout <<"PREPARA-TE, "<<nome_jog;
		gotoxy(mapax0+47,mapay0+14);
		sleep(1500);
		cout <<"A TUA JORNADA POKEMON ESTA ";
		gotoxy(mapax0+47,mapay0+15);
		sleep(1500);
		cout <<"PRESTES A COMECAR. UM MUNDO";
		gotoxy(mapax0+47,mapay0+16);
		sleep(1500);
		cout <<"DE SONHOS E AVENTURA ESPERA";
		gotoxy(mapax0+47,mapay0+17);
		sleep(1500);
		cout <<"POR TI! VAMOS!!";
		sleep(2000);
		gotoxy(mapax0,mapay0+29);
		sleep(1500);

		J = Jogador(1,1,46,8,escolha,nome_jog);//posicao inicial
	} else {
		//CARREGAR JOGO
		//TODO...
		int slot_enc;

		slot_enc = procurarSlotACarregar();  // 0 -nenhuma, 1-3 apenas essa, -1 várias				
		if (slot_enc==0) {
			gotoxy(mapax0+1,mapay0+1);
			cor(h,PRE,BRA);
			cout<<"NAO HA SLOTS GRAVADAS!";
			system("pause");
			exit(0);
		} else if (slot_enc==-1) {
			//escolha da slot
			bool fim = false;
			while (!fim) {
				gotoxy(mapax0+1,mapay0+1);
				cor(h,PRE,BRA);
				cout<<"INDIQUE A SLOT A ABRIR:";
				for (int s=1; s<=3; s++) {
					if (existeSlot(s))
						cout<<"["<<s<<"] ";
				}
				gotoxy(mapax0+1,mapay0+3);
				slot_enc=getch();
				for (int s=1; s<=3; s++) {
					if (existeSlot(slot_enc))
						fim = true;
				}
				if (!fim) {
					gotoxy(mapax0+1,mapay0+1);
					cout<<"SLOT INVÁLIDA. INDIQUE UMA SLOT VALIDA:";
				}
			}
			J = Jogador();
			J.carregar(slot_enc);
		} else {
			J = Jogador();
			J.carregar(slot_enc);
		}
	}
	return J;
}



void centro(){
	
	Ecravazio();
	gotoxy(mapax0+33,mapay0+14);
	cout<<"CURANDO POKEMONS";
	gotoxy(mapax0+35,mapay0+15);
	cor(h,PRE,CIN2);
	char c=178;
	for (int i=0; i<11; i++) {
		cout<<c;
	}
	
	gotoxy(mapax0+35,mapay0+15);
	cor(h,PRE,BRA);
	for (int i=0; i<11; i++) {
		sleep(500);
		cout<<c;
	}
	
	vector<Pokemon>::iterator it;
	for (it = J.pks.begin(); it != J.pks.end(); it++) {
		it->setvida();
	}
	sleep(2000);
	mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
}

//loja
void Loja() {
	

	Ecravazio();
	cor(h,PRE,BRA);
	gotoxy(mapax0,mapay0);
	cout<<"Bem vindo a loja!";
	gotoxy(mapax0,mapay0+1);
	cout<<"O que pertende comprar?";
	gotoxy(mapax0,mapay0+2);
	cout<<"Voce tem "<<J.m.getmoedas()<<" moedas";
	gotoxy(mapax0,mapay0+3);
	cout<<"1-Impulso de ataque(4)";
	gotoxy(mapax0,mapay0+4);
	cout<<"2-Impulso de vida(4)";
	gotoxy(mapax0,mapay0);
	char opcao;
	opcao=getch();
	int mo=J.m.getmoedas();
	int atk=J.m.getimpulso_atk();
	int vida=J.m.getimpulso_vida();
	if (opcao==49) {
		if(mo>=4) {
			J.m.setmoedas(mo-4);
			J.m.setimpulso_atk(atk+1);
			cout<<"impulso adquirido";
		} else {
			cout<<"Nao tem moedas suficientes";
		}
	}
	if (opcao==50) {
		if(mo>=4) {
			J.m.setmoedas(mo-4);
			J.m.setimpulso_vida(vida+1);
			cout<<"impulso adquirido";
		} else {
			cout<<"nao tem moedas suficientes";
		}
	}
	sleep(1000);
	limparsp();
	mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
}

//Luta
void Batalha_P() {
	
	Pokemon PokAdv, PkEsc;
	gotoxy(mapax0,mapay0);
	int Rn;
	srand (time(NULL));
	Rn = rand() % 2;
	if(Rn>0) {

		int T;
		srand (time(NULL));
		Rn =3;
		PkEsc=PKUsar();	
		//Set vida e attk....
		MatBat(PkEsc.numero,Rn);
		//adversario
		PokAdv = Pokemon(Rn);
		PokAdv.setvida();
		PokAdv.setataque_basico(PkEsc.tipo);
		PokAdv.setataque_alternativo1(PkEsc.tipo);
		PokAdv.setataque_alternativo2(PkEsc.tipo);
		PokAdv.setataque_especial(PkEsc.tipo);
		PokAdv.setenergia(10);
		//nosso pokemon
//		PkEsc.setvida();
		PkEsc.setataque_basico(PokAdv.tipo);
		PkEsc.setataque_alternativo1(PokAdv.tipo);
		PkEsc.setataque_alternativo2(PokAdv.tipo);
		PkEsc.setataque_especial(PokAdv.tipo);
		PkEsc.setenergia(10);
		int D=0;
		while(PokAdv.getvida()>0 && PkEsc.getvida()>0) {

			gotoxy(mapax0,mapay0+23);
			cout<<"SUA VIDA:"<< "|" <<PkEsc.getvida()<<"|"<<"                        "<<"VIDA INIMIGA:"<<"|"<<PokAdv.getvida()<<"|"<<"                           ";
			gotoxy(mapax0,mapay0+24);
			cout<<"SUA ENERGIA:"<<"|"<<PkEsc.getenergia()<<"|"<<"                     "<<"ENERGIA INIMIGA:"<<"|"<<PokAdv.getenergia()<<"|"<<"                        ";
			gotoxy(mapax0,mapay0+25);
			cout<<"________________________________________________________________________________";
			gotoxy(mapax0,mapay0+26);
			cout<<"ATAQUES: "<<"1-BASICO"<<"                     "<<"MOCHILA  5-impulso_vida"<<"                      ";
			gotoxy(mapax0,mapay0+27);
			cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-impulso_ataque"<<"                       ";
			gotoxy(mapax0,mapay0+28);
			cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
			gotoxy(mapax0,mapay0+29);
			cout<<"         "<<"4-ESPECIAL"<<"                                                                  ";
			gotoxy(mapax0,mapay0+30);
			cout<<"__________________________________________________________________________________";
			gotoxy(mapax0,mapay0+31);
			if((D%2)==0) {
				T=getch();
				if(T==49) {
					PokAdv.ataque(PkEsc.getataque_basico());
					if(PkEsc.getenergia()<10) {
						PkEsc.setenergia(PkEsc.getenergia()+1);
					}

				} else if(T==50) {
					if(PkEsc.getenergia()>2) {
						PokAdv.ataque(PkEsc.getataque_alternativo1());
						PkEsc.setenergia(PkEsc.getenergia()-3);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
				} else if(T==51) {
					if(PkEsc.getenergia()>4) {
						PokAdv.ataque(PkEsc.getataque_alternativo2());
						PkEsc.setenergia(PkEsc.getenergia()-5);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}

				} else if(T==52) {
					if(PkEsc.getenergia()>6) {
						PokAdv.ataque(PkEsc.getataque_especial());
						PkEsc.setenergia(PkEsc.getenergia()-7);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
				} else if(T==53) {
					//poção de vida
				} else if(T==54) {
					//poção de atack

				} else {
				}
				//atak..........
			}
			//inimigo.......................
			else if((D%2)!=0) {
				sleep(1000);
				if(PokAdv.getenergia()>6) {
					PkEsc.ataque(PokAdv.getataque_especial());
					PokAdv.setenergia(PokAdv.getenergia()-7);
					PokAdv.setenergia(PokAdv.getenergia()+1);

				} else if(PokAdv.getenergia()>4) {
					PkEsc.ataque(PokAdv.getataque_alternativo2());
					PokAdv.setenergia(PokAdv.getenergia()-5);
					PokAdv.setenergia(PokAdv.getenergia()+1);
				} else if(PokAdv.getenergia()>2) {
					PkEsc.ataque(PokAdv.getataque_alternativo1());
					PokAdv.setenergia(PokAdv.getenergia()-3);
					PokAdv.setenergia(PokAdv.getenergia()+1);

				} else {
					PkEsc.ataque(PokAdv.getataque_basico());
					PokAdv.setenergia(PokAdv.getenergia()+1);
				}
			}
			D++;
			//POR VIDA A 0 NO FINAL
			if(PokAdv.getvida()<=0) {
				J.addPokemon(PokAdv.numero);
				J.m.addmoeda();
				
				PkEsc.newExperience();
				
				gotoxy(mapax0,mapay0);
	
				gotoxy(mapax0,mapay0+23);
				cout<<"SUA VIDA:"<< "|" <<PkEsc.getvida()<<"|"<<"                        "<<"VIDA INIMIGA:"<<"|"<<"0"<<"|"<<"                           ";
				gotoxy(mapax0,mapay0+24);
				cout<<"SUA ENERGIA:"<<"|"<<PkEsc.getenergia()<<"|"<<"                     "<<"ENERGIA INIMIGA:"<<"|"<<PokAdv.getenergia()<<"|"<<"                        ";
				gotoxy(mapax0,mapay0+25);
				cout<<"________________________________________________________________________________";
				gotoxy(mapax0,mapay0+26);
				cout<<"ATAQUES: "<<"1-BASICO"<<"                     "<<"MOCHILA  5-impulso_vida"<<"                      ";
				gotoxy(mapax0,mapay0+27);
				cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-impulso_ataque"<<"                       ";
				gotoxy(mapax0,mapay0+28);
				cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
				gotoxy(mapax0,mapay0+29);
				cout<<"         "<<"4-ESPECIAL"<<"                                          VITORIA!!!!!!!!!!   ";
				gotoxy(mapax0,mapay0+30);
				cout<<"__________________________________________________________________________________";
			} else if(PkEsc.getvida()<=0) {
				PkEsc.setvida(0);
				gotoxy(mapax0,mapay0+23);
				cout<<"SUA VIDA:"<< "|" <<PkEsc.getvida()<<"|"<<"                        "<<"VIDA INIMIGA:"<<"|"<<PokAdv.getvida()<<"|"<<"                           ";
				gotoxy(mapax0,mapay0+24);
				cout<<"SUA ENERGIA:"<<"|"<<PkEsc.getenergia()<<"|"<<"                     "<<"ENERGIA INIMIGA:"<<"|"<<PokAdv.getenergia()<<"|"<<"                        ";
				gotoxy(mapax0,mapay0+25);
				cout<<"________________________________________________________________________________";
				gotoxy(mapax0,mapay0+26);
				cout<<"ATAQUES: "<<"1-BASICO"<<"                        "<<"BAG:  5-boost_vida"<<"                      ";
				gotoxy(mapax0,mapay0+27);
				cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-boost_atk"<<"                       ";
				gotoxy(mapax0,mapay0+28);
				cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
				gotoxy(mapax0,mapay0+29);
				cout<<"         "<<"4-ESPECIAL"<<"                                      DERROTA!!!!!!!!!!       ";
				gotoxy(mapax0,mapay0+30);
				cout<<"__________________________________________________________________________________";
			}
		}
		


		gotoxy(mapax0,mapay0+30);
		system("pause");
		limparsp();
	}
	
	
	J.updatePokemon(PkEsc);
	
}
void Batalha() {
	
	Pokemon PokAdv, PkEsc;
	gotoxy(mapax0,mapay0);
	int Rn;
	srand (time(NULL));
	Rn = rand() % 2;
	if(Rn>0) {

		int T;
		srand (time(NULL));
		Rn = rand() % 7;

		if(Rn==3){
			return ;
		}
		PkEsc=PKUsar();	
		//Set vida e attk....

		MatBat(PkEsc.numero,Rn);

		PokAdv = Pokemon(Rn);
		PokAdv.setvida();
		PokAdv.setataque_basico(PkEsc.tipo);
		PokAdv.setataque_alternativo1(PkEsc.tipo);
		PokAdv.setataque_alternativo2(PkEsc.tipo);
		PokAdv.setataque_especial(PkEsc.tipo);
		PokAdv.setenergia(10);
//		PkEsc.setvida();
		PkEsc.setataque_basico(PokAdv.tipo);
		PkEsc.setataque_alternativo1(PokAdv.tipo);
		PkEsc.setataque_alternativo2(PokAdv.tipo);
		PkEsc.setataque_especial(PokAdv.tipo);
		PkEsc.setenergia(10);
		int D=0;
		while(PokAdv.getvida()>0 && PkEsc.getvida()>0) {

			gotoxy(mapax0,mapay0+23);
			cout<<"SUA VIDA:"<< "|" <<PkEsc.getvida()<<"|"<<"                        "<<"VIDA INIMIGA:"<<"|"<<PokAdv.getvida()<<"|"<<"                           ";
			gotoxy(mapax0,mapay0+24);
			cout<<"SUA ENERGIA:"<<"|"<<PkEsc.getenergia()<<"|"<<"                     "<<"ENERGIA INIMIGA:"<<"|"<<PokAdv.getenergia()<<"|"<<"                        ";
			gotoxy(mapax0,mapay0+25);
			cout<<"________________________________________________________________________________";
			gotoxy(mapax0,mapay0+26);
			cout<<"ATAQUES: "<<"1-BASICO"<<"                     "<<"MOCHILA  5-impulso_vida"<<"                      ";
			gotoxy(mapax0,mapay0+27);
			cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-impulso_ataque"<<"                 ";
			gotoxy(mapax0,mapay0+28);
			cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
			gotoxy(mapax0,mapay0+29);
			cout<<"         "<<"4-ESPECIAL"<<"                                                            ";
			gotoxy(mapax0,mapay0+30);
			cout<<"__________________________________________________________________________________";
			gotoxy(mapax0,mapay0+31);
			if((D%2)==0) {
				T=getch();
				if(T==49) {
					PokAdv.ataque(PkEsc.getataque_basico());
					if(PkEsc.getenergia()<10) {
						PkEsc.setenergia(PkEsc.getenergia()+1);
					}

				} else if(T==50) {
					if(PkEsc.getenergia()>2) {
						PokAdv.ataque(PkEsc.getataque_alternativo1());
						PkEsc.setenergia(PkEsc.getenergia()-3);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
				} else if(T==51) {
					if(PkEsc.getenergia()>4) {
						PokAdv.ataque(PkEsc.getataque_alternativo2());
						PkEsc.setenergia(PkEsc.getenergia()-5);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
				} else if(T==52) {
					if(PkEsc.getenergia()>6) {
						PokAdv.ataque(PkEsc.getataque_especial());
						PkEsc.setenergia(PkEsc.getenergia()-7);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
				} else if(T==53) {
					Mochila m;
					int i=J.m.getimpulso_vida();
					if(i>0){
						J.m.setimpulso_vida(i-1);
						PkEsc.setvida();
					}
					else
						D--;
				} else if(T==54) {
					Mochila m;
					int i=J.m.getimpulso_atk();
					if(i>0){
						J.m.setimpulso_atk(i-1);
						PokAdv.ataque(40);
					}
					else
						D--;

				} else {
				}
				//atak...
			}
			//inimigo.......................
			else if((D%2)!=0) {
				sleep(1000);
				if(PokAdv.getenergia()>6) {
					PkEsc.ataque(PokAdv.getataque_especial());
					PokAdv.setenergia(PokAdv.getenergia()-7);
					PokAdv.setenergia(PokAdv.getenergia()+1);

				} else if(PokAdv.getenergia()>4) {
					PkEsc.ataque(PokAdv.getataque_alternativo2());
					PokAdv.setenergia(PokAdv.getenergia()-5);
					PokAdv.setenergia(PokAdv.getenergia()+1);
				} else if(PokAdv.getenergia()>2) {
					PkEsc.ataque(PokAdv.getataque_alternativo1());
					PokAdv.setenergia(PokAdv.getenergia()-3);
					PokAdv.setenergia(PokAdv.getenergia()+1);

				} else {
					PkEsc.ataque(PokAdv.getataque_basico());
					PokAdv.setenergia(PokAdv.getenergia()+1);
				}
			}
			D++;
			//POR VIDA A 0 NO FINAL
			char txt[100];
				
			if(PokAdv.getvida()<=0) {
				
				//PkEsc.setvida();
				J.addPokemon(PokAdv.numero);
				J.m.addmoeda();
				
				PkEsc.newExperience();
			
				gotoxy(mapax0,mapay0);
	
				gotoxy(mapax0,mapay0+23);
				sprintf(txt,"SUA VIDA:    %2d  | EXP: %d     | VIDA INIMIGA:    %2d |       ",PkEsc.getvida(),PkEsc.getxp(),PokAdv.getvida());
				cout<<txt;
				gotoxy(mapax0,mapay0+24);	
				sprintf(txt,"SUA ENERGIA: %2d  | Niv: %d     | ENERGIA INIMIGA: %2d |       ",PkEsc.getenergia(),PkEsc.getnivel(),PokAdv.getenergia());
				cout<<txt;
				gotoxy(mapax0,mapay0+25);
				cout<<"________________________________________________________________________________";
				gotoxy(mapax0,mapay0+26);
				cout<<"ATAQUES: "<<"1-BASICO"<<"                     "<<"MOCHILA  5-impulso_vida"<<"                      ";
				gotoxy(mapax0,mapay0+27);
				cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-impulso_ataque"<<"                    ";
				gotoxy(mapax0,mapay0+28);
				cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
				gotoxy(mapax0,mapay0+29);
				cout<<"         "<<"4-ESPECIAL"<<"                                          VITORIA!!!!!!!!!!   ";
				gotoxy(mapax0,mapay0+30);
				cout<<"__________________________________________________________________________________";
			} else if(PkEsc.getvida()<=0) {
				PkEsc.setvida(0);
				gotoxy(mapax0,mapay0+23);
				sprintf(txt,"SUA VIDA:    %2d  | EXP: %d     | VIDA INIMIGA:    %2d |       ",PkEsc.getvida(),PkEsc.getxp(),PokAdv.getvida());
				cout<<txt;
				gotoxy(mapax0,mapay0+24);	
				sprintf(txt,"SUA ENERGIA: %2d  | Niv: %d     | ENERGIA INIMIGA: %2d |       ",PkEsc.getenergia(),PkEsc.getnivel(),PokAdv.getenergia());
				cout<<txt;
				gotoxy(mapax0,mapay0+25);
				cout<<"________________________________________________________________________________";
				gotoxy(mapax0,mapay0+26);
				cout<<"ATAQUES: "<<"1-BASICO"<<"                        "<<"BAG:  5-boost_vida"<<"                      ";
				gotoxy(mapax0,mapay0+27);
				cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-boost_atk"<<"                       ";
				gotoxy(mapax0,mapay0+28);
				cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
				gotoxy(mapax0,mapay0+29);
				cout<<"         "<<"4-ESPECIAL"<<"                                      DERROTA!!!!!!!!!!       ";
				gotoxy(mapax0,mapay0+30);
				cout<<"__________________________________________________________________________________";
			}
		}
		gotoxy(mapax0,mapay0+30);
		system("pause");
		limparsp();
	}
	J.updatePokemon(PkEsc);
}

int BatalhaGYM() {
	
	int R=1;
	Pokemon PokAdv, PkEsc;
	gotoxy(mapax0,mapay0);
	int Rn;
		int T;
		srand (time(NULL));
		Rn = rand() % 7;
		PkEsc=PKUsar();	
		//Set vida e attk....

		MatBat(PkEsc.numero,Rn);

		PokAdv = Pokemon(Rn);
		PokAdv.setvida();
		PokAdv.setataque_basico(PkEsc.tipo);
		PokAdv.setataque_alternativo1(PkEsc.tipo);
		PokAdv.setataque_alternativo2(PkEsc.tipo);
		PokAdv.setataque_especial(PkEsc.tipo);
		PokAdv.setenergia(10);
		PkEsc.setataque_basico(PokAdv.tipo);
		PkEsc.setataque_alternativo1(PokAdv.tipo);
		PkEsc.setataque_alternativo2(PokAdv.tipo);
		PkEsc.setataque_especial(PokAdv.tipo);
		PkEsc.setenergia(10);
		int D=0;
		while(PokAdv.getvida()>0 && PkEsc.getvida()>0) {

			gotoxy(mapax0,mapay0+23);
			cout<<"SUA VIDA:"<< "|" <<PkEsc.getvida()<<"|"<<"                        "<<"VIDA INIMIGA:"<<"|"<<PokAdv.getvida()<<"|"<<"                           ";
			gotoxy(mapax0,mapay0+24);
			cout<<"SUA ENERGIA:"<<"|"<<PkEsc.getenergia()<<"|"<<"                     "<<"ENERGIA INIMIGA:"<<"|"<<PokAdv.getenergia()<<"|"<<"                        ";
			gotoxy(mapax0,mapay0+25);
			cout<<"________________________________________________________________________________";
			gotoxy(mapax0,mapay0+26);
			cout<<"ATAQUES: "<<"1-BASICO"<<"                     "<<"MOCHILA  5-impulso_vida"<<"                      ";
			gotoxy(mapax0,mapay0+27);
			cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-impulso_ataque"<<"                    ";
			gotoxy(mapax0,mapay0+28);
			cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
			gotoxy(mapax0,mapay0+29);
			cout<<"         "<<"4-ESPECIAL"<<"                                                            ";
			gotoxy(mapax0,mapay0+30);
			cout<<"__________________________________________________________________________________";
			gotoxy(mapax0,mapay0+31);
			if((D%2)==0) {
				T=getch();
				if(T==49) {
					PokAdv.ataque(PkEsc.getataque_basico());
					if(PkEsc.getenergia()<10) {
						PkEsc.setenergia(PkEsc.getenergia()+1);
					}

				} else if(T==50) {
					if(PkEsc.getenergia()>2) {
						PokAdv.ataque(PkEsc.getataque_alternativo1());
						PkEsc.setenergia(PkEsc.getenergia()-3);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
					
				} else if(T==51) {
					if(PkEsc.getenergia()>4) {
						PokAdv.ataque(PkEsc.getataque_alternativo2());
						PkEsc.setenergia(PkEsc.getenergia()-5);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}

				} else if(T==52) {
					if(PkEsc.getenergia()>6) {
						PokAdv.ataque(PkEsc.getataque_especial());
						PkEsc.setenergia(PkEsc.getenergia()-7);
						if(PkEsc.getenergia()<10) {
							PkEsc.setenergia(PkEsc.getenergia()+1);
						}
					} else {
						D--;
					}
				} else if(T==53) {
					//poção de vida
				} else if(T==54) {
					//poção de atack
				} else {
				}
				//atak..........
			}
			//inimigo.......................
			else if((D%2)!=0) {
				sleep(1000);
				if(PokAdv.getenergia()>6) {
					PkEsc.ataque(PokAdv.getataque_especial());
					PokAdv.setenergia(PokAdv.getenergia()-7);
					PokAdv.setenergia(PokAdv.getenergia()+1);

				} else if(PokAdv.getenergia()>4) {
					PkEsc.ataque(PokAdv.getataque_alternativo2());
					PokAdv.setenergia(PokAdv.getenergia()-5);
					PokAdv.setenergia(PokAdv.getenergia()+1);
				} else if(PokAdv.getenergia()>2) {
					PkEsc.ataque(PokAdv.getataque_alternativo1());
					PokAdv.setenergia(PokAdv.getenergia()-3);
					PokAdv.setenergia(PokAdv.getenergia()+1);

				} else {
					PkEsc.ataque(PokAdv.getataque_basico());
					PokAdv.setenergia(PokAdv.getenergia()+1);
				}
			}
			D++;
			//POR VIDA A 0 NO FINAL
			char txt[100];
				
			if(PokAdv.getvida()<=0) {
				
				//PkEsc.setvida();
				J.m.addmoeda();
				
				PkEsc.newExperience();
			
				gotoxy(mapax0,mapay0);
	
				
				gotoxy(mapax0,mapay0+23);
				sprintf(txt,"SUA VIDA:    %2d  | EXP: %d     | VIDA INIMIGA:    %2d |       ",PkEsc.getvida(),PkEsc.getxp(),PokAdv.getvida());
				cout<<txt;
				gotoxy(mapax0,mapay0+24);	
				sprintf(txt,"SUA ENERGIA: %2d  | Niv: %d     | ENERGIA INIMIGA: %2d |       ",PkEsc.getenergia(),PkEsc.getnivel(),PokAdv.getenergia());
				cout<<txt;
				gotoxy(mapax0,mapay0+25);
				cout<<"________________________________________________________________________________";
				gotoxy(mapax0,mapay0+26);
				cout<<"ATAQUES: "<<"1-BASICO"<<"                     "<<"MOCHILA  5-impulso_vida"<<"                      ";
				gotoxy(mapax0,mapay0+27);
				cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-impulso_ataque"<<"                   ";
				gotoxy(mapax0,mapay0+28);
				cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
				gotoxy(mapax0,mapay0+29);
				cout<<"         "<<"4-ESPECIAL"<<"                                          VITORIA!!!!!!!!!!   ";
				gotoxy(mapax0,mapay0+30);
				cout<<"__________________________________________________________________________________";
				int O=0,z,v;
				J.posicaoMx=z;
				J.posicaoMy=v;
				J.m.setkraxa(z,v,1);
				for(int y=0;y<3;y++)
				{
					for(int x=0;x<3;x++)
					{
						if(J.m.getkraxas(x,y)==1)
						{
							O++;
						}
					}
				}
				if(O==9)
				{
					Ecravazio();
					cout<<"Parabens FINALIZOU O JOGO!!!!!";
					R=0;
				}
			} else if(PkEsc.getvida()<=0) {
				PkEsc.setvida(0);
				gotoxy(mapax0,mapay0+23);
				sprintf(txt,"SUA VIDA:    %2d  | EXP: %d     | VIDA INIMIGA:    %2d |       ",PkEsc.getvida(),PkEsc.getxp(),PokAdv.getvida());
				cout<<txt;
				gotoxy(mapax0,mapay0+24);	
				sprintf(txt,"SUA ENERGIA: %2d  | Niv: %d     | ENERGIA INIMIGA: %2d |       ",PkEsc.getenergia(),PkEsc.getnivel(),PokAdv.getenergia());
				cout<<txt;
				gotoxy(mapax0,mapay0+25);
				cout<<"________________________________________________________________________________";
				gotoxy(mapax0,mapay0+26);
				cout<<"ATAQUES: "<<"1-BASICO"<<"                        "<<"BAG:  5-boost_vida"<<"                      ";
				gotoxy(mapax0,mapay0+27);
				cout<<"         "<<"2-ALTERNATIVO 1"<<"                 "<<"      6-boost_atk"<<"                       ";
				gotoxy(mapax0,mapay0+28);
				cout<<"         "<<"3-ALTERNATIVO 2"<<"                 "<<"                                        ";
				gotoxy(mapax0,mapay0+29);
				cout<<"         "<<"4-ESPECIAL"<<"                                      DERROTA!!!!!!!!!!       ";
				gotoxy(mapax0,mapay0+30);
				cout<<"__________________________________________________________________________________";
			}
		}		
	gotoxy(mapax0,mapay0+30);
	system("pause");
	limparsp();
	J.updatePokemon(PkEsc);
	return R;
}

//movimento
void movimento() {

	//Movimento -
	// PMX,PMY - mapa aonde está o robô
	// x,y - posição no mapa aonde está o robô
	// x_ant,y_ant - posição anterior aonde estava o robô

	int b=0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int s=1;
	int movimento;
	int x_ant, y_ant, PMX_ant, PMY_ant;
	int PMX, PMY, x, y;

	J.getposicao(&PMX,&PMY,&x,&y);
	mostraMapaAtivo(PMX,PMY,x,y);

	while (s!=0) {
	
		x_ant=x;
		y_ant=y;
		PMX_ant= PMX;
		PMY_ant= PMY;
		J.setposicao(PMX,PMY,x,y);

		char pos;
		movimento=getch();
		if (movimento==224)
			movimento=22400+getch();

		if(movimento==119||movimento==22472||movimento==87) { //w ou seta para cima ou W
			if(y==0) {
				pos='0';
			} else
				pos=MapaDoMundo[PMX][PMY][x][y-1];

			if(pos=='6'||pos=='p'||pos=='4'||pos=='5') {}
			else if(pos=='3') {
				y--;
				b=1;
				Batalha();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
			} else if(pos=='7'){
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"Bem vindo ao Ginásio!!!";
				sleep(2000);
				s=BatalhaGYM();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
				
			} else if (pos==loja) {
				Loja();
				b=0;
			}else if (pos==center) {
				centro();
				b=0;
			} else if(pos==CasaInicial) {
				limparsp();
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"A sua jornada ainda nao acabou";
				sleep(1000);
				limparsp();
				mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
				b=0;
			} else {
				if(y==0) {
					if(PMY>0) {
						PMY--;
						y=29;
					}
				} else {
					y--;
				}
			}
		} else if(movimento==100||movimento==22477||movimento==68) { //d -> D
			if(x==79) {
				pos='0';
			} else
				pos=MapaDoMundo[PMX][PMY][x+1][y];
			if(pos=='6'||pos=='p'||pos=='4'||pos=='5') {}
			else if(pos=='3') {
				x++;
				b=1;
				Batalha();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
			}else if(pos=='7'){
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"Bem vindo ao Ginásio!!!";
				sleep(2000);
				s=BatalhaGYM();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
				
			}else if (pos==Pikachu){
				x++;
				Batalha_P();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
			} else if (pos==loja) {
				Loja();
				b=0;
			} else if(pos==center){
				centro();
				b=0;
			}else if(pos==CasaInicial) {
				limparsp();
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"A sua jornada ainda nao acabou";
				sleep(1000);
				limparsp();
				mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
				b=0;
			} else {
				if (x==79) { //mudar de mapa para o da dirieta
					if (PMX<2) {
						PMX++;
						x=0;
					}
				} else {
					x++;
				}
			}
		} else if(movimento==115||movimento==22480||movimento==83) { //s v S
			if(y==29) {
				pos='0';
			} else
				pos=MapaDoMundo[PMX][PMY][x][y+1];
			if(pos=='6'||pos=='p'||pos=='4'||pos=='5') {} //passagem proibida
			else if(pos=='3') {
				y++;
				b=1;
				Batalha();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
			} else if(pos=='7'){
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"Bem vindo ao Ginásio!!!";
				sleep(2000);
				s=BatalhaGYM();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
				
			}else if (pos==loja) {
				Loja();
				b=0;
			}else if(pos==center) {
				centro();
				b=0;
			} else if(pos==CasaInicial) {
				limparsp();
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"A sua jornada ainda nao acabou";
				sleep(1000);
				limparsp();
				mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
				b=0;
			} else {
				if(y==29) {
					if (PMY<2) {
						PMY++;
						y=0;
					}
				} else {
					y++;
				}
			}
		} else if(movimento==97||movimento==22475||movimento==65) { //<- A a
			if(x==0) {
				pos='0';
			} else
				pos=MapaDoMundo[PMX][PMY][x-1][y];

			if(pos=='6'||pos=='p'||pos=='4'||pos=='5') {}
			else if(pos=='3') {
				x--;
				b=1;
				Batalha();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
			} else if(pos=='7'){
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"Bem vindo ao Ginásio!!!";
				sleep(2000);
				s=BatalhaGYM();
				b=0;
				mostraMapaAtivo(PMX,PMY,x,y);
				
			}else if (pos==loja) {
				Loja();
				b=0;
			}else if(pos==center) {
				centro();
				b=0;
			} else if(pos==CasaInicial) {
				limparsp();
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"A sua jornada ainda nao acabou";
				system("pause");
				limparsp();
				mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
				b=0;
			} else {
				if (x==0) {
					if (PMX>0) {
						PMX--;
						x=79;
					}
				} else {
					x--;
				}
			}
		} else if (movimento==27) { //ESC-sair do jogo
			gotoxy(0,39);
			cor(h,PRE,BRA);
			s=0;
		}else if (movimento=='m'||movimento=='M'){
			Ecravazio();
			gotoxy(mapax0,mapay0);
			cout<<"moedas:"<<J.m.getmoedas();
			gotoxy(mapax0,mapay0+1);
			cout<<"impulso ataque:"<<J.m.getimpulso_atk();
			gotoxy(mapax0,mapay0+1);			
			cout<<"impulso vida:"<<J.m.getimpulso_vida();
			gotoxy(mapax0,mapay0+1);		
			for(y=0;y<3;y++){
				for(x=0;x<3;x++){	
					cout<<"kraxas"<<J.m.getkraxas(x,y);
					cout<<"\n";
				}
			}
			b=0;
			mostraMapaAtivo(J.posicaoMx,J.posicaoMy,J.posicaox,J.posicaoy);
		}
		 else if (movimento==71||movimento==103) { //guardar o jogo
			int slot =procurarSlotVazia();
			if (slot>=1) {
				//ok
			} else {
				//perguntar qual slot 1-2-3 ?
				Ecravazio();
				gotoxy(mapax0,mapay0);
				cout<<"Memória cheia. Indique a slot a substituir: ";
				bool fim=false;
				while (!fim) {
					slot=getch();
					fim = ((slot >=1) && (slot <= 3));
					if (!fim) {
						gotoxy(mapax0,mapay0);
						cout<<"Slot inválida. Indique a slot a substituir (1, 2 ou 3): ";
					}
				}
			}

			J.gravar(slot);
		}
		if (b==0) {
			if ((x_ant!=x) || (y_ant!=y)) {
				//movimento para outro mapa

				if ((PMX_ant==PMX) && (PMY_ant==PMY)) {
					//movimento dentro do mapa atual
					mostraJogador(PMX, PMY, x_ant,y_ant,x,y);
				} else
					mostraMapaAtivo(PMX,PMY,x,y);
			}
		}
	}
}

//Main
int main() {
	system("MODE CON COLS=160 LINES=40");

	char nomemapa[80], modo[5], nome_jog[20];

	carregarSlots();
	mostraconsola();
	int escolha;
	J = intro();

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//ler mapas
	for(int PMX=0 ; PMX<mundox; PMX++) {
		for(int PMY=0 ; PMY<mundoy ; PMY++) {
			sprintf(nomemapa,"mapaPkm(%d)(%d).txt",PMX,PMY);
			sprintf(modo,"r");
			FILE *ficheiro = abreficheiro(nomemapa,"r");
			PreencheMatriz(abreficheiro(nomemapa,modo), PMX , PMY);
			fclose(ficheiro);
		}
	}
	//ler pokemons
	int n;
	char nomepokemon[80], modoPK[5];
	for(n=0; n<7; n++) {
		sprintf(nomepokemon,"Pokemon(%d).txt",n);
		sprintf(modoPK,"r");
		FILE *ficheiro1 = abreficheiro(nomepokemon,"r");
		PreenchePokemon(abreficheiro(nomepokemon,modoPK),n);
		fclose(ficheiro1);
	}
	movimento();
}
