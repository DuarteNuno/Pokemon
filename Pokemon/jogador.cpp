#include "mochila.h"
#include "pokemon.h"
#include "jogador.h"

//---Jogador----------------------------------------------------------------------

Jogador::Jogador() {}

void Jogador::addPokemon(int pk) {	
	vector<Pokemon>::iterator it;
	for (it = pks.begin(); it != pks.end(); it++) {
		
		if (it->numero == pk)
		{
			return;
		}
	}
	pks.push_back(Pokemon(pk));
}

void Jogador::addPokemon(Pokemon pkm) {
	pks.push_back(pkm);
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

void Jogador::updatePokemon(Pokemon PkEsc) {	
	vector<Pokemon>::iterator it;
	for (it = pks.begin(); it != pks.end(); it++) {
		
		if (it->numero == PkEsc.numero)
		{//atualizar
			it->setvida(PkEsc.getvida());
			it->setxp(PkEsc.getxp());
			it->setnivel(PkEsc.getnivel());
		}
	}
}

void Jogador::gravar(int slot) {
	char nomefich[40];
	sprintf(nomefich,"PK_game_s%d.txt",slot);
	FILE*f=fopen(nomefich,"w");

	gravarFich(f);
	m.gravarFich(f);
	fprintf(f,"pks_size: %d\n",pks.size());
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
	int npks;
	char nomefich[40];
	sprintf(nomefich,"PK_game_s%d.txt",slot);
	FILE*f=fopen(nomefich,"r");

	carregarFich(f);
	m.carregarFich(f);

	fscanf(f,"pks_size: %d\n",&npks);
	pks.clear();
	for (int n=1; n<=npks; n++)
	{
		Pokemon pkm = Pokemon();
		pkm.carregarFich(f);
		addPokemon(pkm);
	}
	fclose(f);
}

void Jogador::carregarFich(FILE*f) {
	fscanf(f,"pk_act: %d\n",&pk_act);
	fscanf(f,"pos_mx: %d\n",&posicaoMx);
	fscanf(f,"pos_my: %d\n",&posicaoMy);
	fscanf(f,"pos_x: %d\n",&posicaox);
	fscanf(f,"pos_y: %d\n",&posicaoy);
}

