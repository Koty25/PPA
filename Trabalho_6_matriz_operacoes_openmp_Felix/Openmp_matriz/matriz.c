#include "matriz.h"
#include <time.h>

//Bugs: Arrumar o liberar_matriz para nao precisar do divisor.

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

matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor) {
  matriz_bloco_t **block = NULL;
  block = (matriz_bloco_t **) calloc(divisor, sizeof(matriz_bloco_t*));
  if (!block || !matriz) {
    printf("ERROR: Out of memory 2\n");
    return NULL;
  }
  for(int i = 0; i< divisor; i++){
    block[i] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
    block[i]->bloco = (bloco_t *) malloc(sizeof(bloco_t));
  }

  if(orientacao == 1){
    int linInit = 0;
    int linFinish = 0;
    for(int i=0; i<divisor; i++){
      linFinish = (i+1)*(mat_lin/divisor);
      block[i]->matriz = matriz;
      block[i]->bloco->lin_inicio = linInit;
      block[i]->bloco->lin_fim = linFinish;
      block[i]->bloco->col_inicio = 0;
      block[i]->bloco->col_fim = mat_col;
      linInit = (i+1) * (mat_lin/divisor);
    }
    // if(mat_lin%divisor != 0){
    //   block[divisor] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
    //   block[divisor]->bloco = (bloco_t *) malloc(sizeof(bloco_t));
    //   block[divisor]->matriz = matriz;
    //   block[divisor]->bloco->lin_inicio = divisor*(mat_lin/divisor);
    //   block[divisor]->bloco->lin_fim = mat_lin;
    //   block[divisor]->bloco->col_inicio = 0;
    //   block[divisor]->bloco->col_fim = mat_col;
    // }
    return block;
  }
  else {
    int colInit = 0;
    int colFinish = 0;
    for(int i=0; i<divisor; i++){
      colFinish = (i+1)* (mat_col/divisor);
      block[i]->matriz = matriz;
      block[i]->bloco->lin_inicio = 0;
      block[i]->bloco->lin_fim = mat_lin;
      block[i]->bloco->col_inicio = colInit;
      block[i]->bloco->col_fim = colFinish;
      colInit = (i+1)* (mat_col/divisor);
    }
    // if(mat_col%divisor != 0){
    //   block[divisor] = (matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
    //   block[divisor]->bloco = (bloco_t *) malloc(sizeof(bloco_t));
    //   block[divisor]->matriz = matriz;
    //   block[divisor]->bloco->lin_inicio = 0;
    //   block[divisor]->bloco->lin_fim = mat_lin;
    //   block[divisor]->bloco->col_inicio = divisor*(mat_col/divisor);
    //   block[divisor]->bloco->col_fim = mat_col;
    // }
    return block;
  }
  return NULL;
}



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
matriz_bloco_t **constroi_submatrizv2 (int mat_lin, int mat_col, int divisor) {
  matriz_bloco_t **vet_subc=NULL;
  vet_subc =  (matriz_bloco_t **) malloc(divisor*sizeof(matriz_bloco_t *));
  if (!vet_subc) {
    printf("ERROR: Out of memory 1\n");
  return NULL;
  }
  for (int i=0; i < divisor; i++){
    vet_subc[i]=(matriz_bloco_t *) malloc(sizeof(matriz_bloco_t));
    vet_subc[i]->bloco=(bloco_t *) malloc(sizeof(bloco_t));
    int **matil = NULL;
    matil = alocar_matriz(mat_lin, mat_col);
    zerar_matriz (matil, mat_lin, mat_col);
    vet_subc[i]->matriz = matil;
    vet_subc[i]->bloco->lin_inicio = 0;
    vet_subc[i]->bloco->lin_fim = mat_lin;
    vet_subc[i]->bloco->col_inicio = 0;
    vet_subc[i]->bloco->col_fim = mat_col;
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
