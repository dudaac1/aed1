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
void Insert(void * pBuffer);
void Delete(void * pBuffer);
void * Search(void * pBuffer);
void List(void * pBuffer);
void * EndProgram(void * pBuffer);
void PressEnter(void);

// principal
int main() {
    printf("InfoList size: %d\n", sizeof(InfoList));
    printf("char size: %d\n", sizeof(char));
    printf("Contact size: %d\n", sizeof(Contact));
    printf("Item size: %d\n", sizeof(Item));

    void * pBuffer;
    pBuffer = malloc(sizeof(InfoList) + sizeof(char) * 11 + sizeof(int) + sizeof(Contact));
    // InfoList contactList + char option + int i + char nome[10] + Contact contato
    if (!pBuffer)
    {
        printf("Desculpa, tivemos um problema.\n");
        exit(1);
    }

    InfoList * contactList;
    contactList = pBuffer;
    (*contactList).first = NULL;
    (*contactList).last = NULL;
    (*contactList).quant = 0;

    char * option = (pBuffer + sizeof(InfoList));
    do {
        Menu();
        scanf(" %c", option);
        getchar();
        switch (*option) {
            case '1':
                printf("Inserindo contato...\n");
                Insert(pBuffer);
                break;
            case '2':
                printf("Removendo contato...\n");
                Delete(pBuffer);
                break;
            case '3':
                printf("Buscando contato...\n");
                pBuffer = Search(pBuffer);
                // int * searchValue = pBuffer(espaço do valor de retorno);
                //se busca = 0, não achou
                // if  (!*busca) print("Contato nao foi encontrado.\n");
                // else ...
                //se busca = 1, então Contact * searchContact = pBuffer(espaço do Contact)
                break;
            case '4':
                printf("Listando contatos...\n");
                List(pBuffer);
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
void Menu() {
    printf("\n\t(1) Adicionar contato\n");
    printf("\t(2) Remover contato\n");
    printf("\t(3) Buscar contato\n");
    printf("\t(4) Listar contatos\n");
    printf("\t(5) Sair\n");
    printf("Insira sua escolha: ");
}

void Insert(void * pBuffer) {
    InfoList * contactList = pBuffer;

    Contact * contact = (pBuffer + sizeof(InfoList) + sizeof(char)*11 + sizeof(int));
    printf("Insira nome: ");
    scanf(" %s", contact->name );
    getchar();
    printf("Insira idade: ");
    scanf("%d", &contact->age);
    while (contact->age < 0) {
        printf("Idade e positiva. Insira outro valor: ");
        scanf("%d", &contact->age);
    }
    getchar();
    printf("Insira telefone: ");
    scanf("%ld", &contact->phone);
    getchar();

    if (!contactList->quant) { //se quant = 0
        contactList->first = (Item *)malloc(sizeof(Item));
        if(!contactList->first) {
            printf("Desculpa, tivemos um problema.\n");
            exit(1);
        }
        strcpy(contactList->first->data.name, contact->name);
        contactList->first->data.age = contact->age;
        contactList->first->data.phone = contact->phone;
        contactList->first->next = NULL;
        contactList->first->prev = NULL;
        contactList->last = contactList->first;
    } else {
        Item * novoContato = (Item *)malloc(sizeof(Item));
        if (!novoContato) {
            printf("Desculpa, tivemos um problema.\n");
                exit(1);
        }
        strcpy(novoContato->data.name, contact->name);
        novoContato->data.age = contact->age;
        novoContato->data.phone = contact->phone;
        novoContato->next = NULL; //novo contato adicionado no final, então n aponta para ninguem a seguir

        if (contactList->quant == 1) { //se quant = 1
            contactList->first->next = novoContato; //primeiro contato aponta para novo contato
            novoContato->prev = contactList->first; //anterior de novo contato aponta para primeiro
        } else { //se quant > 1
            novoContato->prev = contactList->last; //anterior de novo contato aponta pro ultimo
            contactList->last->next = novoContato; //prox do ultimo contato aponta para novo [ultimo] contato
        }
        contactList->last = novoContato; //adiciona o novo contato sempre no final
    }
    contactList->quant++;
}

void Delete(void * pBuffer) {
    // infolist contactlist + char option + int i + char nome[10] + Contact contato
    InfoList * contactList = pBuffer;
    if (contactList->quant == 0) {
        printf("Nenhum contato para deletar.\n");
    }
    // remover contato
}

void * Search(void * pBuffer) {
    InfoList * contactList = pBuffer;
    if (contactList->quant == 0) {
        printf("Nenhum contato para buscar.\n");
    }
    // procurar contato
    return pBuffer;
}

void List(void * pBuffer) {
    InfoList * contactList = pBuffer;
    if (contactList->quant == 0) {
        printf("Nenhum contato para listar.\n");
        return;
    }
    if (contactList->first == contactList->last) {
        printf("Voce possui %d contato armazenado da sua agenda.\n");
    }
    // listar contatos
}

void * EndProgram(void * pBuffer) {
    printf("Tchau!\n");
    InfoList * contactList = pBuffer;
    Item * nextContact;
    while (contactList->first != NULL) {
        nextContact = contactList->first->next;
        free(contactList->first);
        contactList->first = nextContact;
    }
    return pBuffer;
}

void PressEnter() {
    printf("\nPressione ENTER para continuar... ");
    getchar();
    getchar();
}