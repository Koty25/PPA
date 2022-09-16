#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
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

void *mult_thread (void *arg);
void *mult_thread_bloco (void *arg);
void *multiplicar_bb (void *args);
int multiplicar_bloco_pthread (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc, int nro_threads);
int multiplicar_openmp (int **mat_a, int **mat_b, int **mat_c, int N, int M, int La, int Lb);
