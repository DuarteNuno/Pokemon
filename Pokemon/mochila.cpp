#include "mochila.h"
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
void Mochila::addmoeda() {
	moedas=moedas+1;
}
void Mochila::setimpulso_atk(int a) {
	impulso_atk=a;
}
void Mochila::setimpulso_vida(int v) {
	impulso_vida=v;
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
	fprintf(f,"\n");
}


void Mochila::carregarFich(FILE*f) {

	fscanf(f,"moedas: %d\n",&moedas);
	fscanf(f,"impulso_atk: %d\n",&impulso_atk);
	fscanf(f,"impulso_vida: %d\n",&impulso_vida);
	fscanf(f,"kraxa: #9");

	for(int PMX=0; PMX<3; PMX++) {
		for (int PMY=0; PMY<3; PMY++) {
			fscanf(f,",%d", &kraxa[PMX][PMY]);
		}
	}
	fscanf(f,"\n");
}

