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

// principal
int main() {
  void * pBuffer;
  // char escolha; char nomeAux[10]; int i; int quantPessoas; void * lista; void * fila;
  pBuffer = malloc(sizeof(char)*11 + sizeof(int) + sizeof(int) + sizeof(void*) + sizeof(void*));
  if (!pBuffer) {
    printf("Desculpe, tivemos um problema.");
    exit(1);
  }

  *(int *)(pBuffer + sizeof(char)*11 + sizeof(int)) = 0; // quantPessoas = 0
  *(char **)(pBuffer + sizeof(char)*11 + sizeof(int)*2) = NULL; // *nome1Lista = NULL
  *(char **)(pBuffer + sizeof(char)*11 + sizeof(int)*2 + sizeof(char *)) = NULL; // *nome1Fila = NULL

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
  int * quantPessoas = (pBuffer + sizeof(char)*11 + sizeof(int));
  if (*quantPessoas == 0) {
    printf("lista vazia\n");
  }


  //recebendo dados da nova pessoa
  //char nome[10]; int idade; long int telefone; void * proximo; void * anterior;
  void * pessoa = malloc(sizeof(char)*10 + sizeof(int) + sizeof(long int) + sizeof(void *)*2);
  printf("Insira nome: ");
  scanf("%s", (char*)pessoa);
  printf("Insira idade: ");
  scanf("%d", (int*)(pessoa + sizeof(char)*10));
  printf("Insira telefone:");
  scanf("%ld", (long int*)(pessoa + sizeof(char)*10 + sizeof(int)));
  *(void**)(pessoa + sizeof(char)*10 + sizeof(int) + sizeof(long int)) = NULL;
  *(void**)(pessoa + sizeof(char)*10 + sizeof(int) + sizeof(long int) + sizeof(void*)) = NULL;
  
  if (*quantPessoas == 0) { 
    //armazenando pessoa na primeira posição da lista e da fila
    *(void**)(pBuffer + sizeof(char)*11 + sizeof(int)*2) = pessoa;
    *(void**)(pBuffer + sizeof(char)*11 + sizeof(int)*2 + sizeof(char*)) = pessoa;
  } 
  else { 
    //armazenando pessoa na posição seguinte disponivel
    void * pessoaAtual = (void**)(pBuffer+ sizeof(char)*11 + sizeof(int)*2); //pessoaAtual = cabeça da lista
    
    void * proximo = (void**)(pessoaAtual + sizeof(char)*10 + sizeof(int) + sizeof(long int));

    while (proximo != NULL) {
      pessoaAtual = proximo;
      proximo = &*(void**)(proximo + sizeof(char)*10 + sizeof(int) + sizeof(long int));
    }

    // pessoaAtual + sizeof(char)*10 + sizeof(int) + sizeof(long int) = &pessoa;
    *(void**)(pessoaAtual + sizeof(char)*10 + sizeof(int) + sizeof(long int)) = pessoa;

    // TRAVADA
    // AQUI
    // QUE
    // ODIO !!!
    // proximo = &pessoa; // armazenou -x61fe90 em *proximo
    // printf("%s", (char*)proximo);

    //testar nomes para inserir na fila
  }

  printf("char escolha = %c\n", *(char*)(pBuffer));
  printf("int i = %d\n", *(int*)(pBuffer + sizeof(char)*11));
  printf("int quantPessoas = %d\n", *(int*)(pBuffer + sizeof(char)*11 + sizeof(int)));
  printf("void * lista = %p\n", *(void**)(pBuffer+ sizeof(char)*11 + sizeof(int)*2) );
  printf("void * fila = %p\n", *(void**)(pBuffer+ sizeof(char)*11 + sizeof(int)*2 + sizeof(void*)) );  

  *quantPessoas += 1;
    




  return pBuffer;

}

void * remover(void * pBuffer) {

}

void * buscar(void * pBuffer) {

}

void listar(void * pBuffer) {
  void * pessoaAtual = *(void **)(pBuffer + sizeof(char)*11 + sizeof(int)*2);
  printf("%s - ", (char*)pessoaAtual);
  printf("%d - ", *(int*)(pessoaAtual + sizeof(char)*10));
  printf("%d", *(int*)(pessoaAtual + sizeof(char)*10 + sizeof(int)));

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