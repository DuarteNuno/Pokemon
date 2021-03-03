#include "header.h"

//---Pokemon----------------------------------------------------------
const int TPK_FOGO=1;
const int TPK_ERVA=2;
const int TPK_AGUA=3;
const int TPK_ELECTRICO=4;


Pokemon::Pokemon() {}

Pokemon::Pokemon(int pk) {
	numero=pk;
	nivel=0;
	switch(pk) {
		case 0:
			strcpy(nome,"charmander");
			tipo = TPK_FOGO;
			break;
		case 1:
			strcpy(nome,"bulbasaur");
			tipo = TPK_ERVA;
			break;
		case 2:
			strcpy(nome,"squirtle");
			tipo = TPK_AGUA;
			break;
		case 3:
			strcpy(nome,"pikachu");
			tipo = TPK_ELECTRICO;
			break;
		case 4:
			strcpy(nome,"metapod");
			tipo = TPK_ERVA;
			break;
		case 5:
			strcpy(nome,"voltorb");
			tipo = TPK_ELECTRICO;
			break;
		case 6:
			strcpy(nome,"psyduck");
			tipo = TPK_AGUA;
			break;
		default:
			strcpy(nome,"unknown");
	}



}
//get
int Pokemon::getvida() {
	return vida;
}
int Pokemon::getnivel() {
	return nivel;
}
int Pokemon::getxp() {
	return xp;
}
int Pokemon::getataque_basico() {
	return ataque_basico;
}
int Pokemon::getataque_alternativo1() {
	return ataque_alternativo1;
}
int Pokemon::getataque_alternativo2() {
	return ataque_alternativo2;
}
int Pokemon::getataque_especial() {
	return ataque_especial;
}
int Pokemon::getenergia() {
	return energia;
}
//set
void Pokemon::setenergia() {
	energia=10;
}

void Pokemon::setvida() {

	switch (numero) {
		case 0:
			vida=45+(0.9*getnivel());
			break;
		case 1:
			vida=55+(1.2*getnivel());
			break;
		case 2:
			vida=50+(1.0*getnivel());
			break;
		case 3:
			vida=52+(1.1*getnivel());
			break;
		case 4:
			vida=35+(0.9*getnivel());
			break;
		case 5:
			vida=50+(0.85*getnivel());
			break;
		default:
			vida=50;
	}
}

void Pokemon::setvida(int res_ataque) {
	vida=vida-res_ataque;
}
void Pokemon::setnivel(int n) {
	nivel=n;
}
void Pokemon::setxp(int x) {
	xp=x;
}
void Pokemon::setataque_basico(int tipo_adv) {

	// Eficacia  FOGO  ERVA  ELECTR	AGUA
	// 	FOGO      N	    B     N      M
	//  ERVA      M     N     N      B
	//  ELECTR	  N     N     N      B
	//  AGUA	  B	    M     M      N


	int Eficacia[4][4] = { {0,-1,0,1},{1,0,0,-1},{0,0,0,-1},{-1,1,1,0}};
	int fator = 2;

	switch (numero) {
		case 0:
			ataque_basico=4+(1.3*getnivel())+(fator*Eficacia[tipo][tipo_adv]);
			break;
		case 1:
			ataque_basico=2+(1*getnivel());
			break;
		case 2:
			ataque_basico=3+(1*getnivel());
			break;
		case 3:
			ataque_basico=3+(1.1*getnivel());
			break;
		case 4:
			ataque_basico=2+(0.9*getnivel());
			break;
		case 5:
			ataque_basico=3+(1.1*getnivel());
			break;
		default:
			ataque_basico=2;
	}
}
void Pokemon::setataque_alternativo1(int tipo_adv) {
	switch (numero) {
		case 0:
			ataque_alternativo1=8+(1.3*getnivel());
			break;
		case 1:
			ataque_alternativo1=4+(1*getnivel());
			break;
		case 2:
			ataque_alternativo1=6+(1*getnivel());
			break;
		case 3:
			ataque_alternativo1=6+(1.1*getnivel());
			break;
		case 4:
			ataque_alternativo1=4+(0.9*getnivel());
			break;
		case 5:
			ataque_alternativo1=6+(1.1*getnivel());
			break;
		default:
			ataque_alternativo1=5;
	}
}
void Pokemon::setataque_alternativo2(int tipo_adv) {
	switch (numero) {
		case 0:
			ataque_alternativo2=12+(1.3*getnivel());
			break;
		case 1:
			ataque_alternativo2=9+(1*getnivel());
			break;
		case 2:
			ataque_alternativo2=12+(1*getnivel());
			break;
		case 3:
			ataque_alternativo2=15+(1.1*getnivel());
			break;
		case 4:
			ataque_alternativo2=8+(0.9*getnivel());
			break;
		case 5:
			ataque_alternativo2=11+(1.1*getnivel());
			break;
		default:
			ataque_alternativo2=9;
	}
}
void Pokemon::setataque_especial(int tipo_adv) {
	switch (numero) {
		case 0:
			ataque_especial=20+(1.3*getnivel());
			break;
		case 1:
			ataque_especial=15+(1*getnivel());
			break;
		case 2:
			ataque_especial=18+(1*getnivel());
			break;
		case 3:
			ataque_especial=20+(1.1*getnivel());
			break;
		case 4:
			ataque_especial=13+(0.9*getnivel());
			break;
		case 5:
			ataque_especial=16+(1.1*getnivel());
			break;
		default:
			ataque_especial=15;
	}
}

