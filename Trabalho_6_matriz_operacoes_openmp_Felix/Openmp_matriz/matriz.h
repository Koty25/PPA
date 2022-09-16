#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOME_HEADER_FILE_H
#define SOME_HEADER_FILE_H
typedef struct bloco_t{
  int lin_inicio;
  int lin_fim;
  int col_inicio;
  int col_fim;
} bloco_t;

typedef struct matriz_bloco_t{
  int **matriz;
  bloco_t *bloco;
} matriz_bloco_t;

typedef struct param_t{
  int tid;
  int ntasks;
  int N;
  int M;
  int L;
  int **matriza;
  int **matrizb;
  int **matrizc;
} param_t;

typedef struct param_bloco{
  int inicio;
  int final;
  int **mat_suba;
  int **mat_subb;
  int **mat_subc;
  int Col_inicio_a;
  int Col_fim_a;
  int Lin_inicio_b;
  int Lin_fim_b;
  int Col_inicio_b;
  int Col_fim_b;
} param_bloco;

#endif

int gerar_matriz(int **matriz, int linha, int coluna, int valor);
int zerar_matriz (int **matriz, int linha, int coluna);
int imprimir_matriz (int **matriz, int linha, int coluna);
int comparar_matriz (int **matriza, int **matrizb, int linha, int coluna);
int **liberar_matriz (int **matriz, int linha, int coluna);
int **alocar_matriz (int linha, int coluna);

//submatriz
//int gerar_submatriz (int **mat_origem, matriz_bloco_t *submatriz, bloco_t *bloco);
//int imprimir_submatriz (matriz_bloco_t *submatriz);
matriz_bloco_t **particionar_matriz (int **matriz, int mat_lin, int mat_col, int orientacao, int divisor);
matriz_bloco_t **liberar_submatriz (matriz_bloco_t **submatriz, int divisor);
//int imprimir_bloco (matriz_bloco_t *submatriz);
matriz_bloco_t **constroi_submatrizv2 (int mat_lin, int mat_col, int divisor);
