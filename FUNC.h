#include <stdbool.h>

typedef struct Bno no;
typedef struct Registro REG;

struct Bno{
	int num; // Número de chaves armazenadas no nó
	char* chaves[4]; // Armazena as chaves em ordem crescente
	int posicao[4];
	bool folha;
	no* filhos[5];
};

struct Registro {
	char *campos[9];
};

typedef struct arvore_B{
	no *raiz;
} arvB;

REG* preenche_reg(REG *reg);
void print_uso(char const *argv[]);
arvB* cria_arvB(arvB *T);
no* cria_no(no *x);
arvB* insere_arvB(arvB *T, char *k, int *posicao);
void split_filho_arvB(no* x, int i);
no* insereNC_arvB(no* x, char *k, int *posicao);
int busca_arvB(no *x, char *k, int* seeks);