#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structs
typedef struct contact
{ //dados
    char name[10];
    int age;
    long int phone;
} Data;

typedef struct item
{ //nodo
    Data data;
    struct item *next;
    struct item *prev;
} Item;

typedef struct info
{ //sentinela
    unsigned int quant;
    Item *first;
    Item *last;
} InfoList;

// protótipos
void Menu(void);
void *Insert(void *pBuffer);
void *Delete(void *pBuffer);
void Search(void *pBuffer);
void ListOrdered(void *pBuffer);
void *sortListByName(Item *first, void *pBuffer);
void *sortListByAge(Item *first, void *pBuffer);
void List(void *pBuffer);
void *EndProgram(void *pBuffer);
void PressEnter(void);

// principal
int main()
{
    void *pBuffer;
    // InfoList contactList + char option + int i + char nome[10] + Data contact
    pBuffer = malloc(sizeof(InfoList) + sizeof(char) * 11 + sizeof(int) + sizeof(Data));
    if (!pBuffer)
    {
        printf("Desculpa, tivemos um problema.\n");
        exit(1);
    }

    InfoList *contactList;
    contactList = pBuffer;
    contactList->first = NULL;
    contactList->last = NULL;
    contactList->quant = 0;

    char *option = (pBuffer + sizeof(InfoList));
    do
    {
        Menu();
        scanf(" %c", option);
        getchar();
        switch (*option)
        {
        case '1':
            printf("\n-- INSERINDO CONTATO --\n");
            pBuffer = Insert(pBuffer);
            PressEnter();
            break;
        case '2':
            printf("\n-- REMOVENDO CONTATO --\n");
            pBuffer = Delete(pBuffer);
            PressEnter();
            break;
        case '3':
            printf("\n-- BUSCANDO CONTATO --\n");
            Search(pBuffer);
            PressEnter();
            break;
        case '4':
            printf("\n-- LISTANDO CONTATOS --\n");
            ListOrdered(pBuffer);
            PressEnter();
            break;
        case '5':
            pBuffer = EndProgram(pBuffer);
            free(pBuffer);
            exit(0);
        default:
            printf("Opcao nao reconhecida.\n");
            PressEnter();
        }
    } while (*option != '5');
}

// funções
void Menu()
{
    printf("\n\t(1) Adicionar contato\n");
    printf("\t(2) Remover contato\n");
    printf("\t(3) Buscar contato\n");
    printf("\t(4) Listar contatos\n");
    printf("\t(5) Sair\n");
    printf("Insira sua escolha: ");
}

void *Insert(void *pBuffer)
{
    InfoList *contactList = pBuffer;

    Data *contact = (pBuffer + sizeof(InfoList) + sizeof(char) * 11 + sizeof(int));
    printf("Insira nome: ");
    scanf(" %s", contact->name);
    getchar();
    printf("Insira idade: ");
    scanf("%d", &contact->age);
    while (contact->age < 0)
    {
        printf("Idade e positiva. Insira outro valor: ");
        scanf("%d", &contact->age);
    }
    getchar();
    printf("Insira telefone: ");
    scanf("%ld", &contact->phone);
    getchar();

    if (!contactList->quant)
    { //se quant = 0
        contactList->first = (Item *)malloc(sizeof(Item));
        if (!contactList->first)
        {
            printf("Desculpa, tivemos um problema.\n");
            exit(1);
        }

        contactList->first->data = *contact;
        contactList->first->next = NULL;
        contactList->first->prev = NULL;
        contactList->last = contactList->first;
    }
    else
    {
        Item *novoContato = (Item *)malloc(sizeof(Item));
        if (!novoContato)
        {
            printf("Desculpa, tivemos um problema.\n");
            exit(1);
        }

        novoContato->data = *contact;
        novoContato->next = NULL; //novo contato adicionado no final, então n aponta para ninguem a seguir

        if (contactList->quant == 1)
        {                                           //se quant = 1
            contactList->first->next = novoContato; //primeiro contato aponta para novo contato
            novoContato->prev = contactList->first; //anterior de novo contato aponta para primeiro
        }
        else
        {                                          //se quant > 1
            novoContato->prev = contactList->last; //anterior de novo contato aponta pro ultimo
            contactList->last->next = novoContato; //prox do ultimo contato aponta para novo [ultimo] contato
        }
        contactList->last = novoContato; //adiciona o novo contato sempre no final
    }
    contactList->quant++;
    return pBuffer;
}

