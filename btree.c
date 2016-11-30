#include <stdio.h>
#include <stdlib.h>
#include <FUNC.h>
#include <string.h>

int main(int argc, char const *argv[])
{

	FILE *fp;
	arvB *T;
	REG *reg;
	int opcao,pos_reg,num_reg=0,PRR=0,NRR=0,seeks=0,i;
	char *chave,*aux, c;
	/* Verificação das condições necessárias para funcionamento correto do programa */
	if (strcmp(argv[2],"-r")==0 && (atoi(argv[3]) == 1 || atoi(argv[3]) == 2))
	{
		if(((strcmp(argv[1],"data1.txt")==0) && atoi(argv[3]) == 1) || ((strcmp(argv[1],"data2.txt")==0) && atoi(argv[3]) == 2))
		{
			fp = fopen(argv[1], "r+");
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
	/**************** Alocação, Indexação e Inicialização da arvore B *********************************/
	reg = preenche_reg(reg);
	T = cria_arvB(T);
	
	if(atoi(argv[3]) == 1) // Registros de tamanho variável
	{
		chave = (char *)malloc(7*sizeof(char));	
		do
		{
			fread(chave,1,7,fp);
			T = insere_arvB(T,chave,&PRR);
			PRR+=7;
			do{		
				fscanf(fp,"%c",&c);
				PRR++;
			} while(c != '\n' && !feof(fp));
		}while(!feof(fp));
	} else { // Registros de tamanho fixo
		chave = (char *)malloc(4*sizeof(char));	
		do
		{
			fread(chave,1,4,fp);	
			NRR++;
			T = insere_arvB(T,chave,&NRR);
			do{		
				fscanf(fp,"%c",&c);
			} while(c != '\n' && !feof(fp));	
		}while(!feof(fp));
	}
	rewind(fp);
	fclose(fp);

	/******************************* MENU DE OPÇÕES *******************************/
	do{
		printf("**************************************\n");
		printf("*               MENU                 *\n");
		printf("1 - Buscar Registro\n");
		printf("2 - Inserir Registro\n");
		printf("3 - Mostrar Arvore-B\n");
		printf("4 - Sair\n");
		printf("Digite a opcao desejada:");
		scanf("%d",&opcao);
	
		switch(opcao){
			case 1:
				if(atoi(argv[3]) == 1){
					fp = fopen(argv[1], "r");
					printf("Digite a chave do arquivo a ser buscado: ");
					scanf("%s", chave);
					pos_reg = busca_arvB(T->raiz,chave,&seeks);
					pos_reg += strlen(chave) + 1;
					fseek(fp,pos_reg,SEEK_CUR);
					printf("O numero de seeks necessarios seria: %d\n", seeks);
					i = 0;
					do{
						printf("%s", reg->campos[i]);
						i++;
						fscanf(fp,"%c",&c);
						do{
							printf("%c", c);
							fscanf(fp,"%c",&c);
						}while(c != '\n' && c != ';' && !feof(fp));
						printf("\n");
					}while(i < 9);
					seeks = 0;
					rewind(fp);
					fclose(fp);
				} else {

				}
				break;
			case 2:
				if(atoi(argv[3]) == 1){
					fp = fopen(argv[1], "a");
					fputs("\n", fp);
					printf("Digite as informacoes do registro\n");
					printf("Digite a chave primaria:");
					scanf("%s", chave);
					insere_arvB(T,chave,&PRR);
					PRR+= (strlen(chave) + 1);
					fprintf(fp,"%s;",chave);
					PRR++;
					i = 0;
					do{
						printf("%s", reg->campos[i]);
						scanf(" %[^\n]s",aux);
						if(i != 8){
							fprintf(fp,"%s;", aux);
							PRR+= (strlen(aux) + 1);
						}else {
							fprintf(fp,"%s", aux);
							PRR += strlen(aux);
						}
						i++;
					}while(i<9);
					rewind(fp);
					fclose(fp);
				} else {

				}	
				//pos_reg nesse caso é uma posição após o ultimo registro e precisa ser calculada
				//insere_arvB(T,chave,&pos_reg);
				//break;
			//case 3: ;
				//Criar a função responsável por mostrar a arvore

		}

	}while(opcao != 4);

	free(chave);
	
	return 0;
}
