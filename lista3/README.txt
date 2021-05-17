# EXERCICIO 3
Implemente uma árvore AVL.
• PARTE 1: O programa só pergunta um número para o usuário, que será a quantidade de nós. O programa automaticamente gera n nós em sequência com valor aleatório e vai adicionando na árvore. Use srand(time(0)). Ao final, use um código de verificação (já fornecido) para validar a árvore e dar ok.
• PARTE 2: Após a execução da primeira parte, deve-se testar a árvore com os casos mostrados no seguinte link: https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct

# DIRETÓRIOS
    |-- exerc3
    |   ∟ exerc3.c
    |   ∟ teste1.txt
    |   ∟ teste2.txt

# EXECUTANDO OS PROGRAMAS (compilação manual)
Para executar os arquivos, você precisa dos arquivos em seu PC.
Faça download de cada arquivo .c separadamente ou clone o repositório (git clone https://github.com/dudaac1/aed1-exercicios.git).

Abra o terminal na pasta onde está localizado o arquivo .c.
Compile o programa (gcc nomeArquivo.c -o nomeArquivo.exe).
Execute o programa (.\nomeArquivo.exe).

Você também pode utilizar o arquivo de teste.txt presente na pasta do exercício 3.
Para isso, baixe o arquivo e, na hora de executar o programa, coloque o seguinte comando: .\nomeArquivo.exe < teste.txt

# OBSERVAÇÕES
A parte 1 do exercício pode ser acessado ao chamar a opção 1 do programa. A parte 2, a partir da opção 2. Os arquivos de teste possuem o número referente a opção (ou seja, teste1.txt testa a opção 1).
A parte 2 foi criada a partir do seguinte post https://stackoverflow.com/a/3958672, sendo realizados, então, inserções que gerassem as 4 rotações, remoções que gerassem as 4 rotações, e uma pesquisa breve que retorna o nodo pesquisado.
Foram utilizados as constantes TRUE e FALSE e um int de nome BOOLEAN para melhor legibilidade do programa, tendo em vista que, por causa da recursão, tive um pouco de dificuldade inicial para entender o código fornecido pelo professor.
Utilizei os vídeos sobre árvore AVL do Canal Programação Descomplicada como base para a função de Remover Nodo. Acredito que esta parte poderia estar melhor otimizada.

___________________________________
Eduarda A. Carvalho (eduarda.carvalho@inf.ufpel.edu.br).