#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato
{
    char nome[10];
    int idade;
    long int telefone;
} Contato;

void *addContato(void *pBuffer);
void *removerContato(void *pBuffer);
int buscarContato(void *pBuffer);
void listarContatos(void *pBuffer);
void esperePeloEnter(void);

int main()
{
    char escolha;
    void *pBuffer;
    pBuffer = malloc(sizeof(int));
    if (pBuffer == NULL)
    {
        printf("Desculpa, tivemos um problema.\n");
        exit(1);
    }
    *(int *)pBuffer = 0;

    do
    {
        printf("\n\t1) Adicionar contato\n");
        printf("\t2) Remover contato\n");
        printf("\t3) Buscar contato\n");
        printf("\t4) Listar contatos\n");
        printf("\t5) Sair\n");
        printf("Insira sua escolha: ");
        scanf(" %c%*[^\n]", &escolha);
        switch (escolha)
        {
        case '1':
            printf("\n\t # ADICIONANDO CONTATO #\n");
            pBuffer = addContato(pBuffer);
            esperePeloEnter();
            break;
        case '2':
            printf("\n\t# REMOVENDO CONTATO #\n");
            pBuffer = removerContato(pBuffer);
            esperePeloEnter();
            break;
        case '3':
            printf("\n\t# BUSCANDO CONTATO #\n");
            int busca = buscarContato(pBuffer);
            if (busca == -1)
            {
                printf("Seu contato nao foi encontrado.\n");
            }
            else
            {
                Contato contatoBusca = *(Contato *)(pBuffer + sizeof(int) + sizeof(Contato) * busca);
                printf("\nCONTATO #%d\n", busca + 1);
                printf("%s - %d anos\n", contatoBusca.nome, contatoBusca.idade);
                printf("Telefone: %ld\n", contatoBusca.telefone);
            }
            esperePeloEnter();
            break;
        case '4':
            printf("\n\t # LISTANDO CONTATOS #.\n");
            listarContatos(pBuffer);
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

    } while (escolha != '5');
    return 0;
}

void *addContato(void *pBuffer)
{
    getchar(); 

    Contato novoContato;
    printf("Insira nome: ");
    scanf("%s[^\n]", novoContato.nome);
    printf("Insira idade: ");
    scanf("%d", &novoContato.idade);
    printf("Insira telefone: ");
    scanf("%ld", &novoContato.telefone);

    int tamanho = *(int *)pBuffer;
    tamanho++;
    pBuffer = realloc(pBuffer, sizeof(int) + (sizeof(Contato) * tamanho));
    if (pBuffer == NULL)
    {
        printf("Desculpe, tivemos um problema.\n");
        exit(1);
    }

    if (tamanho == 1)
    {
        *(Contato *)(pBuffer + sizeof(int)) = novoContato;
    }
    else
    {
        *(Contato *)(pBuffer + sizeof(int) + (tamanho - 1) * sizeof(Contato)) = novoContato;
    }

    *(int *)pBuffer = tamanho;
    printf("Contato adicionado com sucesso.\n");

    return pBuffer;
}

void *removerContato(void *pBuffer)
{
    int tamanho = *(int *)pBuffer;

    int busca = buscarContato(pBuffer);
    if (busca == -1)
    {
        printf("Nao foi achado nenhum contato com este nome.\n");
        return pBuffer;
    }

    Contato contatoRemover = *(Contato *)(pBuffer + sizeof(int) + sizeof(Contato) * busca);
    if (busca + 1 < tamanho)
    {
        Contato proxContato;
        for (int i = busca; i < tamanho - 1; i++)
        {
            proxContato = *(Contato *)(pBuffer + sizeof(int) + sizeof(Contato) * (i + 1)); //recebe o prox
            *(Contato *)(pBuffer + sizeof(int) + sizeof(Contato) * i) = proxContato; //sobrepoem o anterior
        }
    }

    tamanho--;
    *(int *)pBuffer = tamanho;

    pBuffer = realloc(pBuffer, sizeof(int) + sizeof(Contato) * tamanho);
    if (pBuffer == NULL)
    {
        printf("Desculpe, tivemos um problema.\n");
        exit(1);
    }

    printf("Contato removido com sucesso!\n");

    return pBuffer;
}

int buscarContato(void *pBuffer)
{
    getchar();
    int tamanho = *(int *)pBuffer;

    char nome[10];
    printf("Insira nome: ");
    scanf("%s[^\n]", nome);

    if (!tamanho)
    {
        return -1;
    }

    Contato contatoAtual;
    for (int i = 0; i < tamanho; i++)
    {
        contatoAtual = *(Contato *)(pBuffer + sizeof(int) + i * sizeof(Contato));
        if (strcmp(contatoAtual.nome, nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

void listarContatos(void *pBuffer)
{
    int tamanho = *(int *)pBuffer;
    if (tamanho == 0)
    {
        printf("Nenhum contato para listar.\n");
        return;
    }

    printf("Tem %d contato(s) cadastrado(s).\n", tamanho);
    printf("Insira a quantidade de contatos que deseja listar: ");
    int quant;
    scanf(" %d", &quant);
    while (quant < 1 || quant > tamanho)
    {
        printf("Voce precisa digitar um valor valido, ou seja, de 1 ate %d: ", tamanho);
        scanf(" %d", &quant);
    }

    Contato contatoAtual;
    for (int i = 0; i < quant; i++)
    {
        contatoAtual = *(Contato *)(pBuffer + sizeof(int) + (sizeof(Contato) * i));
        printf("\n\tCONTATO #%d\n", i + 1);
        printf("Nome: %s\n", contatoAtual.nome);
        printf("Idade: %d\n", contatoAtual.idade);
        printf("Telefone: %ld\n", contatoAtual.telefone);
    }
}

void esperePeloEnter()
{
    printf("\nPressione ENTER para continuar... ");
    getchar();
    getchar();
}