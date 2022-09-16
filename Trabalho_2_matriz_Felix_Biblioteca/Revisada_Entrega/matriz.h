#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOME_HEADER_FILE_H
#define SOME_HEADER_FILE_H
typedef struct {
  int lin_inicio;
  int lin_fim;
  int col_inicio;
  int col_fim;
} bloco_t;

typedef struct {
  int **matriz;
  bloco_t *bloco;
  int mat_col;
  int mat_lin;
  int divisor;
} matriz_bloco_t;
#endif

int gerar_matriz(int **matriz, int linha, int coluna, int valor);
int zerar_matriz (int **matriz, int linha, int coluna);
int imprimir_matriz (int **matriz, int linha, int coluna);
int comparar_matriz (int **matriza, int **matrizb, int linha, int coluna);
int **liberar_matriz (int **matriz, int linha, int coluna);
int **alocar_matriz (int linha, int coluna);
