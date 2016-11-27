#include <stdio.h>
#include <stdlib.h>
#include <FUNC.h>
#include <string.h>

int main(int argc, char const *argv[])
{

	FILE *fp;
	arvB *T;
	int opcao,pos_reg,PRR=0;
	char *chave,*aux,*aux1, c;
	/* Verificação das condições necessárias para funcionamento correto do programa */
	if (strcmp(argv[2],"-r")==0 && (atoi(argv[3]) == 1 || atoi(argv[3]) == 2))
	{
		if(((strcmp(argv[1],"data1.txt")==0) && atoi(argv[3]) == 1) || ((strcmp(argv[1],"data2.txt")==0) && atoi(argv[3]) == 2))
		{
			fp = fopen(argv[1], "r");
			if(fp == NULL)
			{
				printf("Não foi possível abrir o arquivo %s\n", argv[1]);
				exit(1);
			}
		} else {
			print_uso(argv);
			return 0; 
		} 
	} else { 
		print_uso(argv);
		return 0;
	}
	/* Alocação, Indexação e Inicialização da arvore B */
	T = cria_arvB(T);
	
	if(atoi(argv[3]) == 1) 
	{
		chave = (char *)malloc(7*sizeof(char));	
		do
		{
			fread(chave,1,7,fp);	
			PRR++;
			insere_arvB(T,chave,PRR);
			for(int j=0;j<10;){		
				fscanf(fp,"%c",&c);
				if(c == ';')j++;
			}
			fscanf(fp,"%s",aux);
			c = fgetc(fp);
			c = fgetc(fp);
		}while(!feof(fp));
	
	}
	/* TESTE COM O ALFABETO */
	/*
	insere_arvB(T,"C",1);
	insere_arvB(T,"D",2);
	insere_arvB(T,"S",3);
	insere_arvB(T,"T",4);
	insere_arvB(T,"A",5);
	insere_arvB(T,"M",5);
	insere_arvB(T,"P",5); 
	insere_arvB(T,"I",5);
	insere_arvB(T,"B",5);
	insere_arvB(T,"W",5);
	insere_arvB(T,"N",5);
	insere_arvB(T,"G",5);
	insere_arvB(T,"U",5);
	insere_arvB(T,"R",5);
	insere_arvB(T,"K",5);
	insere_arvB(T,"E",5);
	insere_arvB(T,"H",5);
	insere_arvB(T,"O",5);
	insere_arvB(T,"L",5);
	insere_arvB(T,"J",5);
	insere_arvB(T,"Y",5);
	insere_arvB(T,"Q",5);
	insere_arvB(T,"Z",5);
	insere_arvB(T,"F",5);
	insere_arvB(T,"X",5);
	insere_arvB(T,"V",5);
	*/
	/* MENU DE OPÇÕES */
	/*do{
		printf("**************************************\n");
		printf("*               MENU                 *\n");
		printf("1 - Buscar Registro\n");
		printf("2 - Inserir Registro\n");
		printf("3 - Mostrar Arvore-B\n");
		printf("4 - Sair\n");
		printf("Digite a opcao desejada:");
		scanf(&opcao);
		while(opcao < 1 && opcao > 4)
		{
			printf("Digite um opcao valida:"); 
			scanf(&opcao);
		}
		switch(opcao):
			case 1:
				printf("Digite a chave do arquivo a ser buscado: ");
				scanf("%s", chave);
				pos_reg = busca_arvB(T->raiz,chave);
			case 2:
				printf("Digite a chave do arquivo a ser inserido: ")
				scanf("%s", chave);
				//pos_reg nesse caso é uma posição após o ultimo registro e precisa ser calculada
				insere_arvB(T,chave,pos_reg);
			case 3: ;
				//Criar a função responsável por mostrar a arvore

		default:
	}while(opcao != 4);
	*/
	//free(chave);
	//fclose(fp);
	
	return 0;
}