void Pokemon::gravarFich(FILE*f) {
	fprintf(f,"numero: %d\n",numero);
	fprintf(f,"nivel: %d\n",nivel);
	fprintf(f,"xp: %d\n",xp);
}

//---Mochila---------------------------------------------------------------------

Mochila::Mochila() {
	moedas = 0;
	impulso_atk = 0;
	impulso_vida = 0;
	impulso_nivel = 0;


	for(int PMX=0; PMX<3; PMX++) {
		for (int PMY=0; PMY<3; PMY++) {
			kraxa[PMX][PMY]=0;
		}
	}
}
//get
int Mochila::getmoedas() {
	return moedas;
}
int Mochila::getimpulso_atk() {
	return impulso_atk;
}
int Mochila::getimpulso_vida() {
	return impulso_vida;
}
int Mochila::getimpulso_nivel() {
	return impulso_nivel;
}
int Mochila::getkraxas(int PMX , int PMY) {
	return kraxa[PMX][PMY];
}
//set
void Mochila::setmoedas(int m) {
	moedas=m;
}
void Mochila::setimpulso_atk(int a) {
	impulso_atk=a;
}
void Mochila::setimpulso_vida(int v) {
	impulso_vida=v;
}
void Mochila::setimpulso_nivel(int in) {
	impulso_nivel=in;
}
void Mochila::setkraxa(int PMX , int PMY,int v) {
	kraxa[PMX][PMY]=v;
}

void Mochila::gravarFich(FILE*f) {

	fprintf(f,"moedas: %d\n",moedas);
	fprintf(f,"impulso_atk: %d\n",impulso_atk);
	fprintf(f,"impulso_vida: %d\n",impulso_vida);
	fprintf(f,"kraxa: #9");

	for(int PMX=0; PMX<3; PMX++) {
		for (int PMY=0; PMY<3; PMY++) {
			fprintf(f,",%d", kraxa[PMX][PMY]);
		}
	}
}

void Mochila::carregarFich(FILE*f) {

	fprintf(f,"moedas: %d\n",moedas);
	fprintf(f,"impulso_atk: %d\n",impulso_atk);
	fprintf(f,"impulso_vida: %d\n",impulso_vida);
	fprintf(f,"kraxa: #9");

	for(int PMX=0; PMX<3; PMX++) {
		for (int PMY=0; PMY<3; PMY++) {
			fprintf(f,",%d", kraxa[PMX][PMY]);
		}
	}
}


//---Jogador----------------------------------------------------------------------

Jogador::Jogador() {}


void Jogador::addPokemon(int pk) {
	pks.push_back(Pokemon(pk));
}

void Jogador::trocaPokemon(int pk) {
	pk_act = pk;
}

Jogador::Jogador(int PMX,int PMY,int x, int y, int escolha, char* nome_jog) {
	setposicao(PMX,PMY,x,y);
	m = Mochila();

	pk_act = escolha;
	addPokemon(escolha);
	strcpy(nome,nome_jog);
}

void Jogador::setposicao(int PMX,int PMY,int x,int y) {
	posicaoMx=PMX;
	posicaoMy=PMY;
	posicaox=x;
	posicaoy=y;
}

void Jogador::getposicao(int *PMX, int *PMY,int *x,int *y ) {
	*PMX=posicaoMx;
	*PMY=posicaoMy;
	*x=posicaox;
	*y=posicaoy;
}

void Jogador::gravar(int slot) {

	char nomefich[40];
	sprintf(nomefich,"PK_%s_s%d.txt",nome,slot);
	FILE*f=fopen(nomefich,"w");

	gravarFich(f);
	m.gravarFich(f);

	vector<Pokemon>::iterator it;
	for (it = pks.begin(); it != pks.end(); it++) {
		Pokemon pkm= *it;
		pkm.gravarFich(f);
	}
	fclose(f);
}

void Jogador::gravarFich(FILE*f) {

	fprintf(f,"pk_act: %d\n",pk_act);
	fprintf(f,"pos_mx: %d\n",posicaoMx);
	fprintf(f,"pos_my: %d\n",posicaoMy);
	fprintf(f,"pos_x: %d\n",posicaox);
	fprintf(f,"pos_y: %d\n",posicaoy);
}

void Jogador::carregar(int slot) {

	char nomefich[40];
	sprintf(nomefich,"PK_game_s%d.txt",nome,slot);
	FILE*f=fopen(nomefich,"w");
	/*
		gravarFich(f);
		m.gravarFich(f);

		vector<Pokemon>::iterator it;
		for (it = pks.begin(); it != pks.end(); it++)
		{	Pokemon pkm= *it;
			pkm.gravarFich(f);
		}
		*/
	fclose(f);
}
/*
bool Slot::carregar(int i){
	char nomeficheiro[10];
	sprintf(nomeficheiro,"PK_%s_s%d.txt",i);
	FILE*f=fopen(nomeficheiro,"r");
	int Mx,My,x,y;
	if (f){
		//j = Jogador(Mx,My,x,y);
		fscanf(f,"mx: %d\n",&Mx);
		fscanf(f,"my: %d\n",&My);
		fscanf(f,"x: %d\n",&x);
		fscanf(f,"y: %d\n",&y);

		//j = Jogador(Mx,My,x,y);
		fclose(f);
	}
	else
		return false;

	return true;
}
*/

