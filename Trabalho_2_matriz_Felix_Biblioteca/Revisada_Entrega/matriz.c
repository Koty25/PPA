#include "matriz.h"
#include <time.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int gerar_matriz(int **matriz, int linha, int coluna, int valor){
  for (int i=0; i < linha; i++)
	  for (int j=0; j < coluna; j++)
			if (valor == -9999)
				matriz[i][j] = rand() % 10;
			else
				matriz[i][j] = valor;
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int zerar_matriz (int **matriz, int linha, int coluna){
	return gerar_matriz(matriz,linha,coluna,0);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int imprimir_matriz (int **matriz, int linha, int coluna){
	for (int j =0; j < coluna; j++)
		printf("\t(%d)", j);
	printf("\n");
	for (int i=0; i < linha; i++) {
		printf("(%d)", i);
	  for (int j=0; j < coluna; j++){
			printf("\t%d", matriz[i][j]);
		}
		printf("\n");
	}
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int comparar_matriz (int **matriza, int **matrizb, int linha, int coluna){
	for (int j =0; j < coluna; j++)
	for (int i=0; i < linha; i++) {
	  for (int j=0; j < coluna; j++){
			if (matriza[i][j] != matrizb[i][j]) {
				printf("O elemento [%d,%d] é diferente nas matrizes analisadas!\n", i,j);
				return 1;
			}
		}

	}
	printf("VERIFICADO: Matrizes identicas\n");
	return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int **liberar_matriz (int **matriz, int linha, int coluna) {
  for (int i =0; i < linha; i++)
			free(matriz[i]);
	free(matriz);
	return NULL;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int **alocar_matriz (int linha, int coluna) {
  int **nova_a = NULL;

	nova_a = (int **) malloc(linha*sizeof(int *));
	if (!nova_a) {
		printf("ERROR: Out of memory\n");
		return NULL;
	}

  for (int i =0; i < linha; i++) {
			nova_a[i] = (int *) malloc(sizeof(int)*coluna);
			if (!nova_a) {
				printf("ERROR: Out of memory\n");
				return NULL;
			}
	}
	return nova_a;
}
