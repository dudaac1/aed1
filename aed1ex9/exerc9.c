#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <processthreadsapi.h> // para calculo do tempo

int *gerarVetor(int tam, int *vetor);
int *insertionSort(int tam, int *vetor);
int *selectionSort(int tam, int *vetor);
void quickSort(int esq, int dir, int *vetor);
int *mergeSort(int tam, int *vetor);
int *merge(int tamVetEsq, int tamVetDir, int *vetorEsq, int *vetorDir, int *vetorFinal);
int verificaOrdenacao(int tam, int *vetor);
double tempoCpu(void);

int main()
{
    int tam;
    printf("Qual tamanho voce deseja que o vetor tenha? ");
    scanf("%d", &tam);
    while (tam <= 0)
    {
        printf("Numero nao pode ser negativo nem nulo. Digite outro: ");
        scanf("%d", &tam);
    }

    int *vetor = gerarVetor(tam, vetor); //criando vetor e inserindo dados dentro

    //alocando espaço para um vetor para cada ordenação
    int *numInsertion = (int *)malloc(tam * sizeof(int));
    if (numInsertion == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }

    int *numSelection = (int *)malloc(tam * sizeof(int));
    if (numSelection == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }

    int *numQuick = (int *)malloc(tam * sizeof(int));
    if (numQuick == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }

    int *numMerge = (int *)malloc(tam * sizeof(int));
    if (numMerge == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }

    //copiando os valores do vetor origem para os outros
    for (int i = 0; i < tam; i++)
    {
        numInsertion[i] = vetor[i];
        numSelection[i] = vetor[i];
        numQuick[i] = vetor[i];
        numMerge[i] = vetor[i];
    }

    printf("\n# Vetor original #\n");
    printf("Tamanho do vetor: %d\n", tam);
    printf(verificaOrdenacao(tam, vetor) ? "O vetor esta ordenado.\n" : "O vetor nao esta ordenado.\n");

    printf("\n# Ordenacao por Insertion Sort #\n");
    double begin = tempoCpu();
    numInsertion = insertionSort(tam, numInsertion);
    double end = tempoCpu();
    printf("Tempo de CPU: %.5f segundos.\n", end - begin);
    printf(verificaOrdenacao(tam, numInsertion) ? "O vetor esta ordenado.\n" : "O vetor nao esta ordenado.\n");

    printf("\n# Ordenacao por Selection Sort #\n");
    begin = tempoCpu();
    numSelection = selectionSort(tam, numSelection);
    end = tempoCpu();
    printf("Tempo de CPU: %.5f segundos.\n", end - begin);
    printf(verificaOrdenacao(tam, numSelection) ? "O vetor esta ordenado.\n" : "O vetor nao esta ordenado.\n");

    printf("\n# Ordenacao por Quick Sort #\n");
    begin = tempoCpu();
    quickSort(0, tam - 1, numQuick);
    end = tempoCpu();
    printf("Tempo de CPU: %.5f segundos.\n", end - begin);
    printf(verificaOrdenacao(tam, numQuick) ? "O vetor esta ordenado.\n" : "O vetor nao esta ordenado.\n");

    printf("\n# Ordenacao por Merge Sort #\n");
    begin = tempoCpu();
    numMerge = mergeSort(tam, numMerge);
    end = tempoCpu();
    printf("Tempo de CPU: %.5f segundos.\n", end - begin);
    printf(verificaOrdenacao(tam, numMerge) ? "O vetor esta ordenado.\n" : "O vetor nao esta ordenado.\n\n");

    free(vetor);
    free(numInsertion);
    free(numSelection);
    free(numQuick);
    free(numMerge);
}

int *gerarVetor(int tam, int *vetor)
{
    vetor = (int *)malloc(tam * sizeof(int));
    if (vetor == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }
    srand(time(0));
    for (int i = 0; i < tam; i++)
        vetor[i] = rand();

    return vetor;
}

