#include <stdlib.h>
#include <stdio.h>


typedef struct tDado {
	int codigo;
	char descricao[30];
	float preco;
} tDado;

typedef struct tNo {
	struct tDado dado;
	struct tNo *prox;
} tNo;

typedef struct tDescritor {
	struct tNo *primeiro;
	int qtd;
} tDescritor;


int menu(void);
void inicializar(struct tDescritor*);
void destruir(struct tDescritor*);
void incluir(struct tDescritor*, struct tNo*);
void excluir(struct tDescritor*, struct tNo*);
struct tNo *consultar(struct tDescritor, int);
int receberChave(void);
void receberDados(struct tDado*);
void mostrarDados(struct tDado);

int main(void) {
	int op, cod;
	struct tDescritor lista; // Descritor
	struct tDescritor backup; // Lista de backup
	struct tNo *p, *q; // ponteiros auxiliares
	
	inicializar(&lista);
	inicializar(&backup);
	do {
		op = menu();
		switch(op) {
			case 1:
				printf("\n\n*** Inclusao ***\n\n");
				cod = receberChave();
				p = malloc(sizeof(struct tNo));
				p->dado.codigo = cod;
				receberDados(&(p->dado));
				incluir(&lista, p);
				break;
			case 2:
				printf("\n\n*** Exclusao ***\n\n");
				p = consultar(lista, receberChave());
				if (p != NULL) {
					mostrarDados(p->dado);
					excluir(&lista, p);
					printf("\nExcluido com sucesso!!!\n");
				}
				else
					printf("\nCodigo nao encontrado!!!\n");
				break;
			case 3:
				printf("\n\n*** Alteracao ***\n\n");
				p = consultar(lista, receberChave());
				if (p != NULL) {
					mostrarDados(p->dado);
					receberDados(&(p->dado));
					printf("\nAlterado com sucesso!!!\n");
				}
				else
					printf("\nCodigo nao encontrado!!!\n");
				break;
			case 4:
				printf("\n\n*** Consulta ***\n\n");
				p = consultar(lista, receberChave());
				if (p != NULL)
					mostrarDados(p->dado);
				else
					printf("\nCodigo nao encontrado!!!\n");
				break;
			case 5:
				printf("\n\n*** Listagem ***\n\n");
				p = lista.primeiro;
				printf("Quantidade: %d\n\n", lista.qtd);
				printf("Cod Descricao                      Valor\n");
				printf("--- ------------------------------ --------\n");
				while (p != NULL) {
					printf("%3d %-30.30s R$ %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.preco);
					p = p->prox;
				}
				break;
			case 6:
				printf("\n\n*** Elimina Duplicados ***\n\n");
				p = lista.primeiro;
				while (p != NULL) {
					if ((p->prox != NULL) && (p->prox->dado.codigo == p->dado.codigo))
						excluir(&lista, p->prox);
					else
						p = p->prox;
				}
				break;
			case 7:
				printf("\n\n*** Backup ***\n\n");
				destruir(&backup); // ja inicializa
				p = lista.primeiro;
				while (p != NULL) {
					q = malloc(sizeof(struct tNo));
					q->dado = p->dado;
					incluir(&backup, q);
					p = p->prox;
				}
				break;
			case 8:
				printf("\n\n*** Recuperar Backup ***\n\n");
				destruir(&lista);
				lista = backup;
				inicializar(&backup);
		}
	} while (op != 0);
	destruir(&lista);
	return 0;
}

int menu(void) {
	int op;
	do {
		printf("\n\n*** MENU ***\n\n");
		printf("1. Incluir\n");
		printf("2. Excluir\n");
		printf("3. Alterar\n");
		printf("4. Consulta\n");
		printf("5. Listar\n");
		printf("6. DESDUPRICAR\n");
		printf("7. BECAPIAR\n");
		printf("8. RESTAURAR\n");
		printf("0. Sair\n\n");
		printf("Digite sua opcao: ");
		scanf("%d", &op);
		if ((op < 0) || (op > 8))
		  printf("\nOpcao invalida!\n");
	} while ((op < 0) || (op > 8));
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
void incluir(struct tDescritor *lista, struct tNo *novo) {
	struct tNo *p, *q;	
	if (((*lista).primeiro == NULL) || (novo->dado.codigo < (*lista).primeiro->dado.codigo)) { // lista vazia OU inicio
		novo->prox = (*lista).primeiro;
		(*lista).primeiro = novo;
	}
	else { // fim OU meio
		p = (*lista).primeiro;
		do {
			q = p;
			p = p->prox;
		} while ((p != NULL) && (p->dado.codigo < novo->dado.codigo));
		novo->prox = p;
		q->prox = novo;
	}
	(*lista).qtd++;
}

//*** EXCLUI ************************************************************
void excluir(struct tDescritor *lista, struct tNo *vitima) {
	struct tNo *p;	
	if ((*lista).primeiro == vitima) // primeiro OU unico
		(*lista).primeiro = vitima->prox;
	else { // fim OU meio
		p = (*lista).primeiro;
		while (p->prox != vitima)
			p = p->prox;
		p->prox = vitima->prox;
	}
	free(vitima);
	(*lista).qtd--;
}

//*** CONSULTA  **********************************************************
struct tNo *consultar(struct tDescritor lista, int chave) {
	struct tNo *p = lista.primeiro;
	while ((p != NULL) && (chave > p->dado.codigo))
		p = p->prox;
	if ((p != NULL) && (chave == p->dado.codigo))
		return p;
	else
		return NULL;
}

//*** RECEBE DADOS, EXCETO A CHAVE **************************************
int receberChave(void) {
	int codigo;
	printf("Digite o codigo...: ");
	scanf("%d", &codigo);
	return codigo;
}

//*** RECEBE DADOS, EXCETO A CHAVE **************************************
void receberDados(struct tDado *elemento) {
	printf("Digite a descricao: ");
	fflush(stdin);
	gets((*elemento).descricao);
	printf("Digite o preco....: R$ ");
	scanf("%f", &((*elemento).preco));
}

//*** MOSTRA OS DADOS, EXCETO A CHAVE ***********************************
void mostrarDados(struct tDado elemento) {
	printf("Descricao.........: %s\n", elemento.descricao);
	printf("Preco.............: R$ %.2f\n", elemento.preco);
}

