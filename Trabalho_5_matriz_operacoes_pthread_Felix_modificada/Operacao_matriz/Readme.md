// Desatualizado
//Instruções de uso para a biblioteca de Operações matriciais

Esse programa tem como objetivo a soma (ij e ji), multiplicação (ijk, jki, jik, ikj, kij e kji) e em blocos de duas matrizes com dimensões MxN.

Os resultados individuais estão contidos em seu proprios arquivos <out*.map-result>. Esses arquivos podem ser acessados atraves do terminal inserindo o comando: "cat <out*.map-result>" e.g.: "cat somarIJ.map-result", sem as aspas.


//Utilizando a biblioteca através do terminal:

Nota 1: Esse código gera duas matrizes, aleatórias, com dimensões MxN, definidas pelo usário dentro do arquivo Makefile.

Nota 2: Acesse o terminal através do atalho ctrl+alt+T (Ubuntu) ou através da interface gráfica de seu sistema operacional.

Passo 1: Navegue ate o diretório onde se encontra o arquivo comprimido da biblioteca. Pode-se utilizar os comandos "cd", e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados" sem as aspas e sendo Pasta1 e Programas_a_serem_avaliados o diretório onde se encontra o arquivo comprimido Operacao_matriz.zip.

Passo 2: Descompacte a biblioteca utilizando o comando: "unzip Operacao_matriz.zip" sem as aspas.

Passo 3: Navegue para o diretório da Operacao_matriz. e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados/Biblioteca_matriz_Felix" sem as aspas e sendo Pasta1, Programas_a_serem_avaliados e Operacao_matriz o diretório onde se encontra os arquivos para a criação da matriz.

Passo 4: Execute o Makefile através do comando: "make" sem as aspas.

Passo 5: Apos a compilação, para criar a matriz e rodar o programa principal utilize o comando: "./main_matriz 10x10-mata.map 10x10-matb.map" sem as aspas.

Nota 3: Para mudar as dimensões da matriz a ser gerada, utilize a seção: Dimensões da Matriz.

Nota 4: Apos mudar as dimensões da matriz a ser gerada, deve-se alterar a linha de comando utilizada no Passo 5 dessa seção, substituindo ambos os numerais 10 pelas novas linha(s) e coluna(s) escolhidas. e.g.: Matriz A a ser gerada tem dimensoes 22x9 e Matriz B tem dimensões 9x55. O comando do Passo 5 sera: "./main_matriz 22x9-mata.map 9x55-matb.map" sem as aspas.





//Dimensões da Matriz:

Nota 1: Seção para a alteração das dimensões das matrizes aleatórias geradas.

Passo 1: Navegue para o diretório da Biblioteca_matriz_Felix.

Passo 2: Acesse o arquivo Makefile através de um editor de texto. Para fazer isso, pode-se utilizar o NE, digitando "ne" sem as aspas, no terminal. Clicando F1, e escolhendo a opção "Open", pode-se então escolher a opção do arquivo "Makefile".

Passo 3: Altere a linha 25 (matriz A) e/ou 26 (matriz B), sendo o primeiro numeral de cada linha o numero de linhas da matriz e o segundo numeral o numero de colunas da matriz (o terceiro argumento de cada linha denota a matriz a ser gerada, podendo ela ser "a" ou "b").

Passo 4: Salve o arquivo utilizando a combinação de teclas ctrl+S ou apertando F1 e escolhendo a opção de salvar.

Passo 5: Retorne ao Passo 3 da seção: "Utilizando a biblioteca através do terminal".

Nota 2: Pode-se também criar uma matriz através do comando:"./gera_matriz2 M N Matriz", sem as aspas. Esse comando tem 3 argumentos, sendo o primeiro o numero de linhas, o segundo argumento é o numero de colunas e o terceiro argumento é a Matriz a ser gerada (aceita os valores "a" ou "b", sem as aspas).

Nota 3: Ao gerar as matrizes através do comando proposta na Nota 2 dessa seção, as matrizes conterão valores completamente diferentes, pois a seed do rand está sendo controlado pelo tempo atual.
