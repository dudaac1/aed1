#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo
{
    int conteudo;
    struct nodo *pai;
    struct nodo *filhoEsq, *filhoDir;
} Nodo;

Nodo *raiz = NULL; //raiz da árvore criada como global

//protótipos das funções
void InserirNodo(Nodo **topo, Nodo *novoNodo);
void balancear(Nodo **nodoRaiz);
int calcularFatorBalanc(Nodo *nodoRaiz);
void balancearEsq(Nodo **nodoRaiz);
void balancearDir(Nodo **nodoRaiz);
int alturaArvore(Nodo *nodoAtual);
void rotarEsq(Nodo **nodoRaiz);
void rotarDir(Nodo **nodoRaiz);

int main()
{
    int nos;
    printf("Quantos nos voce deseja criar? ");
    scanf("%d", &nos);

    srand(time(0));
    for (int i = 0; i < nos; i++)
    {
        Nodo *novoNodo = (Nodo *)malloc(sizeof(Nodo)); //criando nodo
        novoNodo->filhoEsq = NULL;
        novoNodo->filhoDir = NULL;
        novoNodo->conteudo = (rand() % 100); //numeros de 0 a 100;
        InserirNodo(&raiz, novoNodo);        //inserindo nodo na árvore
        //balancear(&raiz); //????
        printf("Nodo %d inserido.\n", novoNodo->conteudo);
    }
}

void InserirNodo(Nodo **nodoAtual, Nodo *novoNodo)
{
    if (!(*nodoAtual))
        novoNodo->pai = NULL;

    while (*nodoAtual)
    { //nodoAtual != NULL
        novoNodo->pai = *nodoAtual;
        if (novoNodo->conteudo >= (*nodoAtual)->conteudo)
            nodoAtual = &(*nodoAtual)->filhoDir;
        else
            nodoAtual = &(*nodoAtual)->filhoEsq;
    }
    *nodoAtual = novoNodo;
    balancear(&(*nodoAtual)->pai); // balancear a arvore - não tá funcionando direito
}

void balancear(Nodo **nodoAtual)
{
    while (*nodoAtual != NULL)
    {
        int fatorBalanc = calcularFatorBalanc(*nodoAtual);
        if (fatorBalanc > 1)
            balancearEsq(nodoAtual);
        else if (fatorBalanc < -1)
            balancearDir(nodoAtual);
        nodoAtual = &(*nodoAtual)->pai;
    };
}

int calcularFatorBalanc(Nodo *nodoRaiz)
{
    if (nodoRaiz == NULL)
        return 0;

    int altEsq = alturaArvore(nodoRaiz->filhoEsq);
    int altDir = alturaArvore(nodoRaiz->filhoDir);
    return altEsq - altDir;
}

void balancearEsq(Nodo **nodoRaiz)
{
    int fbEsq = calcularFatorBalanc((*nodoRaiz)->filhoEsq);
    if (fbEsq > 0)
    {
        rotarDir(nodoRaiz);
    }
    else if (fbEsq < 0)
    { //rotação dupla direita
        rotarEsq(&((*nodoRaiz)->filhoEsq));
        rotarDir(nodoRaiz);
    }
}

void balancearDir(Nodo **nodoRaiz)
{
    int fbDir = calcularFatorBalanc((*nodoRaiz)->filhoDir);
    if (fbDir < 0)
    {
        rotarEsq(nodoRaiz);
    }
    else if (fbDir > 0)
    { //rotação dupla esquerda
        rotarDir(&((*nodoRaiz)->filhoDir));
        rotarEsq(nodoRaiz);
    }
}

int alturaArvore(Nodo *nodoAtual)
{
    if (!nodoAtual)
        return 0;
    int alturaEsq = alturaArvore(nodoAtual->filhoEsq);
    int alturaDir = alturaArvore(nodoAtual->filhoDir);
    if (alturaEsq > alturaDir)
        return alturaEsq + 1;
    else
        return alturaDir + 1;
}

void rotarEsq(Nodo **nodoRaiz)
{
    Nodo *aux;
    aux = (*nodoRaiz)->filhoDir;           //aux = filho a direita
    (*nodoRaiz)->filhoDir = aux->filhoEsq; //filho da direita da raiz = NULL
    aux->filhoEsq = (*nodoRaiz);           //filho esquerdo de aux = raiz

    //isso não tá funcionando direito, o programa fica num loop depois quando volta para balancear()
    aux->pai = aux->filhoEsq->pai;

    if (aux->filhoEsq != NULL)
        aux->filhoEsq->pai = aux; //pai do filho a esq = aux (nova raiz)
    *nodoRaiz = aux;
}

void rotarDir(Nodo **nodoRaiz)
{
    Nodo *aux;
    aux = (*nodoRaiz)->filhoEsq;           //aux - filho a esquerda
    (*nodoRaiz)->filhoEsq = aux->filhoDir; //filho da direita da raiz = null
    aux->filhoDir = (*nodoRaiz);           //filho direito de aux = raiz

    //isso não tá funcionando direito, o programa fica num loop depois quando volta para balancear()
    aux->pai = aux->filhoDir->pai;

    if (aux->filhoDir != NULL)
        aux->filhoDir->pai = aux; //pai do filho a dir = aux (nova raiz)
    *nodoRaiz = aux;
}