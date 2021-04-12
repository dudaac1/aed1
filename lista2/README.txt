# EXERCICIO 5
Faça um programa que armazene a informação de várias pessoas.
    typedef struct {
        char nome[30];
        int idade;
        int altura;
    } Pessoa;
O programa só deve sair quando o usuário disser que não deseja mais entrar com os dados de outra pessoa.
Antes de sair o programa deve apresentar, de forma organizada, os dados de todas as pessoas.

# EXERCICIO 7
Inverso do exercício 3 da Lista 1.
O programa deve armazenar no máximo 10 pessoas.
Todas as variáveis que forem usadas no programa deve ser ponteiros. A única exceção é o item 1 que deve ser uma variável global Pessoa pessoas[10]
    • Os ponteiros devem apontar para um buffer chamado pBuffer onde os dados devem ser armazenados. Por exemplo, um contador para um for deve ser um ponteiro para int e o int vai ficar armazenado dentro de pBuffer.

# DIRETÓRIOS
    |-- exerc5
    |   ∟ exerc5.c
    |   ∟ teste.txt
    |
    |-- exerc7
    |   ∟ exerc7.c 
    |   ∟ teste.txt

# EXECUTANDO OS PROGRAMAS (compilação manual)
Para executar os arquivos, você precisa dos arquivos em seu PC.
Faça download de cada arquivo .c separadamente ou clone o repositório (git clone https://github.com/dudaac1/aed1-exercicios.git).

Abra o terminal na pasta onde está localizado o arquivo .c.
Compile o programa (gcc nomeArquivo.c -o nomeArquivo.exe).
Execute o programa (.\nomeArquivo.exe).

Você também pode utilizar os arquivos de teste.txt presentes em cada pasta. Para isso, baixe-os e, na hora de executar o programa, coloque o seguinte comando: .\nomeArquivo.exe < teste.txt


___________________________________
Eduarda A. Carvalho (eduarda.carvalho@inf.ufpel.edu.br).