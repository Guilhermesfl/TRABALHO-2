#include <stdbool.h>

typedef struct Bno no;
typedef struct Registro1 REG1;
typedef struct Registro2 REG2;

struct Bno{
	int num; // Número de chaves armazenadas no nó
	char* chaves[4]; // Armazena as chaves em ordem crescente
	int posicao[4];
	int pagina; // Número da página que o nó está
	bool folha;
	no* filhos[5];
	int cor;
	no *prox;
	int nivel;
};

struct Registro1 {
	char *campos[9];
};

struct Registro2 {
	char *campos[3];
};

typedef struct arvore_B{
	no *raiz;
} arvB;

typedef struct Pilha{
	no *topo;
} pilha;

REG1* preenche_reg1(REG1 *reg);
REG2* preenche_reg2(REG2 *reg);
void print_uso(char const *argv[]);
arvB* cria_arvB(arvB *T);
no* cria_no(no *x);
arvB* insere_arvB(arvB *T, char *k, int *posicao, int* regulador);
void split_filho_arvB(no* x, int i, int* regulador);
no* insereNC_arvB(no* x, char *k, int *posicao, int* regulador, int *nivel);
int busca_arvB(no *x, char *k, int* seeks);
void imprime(no *x);
void imprime_arvB(no*x);