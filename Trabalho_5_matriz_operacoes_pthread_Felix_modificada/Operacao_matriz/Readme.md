// Desatualizado
//Instru��es de uso para a biblioteca de Opera��es matriciais

Esse programa tem como objetivo a soma (ij e ji), multiplica��o (ijk, jki, jik, ikj, kij e kji) e em blocos de duas matrizes com dimens�es MxN.

Os resultados individuais est�o contidos em seu proprios arquivos <out*.map-result>. Esses arquivos podem ser acessados atraves do terminal inserindo o comando: "cat <out*.map-result>" e.g.: "cat somarIJ.map-result", sem as aspas.


//Utilizando a biblioteca atrav�s do terminal:

Nota 1: Esse c�digo gera duas matrizes, aleat�rias, com dimens�es MxN, definidas pelo us�rio dentro do arquivo Makefile.

Nota 2: Acesse o terminal atrav�s do atalho ctrl+alt+T (Ubuntu) ou atrav�s da interface gr�fica de seu sistema operacional.

Passo 1: Navegue ate o diret�rio onde se encontra o arquivo comprimido da biblioteca. Pode-se utilizar os comandos "cd", e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados" sem as aspas e sendo Pasta1 e Programas_a_serem_avaliados o diret�rio onde se encontra o arquivo comprimido Operacao_matriz.zip.

Passo 2: Descompacte a biblioteca utilizando o comando: "unzip Operacao_matriz.zip" sem as aspas.

Passo 3: Navegue para o diret�rio da Operacao_matriz. e.g.: "cd ~/Pasta1/Programas_a_serem_avaliados/Biblioteca_matriz_Felix" sem as aspas e sendo Pasta1, Programas_a_serem_avaliados e Operacao_matriz o diret�rio onde se encontra os arquivos para a cria��o da matriz.

Passo 4: Execute o Makefile atrav�s do comando: "make" sem as aspas.

Passo 5: Apos a compila��o, para criar a matriz e rodar o programa principal utilize o comando: "./main_matriz 10x10-mata.map 10x10-matb.map" sem as aspas.

Nota 3: Para mudar as dimens�es da matriz a ser gerada, utilize a se��o: Dimens�es da Matriz.

Nota 4: Apos mudar as dimens�es da matriz a ser gerada, deve-se alterar a linha de comando utilizada no Passo 5 dessa se��o, substituindo ambos os numerais 10 pelas novas linha(s) e coluna(s) escolhidas. e.g.: Matriz A a ser gerada tem dimensoes 22x9 e Matriz B tem dimens�es 9x55. O comando do Passo 5 sera: "./main_matriz 22x9-mata.map 9x55-matb.map" sem as aspas.





//Dimens�es da Matriz:

Nota 1: Se��o para a altera��o das dimens�es das matrizes aleat�rias geradas.

Passo 1: Navegue para o diret�rio da Biblioteca_matriz_Felix.

Passo 2: Acesse o arquivo Makefile atrav�s de um editor de texto. Para fazer isso, pode-se utilizar o NE, digitando "ne" sem as aspas, no terminal. Clicando F1, e escolhendo a op��o "Open", pode-se ent�o escolher a op��o do arquivo "Makefile".

Passo 3: Altere a linha 25 (matriz A) e/ou 26 (matriz B), sendo o primeiro numeral de cada linha o numero de linhas da matriz e o segundo numeral o numero de colunas da matriz (o terceiro argumento de cada linha denota a matriz a ser gerada, podendo ela ser "a" ou "b").

Passo 4: Salve o arquivo utilizando a combina��o de teclas ctrl+S ou apertando F1 e escolhendo a op��o de salvar.

Passo 5: Retorne ao Passo 3 da se��o: "Utilizando a biblioteca atrav�s do terminal".

Nota 2: Pode-se tamb�m criar uma matriz atrav�s do comando:"./gera_matriz2 M N Matriz", sem as aspas. Esse comando tem 3 argumentos, sendo o primeiro o numero de linhas, o segundo argumento � o numero de colunas e o terceiro argumento � a Matriz a ser gerada (aceita os valores "a" ou "b", sem as aspas).

Nota 3: Ao gerar as matrizes atrav�s do comando proposta na Nota 2 dessa se��o, as matrizes conter�o valores completamente diferentes, pois a seed do rand est� sendo controlado pelo tempo atual.
