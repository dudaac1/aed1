#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
EXERCICIO 3
Fazer uma agenda que inclua, apague, busque e liste quantas pessoas o usuário desejar.
Toda a informação da agenda deve ficar em uma única variável: void * pBuffer (usar manipulação de memória).
Não perguntar ao usuario quantas pessoas serão incluídas.
Cada pessoa tem nome, idade e telefone.
*/

// estruturas
typedef struct pessoa {
	char nome[10];
	int idade;
	long int telefone;
} Pessoa;

// constantes
#define INT sizeof(int)
#define PESSOA sizeof(Pessoa)

// prototipos
void * inserir(void * pBuffer);
void * remover(void * pBuffer);
void buscar(void * pBuffer);
int buscarIndice(void * pBuffer);
void listar(void * pBuffer);
void erroAloc();

// funções
int main() {
	char escolha;
	void *pBuffer = malloc(INT);
	if (pBuffer == NULL) erroAloc();
	*(int *)pBuffer = 0;

	do {
		printf("\n\t1) Adicionar pessoa\n");
		printf("\t2) Remover pessoa\n");
		printf("\t3) Buscar pessoa\n");
		printf("\t4) Listar pessoas\n");
		printf("\t5) Sair\n");
		printf("Insira sua escolha: ");
		scanf(" %c[^\n]", &escolha);
		getchar();
		switch (escolha) {
			case '1':
				pBuffer = inserir(pBuffer);
				break;
			case '2':
				pBuffer = remover(pBuffer);
				break;
			case '3':
				buscar(pBuffer);
				break;
			case '4':
				listar(pBuffer);
				break;
			case '5':
				printf("Tchau!");
				free(pBuffer);
				exit(0);
			default:
				printf("Opcao nao reconhecida.\n");
		}
		printf("\nPressione ENTER para continuar... ");
		getchar();
	} while (escolha != '5');
	return 0;
}

void * inserir(void * pBuffer) {
	printf("\n\t # ADICIONANDO PESSOA #\n");
	Pessoa novaPessoa;
	printf("Insira nome: ");
	scanf("%s[^\n]", novaPessoa.nome);
	printf("Insira idade: ");
	scanf("%d", &novaPessoa.idade);
	printf("Insira telefone: ");
	scanf("%ld", &novaPessoa.telefone);
	getchar();

	int tamanho = *(int *)pBuffer;
	pBuffer = realloc(pBuffer, INT + PESSOA * (tamanho + 1));
	if (pBuffer == NULL) erroAloc();
	*(Pessoa *)(pBuffer + INT + tamanho * PESSOA) = novaPessoa;
	(*(int*)pBuffer)++;
	printf("Pessoa adicionada com sucesso.\n");

	return pBuffer;
}

void * remover(void * pBuffer) {
	printf("\n\t--- REMOVENDO PESSOA ---\n");
	int indice = buscarIndice(pBuffer);
	if (indice == -1) {
		printf("Pessoa nao encontrada.\n");
		return pBuffer;
	}

	int * tamanho = (int *)pBuffer;
	Pessoa pessoaRemover = *(Pessoa *)(pBuffer + INT + PESSOA * indice);
	if (indice + 1 < *tamanho) {
		Pessoa proxPessoa;
		for (int i = indice; i < (*tamanho - 1); i++) {
			proxPessoa = *(Pessoa *)(pBuffer + INT + PESSOA * (i + 1)); //recebe o prox
			*(Pessoa *)(pBuffer + INT + PESSOA * i) = proxPessoa;			 //sobrepoem o anterior
		}
	}
	(*tamanho)--;
	pBuffer = realloc(pBuffer, INT + PESSOA * (*tamanho));
	if (pBuffer == NULL) erroAloc();
	printf("Pessoa removida com sucesso!\n");

	return pBuffer;
}

void buscar(void *pBuffer) {
	printf("\n\t--- BUSCANDO PESSOA ---\n");
	int indice = buscarIndice(pBuffer);
	if (indice == -1)
		printf("Pessoa nao encontrada.\n");
	else {
		Pessoa pessoaBusca = *(Pessoa *)(pBuffer + INT + PESSOA * indice);
		printf("\nPESSOA #%d\n", indice + 1);
		printf("%s - %d anos\n", pessoaBusca.nome, pessoaBusca.idade);
		printf("Telefone: %ld\n", pessoaBusca.telefone);
	}
}

int buscarIndice(void * pBuffer) {
	char nome[10];
	printf("Insira nome: ");
	scanf("%s[^\n]", nome);
	getchar();

	if (!(*(int *)pBuffer)) // if (tamanho == 0)
		return -1;

	Pessoa pessoaAtual;
	for (int i = 0; i < (*(int *)pBuffer); i++) {
		pessoaAtual = *(Pessoa *)(pBuffer + INT + PESSOA * i);
		if (strcmp(pessoaAtual.nome, nome) == 0)
			return i;
	}

	return -1;
}

void listar(void *pBuffer) {
	printf("\n\t--- LISTANDO PESSOAS ---\n");
	if (!(*(int *)pBuffer)) { //if (tamanho == 0)
		printf("Nenhum pessoa para listar.\n");
		return;
	}
	Pessoa pessoaAtual;
	for (int i = 0; i < (*(int *)pBuffer); i++) {
		pessoaAtual = *(Pessoa *)(pBuffer + INT + (PESSOA * i));
		printf("\n\tPESSOA #%d\n", i + 1);
		printf("Nome: %s\n", pessoaAtual.nome);
		printf("Idade: %d\n", pessoaAtual.idade);
		printf("Telefone: %ld\n", pessoaAtual.telefone);
	}
}

void erroAloc() {
	printf("Desculpe, tivemos um problema.");
	exit(1);
}