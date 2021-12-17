#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
EXERCICIO 8

*/

// constantes
#define TRUE 1
#define FALSE 0

// estruturas
typedef struct nodo {
	int conteudo;
	struct nodo * filhoEsq;
	struct nodo * filhoDir;
} Nodo;

typedef int BOOLEAN; //para retorno das funções

//protótipos
void opcao1(void);
void opcao2(void);
BOOLEAN inserirNodo(Nodo ** nodoAtual, int valor);
BOOLEAN removerNodo(Nodo ** nodoAtual, int valor);
Nodo * procuraMaior(Nodo * nodoAtual);
Nodo * pesquisarNodo(Nodo * nodoAtual, int valor);
BOOLEAN balancear(Nodo ** nodoRaiz);
int calcularFatorBalanc(Nodo * nodoRaiz);
int alturaArvore(Nodo * nodoAtual);
BOOLEAN balancearEsq(Nodo ** nodoRaiz);
BOOLEAN balancearDir(Nodo ** nodoRaiz);
void rotarEsq(Nodo ** raizAtual);
void rotarDir(Nodo ** raizAtual);
void imprimirArvore(Nodo * nodoAtual, int nivel);
BOOLEAN verificaArvoreAVL(Nodo * raizAtual);
void liberarNodo(Nodo * nodoAtual);

int main() {
	char escolha;
	do {
		printf("Voce deseja criar uma arvore:\n");
		printf("\t(1) aleatoria pelo numero de nodos.\n");
		printf("\t(2) com testes pre-definidos.\n");
		printf("Insira sua escolha: ");
		scanf("%c", &escolha);
		getchar();
	} while (escolha != '1' && escolha != '2');

	if (escolha == '1') opcao1();
	else opcao2();

	printf("\nPressione ENTER para encerrar o programa.\n");
	getchar();
}

void opcao1() {
	printf("\n# OPCAO 1: Criando arvore aleatoria #\n");
	Nodo *raiz = NULL;
	int nos;
	printf("Quantos nodos voce deseja criar? ");
	scanf("%d", &nos);

	srand(time(0));
	printf("Nodos gerados: ");
	for (int i = 0; i < nos; i++) {
		int valor = (rand() % 1000);								//numeros de 0 a 1000;
		BOOLEAN lixo = inserirNodo(&raiz, valor); 	//inserindo nodo na árvore
		printf("%d ", valor);
	}
	printf("\nPressione ENTER para continuar...\n");
	getchar();

	printf("# IMPRIMINDO ARVORE #\n");
	imprimirArvore(raiz, 0);

	printf("Arvore eh AVL? ");
	verificaArvoreAVL(raiz) ? printf("Sim") : printf("Nao");

	//pesquisa
	int valor;
	printf("\nInsira valor que deseja buscar: ");
	scanf("%d", &valor);
	Nodo *nodoBusca = pesquisarNodo(raiz, valor);
	if (nodoBusca == NULL)
		printf("Valor nao esta presente nesta arvore.\n");
	else
		printf("Valor presente na arvore: %d\n", nodoBusca->conteudo);

	getchar();

	liberarNodo(raiz);
}

void opcao2() {
	printf("\n-- OPCAO 2: Criando arvore com dados pre-definidos --\n");
	Nodo *raiz = NULL;

	//inserir valores que causem as 4 rotações: 12 (RSD), 21 (RDD), 23 (RSE), 17 (RDE)
	int valoresInserir[] = {34, 65, 20, 14, 12, 21, 22, 23, 16, 18, 17}; 
	printf("Nodos para insercao: ");
	for (int i = 0; i < 11; i++) {
		BOOLEAN lixo = inserirNodo(&raiz, valoresInserir[i]);
		printf("%d ", valoresInserir[i]);
	}

	printf("\n\n");
	imprimirArvore(raiz, 0);

	printf("\nArvore eh AVL? ");
	verificaArvoreAVL(raiz) ? printf("Sim") : printf("Nao");

	printf("\nPressione ENTER para continuar...\n");
	getchar();

	//remover valores que causem as 4 rotacoes
	int valoresRemover[] = {65, 21, 12, 18}; //RSD, RDE, RSE, RDD
	printf("Nodos para remocao: ");
	for (int i = 0; i < 2; i++) {
		BOOLEAN lixo = removerNodo(&raiz, valoresRemover[i]);
		printf("%d ", valoresRemover[i]);
	}

	printf("\n\n");
	imprimirArvore(raiz, 0);

	// ehAvl = verificaArvoreAVL(raiz); //verificando árvore após remoção
	printf("\nArvore eh AVL? ");
	verificaArvoreAVL(raiz) ? printf("Sim") : printf("Nao");
	// if (ehAvl)
	//     printf("Sim.\n");
	// else
	//     printf("Nao.\n");

	//pesquisa
	int valor;
	printf("\nInsira valor que deseja buscar: ");
	scanf("%d", &valor);
	Nodo *nodoBusca = pesquisarNodo(raiz, valor);
	if (nodoBusca == NULL)
		printf("Valor nao esta presente nesta arvore.\n");
	else
		printf("Valor presente na arvore: %d\n", nodoBusca->conteudo);

	getchar();
	liberarNodo(raiz);
}

