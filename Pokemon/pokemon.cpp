#include "pokemon.h"

//---Pokemon----------------------------------------------------------
const int TPK_FOGO=1;
const int TPK_ERVA=2;
const int TPK_AGUA=3;
const int TPK_ELECTRICO=4;


Pokemon::Pokemon() {}

Pokemon::Pokemon(int pk) {
	numero=pk;
	nivel=0;
	setvida();
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
void Pokemon::setenergia(int x) {
	energia=x;
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

void Pokemon::ataque(int res_ataque) {
	vida=vida-res_ataque;
	if (vida < 0) vida=0;
}
void Pokemon::setvida(int v) {
	vida=v;
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

void Pokemon::newExperience()
{
	xp++;
	if (xp==10)
	{
		xp=0;
		nivel++;
	}
}

void Pokemon::gravarFich(FILE*f) {
	fprintf(f,"numero: %d\n",numero);
	fprintf(f,"vida: %d\n",vida);
	fprintf(f,"nivel: %d\n",nivel);
	fprintf(f,"xp: %d\n",xp);
}

void Pokemon::carregarFich(FILE*f) {
	fscanf(f,"numero: %d\n",&numero);
	fscanf(f,"vida: %d\n",&vida);
	fscanf(f,"nivel: %d\n",&nivel);
	fscanf(f,"xp: %d\n",&xp);
}


