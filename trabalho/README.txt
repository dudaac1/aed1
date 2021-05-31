# DESCRIÇÃO
Continuar a sua implementação da agenda (lista1, exercício 3) dentro dos mesmos parâmetros, porém incluir o seguinte:
Nenhuma variável pode ser declarado em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
• Exemplo do que não pode: int c; char a; int v[10];
• Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
Imprimir de forma ordenada usando uma fila ordenada.
• O usuário escolhe um parâmetro de ordenação e uma fila ordenada é criada.
• Depois o programa imprime na tela o conteúdo da fila.
Implementar a base de dados da agenda usando lista duplamente ligada.
• Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.

# DIRETÓRIOS
    |-- trabalho
    |   ∟ agenda.c
    |   ∟ teste.txt

# EXECUTANDO OS PROGRAMAS (compilação manual)
Para executar os arquivos, você precisa dos arquivos em seu PC.
Faça download de cada arquivo .c separadamente ou clone o repositório (git clone https://github.com/dudaac1/aed1-exercicios.git).

Abra o terminal na pasta onde está localizado o arquivo .c.
Compile o programa (gcc nomeArquivo.c -o nomeArquivo.exe).
Execute o programa (.\nomeArquivo.exe).

# OBSERVAÇÕES
Tive um pouco de dificuldade de implementar a função Delete, pois em versões anteriores com exercícios semelhantes, eu utilizava a função Buscar/Search para retornar os dados os quais seriam removidos. Neste trabalho, as função Delete e Search estão isoladas uma da outra, cada uma fazendo a busca por si.
Também tive um pouco de dificuldade para implementar a função de ordenar a lista e acabei por desenvolver uma função que trocasse apenas o conteúdo (nome, idade e telefone) de nodo, sem mexer nos ponteiros referentes aos nodos anteriores ou seguintes.

___________________________________
Eduarda A. Carvalho (eduarda.carvalho@inf.ufpel.edu.br).