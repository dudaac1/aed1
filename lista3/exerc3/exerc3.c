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
        InserirNodo(&raiz, novoNodo); //inserindo nodo na árvore
        balancear(&raiz); //????
        printf("Nodo %d inserido.\n", novoNodo->conteudo);
    }
}

void InserirNodo(Nodo **tracer, Nodo *novoNodo)
{
    if (!(*tracer))
        novoNodo->pai = NULL;

    while (*tracer)
    { //tracer != NULL
        novoNodo->pai = *tracer;
        if (novoNodo->conteudo >= (*tracer)->conteudo)
            tracer = &(*tracer)->filhoDir;
        else
            tracer = &(*tracer)->filhoEsq;
    }
    *tracer = novoNodo;
    // balancear(&(*tracer)->pai); // balancear a arvore - não tá funcionando direito
}

void balancear(Nodo **nodoRaiz)
{
    int fatorBalanc = calcularFatorBalanc(*nodoRaiz);
    if (fatorBalanc > 1)
        balancearEsq(nodoRaiz);
    else if (fatorBalanc < -1)
        balancearDir(nodoRaiz);
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
    (*nodoRaiz)->filhoDir = aux->filhoEsq; //o filho da direita = NULL
    aux->pai = (*nodoRaiz)->pai;           //pai de aux = pai de raiz
    aux->filhoEsq = (*nodoRaiz);           //testar - o filho de aux = raiz
    (*nodoRaiz) = aux;
    aux->filhoEsq->pai = aux; //testar - pai do filho a esquerda = 2
    aux->filhoDir->pai = aux; //testar - pai do filho a direita = 2
}

void rotarDir(Nodo **nodoRaiz)
{
    Nodo *aux;
    aux = (*nodoRaiz)->filhoEsq;
    (*nodoRaiz)->filhoEsq = aux->filhoDir;
    aux->pai = (*nodoRaiz)->pai; //testar
    aux->filhoDir = (*nodoRaiz);
    (*nodoRaiz) = aux;
    aux->filhoEsq->pai = aux; //testar
    aux->filhoDir->pai = aux; //testar
}
