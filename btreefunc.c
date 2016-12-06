#include <stdio.h>
#include <stdlib.h>
#include <FUNC.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* FUNÇÃO RESPONSÁVEL POR INDICAR O FUNCIONAMENTO CORRETO DO PROGRAMA */
void print_uso(char const *argv[])
{
	printf("Uso: %s <file> -r 1 or 2\n", argv[0]);
	printf("<file>\n");
	printf("data1.txt - Registros de tamanho variavel\n");
	printf("data2.txt - Registros de tamanho fixo\n");
	printf("Options:\n");
	printf("1 - Registros de tamanho variavel\n");
	printf("2 - Registros de tamanho fixo\n");
	printf("\n");
}
/* FUNÇÃO QUE PREENCHE O SIGNIFICADO DOS CAMPOS DO REGISTRO */
REG1* preenche_reg1(REG1 *reg)
{
	reg = (REG1 *)malloc(sizeof(REG1));
	reg->campos[0] = "Nome:";
	reg->campos[1] = "Sobrenome:";
	reg->campos[2] = "Empresa:";
	reg->campos[3] = "Endereço:";
	reg->campos[4] = "Cidade:";
	reg->campos[5] = "Estado:";
	reg->campos[6] = "ZIP/PostalCode:";
	reg->campos[7] = "Phone1:";
	reg->campos[8] = "Phone2:";

	return reg;
}
REG2* preenche_reg2(REG2 *reg)
{
	reg = (REG2 *)malloc(sizeof(REG2));
	reg->campos[0] = "Nome:";
	reg->campos[1] = "Data:";
	reg->campos[2] = "Empresa:";

	return reg;

}
/* FUNÇÃO DE CRIAÇÃO DE CADA NÓ DA ÁRVORE B */
no* cria_no(no* x)
{
	x = (no *)calloc(1,sizeof(no));
	for (int i = 0; i < 4; ++i) x->posicao[i] = -1;
	
	return x;
}
/* FUNÇÃO DE CRIAÇÃO DA ESTRUTURA PRINCIPAL DA ÁRVORE B*/
arvB* cria_arvB(arvB *T)
{
	no* x;
	T = (arvB *)malloc(sizeof(arvB));
	x = cria_no(x);
	x->folha = TRUE;
	x->num = 0;
	x->pagina = 0;
	x->cor = 0;
	T->raiz = x;

	return T;
}
/* FUNÇÃO QUE REALIZA O SPLIT DO NÓ QUANDO NECESSÁRIO */
void split_filho_arvB(no* x, int i, int* regulador)
{
	no *z, *y;
	z = cria_no(z);
	y = x->filhos[i];
	z->folha = y->folha;
	z->num = 1;

	*regulador = *regulador +1;
	z->pagina = *regulador;
	z->nivel = y->nivel;

	for (int j = 0; j < 1; ++j) z->chaves[j] = y->chaves[j+3];
	for (int j = 0; j < 1; ++j) z->posicao[j] = y->posicao[j+3];
	
	if(y->folha == FALSE)
	{
		for (int j = 0; j < 2; ++j) z->filhos[j] = y->filhos[j+3];
		for (int j = 0; j < 3; ++j) y->filhos[j+3] = NULL;
	}	

	for (int j = x->num; j >= i; --j) x->filhos[j+1] = x->filhos[j];
	for (int j = x->num-1; j >= i; --j){ 
		x->chaves[j+1] = x->chaves[j];
		x->posicao[j+1] = x->posicao[j];
	}
	
	x->filhos[i+1] = z;
	x->chaves[i] = y->chaves[2];
	x->posicao[i] = y->posicao[2];
	x->num++;	

	for (int j = 0; j < 2; ++j)
	{
		y->chaves[j+2] = NULL;
		y->posicao[j+2] = -1;
	}
	y->num = 2;

}
/* FUNÇÃO DE INSERÇÃO DA CHAVE NA ÁRVORE */
arvB* insere_arvB(arvB *T, char *k, int *posicao, int* regulador)
{
	no *r;
	int vef = 0;
	int nivel = 0;
	r = T->raiz;
	if(r->num == 4){
		no *s;
		s = cria_no(s);
		T->raiz = s;
		s->folha = FALSE;
		s->num = 0;
		s->filhos[0] = r;
		r->nivel = 1;
		split_filho_arvB(s,0,regulador); //Para a raiz
		s = insereNC_arvB(s,k,posicao,regulador,&nivel);
		*regulador = *regulador +1;
		s->pagina = *regulador;
	} else {
		r = insereNC_arvB(r,k,posicao,regulador,&nivel);
	}
	return T;
}
/* FUNÇÃO DE INSERÇÃO DE CHAVE QUANDO O NÓ NÃO ESTÁ CHEIO */
no* insereNC_arvB(no* x, char *k, int *posicao, int* regulador, int *nivel)
{
	char *aux;
	int i;
	int vef = 0;
	i = x->num;
	aux = (char *)calloc(7,sizeof(char));
	strcpy(aux,k);
	if(x->folha == TRUE)
	{
		if(i > 0){
			while(i > 0 && strcmp(aux,x->chaves[i-1])<0)
			{
				x->chaves[i] = x->chaves[i-1];
				x->posicao[i] = x->posicao[i-1]; 
				i--;
			}
			x->posicao[i] = *posicao;
			x->chaves[i] = aux;
			x->num++;
		} else {
			x->posicao[i] = *posicao;
			x->chaves[i] = aux;
			x->num++;
		}
		x->nivel = *nivel;
	} 
	else
	{
		while(i > 0 && strcmp(aux,x->chaves[i-1])< 0) i--;
		if(x->filhos[i]->num == 4)
		{
			split_filho_arvB(x,i,regulador); //Para nó folha
			if(strcmp(aux,x->chaves[i])>0) i++; 
		}
		*nivel = *nivel + 1;
		insereNC_arvB(x->filhos[i],aux,posicao,regulador,nivel);
	}

	return x;
}
/* FUNÇÃO DE BUSCA NA ARVORE B */
int busca_arvB(no *x, char* k, int* seeks)
{
	int i=0;
	*seeks = *seeks + 1;

	while(i < x->num && strcmp(k,x->chaves[i])>0) i++;

	if(i< x->num && strcmp(k,x->chaves[i])==0) return x->posicao[i];
	else if(x->folha == TRUE) return -1;
	else return busca_arvB(x->filhos[i],k,seeks);
}

