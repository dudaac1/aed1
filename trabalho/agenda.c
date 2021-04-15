#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structs
typedef struct contact { //dados
    char name[10];
    int age;
    long int phone;
} Contact; 

typedef struct item { //nodo
    Contact data;
    struct item * next;
    struct item * prev;
} Item; 

typedef struct info { //sentinela
    unsigned int quant;
    Item * first;
    Item * last;
} InfoList; 

// protótipos
void Menu(void);
void Insert(InfoList * contactList);
void Delete(InfoList * contactList);
void Search(InfoList * contactList);
void List(InfoList * contactList);
void EndProgram(InfoList * contactList, void * pBuffer);
void PressEnter(void);

// principal
int main() {
    InfoList * contactList;
    contactList->quant = 0;
    contactList->first = NULL;

    void * pBuffer;
    pBuffer = malloc(sizeof(char));
    if (pBuffer == NULL)
    {
        printf("Desculpa, tivemos um problema.\n");
        exit(1);
    }

    char * option = pBuffer;
    do {
        Menu();
        scanf(" %c", option);
        switch (*option) {
            case '1':
                printf("Inserindo contato...\n");
                Insert(contactList);
            case '2':
                printf("Removendo contato...\n");
                Delete(contactList);
            case '3':
                printf("Buscando contato...\n");
                Search(contactList);
            case '4':
                printf("Listando contatos...\n");
                List(contactList);
            case '5':
                EndProgram(contactList, pBuffer);
                free(pBuffer);
                exit(0);
        }
    } while (*option != '5');
}

// funções 
void Menu() {
    printf("\n\t(1) Adicionar contato\n");
    printf("\t(2) Remover contato\n");
    printf("\t(3) Buscar contato\n");
    printf("\t(4) Listar contatos\n");
    printf("\t(5) Sair\n");
    printf("Insira sua escolha: ");
}

void Insert(InfoList * contactList) {
    // inserir contato
}

void Delete(InfoList * contactList) {
    if (contactList == NULL) {
        printf("Nenhum contato para deletar.\n");
    }
    // remover contato
}

void Search(InfoList * contactList) {
    if (contactList == NULL) {
        printf("Nenhum contato para buscar.\n");
    }
    // procurar contato
}

void List(InfoList * contactList) {
    if (contactList == NULL) {
        printf("Nenhum contato para listar.\n");
    }
    // listar contatos
}

void EndProgram(InfoList * contactList, void * pBuffer) {
    printf("Tchau!\n");
    // if (contactList != NULL) {
    //      for (etc etc etc)
    // }
    // free nos nodos
}

void PressEnter() {
    printf("\nPressione ENTER para continuar... ");
    getchar();
    getchar();
}