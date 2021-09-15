#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
  Uma agenda que inclua, apague, busque e liste pessoas.
  Cada pessoa tem nome, idade e telefone.
  Nenhuma variável pode ser declarada em todo o programa, somente ponteiros que apontam para dentro de um ponteiro void chamado pBuffer (void * pBuffer).
  Nao pode usar struct.
  Implementar a base de dados da agenda usando lista duplamente ligada.
  Usar fila ordenada para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
*/

//constantes
#define CHAR (sizeof(char))
#define NOME (CHAR*10)
#define INT (sizeof(int))
#define TEL (sizeof(long int))
#define PtoP (sizeof(void*))

//prototipos
void menu(void);
void * inserir(void * pBuffer);
void * inserirFila(void * pBuffer, void * pessoa);
void * remover(void * pBuffer);
void buscar(void * pBuffer);
void * buscarPorNome(void * pBuffer);
void listar(void * pBuffer); 
void listarLista(void * pBuffer); 
void listarFila(void * pBuffer);
void * fecharPrograma(void * pBuffer);
void esperePeloEnter(void);

// principal
int main() {
  void * pBuffer;
  pBuffer = malloc(CHAR + NOME + (INT*2) + (PtoP*2));
  if (!pBuffer) {
    printf("Desculpe, tivemos um problema.");
    exit(1);
  }

  *(int *)(pBuffer + CHAR + NOME + INT) = 0; // quantPessoas = 0
  *(void **)(pBuffer + CHAR + NOME + (INT*2)) = NULL; // *nome1Lista = NULL
  *(void **)(pBuffer + CHAR + NOME + (INT*2) + PtoP) = NULL; // *nome1Fila = NULL

  char *escolha = pBuffer;
  do {
    menu();
    scanf("%c", escolha);
    getchar();
    switch(*escolha) {
      case '1':
        pBuffer = inserir(pBuffer);
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
        fecharPrograma(pBuffer);
        exit(0);
        break;
      default:
        printf("Opcao nao reconhecida.\n");
    }
    esperePeloEnter();
  } while (*escolha != '6');
}

// funções
void menu() {
  printf("\n\t1. Novo contato\n");
  printf("\t2. Remover contato\n");
  printf("\t3. Buscar contato\n");
  printf("\t4. Listar contatos\n");
  printf("\t5. Sair\n");
  printf("Insira sua escolha: ");
}

void * inserir(void * pBuffer) {
  printf("\n-- INSERINDO CONTATO\n");
  void * pessoa = malloc(NOME + INT + TEL + PtoP*2);
  if (!pessoa) {
    printf("Desculpe, tivemos um problema.\n");
    exit(1);
  }

  //recebendo dados da nova pessoa
  printf("Insira nome: ");
  scanf("%s", (char*)pessoa);
  printf("Insira idade: ");
  scanf("%d", (int*)(pessoa + NOME));
  printf("Insira telefone:");
  scanf("%ld", (long int*)(pessoa + NOME + INT));
  *(void**)(pessoa + NOME + INT + TEL) = NULL; // anterior = NULL
  *(void**)(pessoa + NOME + INT + TEL + PtoP) = NULL; // proximo = NULL
  getchar();
  
  //armazenando pessoa na primeira posição da lista e da fila
  int * quantPessoas = (pBuffer + CHAR + NOME + INT);
  if (!(*quantPessoas)) { 
    *(void**)(pBuffer + CHAR + NOME + INT*2) = pessoa;
    *(void**)(pBuffer + CHAR + NOME + INT*2 + PtoP) = pessoa;
    // proximo e anterior não mexe,já que só há um contato
  } 
  else { 
    //armazenando pessoa na posição seguinte disponivel
    //pessoaAtual = cabeça da lista
    void * pessoaAtual = *(void**)(pBuffer + CHAR + NOME + INT*2);
    void * proximo = *(void**)(pessoaAtual + NOME + INT + TEL);

    while (proximo != NULL) { 
      pessoaAtual = proximo;
      proximo = *(void**)(proximo + NOME + INT + TEL);
    }

    *(void**)(pessoaAtual + NOME + INT + TEL) = pessoa; 
    // tem que arrumar os proximos e anteriores
    
    //testar nomes para inserir na fila em ordem
    pBuffer = inserirFila(pBuffer, pessoa);
  }

  (*quantPessoas)++;

  return pBuffer;
}

void * inserirFila(void * pBuffer, void * pessoa) {
  // insertion Sort
}

