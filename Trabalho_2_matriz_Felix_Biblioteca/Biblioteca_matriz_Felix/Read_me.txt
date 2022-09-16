// Instrucoes de uso para a biblioteca de Ordenacao

//Utilizando a biblioteca atraves do terminal:

Nota 1: Esse codigo gera uma Matriz, aleatoria, com dimensoes MxN, definidas pelo usario dentro do arquivo Makefile. Para comparacao utiliza-se de uma segunda matriz de zeros.

Nota 2: Acesse o terminal atraves do atalho ctrl+alt+T (Ubuntu) ou atraves da interface grafica de seu sistema operacional.

Passo 1: Navegue ate o diretorio onde se encontra o arquivo comprimido da biblioteca. Pode-se utilizar os comandos "cd", e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados" sem as aspas e sendo Pasta1 e Programas_a_serem_avaliados o diretorio onde se econtra o arquivo comprimido Biblioteca_matriz_Felix.zip.

Passo 2: Descompacte a biblioteca utilizando o comando: "unzip Biblioteca_matriz_Felix.zip" sem as aspas.

Passo 3: Navegue para o diretorio da Biblioteca_matriz_Felix. e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados/Biblioteca_matriz_Felix" sem as aspas e sendo Pasta1, Programas_a_serem_avaliados e Biblioteca_matriz_Felix o diretorio onde se econtra os arquivos para a criacao da matriz.

Passo 4: Execute o Makefile atraves do comando: "make" sem as aspas.

Passo 5: Apos a compilacao, para criar a matriz e rodar o programa principal utilize o comando: "./main_matriz 10x10-mat.map mat_b_0.map" sem as aspas.

Nota 3: Pode-se utilizar o comando "./teste" para executar o programa teste, que criara uma matriz 10x10. Para modificar as dimensoes criadas atraves desse codigo, utilize a secao: "Dimensoes Matrizes ./teste".

Nota 4: Para mudar as dimensoes da matriz a ser gerada, utilize a secao: Dimensoes da Matriz.

Nota 5: Apos mudar as dimensoes da matriz a ser gerada, deve-se alterar a linha de comando utilizada no Passo 5 dessa secao, substituindo ambos os numerais 10 pelas novas linha e coluna escolhidas. e.g.: Matriz a ser gerada tem dimensoes 22x9. O comando do Passo 5 sera: "./main_matriz 22x9-mat.map mat_b_0.map" sem as aspas.





//Dimensoes da Matriz:

Nota 1: Secao para a alteracao das dimensoes da Matriz aleatoria gerada.

Passo 1: Navegue para o diretorio da Biblioteca_matriz_Felix.

Passo 2: Acesse o arquivo Makefile atraves de um editor de texto. Para fazer isso, pode-se utilizar o NE, digitando "ne" sem as aspas, no terminal. Clicando F1, e escolhendo a opcao "Open", pode-se entao escolher a opcao do arquivo "Makefile".

Passo 3: Altere a linha 25, sendo o primeiro numeral o numero de linhas da matriz e o segundo numeral o numero de colunas da matriz.

Passo 4: Salve o arquivo utilizando a combinacao de teclas ctrl+S ou apertando F1 e escolhendo a opcao de salvar.

Passo 5: Retorne ao Passo 3 da secao: "Utilizando a biblioteca atraves do terminal".





//Dimensoes Matrizes ./teste

Nota 1: Secao para a alteracao das dimensoes da Matriz gerada pelo comando ./teste.

Passo 1: Navegue para o diretorio da Biblioteca_matriz_Felix.

Passo 2: Acesse o arquivo teste.c atraves de um editor de texto. Para fazer isso, pode-se utilizar, por exemplo, o NE, digitando "ne" sem as aspas, no terminal. Clicando F1, e escolhendo a opcao "Open", pode-se entao escolher a opcao do arquivo "teste.c".

Passo 3: Altere a linha 7 e 8, sendo o primeiro numeral o numero de linhas da matriz e o segundo numeral o numero de colunas da matriz.

Passo 4: Salve o arquivo utilizando a combinacao de teclas ctrl+S ou apertando F1 e escolhendo a opcao de salvar.

Passo 5: Retorne ao Passo 3 da secao: "Utilizando a biblioteca atraves do terminal".
