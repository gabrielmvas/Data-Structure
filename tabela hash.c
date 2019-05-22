//   Objetivo: Hash - Distribuir os 22 nomes em 44 posicoes com no maximo 11 colisoes 
#include <stdio.h>
#include <string.h>
#define TAM_NOME 50

typedef struct {
	char nome[TAM_NOME];
} Dado;

typedef struct {
	struct {
		int colisao; // -1 = vazio; 0..N = qtd de colisoes
		Dado dado;
	} tabelaDispersao[70];
	
	int posicaoLivre;
	Dado tabelaColisao[34];
} tHash;


void inicializar(tHash *esp) {
	int i;
	esp->posicaoLivre = 0;
	
	for (i = 0;i < 70;i++)
		esp->tabelaDispersao[i].colisao = -1;
}

int funcaoHash(char *nome) {
	int i, valor = 0, prim, ult;
	
	prim = (int) nome[0];
	ult = (int) nome[strlen(nome) - 1];
	
	for (i = 0;i < strlen(nome);i++) {
		switch (nome[i]) {
		  case 'A': valor += (2 * (ult * prim)); break;
		  case 'E': valor += (3 + (ult * prim)); break;
		  case 'I': valor += (7 / (ult * prim)); break;
		  case 'O': valor += (5 * (ult * prim)); break;
		  case 'U': valor += (11 + (ult * prim)); break;
		  default: valor += valor * (1 / (ult * ult)); break;
		}
	}
	
	
	return valor % 70;	
}

void incluir(tHash *esp, Dado dado) {
	int posicao = funcaoHash(dado.nome);
	
	if (esp->tabelaDispersao[posicao].colisao++ == -1) // livre
		esp->tabelaDispersao[posicao].dado = dado;
	else
		esp->tabelaColisao[esp->posicaoLivre++] = dado;
}

int main(void) {
	int i, cont;
	char str[60];
	Dado dado;
	tHash espalhamento;
	FILE *arq = fopen("alunos.txt","r");
	
	if (arq == NULL) {
		printf("Erro de abertura do arquivo alunos.txt");
		return 1;
	}
	
	inicializar(&espalhamento);
	
	while (fgets(str, TAM_NOME, arq)) {
		cont = 0;
		for(i = 0; i < strlen(str); i++) {
			dado.nome[cont++] = str[i];
		}
		incluir(&espalhamento, dado);
	}
	fclose(arq);
  
	printf("Colisoes: %d\n", espalhamento.posicaoLivre);
	
	//printf("Dispersao:\n");
	//for (i = 0; i < 70; i++)
    //	printf("[%d] - Colisao: %d\n", i, espalhamento.tabelaDispersao[i].colisao);
    	
    printf("Colisao:\n");
	for (i = 0; i < espalhamento.posicaoLivre; i++)
    	printf("[%d] - Nome: %s\n", i, espalhamento.tabelaColisao[i].nome);
	
  return 0;
}
