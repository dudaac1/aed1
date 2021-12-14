#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
EXERCICIO 5
Programa que armazene informações de várias pessoas (struct: char nome[30]; int idade; int altura;).
O programa só sai quando o usuário não desejar incluir mais pessoas.
Antes de sair, mostrar os dados de todas as pessoas
*/

// constantes
#define MAX_NOME 30

// estruturas
typedef struct pessoa {
	char nome[MAX_NOME];
	int idade;
	int altura;
} Pessoa;

typedef struct lista {
	Pessoa * pessoas;
	int quantidade;
} Lista;

// protótipos
Lista inserir(Lista lista);
void listar(Lista lista);

// funções
int main() {
	Lista lista;
	lista.pessoas = NULL;
	lista.quantidade = 0;

	char escolha;
	do {
		printf("Inserir dados de uma pessoa? (1) Sim - (2) Nao:  ");
		scanf("%c[^\n]", &escolha);
		getchar();
		switch (escolha) {
			case '1':
				lista = inserir(lista);
				break;
			case '2':
				listar(lista);
				free(lista.pessoas);
				printf("\nTchau!");
				exit(0);
		default:
			printf("Opcao nao reconhecida.\n");
			break;
		}
	} while (escolha != '2');
}

Lista inserir(Lista lista) {
	printf("\n\t# INSERINDO NOVA PESSOA #\nDigite nome: ");
	Pessoa novaPessoa;
	char letra;
	int i;
	for (i = 0; (letra = getchar()) != '\n'; i++)
		if (i < MAX_NOME)
			novaPessoa.nome[i] = letra;
	if (i >= MAX_NOME)
		i = MAX_NOME - 1;
	novaPessoa.nome[i] = '\0';
	if (strlen(novaPessoa.nome) == 0) {
		printf("Palavras vazias nao sao nomes.\n");
		return lista;
	}

	do {
		printf("Digite idade (valor positivo): ");
		scanf("%d", &novaPessoa.idade);
		getchar();
	} while (novaPessoa.idade < 0);

	do {
		printf("Digite altura em centimetros (valor entre 0 e 300): ");
		scanf("%d", &novaPessoa.altura);
		getchar();
	} while (novaPessoa.altura < 0 || novaPessoa.altura > 300);

	lista.quantidade++;
	lista.pessoas = (Pessoa *)realloc(lista.pessoas, lista.quantidade * sizeof(Pessoa));
	if (lista.pessoas == NULL) {
		printf("Desculpe, tivemos um problema.");
		exit(1);
	}
	lista.pessoas[lista.quantidade-1] = novaPessoa;
	printf("Novos dados incluido na lista.\n\n");
	return lista;
}

void listar(Lista lista) {
	printf("\n\t# LISTANDO PESSOAS #\n");
	if (!lista.quantidade) 
		printf("Nenhum dado encontrado.\n\n");
	else 
		for (int i = 0; i < lista.quantidade; i++) {
			printf("Nome: %s\n", lista.pessoas[i].nome);
			printf("Idade: %d\n", lista.pessoas[i].idade);
			printf("Altura: %d\n\n", lista.pessoas[i].altura);
		}

	printf("Pressione ENTER para continuar... ");
	getchar();
}