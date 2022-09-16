#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <omp.h>

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

#endif

int mult_bloco_openmp (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc);
int mult_seq_openmp (int **mat_a, int **mat_b, int **mat_c, int N, int M, int La, int divisor);
