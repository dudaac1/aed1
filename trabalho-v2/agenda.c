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

//prototipos
void menu(void);
void * inserir(void * pBuffer);
void * remover(void * pBuffer);
void * buscar(void * pBuffer);
void listar(void * pBuffer); 
void listarOrdenado(void * pBuffer);
void * fecharPrograma(void * pBuffer);
void esperePeloEnter(void);

//constantes
#define NOME (sizeof(char)*10)
#define CHAR (sizeof(char))
#define INT (sizeof(int))
#define TEL (sizeof(long int))
#define PtoP (sizeof(void*))

// principal
int main() {
  void * pBuffer;
  // char escolha; char nomeAux[10]; int i; int quantPessoas; void * lista; void * fila;
  // pBuffer = malloc(sizeof(char)*11 + sizeof(int) + sizeof(int) + sizeof(void*) + sizeof(void*));
  pBuffer = malloc(CHAR + NOME + (INT*2) + (PtoP*2));
  if (!pBuffer) {
    printf("Desculpe, tivemos um problema.");
    exit(1);
  }
  // *(int *)(pBuffer + sizeof(char)*11 + sizeof(int)) = 0; // quantPessoas = 0
  // *(char **)(pBuffer + sizeof(char)*11 + sizeof(int)*2) = NULL; // *nome1Lista = NULL
  // *(char **)(pBuffer + sizeof(char)*11 + sizeof(int)*2 + sizeof(char *)) = NULL; // *nome1Fila = NULL

  *(int *)(pBuffer + CHAR + NOME + INT) = 0; // quantPessoas = 0
  *(char **)(pBuffer + CHAR + NOME + (INT*2)) = NULL; // *nome1Lista = NULL
  *(char **)(pBuffer + CHAR + NOME + (INT*2) + PtoP) = NULL; // *nome1Fila = NULL


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
        listarOrdenado(pBuffer);
        break;
      case '6':
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
  printf("\t4. Listar contatos por ordem de insercao\n");
  printf("\t5. Listar contatos por ordem alfabetica\n");
  printf("\t6. Sair\n");
  printf("Insira sua escolha: ");
}

void * inserir(void * pBuffer) {
  // char escolha; char nomeAux[10]; int i; int quantPessoas; char * nome1Lista; char * nome1Fila;
  // int * quantPessoas = (pBuffer + sizeof(char)*11 + sizeof(int));
  int * quantPessoas = (pBuffer + CHAR + NOME + INT);

  //recebendo dados da nova pessoa
  //char nome[10]; int idade; long int telefone; void * proximo; void * anterior;
  // void * pessoa = malloc(sizeof(char)*10 + sizeof(int) + sizeof(long int) + sizeof(void *)*2);
  void * pessoa = malloc(NOME + INT + TEL + PtoP*2);
  printf("Insira nome: ");
  scanf("%s", (char*)pessoa);
  printf("Insira idade: ");
  scanf("%d", (int*)(pessoa + NOME));
  printf("Insira telefone:");
  scanf("%ld", (long int*)(pessoa + NOME + INT));
  *(void**)(pessoa + NOME + INT + TEL) = NULL;
  *(void**)(pessoa + NOME + INT + TEL + PtoP) = NULL;
  getchar();
  
  printf("ENDERECO DE PESSOA %p\n", &pessoa);
    printf("EM PESSOA %p\n", pessoa);
    printf("EM PESSOA* %c\n", *(char*)pessoa);

  if (!(*quantPessoas)) { // se quantPessoas == 0
    //armazenando pessoa na primeira posição da lista e da fila
    *(void**)(pBuffer + CHAR + NOME + INT*2) = pessoa;
    *(void**)(pBuffer + CHAR + NOME + INT*2 + PtoP) = pessoa;

    
  } 
  else { 
    //armazenando pessoa na posição seguinte disponivel
    void * pessoaAtual = *(void**)(pBuffer + CHAR + NOME + INT*2); //pessoaAtual = cabeça da lista
    void * proximo = *(void**)(pessoaAtual + NOME + INT + TEL);

    while (proximo != NULL) { // ??
      pessoaAtual = proximo;
      proximo = *(void**)(proximo + NOME + INT + TEL);
    }

    // pessoaAtual + sizeof(char)*10 + sizeof(int) + sizeof(long int) = &pessoa;
    *(void**)(pessoaAtual + NOME + INT + TEL) = pessoa; // ??
    printf("\n");
    //testar nomes para inserir na fila em ordem
  }


  // printf("char escolha = %c\n", *(char*)(pBuffer));
  // printf("int i = %d\n", *(int*)(pBuffer + sizeof(char)*11));
  // printf("int quantPessoas = %d\n", *(int*)(pBuffer + sizeof(char)*11 + sizeof(int)));
  // printf("void * lista = %p\n", *(void**)(pBuffer+ sizeof(char)*11 + sizeof(int)*2) );
  // printf("void * fila = %p\n", *(void**)(pBuffer+ sizeof(char)*11 + sizeof(int)*2 + sizeof(void*)) );  

  (*quantPessoas)++;
    




  return pBuffer;

}

void * remover(void * pBuffer) {

}

void * buscar(void * pBuffer) {

}

void listar(void * pBuffer) {
  void * pessoaAtual = *(void **)(pBuffer + sizeof(char)*11 + sizeof(int)*2);
  while (pessoaAtual != NULL) {
    printf("nome: %s - ", (char*)pessoaAtual);
    printf("\t%d anos - %d\n", *(int*)(pessoaAtual + NOME),  *(long int*)(pessoaAtual + NOME + INT));
    pessoaAtual = *(void**)(pessoaAtual + NOME + INT + TEL);
  }

  // char * proximo = pessoaAtual;
    // int * proximo = (int*)(pessoaAtual + sizeof(char)*10);
    // long int * proximo = (long int*)(pessoaAtual + sizeof(char)*10 + sizeof(int));
    // void * proximo = *(void**)(pessoaAtual + sizeof(char)*10 + sizeof(int) + sizeof(long int));


}

void listarOrdenado(void * pBuffer) {

}

void * fecharPrograma(void * pBuffer) {
  // free nos malloc
  printf("Tchau!");
}

void esperePeloEnter() {
  printf("\nPressione ENTER para continuar... ");
  getchar();
}