int *insertionSort(int tam, int *vetor)
{
    int aux, i, j;
    for (i = 1; i < tam; i++)
    {
        j = i - 1;
        aux = vetor[i];
        while (j >= 0 && aux < vetor[j])
        {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = aux;
    }
    return vetor;
}

int *selectionSort(int tam, int *vetor)
{
    int aux, i, j, menor, menorIndice = 0;
    for (i = 0; i < tam - 1; i++)
    {
        menor = vetor[i];
        for (j = i + 1; j < tam; j++)
            if (vetor[j] < menor)
            {
                menor = vetor[j];
                menorIndice = j;
            }
        aux = vetor[i];
        vetor[i] = vetor[menorIndice];
        vetor[menorIndice] = aux;
        menorIndice = i + 1;
    }
    return vetor;
}

void quickSort(int esq, int dir, int *vetor)
{
    // dir e esq são indices do vetor
    int pivo, aux, i, j;
    i = esq;
    j = dir;

    //pivo = indice aleatorio do vetor de valor da esq até dir
    srand(time(0));
    int pivoIndice = (rand() % (dir - esq)) + esq;
    pivo = vetor[pivoIndice];

    do
    {
        while (vetor[i] < pivo)
            i++;
        while (pivo < vetor[j])
            j--;
        if (i <= j)
        {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);

    if (esq < j)
        quickSort(esq, j, vetor);
    if (i < dir)
        quickSort(i, dir, vetor);
}

int *mergeSort(int tamVetor, int *vetor)
{
    if (tamVetor <= 1)
        return vetor;

    int meioIndice = tamVetor / 2;
    int tamVetEsq = meioIndice;
    int tamVetDir = meioIndice;
    if (tamVetor % 2 == 0)
        meioIndice--; // se tamVetor = par, meio = tam/2 - 1, devido ao vetor começar em 0
    else
        tamVetEsq++; // para tamVetor = impar, o vetor a esquerda sempre será o maior

    int *vetorEsq = (int *)malloc(sizeof(int) * tamVetEsq);
    if (vetorEsq == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }
    int *vetorDir = (int *)malloc(sizeof(int) * tamVetDir);
    if (vetorDir == NULL)
    {
        printf("Um erro ocorreu.\n");
        exit(1);
    }

    int i;
    for (i = 0; i <= meioIndice; i++)
        vetorEsq[i] = vetor[i];
    for (i; i < tamVetor; i++) // esse for continua a contagem de i iniciada no for anterior
        vetorDir[i - meioIndice - 1] = vetor[i];

    vetorEsq = mergeSort(tamVetEsq, vetorEsq);
    vetorDir = mergeSort(tamVetDir, vetorDir);
    vetor = merge(tamVetEsq, tamVetDir, vetorEsq, vetorDir, vetor);

    free(vetorEsq);
    free(vetorDir);

    return vetor;
}

int *merge(int tamVetEsq, int tamVetDir, int *vetorEsq, int *vetorDir, int *vetorFinal)
{
    int contVetFinal = 0, contVetEsq = 0, contVetDir = 0;
    while (tamVetEsq > 0 || tamVetDir > 0)
    {
        if (tamVetEsq > 0 && tamVetDir > 0)
        {
            if (vetorEsq[contVetEsq] <= vetorDir[contVetDir])
            {
                vetorFinal[contVetFinal++] = vetorEsq[contVetEsq++];
                tamVetEsq--;
            }
            else
            {
                vetorFinal[contVetFinal++] = vetorDir[contVetDir++];
                tamVetDir--;
            }
        }
        else if (tamVetEsq > 0)
        {
            vetorFinal[contVetFinal++] = vetorEsq[contVetEsq++];
            tamVetEsq--;
        }
        else if (tamVetDir > 0)
        {
            vetorFinal[contVetFinal++] = vetorDir[contVetDir++];
            tamVetDir--;
        }
    }
    return vetorFinal;
}

int verificaOrdenacao(int tam, int *vetor)
{ //o anterior deve ser menor que o posterior, e assim para todos
    int cont = 1;
    if (tam > 1)
        for (int i = 1; i < tam; i++)
        {
            if (vetor[i - 1] <= vetor[i])
                cont++;
            else
                return 0;
        }

    if (cont == tam)
        return 1;
}

double tempoCpu()
{
    FILETIME a, b, c, d;
    if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0)
    {
        return (double)(d.dwLowDateTime |
                        ((unsigned long long)d.dwHighDateTime << 32)) *
               0.0000001;
    }
    else
        return 0;
}