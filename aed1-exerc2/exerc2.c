#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inserirNome(void);
void removerNome(void);
void listarNomes(void);
void esperePeloEnter(void);

char *listaNomes;
int tamListaNomes = 0;

int main()
{
	listaNomes = malloc(sizeof(char));
	if (listaNomes == NULL)
	{
		printf("Desculpe, tivemos um problema.");
		exit(1);
	}
	
	char option;
	do {

		printf("\n\t1) Adicionar nome\n");
		printf("\t2) Remover nome\n");
		printf("\t3) Listar\n");
		printf("\t4) Sair\n");
		printf("Insira sua escolha: ");
		scanf(" %c%*[^\n]", &option);
		switch (option)
		{
		case '1':
			printf("\n--- ADICIONANDO NOME ---\n");
			inserirNome();
			esperePeloEnter();
			break;

		case '2':
			printf("\n--- REMOVENDO NOME ---\n");
			removerNome();
			esperePeloEnter();
			break;

		case '3':
			printf("\n--- LISTANDO NOMES ---\n");
			listarNomes();
			esperePeloEnter();
			break;

		case '4':
			printf("Tchau!");
			free(listaNomes);
			exit(0);

		default:
			printf("Opcao nao reconhecida.\n");
			esperePeloEnter();
		}
	} while (option != '4');
}

void inserirNome()
{
	getchar();
	printf("Insira o nome: ");
	char nomeIn[51] = {""}, letra;
	int i = 0;
	while (((letra = getchar()) != '\n') && i < 50)
	{
		nomeIn[i] = letra;
		i++;
	}
	if (i == 50) //para remover caracteres excedentes
	{
		while ((letra = getchar()) != '\n' && letra != EOF)
		{
		}
		i--;
	}

	if (strlen(nomeIn) == 0) {
		printf("Palavras vazias nao sao nomes.\n");
		return;
	}

	nomeIn[i] = '#';
	nomeIn[++i] = '\0';
	int tamAnterior = tamListaNomes;
	tamListaNomes += strlen(nomeIn);
	listaNomes = (char *)realloc(listaNomes, tamListaNomes * sizeof(char));
	if (listaNomes == NULL)
	{
		printf("Desculpe, tivemos um problema.");
		exit(1);
	}
	for (int i = tamAnterior; i < tamListaNomes; i++)
	{
		listaNomes[i] = nomeIn[i - tamAnterior];
	}
	printf("O nome foi inserido na lista.\n");
}

void removerNome()
{
	getchar();
	printf("Qual nome voce deseja remover: ");
	char nomeDel[51] = {""}, letra;
	int i = 0;
	while (((letra = getchar()) != '\n') && i < 50)
	{
		nomeDel[i] = letra;
		i++;
	}
	
	if (i == 50)//para remover caracteres excedentes
	{
		while ((letra = getchar()) != '\n' && letra != EOF)
		{
		}
		i--;
	}

	if (strlen(nomeDel) == 0) {
		printf("Palavras vazias nao sao nomes.\n");
		return;
	}

	nomeDel[i] = '#';
	nomeDel[++i] = '\0';

	int nomeRemovido = 0;
	for (i = 0; i < tamListaNomes; i++)
	{
		if (listaNomes[i] == nomeDel[0])
		{
			char *nomeAcum; //para acumular letras iguais ao de nomeDel
			int tamNomeAcum = 0;
			nomeAcum = (char *)malloc(sizeof(char));
			if (nomeAcum == NULL)
			{
				printf("Desculpe, tivemos um problema.");
				exit(1);
			}
			int tamNomeDel = strlen(nomeDel);
			for (int j = i; j < i + tamNomeDel; j++)
			{
				if (listaNomes[j] != nomeDel[j - i])
				{
					break;
				}

				tamNomeAcum++;
				nomeAcum = (char *)realloc(nomeAcum, sizeof(char) * tamNomeAcum + 1); //+1 p drmemory n dar erro
				if (nomeAcum == NULL)
				{
					printf("Desculpe, tivemos um problema.");
					exit(1);
				}
				nomeAcum[tamNomeAcum - 1] = listaNomes[j];
			}
			nomeAcum[tamNomeAcum] = '\0';
			if (strcmp(nomeDel, nomeAcum) == 0)
			{
				for (int j = i; j < tamListaNomes - 1; j++)
				{
					//se a letra a ser inserida é maior que a quant de letras na lista, quebra o loop
					if (j + tamNomeDel > tamListaNomes)
					{
						break;
					}
					listaNomes[j] = listaNomes[j + tamNomeDel];
				}
				tamListaNomes -= tamNomeDel;
				listaNomes = (char *)realloc(listaNomes, sizeof(char) * tamListaNomes);
				if (listaNomes == NULL && tamListaNomes != 0)
				{
					printf("Desculpe, tivemos um problema.");
					exit(1);
				}
				printf("O nome foi removido!\n");
				nomeRemovido = 1;
				free(nomeAcum);
				break;
			}
			free(nomeAcum);
		}
	}
	if (nomeRemovido == 0 && i == tamListaNomes)
	{
		printf("Nenhum nome semelhante foi encontrado para remocao.\n");
	}
}

void listarNomes()
{
	getchar();
	if (tamListaNomes == 0) {
		printf("Nenhum nome encontrado.\n");
		return;
	}

	for (int i = 0; i < tamListaNomes; i++)
	{
		if (listaNomes[i] != '#')
		{
			printf("%c", listaNomes[i]);
		}
		else
		{
			printf("\n");
		}
	}
}

void esperePeloEnter()
{
	printf("\nPressione ENTER para continuar... ");
	getchar();
}