#include <stdio.h>

typedef struct tDado {
  int numero;
} tDado;

typedef struct tNodo {
  struct tDado dado;
  struct tNodo *prox;	
} tNodo;

typedef struct tDescritor {
  struct tNodo *ini;	
  struct tNodo *fim;	
  int qtd;
} tDescritor;

int menu(void);
void inicializar(struct tDescritor*);
void destruir(struct tDescritor);
void enqueue(struct tDescritor*, struct tNodo*);
struct tNodo* dequeue(struct tDescritor*);
void listar(struct tDescritor); // NAO E OPERACAO DE FILA

int main(void) {
  struct tDescritor fila1;
  struct tNodo *q;
  int op;
  
  inicializar(&fila1);
  do {
    op = menu();
    switch (op) {
	  case 1:
        printf("\n\n* EnQueue *\n\n");
      	q = (struct tNodo*) malloc(sizeof(struct tNodo));
      	printf("Digite o valor: ");
		scanf("%d", &(q->dado.numero));
		enqueue(&fila1, q);
   	    break;
	  case 2:
        printf("\n\n* DeQueue *\n\n");
        q = dequeue(&fila1);
        if (q == NULL)
      	  printf("Fila vazia!");
      	else {
      	  printf("Valor: %d", q->dado.numero);
      	  free(q);
		}
   	    break;
      case 3: 
        printf("\n\n* Listar *\n\n");
        listar(fila1);
	}
  } while (op != 0);
  destruir(fila1);
	
  return 0;
}

int menu(void) {
  int op;
  printf("\n\n*** Menu ***\n\n");
  printf("1. EnQueue\n");
  printf("2. DeQueue\n");
  printf("3. Listar\n");
  printf("0. Sair\n\n");
  printf("Digite sua opcao: ");
  scanf("%d", &op);
  return op;
}

//*** inicializa fila *************************************************************
void inicializar(struct tDescritor *desc) {
  (*desc).qtd = 0;
  (*desc).ini = NULL;
  //(*desc).fim = NULL;
}

//*** destruir fila *************************************************************
void destruir(struct tDescritor desc) {
  struct tNodo *p;
  int i;
  for (i=0; i<desc.qtd; i++) {
    p = desc.ini;
    desc.ini = desc.ini->prox;
    free(p);
  }
}

//*** Enqueue(incluir na fila) *************************************************************
void enqueue(struct tDescritor *fila, struct tNodo *n) {
  if ((*fila).ini == NULL) // Fila vazia
    (*fila).ini = n;
  else
    (*fila).fim->prox = n;
  (*fila).fim = n;
  (*fila).qtd++;
  n->prox = NULL;
}

//*** Dequeue(remover da fila) *************************************************************
struct tNodo* dequeue(struct tDescritor *fila) {
  struct tNodo *p = (*fila).ini;
  
  if ((*fila).ini != NULL) {
    (*fila).ini = (*fila).ini->prox;
    (*fila).qtd--;
  }
  return p;
}

//*** listar *************************************************************
void listar(struct tDescritor desc) {
  struct tNodo *p = desc.ini;
  int i;
  printf("Num\n");
  printf("=====\n");
  for (i=0; i<desc.qtd; i++) {
    printf("%5d\n", p->dado.numero);
    p = p->prox;
  }
}
