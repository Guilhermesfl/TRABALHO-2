#include <stdbool.h>

typedef struct Bno no;

struct Bno{
	int num; // Número de chaves armazenadas no nó
	char* chaves[4]; // Armazena as chaves em ordem crescente
	int posicao[4];
	bool folha;
	no* filhos[5];
};

typedef struct arvore_B{
	no *raiz;
} arvB;

void print_uso(char const *argv[]);
arvB * cria_arvB(arvB *T);
no* cria_no(no *x);
void insere_arvB(arvB *T, char *k, int posicao);
void split_filho_arvB(no* x, int i);
void insereNC_arvB(no* x, char *k, int posicao);
int busca_arvB(no *x, char *k);