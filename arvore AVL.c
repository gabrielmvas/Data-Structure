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
void balancear(struct tNodo **);
int fatorBalanceamento(struct tNodo *);
void rotacaoSimplesDireita(struct tNodo**);
void rotacaoSimplesEsquerda(struct tNodo**);
void rotacaoDuplaDireita(struct tNodo**);
void rotacaoDuplaEsquerda(struct tNodo**);


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

//*** Excluir *************************************************************
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
	balancear(raiz);
}
//*** Excluir2 *************************************************************
int excluir2(struct tNodo **raiz, struct tNodo *cara) {
	struct tNodo *me;
	if ((*raiz) == NULL)
		return 0;
	if ((*raiz) == cara) {
		if ((cara->esq == NULL) && (cara->dir == NULL)) {
			free(cara);
			(*raiz) = NULL;
		}
		else {
			if ((cara->esq != NULL) && (cara->dir == NULL)) {
				(*raiz) = cara->esq;
				free(cara);
			}
			else {
				if ((cara->esq == NULL) && (cara->dir != NULL)) {
					(*raiz) = cara->dir;
					free(cara);
				}
				else {
					me = menor(cara->dir);
					(*raiz)->valor = me->valor;
					excluir(&((*raiz)->dir), me);
				}
			}
		}
		return 1;
	}
    if (cara->valor < (*raiz)->valor)
		return excluir(&((*raiz)->esq), cara);
	return excluir(&((*raiz)->dir), cara);
}
//*** FB ******************************************************************
int fatorBalanceamento(struct tNodo *raiz) {
  if (raiz == NULL)
    return 0;
  return altura(raiz->dir) - altura(raiz->esq);
}

//*** Rotação Simples Direita ***********************************************
void rotacaoSimplesDireita(struct tNodo **raiz) {
  struct tNodo *q, *temp;
  q = (*raiz)->esq;
  temp = q->dir;
  q->dir = (*raiz);
  (*raiz)->esq = temp;
  (*raiz) = q;
}

//*** Rotação Simples Esquerda ***********************************************
void rotacaoSimplesEsquerda(struct tNodo **raiz) {
  struct tNodo *q, *temp;
  q = (*raiz)->dir;
  temp = q->esq;
  q->esq = (*raiz);
  (*raiz)->dir = temp;
  (*raiz) = q;
}

//*** Rotação Dupla Direita ************************************************
void rotacaoDuplaDireita(struct tNodo **raiz) {
  rotacaoSimplesEsquerda(&(*raiz)->esq);
  rotacaoSimplesDireita(&(*raiz));
}

//*** Rotação Dupla Esquerda ***********************************************
void rotacaoDuplaEsquerda(struct tNodo **raiz) {
  rotacaoSimplesDireita(&((*raiz)->dir));
  rotacaoSimplesEsquerda(&(*raiz));
}

//*** Menor ***************************************************************
struct tNodo* menor(struct tNodo *raiz) {
  if (raiz == NULL)
    return NULL;
  if (raiz->esq == NULL)
    return raiz;
  return menor(raiz->esq);
}

//*** Menu ****************************************************************
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

//*** Inicializar *******************************************************
void inicializar(struct tNodo **raiz) {
	(*raiz) = NULL;
}

//*** Destruir **********************************************************
void destruir(struct tNodo **raiz) {
	if((*raiz) != NULL) {
		destruir(&((*raiz)->esq));
		destruir(&((*raiz)->dir));
		free((*raiz));
	}
}

//*** Pesquisar **********************************************************
struct tNodo* pesquisar(struct tNodo *raiz, int valor) {
	
	if( (raiz == NULL) || (raiz->valor == valor) )
		return raiz;
	
	if(valor < raiz->valor)
		return pesquisar(raiz->esq, valor);
		
	return pesquisar(raiz->dir, valor);
}

//*** Balancear **********************************************************
void balancear(struct tNodo **raiz) {
  int fb = fatorBalanceamento(*raiz);

  if ((fb == 2) && (fatorBalanceamento((*raiz)->dir) == 1))
    rotacaoSimplesEsquerda(&(*raiz));

  if ((fb == 2) && (fatorBalanceamento((*raiz)->dir) == -1))
    rotacaoDuplaEsquerda(&(*raiz));

  if ((fb == -2) && (fatorBalanceamento((*raiz)->esq) == -1))
    rotacaoSimplesDireita(&(*raiz));

  if ((fb == -2) && (fatorBalanceamento((*raiz)->esq) == 1))
    rotacaoDuplaDireita(&(*raiz));
}

//*** Incluir ***********************************************************
void incluir(struct tNodo **raiz, struct tNodo *novo) {
	novo->esq = novo->dir = NULL;
	
	if ((*raiz) == NULL)
		(*raiz) = novo;
	else {
		if (novo->valor < (*raiz)->valor)
			incluir(&((*raiz)->esq), novo);

		if (novo->valor > (*raiz)->valor)
			incluir(&((*raiz)->dir), novo);

		balancear(raiz);
	}
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

//*** Altura ***********************************************************
int altura(struct tNodo *raiz) {
	int e, d;
	if (raiz == NULL)
		return -1;
	e = altura(raiz->esq);
	d = altura(raiz->dir);
	if (e > d)
		return e+1;
	return d+1;
}

