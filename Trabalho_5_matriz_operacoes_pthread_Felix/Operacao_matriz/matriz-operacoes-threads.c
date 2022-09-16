#include "matriz-operacoes-threads.h"
#include "matriz-operacoes.h"


void *mult_thread (void *arg) {
  param_t *p = (param_t *) arg;
  int passo, ini, fin, N, M, L;

  N = p->N;
  M = p->M;
  L = p->L;
  passo = N/p->n_tasks;
  ini = p->tid*passo;
  fin = (p->tid+1)*passo;

  for(int i=inicio; i < final; i++){
    for(int k=0; k< L; k++){
      for(int j=0; j< M; j++){
        p->matrizc[i][k]+= p->matriza[i][j]*p->matrizb[j][k];
      }
    }
  }

  return NULL;
}


void *mult_thread_bloco (void *arg) {
  param_t *p = (param_t *) arg;
  //printf ("(mult_thread) thread_init(%d); matriza [0][0] = %d matrizb [0][0]= %d matrizc[0][0] = %d\n", p->tid, p->matriza[0][0], p->matrizb[0][0], p->matrizc[0][0]);
  for (int z=0; z<(p->ntasks); z++){
    for(int i = p->submatriza[p->tid]->bloco->lin_inicio; i < p->submatriza[p->tid]->bloco->lin_fim; i++){
      for(int k = p->submatriza[p->tid]->bloco->col_inicio; k < p->submatriza[p->tid]->bloco->col_fim; k++){
        for(int j = p->submatrizb[z]->bloco->col_inicio; j < p->submatrizb[z]->bloco->col_fim; j++){
          p->submatrizc[p->tid]->matriz[i][j] += p->submatriza[p->tid]->matriz[i][k] * p->submatrizb[z]->matriz[k][j];
        }
      }
    }
  }
    // for(int k=0; k<((p->divisor)-1); k=k+2){
  //   somarIJ(p[p->tid].submatrizc[k]->matriz,p[p->tid].submatrizc[k+1]->matriz,p[p->tid].matrizsoma, p[p->tid].linha, p[p->tid].colunas, p[p->tid].coluna);
  // }
  printf("thread id=%d\nmatriza[0][0]=%d\nmatrizb[0][0]=%d\nmatrizc[0][0]=%d\nlinha inicial a=%d\nlinha final a=%d\ncoluna inicial a=%d\ncoluna final a=%d\nlinha inicial b=%d\nlinha final b=%d\ncoluna inicial b=%d\ncoluna final b=%d\nlinha inicial c=%d\nlinha final c=%d\ncoluna inicial c=%d\ncoluna final c=%d\n", p->tid, p->submatriza[p->tid]->matriz[p->tid*p->divisor][0], p->submatrizb[p->tid]->matriz[p->tid*p->divisor][0], p->submatrizc[p->tid]->matriz[p->tid*p->divisor][0],p->submatriza[p->tid]->bloco->lin_inicio,p->submatriza[p->tid]->bloco->lin_fim,p->submatriza[p->tid]->bloco->col_inicio,p->submatriza[p->tid]->bloco->col_fim,p->submatrizb[p->tid]->bloco->lin_inicio,p->submatrizb[p->tid]->bloco->lin_fim,p->submatrizb[p->tid]->bloco->col_inicio,p->submatrizb[p->tid]->bloco->col_fim,p->submatrizc[p->tid]->bloco->lin_inicio,p->submatrizc[p->tid]->bloco->lin_fim,p->submatrizc[p->tid]->bloco->col_inicio,p->submatrizc[p->tid]->bloco->col_fim);


  // for(int k=0; k<((p->divisor)-1); k=k+2){
  //   somarIJ(p->submatrizc[k]->matriz,p->submatrizc[k+1]->matriz,p->matrizsoma, p->N, p->L, p->M);
  // }
  //printf ("(mult_thread) thread_end(%d); matriza [0][0] = %d matrizb [0][0]= %d matrizc[%d][0] = %d\n", p->tid, p->matriza[0][0], p->matrizb[0][0], p->N, p->matrizc[p->N][0]);
  return NULL;
}