void imprime_arvB(no*x)
{
	int i=0,j,k;
	pilha Q;
	no *u,*aux;

	Q.topo = x;
	aux = Q.topo;

	while(Q.topo != NULL)
	{
		u = Q.topo;
		if(Q.topo->prox != NULL) Q.topo =  Q.topo->prox;
		else Q.topo = NULL;
		if(u->folha == FALSE){
			while(i <= u->num){
				if(u->filhos[i]->cor == 0){
					u->filhos[i]->cor = 1;
					if(Q.topo == NULL){
						Q.topo = u->filhos[i];
						aux = Q.topo;
					}
					else{
						aux->prox = u->filhos[i];
						aux = aux->prox;
					} 
				}
				i++;
			}
		}
		imprime(u);

		u->cor = 2;
		i=0;
	}


}
void imprime(no *x)
{
	int j = 0,k,i = 0;;
	printf("N%d:", x->nivel);
	printf("\n");
	printf("P%d:", x->pagina);

	while(x->chaves[i]!=NULL && i < x->num){
		printf("%s|", x->chaves[i]);
		i++;
	}
	printf("      ");
	i = 0;
	while(x->filhos[i]!=NULL && i <= x->num){
		printf("%d|", x->filhos[i]->pagina);
		i++;
	}
	printf("\n");	
	j++;
}
