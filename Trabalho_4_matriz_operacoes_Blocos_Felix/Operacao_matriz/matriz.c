#include "matriz.h"
#include <time.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int gerar_matriz(int **matriz, int linha, int coluna, int valor){
  srand(time(0));
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
				printf("O elemento [%d,%d] é diferente nas matrizes analisadas!", i,j);
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

// //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// int gerar_submatriz (int **mat_origem, matriz_bloco_t *submatriz, bloco_t *bloco) {
//         #TODO
//   return 0;
// }
//
// // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// int imprimir_submatriz (matriz_bloco_t *submatriz){
//         #TODO
// 	return 0;
//}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// int imprimir_bloco (matriz_bloco_t *submatriz) {
//         #TODO
// 	return 0;
// }

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// orientacao, 1 corte horizontal, 0 para corte vertical
matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor) {
  matriz_bloco_t **block = NULL;
  block = (matriz_bloco_t **) calloc(divisor, sizeof(matriz_bloco_t*));
  if (!block || !matriz) {
    printf("ERROR: Out of memory\n");
    return NULL;
  }
  for(int i = 0; i< divisor; i++){
    block[i] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
    block[i]->bloco = (bloco_t *) malloc(sizeof(bloco_t));
  }

  if(orientacao == 0){
    int linInit = 0;
    int linFinish = mat_col/divisor;
    for(int i=0; i<divisor; i++){
      block[i]->matriz = matriz;
      block[i]->bloco->lin_inicio = linInit;
      block[i]->bloco->lin_fim = linFinish;
      block[i]->bloco->col_inicio = 0;
      block[i]->bloco->col_fim = mat_col;
      linInit = mat_col/divisor;
      linFinish = mat_lin;
    }
    return block;
  } else {
    int colInit = 0;
    int colFinish = mat_lin/divisor;
    for(int i=0; i<divisor; i++){
      block[i]->matriz = matriz;
      block[i]->bloco->lin_inicio = 0;
      block[i]->bloco->lin_fim = mat_lin;
      block[i]->bloco->col_inicio = colInit;
      block[i]->bloco->col_fim = colFinish;
      colInit = mat_lin/divisor;
      colFinish = mat_col;
    }
    return block;
  }
  return NULL;
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
matriz_bloco_t **constroi_submatrizv2 (int mat_lin, int mat_col, int divisor) {
  matriz_bloco_t **vet_subc=NULL;
  vet_subc =  (matriz_bloco_t **) malloc(divisor*sizeof(matriz_bloco_t *));
  if (!block) {
    printf("ERROR: Out of memory\n");
  return NULL;
  }
  for (int i=0; i < divisor; i++){
    vet_subc[i]=(matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
    vet_subc[i]->bloco=(bloco_t *) malloc(sizeof(bloco_t));
    int **matil = alocar_matriz(mat_lin, mat_col);
    block[i]->matriz = matil;
    block[i]->bloco->lin_inicio = 0;
    block[i]->bloco->lin_fim = mat_lin;
    block[i]->bloco->col_inicio = 0;
    block[i]->bloco->col_fim = mat_col;
  }
  return vet_subc;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz, int divisor) {
    for(int i = 0; i<divisor; i++){
      free(submatriz[i]->bloco);
      free(submatriz[i]);
    }
    free(submatriz);
  return NULL;
}
