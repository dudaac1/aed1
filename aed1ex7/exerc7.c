#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
EXERCICIO 7
Programa semelhante ao exercício 3, sendo que este deve armazenar no máximo 10 pessoas.
Todas as variáveis que forem usadas devem ser ponteiros (com exceção da variável global Pessoa pessoas[10]),
os quais devem apontar para a variável void * pBuffer, onde os dados devem ser armazenados. 
*/

// estruturas
typedef struct pessoa {
    char nome[10];
    int idade;
    int altura;
} Pessoa;

Pessoa pessoas[10];

// constantes
#define INT sizeof(int)
#define ESCOLHA sizeof(char)
#define NOME sizeof(char)*10

// protótipos
void * adicionar(void * pBuffer);
void * remover(void * pBuffer);
void buscar(void * pBuffer);
void * buscarIndice(void * pBuffer);
void listar(void * pBuffer);
void erroAloc();

// funções
int main() {
    void * pBuffer = malloc(INT + ESCOLHA + INT + INT + NOME); // tam - escolha - busca - i - nome[10]
    if (pBuffer == NULL) erroAloc();
    *(int *)pBuffer = 0;
    char * escolha = (pBuffer + INT);

    do {
        printf("\n\t1) Adicionar pessoa\n");
        printf("\t2) Remover pessoa\n");
        printf("\t3) Buscar pessoa\n");
        printf("\t4) Listar pessoas\n");
        printf("\t5) Sair\n");
        printf("Insira sua escolha: ");
        scanf("%c", escolha);
        getchar();
        switch (*escolha) {
            case '1':
                pBuffer = adicionar(pBuffer);
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
    } while (*escolha != '5');
    return 0;
}

void * adicionar(void * pBuffer) {
    printf("\n\t # ADICIONANDO DADOS #\n");
    if (*(int*)pBuffer == 10) {
        printf("A lista de pessoas esta cheia.\n");
        return pBuffer;
    }

    int * tam = pBuffer;
    printf("Insira nome: ");
    scanf("%s[^\n]", pessoas[*tam].nome);
    getchar();

    do {
        printf("Insira idade (valor positivo): ");
        scanf("%d", &pessoas[*tam].idade);
        getchar();
    } while (pessoas[*tam].idade < 0);

    do {
        printf("Insira altura em centimetros (valor entre 0 e 300): ");
        scanf("%d", &pessoas[*tam].altura);
        getchar();
    } while (pessoas[*tam].altura < 0 || pessoas[*tam].altura > 300);

    (*tam)++;
    printf("\nDados adicionados.\n");
    return pBuffer;
}

void * remover(void *pBuffer) {
    printf("\n\t# REMOVENDO PESSOA #\n");
    pBuffer = buscarIndice(pBuffer);

    if (*(int*)(pBuffer + INT + ESCOLHA) == -1) {
        printf("Pessoa nao encontrada.\n");
        return pBuffer;
    }

    int * i = (pBuffer + INT + ESCOLHA + INT);
    int * busca = (pBuffer + INT + ESCOLHA);
    for (*i = *busca; *i < ((*(int*)pBuffer) - 1); (*i)++)
        pessoas[*i] = pessoas[*i + 1];

    (*(int*)pBuffer)--;
    printf("\nPessoa removida.\n");
    return pBuffer;
}

void buscar(void * pBuffer) {
    printf("\n\t# BUSCANDO PESSOA #\n");
    pBuffer = buscarIndice(pBuffer);
    int * busca = (pBuffer + INT + ESCOLHA);
    if (*busca == -1)
        printf("Pessoa nao encontrada.\n");
    else
        printf("%s, %d anos, %d cm.\n", pessoas[*busca].nome, pessoas[*busca].idade, pessoas[*busca].altura);
}

void * buscarIndice(void *pBuffer) {
    int  *tam = pBuffer;
    if (pBuffer == NULL) erroAloc();

    char * nome = (pBuffer + INT + ESCOLHA + INT + INT);
    printf("Insira o nome: ");
    scanf("%s", nome);
    getchar();

    if (*tam == 0) {
        *(int *)(pBuffer + INT + ESCOLHA) = -1;
        return pBuffer;
    }

    int * i = (pBuffer + INT + ESCOLHA + INT);
    for (*i = 0; *i < *tam; (*i)++) {
        if (strcmp(nome, pessoas[*i].nome) == 0) {
            *(int *)(pBuffer + INT + ESCOLHA) = *i; // busca = i e retorna
            return pBuffer;
        }
    }

    *(int *)(pBuffer + INT + ESCOLHA) = -1;
    return pBuffer;
}

void listar(void *pBuffer) {
    printf("\n\t # LISTANDO PESSOAS #\n");
    int *tam = pBuffer;
    if (*tam == 0) {
        printf("Nenhum dado encontrado.\n");
        return;
    }

    int *i = (pBuffer + INT + ESCOLHA);
    for (*i = 0; *i < *tam; (*i)++) {
        printf("\nNome: %s\n", pessoas[*i].nome);
        printf("Idade: %d anos\n", pessoas[*i].idade);
        printf("Altura: %d cm\n", pessoas[*i].altura);
    }
}

void erroAloc() {
    printf("Desculpe, tivemos um problema. \n");
    exit(1);
}