void *Delete(void *pBuffer)
{
    InfoList *contactList = pBuffer;

    char *name = (pBuffer + sizeof(InfoList) + sizeof(char) + sizeof(int));
    printf("Insira nome: ");
    scanf(" %s", name);
    getchar();

    if (contactList->quant == 0)
    {
        printf("Contato nao encontrado.\n");
        return pBuffer;
    }

    int *i = (pBuffer + sizeof(InfoList) + sizeof(char));
    Item *currentContact = contactList->first;

    *i = 0;
    while (*i < contactList->quant)
    {
        if (strcmp(currentContact->data.name, name) == 0)
        {
            //se quant = 1, first = last = NULL
            if (contactList->quant == 1)
            {
                contactList->first = NULL;
                contactList->last = NULL;
            }
            else
            {
                //se remover = inicio, inicio <= prox, inicio.prev = NULL;
                if (currentContact == contactList->first)
                {
                    contactList->first = contactList->first->next;
                    contactList->first->prev = NULL;
                }
                else if (currentContact == contactList->last)
                {
                    //se remover = fim, fim <= prev, fim.next = NULL;
                    contactList->last = contactList->last->prev;
                    contactList->last->next = NULL;
                }
                else
                {
                    //se não atual.anterior.prox = atual.prox
                    //       atual.proximo.prev = atual.prev
                    currentContact->prev->next = currentContact->next;
                    currentContact->next->prev = currentContact->prev;
                }
            }
            free(currentContact);
            contactList->quant--;
            printf("Contato removido com sucesso.\n");
            return pBuffer;
        }
        currentContact = currentContact->next;
        *i = *i + 1;
    }

    printf("Contato nao encontrado.\n");
    return pBuffer;
}

void Search(void *pBuffer)
{
    InfoList *contactList = pBuffer;

    char *name = (pBuffer + sizeof(InfoList) + sizeof(char) + sizeof(int));
    printf("Insira nome: ");
    scanf(" %s", name);
    getchar();

    if (contactList->quant == 0)
    {
        printf("Contato nao encontrado.\n");
        return;
    }

    int *i = (pBuffer + sizeof(InfoList) + sizeof(char));
    Item *currentContact = contactList->first;

    *i = 0;
    while (*i < contactList->quant)
    {
        if (strcmp(currentContact->data.name, name) == 0)
        {
            printf("%s - %d anos\n", currentContact->data.name, currentContact->data.age);
            printf("Telefone: %ld\n", currentContact->data.phone);
            return;
        }
        currentContact = currentContact->next;
        *i = *i + 1;
    }

    printf("Contato nao encontrado.\n");
}

void ListOrdered(void *pBuffer)
{
    InfoList *contactList = pBuffer;
    if (contactList->quant == 0)
    {
        printf("Nenhum contato para listar.\n");
        return;
    }

    if (contactList->quant == 1)
    {
        List(pBuffer);
        return;
    }

    char *option = (pBuffer + sizeof(InfoList));
    printf("Voce deseja listar seus contatos ordenados por: \n");
    printf("\t(1) Nome\n");
    printf("\t(2) Idade\n");
    printf("Insira sua escolha: ");
    scanf(" %c", option);
    getchar();
    switch (*option)
    {
    case '1':
        pBuffer = sortListByName(contactList->first, pBuffer);
        break;
    case '2':
        pBuffer = sortListByAge(contactList->first, pBuffer);
        break;
    default:
        printf("Opcao nao reconhecida.\n");
        printf("Estamos retornando ao Menu Principal.\n");
        PressEnter();
        return;
    }
    List(pBuffer);
}

void *sortListByName(Item *first, void *pBuffer)
{
    Item *current = NULL, *next = NULL;
    Data *temp = (pBuffer + sizeof(InfoList) + sizeof(char) * 11 + sizeof(int));
    for (current = first; current->next != NULL; current = current->next)
    {
        for (next = current->next; next != NULL; next = next->next)
        {
            if (strcmp(current->data.name, next->data.name) > 0)
            {
                *temp = current->data;
                current->data = next->data;
                next->data = *temp;
            }
        }
    }
    return pBuffer;
}

void *sortListByAge(Item *first, void *pBuffer)
{
    Item *current = NULL, *next = NULL;
    Data *temp = (pBuffer + sizeof(InfoList) + sizeof(char) * 11 + sizeof(int));
    for (current = first; current->next != NULL; current = current->next)
    {
        for (next = current->next; next != NULL; next = next->next)
        {
            if (current->data.age > next->data.age)
            {
                *temp = current->data;
                current->data = next->data;
                next->data = *temp;
            }
        }
    }
    return pBuffer;
}

void List(void *pBuffer)
{
    InfoList *contactList = pBuffer;
    int *i = (pBuffer + sizeof(InfoList) + sizeof(char));
    Item *currentContact = contactList->first;
    for (*i = 0; *i < contactList->quant; *i = *i + 1)
    {
        printf("\n%s\n", currentContact->data.name);
        printf("%d anos\n", currentContact->data.age);
        printf("Telefone: %ld\n", currentContact->data.phone);
        currentContact = currentContact->next;
    }
}

void *EndProgram(void *pBuffer)
{
    printf("Tchau!\n");
    InfoList *contactList = pBuffer;
    Item *nextContact;
    while (contactList->first != NULL)
    {
        nextContact = contactList->first->next;
        free(contactList->first);
        contactList->first = nextContact;
    }
    return pBuffer;
}

void PressEnter()
{
    printf("\nPressione ENTER para continuar... ");
    getchar();
}