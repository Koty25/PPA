//Instrucoes de uso para a biblioteca de Ordenacao

Passo 1: Abra o terminal utilizando ctrl+alt+t.

Passo 2: Navegue ate a pasta onde se encontra a biblioteca.

Passo 3: Utilize o makefile, digitando "make", sem aspas, no terminal e aperte Enter.

Passo 4: Copie "./sort vector-10.map", sem as aspas, no terminal e aperte Enter.
Nota 1: O numeral apos "vector-" dependera do tamanho do vetor escolhido dentro do make file. Para mudar o tamanho do vetor padrao, tamanho=10, acesse o makefile com qualquer editor de testo e modifique a linha "./gera_vector 10 -9999", sendo o primeiro argumento o tamanho do vetor, e o segundo a ordenacao do vetor (-9999=aleatorio, -8888=crescente, -7777=descrescente, 0=vetor 0).
Nota 2: Nao se esqueca de mudar o nome do arquivo "vector-" quando o tamanho do vetor for trocado.

Resultados: As saidas serao em ordem: Vetor antes de ser ordenado -> Vetor ordenado atraves do metodo Quick Sort -> Tempo de execucao do Quick Sort -> Vetor ordenado atraves do Bubble Sort -> Tempo de execucao do Bubble Sort -> Vetor ordenado atraves do metodo Merge Sort -> Tempo de execucao do Merge Sort
