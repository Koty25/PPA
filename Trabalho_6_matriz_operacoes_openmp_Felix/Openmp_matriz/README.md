# Operaçoes matrizes openMP

Esse programa tem como objetivo a multiplicação (ikj) e em blocos de duas matrizes com dimensões MxN.

**Os resultados individuais estão contidos em seu próprios arquivos <out*.map-result>. Esses arquivos podem ser acessados atraves do terminal inserindo o comando: "cat <out*.map-result>" e.g.: "cat somarIJ.map-result", sem as aspas.**

*Instruções resumidas:*

################################################################################################################################
# 1. Utilize o makefile para a escolha das dimensões da matriz.                                                                #
# 2. Compile o código com "make".                                                                                              #
# 3. Rode o programa com "make run" (alternativamente utilize ./main_omp 1000x1000-mat.map 1000x1000-mat.map).              #
# 4. Pode-se gerar uma nova matriz com o comando "make matriz". As dimensões se encontram no makefile                          #
#    (alternativamente use ./gera_matriz2"DIMENSAO_X""DIMENSAO_Y").                                                            #
################################################################################################################################

**Ao se gerar uma matriz com o comando "./gera_matriz2", utilize o método alternativo para executar o código (./main_omp 1000x1000-mat.map 1000x1000-mat.map).**             


## Intruções expandidas:

Nota 1: Esse código gera uma matriz, aleatória, com dimensão MxN, definidas pelo usuário dentro do arquivo Makefile.

Nota 2: Acesse o terminal através do atalho ctrl+alt+T (Ubuntu) ou através da interface gráfica de seu sistema operacional.

>Passo 1: Navegue ate o diretório onde se encontra o arquivo comprimido da biblioteca. Pode-se utilizar os comandos "cd", e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados" sem as aspas e sendo Pasta1 e Programas_a_serem_avaliados o diretório onde se encontra o arquivo comprimido Openmp_matriz.zip.

>Passo 2: Descompacte a biblioteca utilizando o comando: "unzip Openmp_matriz.zip" sem as aspas.

>Passo 3: Navegue para o diretório da Openmp_matriz. e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados/Biblioteca_matriz_Felix" sem as aspas e sendo Pasta1, Programas_a_serem_avaliados e Biblioteca_matriz_Felix o diretório onde se encontra os arquivos para a criação da matriz.

>Passo 4: Execute o Makefile através do comando: "make" sem as aspas.

>Passo 5: Apos a compilação, para criar a matriz e rodar o programa principal utilize o comando: "./main_omp 10x10-mata.map 10x10-matb.map" sem as aspas.

Nota 3: Para mudar as dimensões da matriz a ser gerada, utilize a seção: Dimensões da Matriz.

Nota 4: Apos mudar as dimensões da matriz a ser gerada, deve-se alterar a linha de comando utilizada no Passo 5 dessa seção, substituindo ambos os numerais 10 pelas novas linha(s) e coluna(s) escolhidas. e.g.: Matriz A a ser gerada tem dimensoes 22x9 e Matriz B tem dimens�es 9x55. O comando do Passo 5 sera: "./main_omp 22x9-mat.map 9x55-mat.map" sem as aspas.





## Dimensões da Matriz:

Nota 1: Seção para a alteração das dimensões das matrizes aleatórias geradas.

Passo 1: Navegue para o diretório da Biblioteca_matriz_Felix.

>Passo 2: Acesse o arquivo Makefile através de um editor de texto. Para fazer isso, pode-se utilizar o NE, digitando "ne" sem as aspas, no terminal. Clicando F1, e escolhendo a opção "Open", pode-se então escolher a opÇão do arquivo "Makefile".

>Passo 3: Altere a linha 11 e 12, sendo a primeira linha o numero de linhas da matriz e a segunda linha o numero de colunas da matriz.

>Passo 4: Salve o arquivo utilizando a combinação de teclas ctrl+S ou apertando F1 e escolhendo a opção de salvar.

>Passo 5: Retorne ao Passo 3 da seção: "Utilizando a biblioteca através do terminal".

Nota 2: Pode-se também criar uma matriz através do comando:"./gera_matriz2 M N", sem as aspas. Esse comando tem 2 argumentos, sendo o primeiro o numero de linhas e o segundo argumento é o numero de colunas.

Nota 3: Ao gerar a matriz através do comando proposta na Nota 2 dessa seção, a matriz conterão valores completamente diferentes, pois a seed do rand está sendo controlada pelo tempo atual.
