#include <stdio.h>
#include <stdlib.h>

typedef struct tNodo {
  struct tNodo *esq;	
  int valor;
  struct tNodo *dir;	
} tNodo;

int menu(void);
void inicializar(struct tNodo**);
void destruir(struct tNodo**);
void incluir(struct tNodo**, struct tNodo*);
void caminharEmOrdem(struct tNodo*);
void caminharPreOrdem(struct tNodo *);
void caminharPosOrdem(struct tNodo *);
void excluir(struct tNodo **, int);
struct tNodo* pesquisar(struct tNodo *, int);
struct tNodo* menor(struct tNodo *);
int altura(struct tNodo *, struct tNodo *);

int main(void) {
	struct tNodo *raiz, *novo;
	int op, valor;
	
	inicializar(&raiz);
	do {
		op = menu();
		switch (op) {
		  case 1:
		    printf("\n\n*** Incluir ***\n\n");
		  	novo = (struct tNodo*) malloc(sizeof(struct tNodo));
		  	printf("Digite o valor: ");
			scanf("%d", &(novo->valor));
			incluir(&raiz, novo);
		    break;
		  case 2: 
		    printf("\n\n*** Buscar ***\n\n");
		  	printf("Digite o valor: ");
			scanf("%d", &valor);
			if(pesquisar(raiz, valor))
				printf("Encontrado.");
			else
				printf("Nao encontrado.");
		    break;
		  case 3: 
		    printf("\n\n*** Caminhar Em-ordem ***\n\n");
		    printf("Nodos: ");
		    caminharEmOrdem(raiz);
		    break;
		  case 4: 
		    printf("\n\n*** Caminhar Pre-ordem ***\n\n");
			printf("Nodos: ");
		    caminharPreOrdem(raiz);
		    break;
		  case 5: 
		    printf("\n\n*** Caminhar Pos-ordem ***\n\n");
			printf("Nodos: ");
		    caminharPosOrdem(raiz);
		    break;
		  case 6:
		  	printf("\n\n*** Excluir ***\n\n");
		    printf("Digite o valor: ");
		    scanf("%d", &valor);
		    excluir(&raiz, valor);
		    break;
		  case 7: 
		    printf("\n\n* Altura *\n\n");
		  	printf("Digite o valor: ");
			scanf("%d", &valor);
			novo = pesquisar(raiz, valor);
			if (!novo)
		  	  printf("Nao achei!");
		  	else
		  	  printf("Altura = %d", altura(raiz, novo));
		    break;
		}
	} while (op != 0);
	destruir(&raiz);
	return 0;
}

//*** Delete *************************************************************
void excluir(struct tNodo **raiz, int valor) {
	struct tNodo *p;
	
	if((*raiz) != NULL) {
		if(valor < (*raiz)->valor) 
			excluir(&((*raiz)->esq), valor);
		else {
			if(valor > (*raiz)->valor)
				excluir(&((*raiz)->dir), valor);
			else { //(valor == (*raiz)->dado) == Excluir
				if( ((*raiz)->esq == NULL ) && ((*raiz)->dir == NULL ) ) {
					free(*raiz);
					(*raiz) = NULL;
				} else {
					if((*raiz)->esq == NULL) {
						p = (*raiz);
						(*raiz) = p->dir;
						free(p);
					} else {
						if((*raiz)->dir == NULL) {
							p = (*raiz);
							(*raiz) = p->esq;
							free(p);
						} else { // 2 filhos
							p = menor((*raiz)->dir);
				            (*raiz)->valor = p->valor;
				            excluir(&((*raiz)->dir), p->valor);
						}
					}
				}
			}
		}
			
	}
	
}

//*** Minor ***************************************************************
struct tNodo* menor(struct tNodo *raiz) {
  if (raiz == NULL)
    return NULL;
  if (raiz->esq == NULL)
    return raiz;
  return menor(raiz->esq);
}

int menu(void) {
	int op;
	do {
		printf("\n\n*** MENU ***\n\n");
		printf("1. Incluir\n");
		printf("2. Buscar\n");
		printf("3. Caminhar Em-ordem\n");
		printf("4. Caminhar Pre-ordem\n");
		printf("5. Caminhar Pos-ordem\n");
		printf("6. Excluir\n");
		printf("7. Altura\n");
		printf("0. Sair\n\n");
		printf("Digite sua opcao: ");
		scanf("%d", &op);
	if ((op < 0) || (op > 7))
	  printf("\nOpcao invalida!\n");
	} while ((op < 0) || (op > 7));
	return op;
}

//*** Inicialize *******************************************************
void inicializar(struct tNodo **raiz) {
	(*raiz) = NULL;
}

//*** Destroy **********************************************************
void destruir(struct tNodo **raiz) {
	if((*raiz) != NULL) {
		destruir(&((*raiz)->esq));
		destruir(&((*raiz)->dir));
		free((*raiz));
	}
}

//*** Search **********************************************************
struct tNodo* pesquisar(struct tNodo *raiz, int valor) {
	
	if( (raiz == NULL) || (raiz->valor == valor) )
		return raiz;
	
	if(raiz->valor < valor)
		return pesquisar(raiz->esq, valor);
		
	return pesquisar(raiz->esq, valor);
}

//*** Include ***********************************************************
void incluir(struct tNodo **raiz, struct tNodo *novo) {
	novo->esq = novo->dir = NULL;
	
	if ((*raiz) == NULL)
		(*raiz) = novo;
	else
		if (novo->valor < (*raiz)->valor)
			incluir(&((*raiz)->esq), novo);
	else
		incluir(&((*raiz)->dir), novo);
}

//*** Caminhar Em Ordem ************************************************
void caminharEmOrdem(struct tNodo *raiz) {
	if (raiz != NULL) {
		caminharEmOrdem(raiz->esq);
		printf("%d, ", raiz->valor);
		caminharEmOrdem(raiz->dir);
	}
}

//*** Caminhar PRE Ordem ************************************************
void caminharPreOrdem(struct tNodo *raiz) {
	if (raiz != NULL) {
		printf("%d, ", raiz->valor);
		caminharEmOrdem(raiz->esq);
		caminharEmOrdem(raiz->dir);
	}
}

//*** Caminhar POS Ordem ************************************************
void caminharPosOrdem(struct tNodo *raiz) {
	if (raiz != NULL) {
		caminharEmOrdem(raiz->esq);
		caminharEmOrdem(raiz->dir);
		printf("%d, ", raiz->valor);
	}
}

//*** Altura ************************************************************
int altura(struct tNodo *raiz, struct tNodo *no) {
	int maior, ad;
	if (raiz == NULL)
		return -1;
	if (raiz == no)
		return 0;
	maior = altura(raiz->esq, no);
	ad = altura(raiz->dir, no);
	if ((maior == -1) && (ad == -1))
		return -1;
	if (ad > maior)
	  maior = ad;
  	return maior + 1;
}