void * remover(void * pBuffer) {
  printf("\n-- REMOVENDO CONTATO\n");

  if (!(*(int*)(pBuffer + CHAR + NOME + INT))) {
    printf("Agenda vazia. Nao ha ninguem para remover.\n");
    return pBuffer;
  }

  pBuffer = buscarPorNome(pBuffer);
  int * num = pBuffer + CHAR + NOME;
  if (*num == -1) return pBuffer;
  
  void * pessoaRemover = (*(void**)(pBuffer + CHAR + NOME + INT*2)) + *num;
  printf("%s, ", (char*)pessoaRemover);
  printf("%d anos: ", *(int*)(pessoaRemover + NOME));
  printf("%ld\n", *(long int*)(pessoaRemover + NOME + INT));

  return pBuffer;
}

void buscar(void * pBuffer) {
  printf("\n-- BUSCANDO CONTATO\n");

  if (!(*(int*)(pBuffer + CHAR + NOME + INT))) {
    printf("Agenda vazia. Nao ha ninguem para buscar.\n");
    return;
  }

  pBuffer = buscarPorNome(pBuffer);
  int * num = pBuffer + CHAR + NOME;
  if (*num == -1) return;
  
  void * pessoaRemover = (*(void**)(pBuffer + CHAR + NOME + INT*2)) + *num;
  printf("Contato #%d\n", (*num)+1);
  printf("%s, ", (char*)pessoaRemover);
  printf("%d anos: ", *(int*)(pessoaRemover + NOME));
  printf("%ld\n", *(long int*)(pessoaRemover + NOME + INT));
}

void * buscarPorNome (void * pBuffer) {
  char * nome = pBuffer + CHAR;
  printf("Insira nome do contato: ");
  scanf("%s", nome);
  getchar();

  int * i = pBuffer + CHAR + NOME;
  int * quantPessoas = pBuffer + CHAR + NOME + INT;
  void * pessoaAtual = *(void**)(pBuffer + CHAR + NOME + INT*2);
  for (*i = 0; *i < *quantPessoas; (*i)++) {
    if (strcmp(pessoaAtual, nome) == 0) {
      printf("Sao iguais!\n");
      *i *= (NOME + INT + TEL + PtoP*2); //retorna o deslocamente que sera necessario
      return pBuffer;
    }
    pessoaAtual = *(void**)(pessoaAtual + NOME + INT + TEL);
  }

  printf("Contato nao encontrado.\n");
  *i = -1;

  return pBuffer;
}

void listar(void * pBuffer) {
  printf("\n-- LISTANDO CONTATOS\n");

  if (!(*(int *)(pBuffer + CHAR + NOME + INT))) {
    printf("Agenda vazia. Nao ha ninguem para listar.\n");
    return;
  }  

  for(;;) {
    printf("Voce deseja:\n");
    printf("\t1. Listar por ordem de insercao\n");
    printf("\t2. Listar por ordem alfabetica\n");
    printf("\t3. Voltar ao menu\n");
    printf("Sua escolha -- ");
    scanf("%c", (char*)pBuffer);
    getchar();

    switch(*(char*)pBuffer) {
      case '1':
        listarLista(pBuffer);
        break;
      case '2':
        listarFila(pBuffer);
        break;
      case '3':
        return;
      default: 
        printf("Opcao nao reconhecida.\n");
    }
    esperePeloEnter();
  }
}

void listarLista(void * pBuffer) {
  void * pessoaAtual = *(void **)(pBuffer + CHAR + NOME + INT*2);
  while (pessoaAtual != NULL) {
    printf("%s, ", (char*)pessoaAtual);
    printf("%d anos: ", *(int*)(pessoaAtual + NOME));
    printf("%d\n",  *(long int*)(pessoaAtual + NOME + INT));
    pessoaAtual = *(void**)(pessoaAtual + NOME + INT + TEL);
  }
}

void listarFila(void * pBuffer) {
  printf("Listando fila\n");
  // void * pessoaAtual = *(void **)(pBuffer + CHAR + NOME + INT*2 + PtoP);
  // while (pessoaAtual != NULL) {
  //   printf("nome: %s, ", (char*)pessoaAtual);
  //   printf("%d anos - ", *(int*)(pessoaAtual + NOME));
  //   printf("%d\n",  *(long int*)(pessoaAtual + NOME + INT));
  //   pessoaAtual = *(void**)(pessoaAtual + NOME + INT + TEL);
  // }
}

void * fecharPrograma(void * pBuffer) {
  // free nos malloc
  printf("Tchau!");
}

void esperePeloEnter() {
  printf("\nPressione ENTER para continuar... ");
  getchar();
}