## 💻 algoritmos-estruturas-de-dados
Repositório para armazenar os exercícios referentes a cadeira de Algoritmos e Estruturas de Dados I e II do curso de Ciência da Computação.

## 📚 conteúdos
### algoritmos e estruturas de dados I
*Bibliografia: Algoritmos - Teoria e Prática, 3ª ed., Thomas Cormen.*
- Fila
  - Fila de prioridade
- Pilha
- Lista
- Árvore
  - Árvore AVL
  - Árvore Rubro-Negra
- Insertion Sort
- Selection Sort
- Quick Sort
- Merge Sort<br>

### algoritmos e estruturas de dados II
- Grafos
  - Dijsktra
  - Kruskall
- Hashing
- Tries
  - Árvore Patricia

## 🗂 organização
O prefixo inicial no nome de cada pasta dos exercícios identificam a qual disciplina este pertence. Sendo assim, caso o prexifo seja:
- **aed1**: os exercícios são referentes à conteúdos da cadeira Algoritmos e Estruturas de Dados I;
- **aed2**: os exercicios tem seu conteúdo ligado à cadeira de Algoritmos e Estruturas de Dados II.

Dentro de cada pasta, haverá um arquivo **.c** com o desenvolvimento do exercício (a descrição completa do mesmo estará comentado no corpo da resolução) e um arquivo **.txt** com testes para o desenvolvimento (este arquivo é *opcional*, portanto, algumas pastas podem não possui-lo).
Todos os exercícios são passados no [Dr. Memory](https://drmemory.org/)  para verificar a não existência de *leaks* de memória.

## exercícios
Segue abaixo resumo da descrição dos exercícios solicitados:<br>
**Exercício 2:** programa que deve adicionar e remover nomes da mesma *string* sem haver desperdício de memória.<br>
**Exercício 3:** agenda de contatos (nome, idade, telefone) armazenada em `void * pBuffer`. usar manipulação de memória.<br>
**Exercício 5:** adicionar quantas pessoas (nome, idade, altura) o usuário desejar e, antes de sair, listar os dados.<br>

 
## ⏯ executando os programas
Para executar os programas, você precisará dos arquivos em seu PC. Faça download de cada arquivo .c separadamente ou clone o repositório:<br>
`git clone https://github.com/dudaac1/algoritmos-estruturas-de-dados.git`<br><br>
Abra o terminal onde está localizado o arquivo .c.<br>
Compile:<br>
`gcc nomeArquivo.c -o nomeArquivo.exe`<br><br>
E depois execute o programa:<br>
`.\nomeArquivo.exe`<br><br>
Para utilizar os arquivos teste.txt presente em algumas das pastas, baixe-os se não tiver feito, coloque na mesma pasta do arquivo .c e execute o programa (após compilação):<br>
`.\nomeArquivo.exe < teste.txt`<br>


##
*Eduarda A. Carvalho, abril/2021.<br>
Última alteração: dezembro/2021.<br>
eduarda.carvalho@inf.ufpel.edu.br*
