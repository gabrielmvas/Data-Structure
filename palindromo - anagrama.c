//   Objetivo: Receber uma string (do usuário), carreguar numa LSE (char) e verificar se: 
//    a. é palíndromo; 
//    b. é um anagrama de outra palavra (recebida do usuário)"
#include <stdlib.h>
#include <stdio.h>

typedef struct tNo {
	char dado;
	struct tNo *prox;
} tNo;

typedef struct tDescritor {
	struct tNo *primeiro;
	int qtd;
} tDescritor;

int menu(void);
void inicializar(struct tDescritor*);
void destruir(struct tDescritor*);
void incluir(struct tDescritor*, char);
char excluir(struct tDescritor*, char);
char buscar(struct tDescritor, int);

int main(void) {
	struct tDescritor lista; // Descritor
	struct tNo *p; // ponteiro auxiliar
	char letra, palavra[50];
	int op, i, flag;
	
	inicializar(&lista);
	do {
		op = menu();
		switch(op) {
			case 1:
				printf("\n\n*** Recebe string ***\n\n");
				printf("Digite a palavra: ");
				fflush(stdin);
				gets(palavra);
				destruir(&lista);
				for (i=0; i<strlen(palavra); i++)
					incluir(&lista, palavra[i]);
				break;
			case 2:
				printf("\n\n*** Verifica: palindromo ***\n\n");
				p = lista.primeiro;
				flag = 1;
				for (i=0; i<lista.qtd/2; i++) {
					if (p->dado != buscar(lista, lista.qtd-i))
						flag = 0;
					p = p->prox;
				}
				if (flag)
					printf("Eh sim!!!\n");
				else
					printf("Nao e nao!!!\n");
				break;
			case 3:
				printf("\n\n*** Verifica: anagrama ***\n\n");
				printf("Digite a palavra: ");
				fflush(stdin);
				gets(palavra);
				flag = 1;
				if (lista.qtd != strlen(palavra))
					flag = 0;
				else {
					for (i=0; i<strlen(palavra); i++)
						excluir(&lista, palavra[i]);
					if (lista.qtd != 0)
						flag = 0;
				}
				if (flag)
					printf("Eh sim!!!\n");
				else
					printf("Nao e nao!!!\n");
				break;
			case 4:
				printf("\n\n*** Listagem ***\n\n");
				p = lista.primeiro;
				printf("Palavra: ");
				while (p != NULL) {
					printf("%c", p->dado);
					p = p->prox;
				}
		}
	} while (op != 0);
	destruir(&lista);
	return 0;
}

int menu(void) {
	int op;
	do {
		printf("\n\n*** MENU ***\n\n");
		printf("1. Recebe string\n");
		printf("2. Verifica: palindromo\n");
		printf("3. Verifica: anagrama\n");
		printf("4. Listar\n");
		printf("0. Sair\n\n");
		printf("Digite sua opcao: ");
		scanf("%d", &op);
		if ((op < 0) || (op > 4))
		  printf("\nOpcao invalida!\n");
	} while ((op < 0) || (op > 4));
	return op;
}

//*** INICIALIZA A LISTA ************************************************
void inicializar(struct tDescritor *lista) {
	(*lista).primeiro = NULL;
	(*lista).qtd = 0;
}

//*** DESTROI A LISTA ***************************************************
void destruir(struct tDescritor *lista) {
	struct tNo *p = (*lista).primeiro;
	while (p != NULL) {
		(*lista).primeiro = p;
		p = p->prox;
		free((*lista).primeiro);
	}
	inicializar(lista);
}

//*** INCLUI ************************************************************
void incluir(struct tDescritor *lista, char letra) {
	struct tNo *p, *novo;	
	novo = malloc(sizeof(struct tNo));
	novo->dado = letra;
	if ((*lista).primeiro == NULL) // lista vazia
		(*lista).primeiro = novo;
	else { // fim
		p = (*lista).primeiro;
		while (p->prox != NULL)
			p = p->prox;
		p->prox = novo;
	}
	novo->prox = NULL;
	(*lista).qtd++;
}

//*** EXCLUI ************************************************************
char excluir(struct tDescritor *lista, char chave) {
	struct tNo *q, *p = (*lista).primeiro;
	char retorno;
	while ((p != NULL) && (chave != p->dado))
		p = p->prox;
	if (p != NULL) {
		if ((*lista).primeiro == p) // primeiro OU unico
			(*lista).primeiro = p->prox;
		else { // fim OU meio
			q = (*lista).primeiro;
			while (q->prox != p)
				q = q->prox;
			q->prox = p->prox;
		}
		retorno = p->dado;
		free(p);
		(*lista).qtd--;
		return retorno;
	}
	else
		return '\0';
}

//*** BUSCA por posicao *************************************************
char buscar(struct tDescritor lista, int posicao) {
	struct tNo *p = lista.primeiro;
	int i;
	if (lista.qtd < posicao)
		return '\0';
	for (i=1; i<posicao; i++)
		p = p->prox;
	return p->dado;
}

