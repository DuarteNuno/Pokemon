#include "header.h"
#include "Slot.h"


Slot::Slot() {}

Slot::Slot(int ind) {
	i=ind;
}

void Slot::guardar() {
	char nomeficheiro[10];
	sprintf(nomeficheiro,"jogo%d.txt",i);
	FILE*f=fopen(nomeficheiro,"w");

	fprintf(f,"mx: %d\n",j.posicaoMx);
	fprintf(f,"my: %d\n",j.posicaoMy);
	fprintf(f,"x: %d\n",j.posicaox);
	fprintf(f,"y: %d\n",j.posicaoy);

	fclose(f);
}

bool Slot::carregar(int i) {
	char nomeficheiro[10];
	sprintf(nomeficheiro,"jogo%d.txt",i);
	FILE*f=fopen(nomeficheiro,"r");
	int Mx,My,x,y;
	if (f) {
		//j = Jogador(Mx,My,x,y);
		fscanf(f,"mx: %d\n",&Mx);
		fscanf(f,"my: %d\n",&My);
		fscanf(f,"x: %d\n",&x);
		fscanf(f,"y: %d\n",&y);

		fclose(f);
	} else
		return false;
	return true;
}

