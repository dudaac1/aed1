#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa
{
    char nome[30];
    int idade;
    int altura;
    struct pessoa *prox;
} Pessoa;

void Inserir(Pessoa **listaPessoas);
void Listar(Pessoa *listaPessoas);
void FinalizarPrograma(Pessoa *listaPessoas);

int main() {
    Pessoa *listaPessoas = NULL; //o conteudo de listaPessoas = vazio/nulo
    char escolha;
    do {
        printf("Inserir dados de uma pessoa? S - sim; N - nao:  ");
        scanf(" %c%*[^\n]", &escolha);
        switch (escolha) {
        case 's':
        case 'S':
            printf("\n\t# INSERINDO NOVA PESSOA #\n");
            Inserir(&listaPessoas); //enviando o endereço de memória de listaPessoas
            break;

        case 'n':
        case 'N':
            printf("\n\t# LISTANDO PESSOAS #\n");
            Listar(listaPessoas);
            printf("\nTchau!");
            FinalizarPrograma(listaPessoas);
            exit(0);

        default:
            printf("Opcao nao reconhecida.\n");
            getchar();
            break;
        }
    } while (escolha != 'n' || escolha == 'N');
}

void Inserir(Pessoa **listaPessoas)
{
    getchar();
    printf("Digite nome: ");
    char nome[30], letra;
    int i = 0;
    while (((letra = getchar()) != '\n') && i < 30) { //caracter a caracter, inclusive espaços
        nome[i] = letra;
        i++;
    }
    if (i==30) { //teste para remover caracteres excedentes
        while ((letra = getchar()) != '\n' && letra != EOF) {}
        i--;
    }
    if (strlen(nome) == 0) {
		printf("Palavras vazias nao sao nomes.\n");
		return;
	}

    nome[i] = '\0';

    int idade;
    printf("Digite idade: ");
    scanf("%d", &idade);
    getchar();
    while (idade < 0) {
        printf("Idade e positiva, insira outro valor: ");
        scanf("%d", &idade);
        getchar();
    }

    int altura;
    printf("Agora sua altura (em centimetros): ");
    scanf("%d", &altura);
    getchar();
    while (altura < 0) {
        printf("Altura e positiva, insira outro valor: ");
        scanf("%d", &altura);
        getchar();
    }
    while (altura > 300) {
        printf("Eu nunca conheci alguem com mais de 3m. Insira outro valor: ");
        scanf("%d", &altura);
        getchar();
    }

    if (*listaPessoas == NULL) {
        *listaPessoas = (Pessoa *)malloc(sizeof(Pessoa));
        if(!listaPessoas) {
            printf("Um erro inesperado aconteceu. Tente novamente mais tarde.\n");
            return;
        }
        strcpy((*listaPessoas)->nome, nome);
        (*listaPessoas)->altura = altura;
        (*listaPessoas)->idade = idade;
        (*listaPessoas)->prox = NULL;
    }
    else {
        Pessoa *novaPessoa, *pessoaAtual;
        pessoaAtual = *listaPessoas;
        while (pessoaAtual->prox != NULL) {
            pessoaAtual = pessoaAtual->prox;
        }
        novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));
        if(!novaPessoa) {
            printf("Um erro inesperado aconteceu. Tente novamente mais tarde.\n");
            return;
        }
        strcpy(novaPessoa->nome, nome);
        novaPessoa->altura = altura;
        novaPessoa->idade = idade;
        novaPessoa->prox = NULL;
        pessoaAtual->prox = novaPessoa;
    }
    printf("Novos dados incluido na lista.\n\n");
}

void Listar(Pessoa *listaPessoas) {
    Pessoa *pessoaAtual = listaPessoas;
    if (listaPessoas == NULL) {
        printf("Nenhuma informacao encontrada.\n\n");
    }
    else {
        while (pessoaAtual != NULL) {
            printf("Nome: %s\n", pessoaAtual->nome);
            printf("Idade: %d\n", pessoaAtual->idade);
            printf("Altura: %d\n\n", pessoaAtual->altura);
            pessoaAtual = pessoaAtual->prox;
        }
    }
    getchar();
}

void FinalizarPrograma(Pessoa *listaPessoas) {
    Pessoa *pessoaAtual = listaPessoas;
    while (pessoaAtual != NULL) {
        listaPessoas = pessoaAtual->prox;
        free(pessoaAtual);
        pessoaAtual = listaPessoas;
    }
}