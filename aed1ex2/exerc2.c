#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
EXERCICIO 2
Programa que armazena nomes, estando TODOS na mesma string.
O tamanho da string deve crescer/diminuir conforme demanda, sem desperdicio de memoria.
Utilizar menu: adicionar nome, remover nome, listar, sair.
*/

// constantes
#define MAX_NOME 100

// estruturas
typedef struct nome {
	char * letras;
	int tamanho;
} Nome;

// prototipos
Nome inserir(Nome lista);
Nome remover(Nome lista);
void listar(Nome lista);
Nome lerNome(Nome nome, char * funcao); 
void erroAloc(void);

// funções
int main() {
	Nome lista;
	lista.letras = NULL;
	lista.tamanho = 0;	
	char escolha;
	do {
		printf("\n\t1) Adicionar nome\n");
		printf("\t2) Remover nome\n");
		printf("\t3) Listar nomes\n");
		printf("\t4) Sair\n");
		printf("Insira sua escolha: ");
		scanf("%c[^\n]", &escolha);
		getchar();
		switch (escolha) {
			case '1':
				lista = inserir(lista);
				break;
			case '2':
				lista = remover(lista);
				break;
			case '3':
				listar(lista);
				break;
			case '4':
				printf("Tchau!");
				free(lista.letras); 
				exit(0);
			default:
				printf("Opcao nao reconhecida.\n");
		}
		printf("\nPressione ENTER para continuar... ");
		getchar();	
	} while (escolha != '4');
}

Nome inserir(Nome lista) {
	printf("\n--- ADICIONANDO NOME ---\n");
	Nome nome = lerNome(nome, "inserir");

	if (nome.tamanho == 1) { // "#"
		printf("Palavras vazias nao sao nomes.\n");
		free(nome.letras);
		return lista;
	}

	lista.tamanho += nome.tamanho;
	lista.letras = (char *)realloc(lista.letras, lista.tamanho * sizeof(char));
	if (lista.letras == NULL) erroAloc();
	for (int i = lista.tamanho - nome.tamanho, j = 0; i < lista.tamanho; i++, j++)
		lista.letras[i] = nome.letras[j];
	free(nome.letras);
	printf("O nome foi inserido na lista.\n");
	return lista;
}

Nome remover(Nome lista) {
	printf("\n--- REMOVENDO NOMES ---\n");
	Nome nome = lerNome(nome, "remover");

	if (nome.tamanho == 1) { // "#"
		printf("Palavras vazias nao sao nomes.\n");
		free(nome.letras);
		return lista;
	}

	char * pontNome = strstr(lista.letras, nome.letras);
	if (pontNome == NULL) {
		printf("Nome nao encontrado.\n");
		free(nome.letras);
		return lista;
	}

	int tamResto = strlen(pontNome) - nome.tamanho;
	lista.tamanho -= nome.tamanho;
	if (lista.tamanho != 0) {
		int i;
		for (i = 0; i < tamResto; i++) 
			pontNome[i] = pontNome[i + nome.tamanho];
		pontNome[i] = '\0';
	}

	lista.letras = (char *)realloc(lista.letras, (lista.tamanho+1) * sizeof(char));
	free(nome.letras);
	printf("Nome removido.\n");
	return lista;
}

void listar(Nome lista) {
	printf("\n--- LISTANDO NOMES ---\n");
	if (lista.tamanho == 0) {
		printf("Nenhum nome encontrado.\n");
		return;
	}
	for (int i = 0; i < lista.tamanho; i++)
	{
		if (lista.letras[i] != '#')
			printf("%c", lista.letras[i]);
		else
			printf("\n");
	}
}

Nome lerNome(Nome nome, char * funcao) {
	nome.letras = (char *)malloc(sizeof(char) * (MAX_NOME+1));
	if (nome.letras == NULL) erroAloc();
	printf("Qual nome voce deseja %s: ", funcao);
 	char letra;
	int i;
	for (i = 0; (letra = getchar()) != '\n'; i++)
		if (i < MAX_NOME)
			nome.letras[i] = letra;
	if (i >= MAX_NOME)
		i = MAX_NOME - 1;
	nome.letras[i++] = '#';
	nome.letras[i] = '\0';
	nome.tamanho = i;
	return nome;
}

void erroAloc() {
	printf("Desculpe, tivemos um problema.");
	exit(1);
}