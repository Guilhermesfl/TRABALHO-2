#include <stdio.h>
#include <stdlib.h>
#include <FUNC.h>
#include <string.h>

int main(int argc, char const *argv[])
{

	FILE *fp;
	arvB *T;
	REG1 *reg1;
	REG2 *reg2;
	int opcao,pos_reg,num_reg=0,PRR=0,NRR=0,seeks=0,i,verificador=0,pagina=0, regulador = 0, regulador2 = 0;
	int numerador = 1,j,k;
	char *chave,*aux, c;
	no *no_aux;
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
	/* Alocação, Indexação e Inicialização da arvore B */

	T = cria_arvB(T);
	
	if(atoi(argv[3]) == 1) // Registros de tamanho variável com CP de tamanho fixo
	{
		reg1 = preenche_reg1(reg1);
		verificador = 1;
		chave = (char *)malloc(7*sizeof(char));	
		do
		{
			fread(chave,1,7,fp);
			T = insere_arvB(T,chave,&PRR,&regulador);
			PRR+=7;
			do{		
				fscanf(fp,"%c",&c);
				PRR++;
			} while(c != '\n' && !feof(fp));
		}while(!feof(fp));
	} else { // Registros de tamanho fixo
		reg2 = preenche_reg2(reg2);
		verificador = 2;
		chave = (char *)malloc(4*sizeof(char));	
		do
		{
			fread(chave,1,4,fp);	
			NRR++;
			T = insere_arvB(T,chave,&NRR,&regulador);
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
				if(verificador == 1){
					fp = fopen("data1.txt", "r");
					printf("Digite a chave do arquivo a ser buscado: ");
					scanf("%s", aux);
					pos_reg = busca_arvB(T->raiz,aux,&seeks);
					if(pos_reg == -1){
						printf("Essa chave nao existe\n");
						return 0;
					}
					pos_reg = pos_reg + strlen(aux) + 1;
					fseek(fp,pos_reg,SEEK_CUR);
					printf("O numero de seeks necessarios seria: %d\n", seeks);
					i = 0;
					do{
						printf("%s", reg1->campos[i]);
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
					fp = fopen("data2.txt", "r");
					printf("Digite a chave do arquivo a ser buscado: ");
					scanf("%s", chave);
					if(strlen(chave) != 4){
						printf("Essa chave nao existe\n");
						break;
					} else {
						pos_reg = busca_arvB(T->raiz,chave,&seeks);
						if(pos_reg == -1){
							printf("Essa chave nao existe\n");
							break;
						} else {
							printf("O numero de seeks necessarios seria: %d\n", seeks);
							if(pos_reg < 47)fseek(fp,(pos_reg-1)*123+5,SEEK_CUR);
							else fseek(fp,(pos_reg-1)*123+2,SEEK_CUR);
							i = 0;
							fscanf(fp,"%c",&c);
							do{
								j=0;
								printf("%s", reg2->campos[i]);
								printf("%c", c);
								fscanf(fp,"%c",&c);
								i++;
								do{
									printf("%c", c);
									fscanf(fp,"%c",&c);
									if(c == ' ')
									{	
										fscanf(fp,"%c",&c);
										if(c == ' ')
										{
											while(c == ' ') fscanf(fp,"%c",&c);
											j=1;
										} else {
											printf(" ");
										}
									}
								}while(j != 1);
								printf("\n");
							}while(i < 3);
							seeks = 0;
							rewind(fp);
							fclose(fp);
						}
					}
				}
				break;

			case 2:
				if(verificador == 1){
					fp = fopen("data1.txt", "a");
					fputs("\n", fp);
					printf("Digite as informacoes do registro\n");
					printf("Digite a chave primaria:");
					scanf("%s", aux);
					getchar();
					insere_arvB(T,aux,&PRR,&regulador);
					PRR = PRR + strlen(chave) + 1;
					fprintf(fp,"%s;",aux);
					i = 0;
					do{
						printf("%s", reg1->campos[i]);
						scanf("%[^\n]s", aux);
						getchar();
						if(i != 8) fprintf(fp,"%s;", aux);
						else fprintf(fp,"%s", aux);
						PRR=PRR+strlen(aux)+1;
						i++;
					}while(i<9);
					rewind(fp);
					fclose(fp);
				} else {
					fp = fopen("data2.txt", "a");
					fputs("\n", fp);
					printf("Digite as informacoes do registro\n");
					printf("Digite a chave primaria:");
					scanf("%s", aux);
					if(strlen(aux) != 4)
					{
						printf("Tamanho de chave invalido!\n");
						break;
					}
					getchar();
					NRR++;
					insere_arvB(T,aux,&NRR,&regulador);
					fprintf(fp,"%s ",aux);
					i = 0;
					do{
						printf("%s", reg2->campos[i]);
						scanf("%[^\n]s", aux);
						getchar();
						fprintf(fp,"%s", aux);
						if(i==0){
							for(j=strlen(aux);j<69;j++) fprintf(fp,"%s"," ");
						} else if (i ==1){
							for(j=strlen(aux);j<22;j++) fprintf(fp,"%s"," ");
						} else{
							for(j=strlen(aux);j<25;j++) fprintf(fp,"%s"," ");
						} 
						i++;
					}while(i<3);
					rewind(fp);
					fclose(fp);
				}	
				break;

			case 3:
				imprime_arvB(T->raiz);
				break;

			default:

				break;
				
		}	
	}while(opcao != 4);
	
	return 0;
}