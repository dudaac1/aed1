#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa
{
    char nome[10];
    int idade;
    int altura;
} Pessoa;

Pessoa pessoas[10] = {};

void *adicionar(void *pBuffer);
void *remover(void *pBuffer);
void *buscar(void *pBuffer);
void listar(void *pBuffer);
void esperePeloEnter(void);

int main()
{
    void *pBuffer;
    pBuffer = malloc(sizeof(int) * 3 + sizeof(char) * 11);
    // int, char, int, int, char[10] = tam, escolha, busca, i, nome[10]

    if (pBuffer == NULL)
    {
        printf("Desculpa, tivemos um problema.\n");
        exit(1);
    }
    *(int *)pBuffer = 0;

    char *escolha = (pBuffer + sizeof(int));

    do
    {
        printf("\n\t1) Adicionar\n");
        printf("\t2) Remover\n");
        printf("\t3) Buscar\n");
        printf("\t4) Listar\n");
        printf("\t5) Sair\n");
        printf("Insira sua escolha: ");
        scanf(" %c", escolha);
        switch (*escolha)
        {
        case '1':
            printf("\n\t # ADICIONANDO DADOS #\n");
            pBuffer = adicionar(pBuffer);
            esperePeloEnter();
            break;
        case '2':
            printf("\n\t# REMOVENDO PESSOA #\n");
            pBuffer = remover(pBuffer);
            esperePeloEnter();
            break;
        case '3':
            printf("\n\t# BUSCANDO ALGUEM #\n");
            pBuffer = buscar(pBuffer);
            int *busca = (pBuffer + sizeof(int) + sizeof(char));
            if (*busca == -1)
            {
                printf("Esta pessoa nao foi encontrada.\n");
            }
            else
            {
                printf("%s, %d anos, %d cm.\n", pessoas[*busca].nome, pessoas[*busca].idade, pessoas[*busca].altura);
            }
            esperePeloEnter();
            break;
        case '4':
            printf("\n\t # LISTANDO PESSOAS #.\n");
            listar(pBuffer);
            esperePeloEnter();
            break;
        case '5':
            printf("Tchau!");
            free(pBuffer);
            exit(0);
        default:
            printf("Opcao nao reconhecida.\n");
            esperePeloEnter();
        }

    } while (*escolha != '5');
    return 0;
}

void *adicionar(void *pBuffer)
{
    int *tam = pBuffer;

    if (*tam == 10)
    {
        printf("A lista de pessoas esta cheia.\n");
        return pBuffer;
    }

    printf("Insira nome: ");
    scanf("%s[^\n]", pessoas[*tam].nome);

    printf("Insira idade: ");
    scanf("%d", &pessoas[*tam].idade);
    while (pessoas[*tam].idade < 0)
    {
        printf("Idade e positiva, insira outro valor: ");
        scanf("%d", &pessoas[*tam].idade);
        getchar();
    }

    printf("Insira altura (em centimetros): ");
    scanf("%d", &pessoas[*tam].altura);
    while (pessoas[*tam].altura < 0 || pessoas[*tam].altura > 300)
    {
        printf("Insira um valor de 0 a 300: ");
        scanf("%d", &pessoas[*tam].altura);
        getchar();
    }

    printf("Dados adicionados com sucesso!\n");

    *tam = *tam + 1;
    return pBuffer;
}

void *remover(void *pBuffer)
{
    pBuffer = buscar(pBuffer);

    int *busca = (pBuffer + sizeof(int) + sizeof(char));
    if (*busca == -1)
    {
        printf("Nao posso remover esta pessoa, pois ela nao esta na lista.\n");
        return pBuffer;
    }
    int *tam = pBuffer;

    if (*busca + 1 < *tam) // se busca+1 < tam || busca != 1
    {

        if (pBuffer == NULL)
        {
            printf("Desculpa, tivemos um problema.\n");
            exit(1);
        }
        int *i = (pBuffer + sizeof(int) + sizeof(char) + sizeof(int));

        for (*i = *busca; *i < *tam - 1; *i = *i + 1)
        {
            pessoas[*i] = pessoas[*i + 1];
        }
    }

    *tam = *tam - 1;
    printf("Pessoa removida com sucesso da lista!\n");
    return pBuffer;
}

void *buscar(void *pBuffer)
{
    int *tam = pBuffer;
    if (pBuffer == NULL)
    {
        printf("Desculpa, tivemos um problema.\n");
        exit(1);
    }

    char *nome = (pBuffer + sizeof(int) + sizeof(char) + sizeof(int) * 2);
    printf("Insira o nome: ");
    scanf("%s", nome);

    if (*tam == 0)
    {
        *(int *)(pBuffer + sizeof(int) + sizeof(char)) = -1;
        return pBuffer;
    }

    int *i = (pBuffer + sizeof(int) + sizeof(char) + sizeof(int));
    for (*i = 0; *i < *tam; *i = *i + 1)
    {
        if (strcmp(nome, pessoas[*i].nome) == 0)
        {
            *(int *)(pBuffer + sizeof(int) + sizeof(char)) = *i;
            return pBuffer;
        }
    }

    *(int *)(pBuffer + sizeof(int) + sizeof(char)) = -1;
    return pBuffer;
}

void listar(void *pBuffer)
{
    int *tam = pBuffer;
    if (*tam == 0)
    {
        printf("Nenhum dado encontrado.\n");
        return;
    }

    int *i = (pBuffer + sizeof(int) + sizeof(char));
    for (*i = 0; *i < *tam; *i = *i + 1)
    {
        printf("\nNome: %s\n", pessoas[*i].nome);
        printf("Idade: %d anos\n", pessoas[*i].idade);
        printf("Altura: %d cm\n", pessoas[*i].altura);
    }
}

void esperePeloEnter()
{
    printf("\nPressione ENTER para continuar... ");
    getchar();
    getchar();
}