BOOLEAN inserirNodo(Nodo **nodoAtual, int valor) {
	if (*nodoAtual == NULL) {
		*nodoAtual = (Nodo *)malloc(sizeof(Nodo)); //criando nodo
		(*nodoAtual)->filhoEsq = NULL;
		(*nodoAtual)->filhoDir = NULL;
		(*nodoAtual)->conteudo = valor;
		return TRUE;
	}

	else if (valor < (*nodoAtual)->conteudo) { 						//permite valores repetidos
		if (inserirNodo(&(*nodoAtual)->filhoEsq, valor)) {  //if inserirNodo == TRUE{
			if (balancear(nodoAtual)) 												//if Balanceamento == TRUE
				return FALSE;
			else
				return TRUE;
		}
	}
	else if (valor >= (*nodoAtual)->conteudo) {
		if (inserirNodo(&(*nodoAtual)->filhoDir, valor)) {
			if (balancear(nodoAtual)) 
				return FALSE;
			else 
				return TRUE;
		}
		else 
			return FALSE;
	}
}

BOOLEAN removerNodo(Nodo ** nodoAtual, int valor) {
	if (*nodoAtual == NULL) return FALSE;

	if (valor < (*nodoAtual)->conteudo) {
		if (removerNodo(&(*nodoAtual)->filhoEsq, valor)) {
			int fatorBalanc = calcularFatorBalanc(*nodoAtual);
			fatorBalanc = fatorBalanc >= 0 ? fatorBalanc : fatorBalanc * -1; //função retorna valores negativos
			if (fatorBalanc >= 2) { //comparando altura das arvores do filho a direita
				if (alturaArvore((*nodoAtual)->filhoDir->filhoEsq) <= alturaArvore((*nodoAtual)->filhoDir->filhoDir))
					rotarEsq(nodoAtual); //rotação rr
				else {																			 //rotação rl = ll + rr
					rotarDir(&((*nodoAtual)->filhoDir)); //rotação ll
					rotarEsq(nodoAtual);								 //rotação rr
				}
				return TRUE;
			}
		}
	}
	else if (valor > (*nodoAtual)->conteudo) {
		if (removerNodo(&(*nodoAtual)->filhoDir, valor)) {
			int fatorBalanc = calcularFatorBalanc(*nodoAtual);
			fatorBalanc = fatorBalanc >= 0 ? fatorBalanc : fatorBalanc * -1; //função retorna valores negativos
			//comparando altura das arvores do filho a esquerda
			if (fatorBalanc >= 2) {
				if (alturaArvore((*nodoAtual)->filhoEsq->filhoDir) <= alturaArvore((*nodoAtual)->filhoEsq->filhoEsq))
					rotarDir(nodoAtual); //rotação ll
				else {																			 //rotação lr = rr + ll
					rotarEsq(&((*nodoAtual)->filhoEsq)); //rotação rr
					rotarDir(nodoAtual);								 //rotação ll
				}
				return TRUE;
			}
		}
	}
	else { //se valor == nodoAtual->conteudo
		//se tiver 1 filho ou 0 filhos
		if ((*nodoAtual)->filhoEsq == NULL || (*nodoAtual)->filhoDir == NULL) {
			Nodo *nodoRemover = (*nodoAtual);
			if ((*nodoAtual)->filhoEsq != NULL)
				*nodoAtual = (*nodoAtual)->filhoEsq;
			else
				*nodoAtual = (*nodoAtual)->filhoDir;
			free(nodoRemover);
			return TRUE;
		}
		else { //se tiver 2 filhos
			Nodo *aux = procuraMaior((*nodoAtual)->filhoEsq);
			(*nodoAtual)->conteudo = aux->conteudo; //como contornar?
			removerNodo(&(*nodoAtual)->filhoEsq, (*nodoAtual)->conteudo);

			if (calcularFatorBalanc(*nodoAtual) >= 2) {
				if (alturaArvore((*nodoAtual)->filhoEsq->filhoDir) <= alturaArvore((*nodoAtual)->filhoEsq->filhoEsq))
					rotarDir(nodoAtual); //rotação ll
				else {																			 //rotação lr = rr + ll
					rotarEsq(&((*nodoAtual)->filhoEsq)); //rotação rr
					rotarDir(nodoAtual);								 //rotação ll
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

//função responsável por tratar a remoção de um nó com 2 filhos
Nodo *procuraMaior(Nodo *nodoAtual) {
	Nodo *nodoRetorno = nodoAtual;
	Nodo *nodoDir = nodoAtual->filhoDir;
	while (nodoDir != NULL) {
		nodoRetorno = nodoDir;
		nodoDir = nodoDir->filhoDir;
	}
	return nodoRetorno;
}

Nodo *pesquisarNodo(Nodo *nodoAtual, int valor) {
	while (nodoAtual != NULL && valor != nodoAtual->conteudo) {
		if (valor > nodoAtual->conteudo)
			nodoAtual = nodoAtual->filhoDir;
		else if (valor < nodoAtual->conteudo)
			nodoAtual = nodoAtual->filhoEsq;
	}
	return nodoAtual;
}

BOOLEAN balancear(Nodo **nodoAtual) {
	int fatorBalanc = calcularFatorBalanc(*nodoAtual);
	if (fatorBalanc > 1)
		return balancearEsq(nodoAtual);
	else if (fatorBalanc < -1)
		return balancearDir(nodoAtual);
	else
		return FALSE;
}

int calcularFatorBalanc(Nodo *nodoRaiz) {
	if (nodoRaiz == NULL) 
		return 0;

	int altEsq = alturaArvore(nodoRaiz->filhoEsq);
	int altDir = alturaArvore(nodoRaiz->filhoDir);
	return altEsq - altDir;
}

int alturaArvore(Nodo *nodoAtual) {
	if (!nodoAtual) 
		return 0;

	int alturaEsq = alturaArvore(nodoAtual->filhoEsq);
	int alturaDir = alturaArvore(nodoAtual->filhoDir);
	if (alturaEsq > alturaDir)
		return alturaEsq + 1;
	else
		return alturaDir + 1;
}

BOOLEAN balancearEsq(Nodo **nodoRaiz) {
	int fbEsq = calcularFatorBalanc((*nodoRaiz)->filhoEsq);
	if (fbEsq > 0)
	{ //rotação simples
		rotarDir(nodoRaiz);
		return TRUE;
	}
	else if (fbEsq < 0)
	{ //rotação dupla direita
		rotarEsq(&((*nodoRaiz)->filhoEsq));
		rotarDir(nodoRaiz);
		return TRUE;
	}
	return FALSE;
}

BOOLEAN balancearDir(Nodo **nodoRaiz) {
	int fbDir = calcularFatorBalanc((*nodoRaiz)->filhoDir);
	if (fbDir < 0) { //rotação simples
		rotarEsq(nodoRaiz);
		return TRUE;
	}
	else if (fbDir > 0) { //rotação dupla esquerda
		rotarDir(&((*nodoRaiz)->filhoDir));
		rotarEsq(nodoRaiz);
		return TRUE;
	}
	return FALSE;
}

void rotarEsq(Nodo **raizAtual) {
	Nodo *novaRaiz;
	novaRaiz = (*raizAtual)->filhoDir;					 //novaRaiz = filho a direita
	(*raizAtual)->filhoDir = novaRaiz->filhoEsq; //filho da direita da raiz = NULL
	novaRaiz->filhoEsq = (*raizAtual);					 //filho esquerdo de novaRaiz = raiz
	*raizAtual = novaRaiz;											 //o endereço da raiz = novaRaiz
}

void rotarDir(Nodo **raizAtual) {
	Nodo *novaRaiz;
	novaRaiz = (*raizAtual)->filhoEsq;					 //novaRaiz - filho a esquerda
	(*raizAtual)->filhoEsq = novaRaiz->filhoDir; //filho da direita da raiz = null
	novaRaiz->filhoDir = (*raizAtual);					 //filho direito de novaRaiz = raiz
	*raizAtual = novaRaiz;											 //o endereço da raiz = novaRaiz
}

void imprimirArvore(Nodo *nodoAtual, int nivel) {
	if (nodoAtual == NULL)
		return;

	for (int i = 0; i < nivel; i++) //imprimindo nivel da arvore; 2 espaços a mais por nivel
		printf("  ");
	printf("%d\n", nodoAtual->conteudo); //imprimindo conteudo do nodo

	imprimirArvore(nodoAtual->filhoEsq, nivel + 1);
	imprimirArvore(nodoAtual->filhoDir, nivel + 1);
}

BOOLEAN verificaArvoreAVL(Nodo *raizAtual) {
	if (raizAtual == NULL)
		return TRUE;

	if (!verificaArvoreAVL(raizAtual->filhoEsq))
		return FALSE;
	if (!verificaArvoreAVL(raizAtual->filhoDir))
		return FALSE;

	int fatorBalanc = calcularFatorBalanc(raizAtual);
	if (fatorBalanc > 1 || fatorBalanc < -1)
		return FALSE;
	else
		return TRUE;
}

void liberarNodo(Nodo *nodoAtual) {
	if (nodoAtual == NULL)
		return;

	liberarNodo(nodoAtual->filhoDir);
	liberarNodo(nodoAtual->filhoEsq);
	free(nodoAtual);
}