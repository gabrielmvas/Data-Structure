#include <stdio.h>
#include <stdlib.h>

typedef struct tDado {
	int codigo;
	char descricao[30];
	float preco;
} tDado;

typedef struct tNo {
	struct tDado dado;
	struct tNo *prox;
	struct tNo *ant;
} tNo;

typedef struct tDescritor {
	struct tNo *primeiro;
	int qtd;
} tDescritor;

void inicializar(struct tDescritor *lista);
void incluir(struct tDescritor *lista, struct tNo *novo);
void mostrarDados(struct tDado elemento);
void excluir(struct tDescritor *lista, struct tNo *velho);
void destruir(struct tDescritor *lista);
void receberDados(struct tDado *elemento);
int receberChave();
struct tNo *consultar(struct tDescritor lista, int chave);


int main() {
	
	struct tDescritor lista, backup;
	struct tNo *p, *q;
	int op, cod;
	
	inicializar(&lista);
	inicializar(&backup);
	do {
		printf("1 - Incluir\n2 - Excluir\n3 - Listar\n4 - Consultar\n5 - Alterar\n6 - Backup\n7 - Restore\n0 - Sair\n Informe a opcao: ");
		scanf("%d", &op);
		switch(op) {
			case 1:
				system("cls");
				printf("** Inclusao **\n");
				cod = receberChave();
				p = consultar(lista, cod);
				if (p == NULL) {
					p = malloc(sizeof(struct tNo));
					p->dado.codigo = cod;
					receberDados(&(p->dado));
					incluir(&lista, p);
				} else {
					printf("\nCodigo ja existente!!!\n");
					getch();
				}			
				break;
			case 2:
				system("cls");
				printf("** Exclusao **\n");
				p = consultar(lista, receberChave());
				if(p != NULL) {
					mostrarDados(p->dado);
					excluir(&lista, p);
					printf("\nExcluido com sucesso.");
				} else
					printf("\n*Codigo nao encotrado*\n");
				getch();
				break;
			case 3:
				system("cls");
				printf("** Listagem **\n");
				p = lista.primeiro;
				printf("Quantidade: %d\n\n", lista.qtd);
				printf("Cod Descricao                      Valor\n");
				printf("--- ------------------------------ --------\n");
				while(p != NULL) {
					printf("%3d %-30.30s R$ %.2f\n", p->dado.codigo, p->dado.descricao, p->dado.preco);
					p = p->prox;
				}
				getch();
				break;
			case 4:
				system("cls");
				printf("** Consulta **\n");
				p = consultar(lista, receberChave());
				if(p != NULL) 
					mostrarDados(p->dado);
				else
					printf("\n*Codigo nao encotrado*\n");
					getch();
				break;
			case 5:
				system("cls");
				printf("** Alteracao **\n");
				p = consultar(lista, receberChave());
				if(p != NULL) {
					
					mostrarDados(p->dado);
					receberDados(&(p->dado));
					printf("\nAlterado com sucesso.\n");
					
				} else
					printf("\n*Codigo nao encotrado*\n");
				getch();
				break;
			case 6:
				system("cls");
				printf("** Backup **\n");
				destruir(&backup);
				p = lista.primeiro;
				while(p != NULL) {
					q = malloc(sizeof(struct tNo));
					q->dado = p->dado;
					incluir(&backup, q);
					p = p->prox;
				}
				printf("\nBackup realizado com sucesso.\n");
				getch();
				break;
			case 7:
				system("cls");
				printf("** Restore **\n");
				destruir(&lista);
				lista = backup;
				inicializar(&backup);
				printf("\nRestore realizado com sucesso.\n");
				getch();
				break;
		}
		system("cls");
	} while (op != 0);
	
	
	
	return 0;
}

void destruir(struct tDescritor *lista) {
	
	struct tNo *p = lista->primeiro;
	
	while(p != NULL) {
		
		lista->primeiro = p;
		p = p->prox;
		free(lista->primeiro);
		
	}
	
	inicializar(lista);
}

void excluir(struct tDescritor *lista, struct tNo *velho) {
	
	struct tNo *p;
	
	if( (lista->primeiro == velho) ) { //primeiro ou unico
		lista->primeiro = velho->prox;
	} else {
		p = lista->primeiro;
		while( p->prox != velho ) 
			p = p->prox;
			
		p->prox = velho->prox;

		if(velho->prox != NULL) 
			velho->prox->ant = p;	
		
	}
	free(velho);
	lista->qtd--;
}

struct tNo *consultar(struct tDescritor lista, int chave) {
	
	struct tNo *p = lista.primeiro;
	
	while ( (p != NULL) && (p->dado.codigo < chave) ) 
		p = p->prox;
		
	if( (p != NULL) && (p->dado.codigo == chave) )
		return p;
	else 
		return NULL;
	
}

void mostrarDados(struct tDado elemento) {
	printf("Descricao.........: %s\n", elemento.descricao);
	printf("Preco.............: R$ %.2f\n", elemento.preco);
}


void receberDados(struct tDado *elemento) {
	
	printf("\nIforme a descricao: \n");
	fflush(stdin);
	fgets(elemento->descricao, 30, stdin);
	fflush(stdin);
	
	printf("\nIforme o preco: \n");
	scanf("%f", &elemento->preco);
	
}

int receberChave() {
	int chave;
	
	printf("\nIforme o codigo: \n");
	scanf("%d", &chave);
	
	return chave;
	
}
void inicializar(struct tDescritor *lista) {
	
	lista->primeiro = NULL;
	lista->qtd = 0;
	
}

void incluir(struct tDescritor *lista, struct tNo *novo) {
	
	struct tNo *p, *q;
	
	if((lista->primeiro == NULL) || (novo->dado.codigo < lista->primeiro->dado.codigo)) { //Vazia ou inicio
		
		novo->prox = lista->primeiro;
		novo->ant = NULL;
		lista->primeiro = novo;
		
	} else { //Meio ou fim
		
		p = lista->primeiro;
		do {
			
			q = p; 
			p = p->prox;
			
		} while ( (p != NULL) && (p->dado.codigo < novo->dado.codigo) );
	
		novo->prox = p;
		novo->ant = q;
		q->prox = novo;
		
	}
	
	lista->qtd++;
}

