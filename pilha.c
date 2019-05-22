#include <stdlib.h>
#include <stdio.h>

typedef struct tNo {
	char dado;
	struct tNo *prox;
} tNo;

typedef struct tDescritor {
	struct tNo *iniTopo; // ini = fila ou lista; topo = pilha
	struct tNo *fim;
} tDescritor;

int menu(void);
void inicializar(struct tDescritor*);
void destruir(struct tDescritor*);
void push(struct tDescritor*, char);
char pop(struct tDescritor*);
int vazio(struct tDescritor*);
void enqueue(struct tDescritor*, char);
char dequeue(struct tDescritor*);

int main(void) {
	struct tDescritor pilha, fila;
	struct tNo *p;
	char letra;
	int op;
	
	inicializar(&pilha);
	inicializar(&fila);
	do {
		op = menu();
		switch(op) {
			case 1:
				printf("\n\n*** PUSH ***\n\n");
				printf("Digite uma letra: ");
				fflush(stdin);
				scanf("%c", &letra);
				push(&pilha, letra);
				break;
			case 2:
				printf("\n\n*** POP ***\n\n");
				printf("Letra: %c", pop(&pilha));
				break;
			case 3:
				printf("\n\n*** LISTAR ***\n\n");
				printf("PILHA:\n");
				printf("TOPO: ");
				p = pilha.iniTopo;
				while (p != NULL) {
					printf("%c, ", p->dado);
					p = p->prox;
				}
				printf(": BASE\n");
				printf("\nFILA:\n");
				printf("FIM: ");
				p = fila.iniTopo;
				while (p != NULL) {
					printf("%c, ", p->dado);
					p = p->prox;
				}
				printf(": INICIO\n");
				break;
			case 4:
				printf("\n\n*** ENQUEUE ***\n\n");
				printf("Digite uma letra: ");
				fflush(stdin);
				scanf("%c", &letra);
				enqueue(&fila, letra);
				break;
			case 5:
				printf("\n\n*** DEQUEUE ***\n\n");
				printf("Letra: %c", dequeue(&fila));
				break;
		}
	} while (op != 0);
	destruir(&pilha);
	destruir(&fila);
	return 0;
}

int menu(void) {
	int op;
	do {
		printf("\n\n*** MENU ***\n\n");
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("3. Listar \n");
		printf("4. Enqueue\n");
		printf("5. Dequeue\n");
		printf("0. Sair\n\n");
		printf("Digite sua opcao: ");
		scanf("%d", &op);
		if ((op < 0) || (op > 5))
		  printf("\nOpcao invalida!\n");
	} while ((op < 0) || (op > 5));
	return op;
}

//*** INICIALIZA A PILHA OU FILA ****************************************
void inicializar(struct tDescritor *lista) {
	(*lista).iniTopo = NULL;
	(*lista).fim = NULL;
}

//*** DESTROI A PILHA OU FILA *******************************************
void destruir(struct tDescritor *lista) {
	struct tNo *p = (*lista).iniTopo;
	while (p != NULL) {
		(*lista).iniTopo = p;
		p = p->prox;
		free((*lista).iniTopo);
	}
	inicializar(lista);
}

//*** PUSH **************************************************************
void push(struct tDescritor *pilha, char letra) {
	struct tNo *novo;	
	novo = malloc(sizeof(struct tNo));
	novo->dado = letra;
	novo->prox = (*pilha).iniTopo;
	(*pilha).iniTopo = novo;
}

//*** POP ***************************************************************
char pop(struct tDescritor *pilha) {
	struct tNo *p = (*pilha).iniTopo;
	char retorno;
	if (p == NULL)
		return '\0';
	retorno = p->dado;
	(*pilha).iniTopo = p->prox;
	free(p);
	return retorno;
}

//*** VAZIO *************************************************************
int vazio(struct tDescritor *lista) {
	if ((*lista).iniTopo == NULL)
		return 1;
	return 0;
}

//*** ENQUEUE ***********************************************************
void enqueue(struct tDescritor *fila, char letra) {
	push(fila, letra);
}

//*** DEQUEUE ***********************************************************
char dequeue(struct tDescritor *fila) {
	struct tDescritor pilhaAux;
	char aux;
	
	inicializar(&pilhaAux);
	while (!vazio(fila))
		push(&pilhaAux, pop(fila));
	aux = pop(&pilhaAux);
	while (!vazio(&pilhaAux))
		push(fila, pop(&pilhaAux));
	return aux;
}











