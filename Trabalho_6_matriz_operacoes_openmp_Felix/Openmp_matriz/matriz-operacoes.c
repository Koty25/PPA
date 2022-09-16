	#include "matriz-operacoes.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somarIJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			mat_c[i][j]+= mat_a[i][j] + mat_b[i][j];

  return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somarJI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for (int j=0; j < M; j++)
		for (int i=0; i < N; i++)
			mat_c[i][j]+= mat_a[i][j] + mat_b[i][j];
  return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarIJK (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < M; j ++)
			for(int k = 0; k < L; k ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarIKJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int i = 0; i < N; i ++)
		for(int k = 0; k < L; k ++)
			for(int j = 0; j < M; j ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarKIJ (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int k = 0; k < L; k ++)
		for(int i = 0; i < N; i ++)
			for(int j = 0; j < M; j ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
  return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarKJI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int k = 0; k < L; k ++)
		for(int j = 0; j < M; j ++)
			for(int i = 0; i < N; i ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
  return 0;

}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicarJIK (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int j = 0; j < M; j ++)
		for(int i = 0; i < N; i ++)
			for(int k = 0; k < L; k ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
  return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Mais eficiente
int multiplicarJKI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int j = 0; j < M; j ++)
		for(int k = 0; k < L; k ++)
			for(int i = 0; i < N; i ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
  return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc) {
  if(!mat_suba || !mat_subb || !mat_subc){
		printf("ERROR: Out of memory 11\n");
		return 1;
	}
	int ma_lin_ini = mat_suba->bloco->lin_inicio;
	int ma_lin_fim = mat_suba->bloco->lin_fim;
	int ma_col_ini = mat_suba->bloco->col_inicio;
	int ma_col_fim = mat_suba->bloco->col_fim;
	int mb_col_ini = mat_subb->bloco->col_inicio;
	int mb_col_fim = mat_subb->bloco->col_fim;

  for(int i = ma_lin_ini; i < ma_lin_fim; i++){
  	for(int k = ma_col_ini; k < ma_col_fim; k++){
  		for(int j = mb_col_ini; j < mb_col_fim; j++){
  			mat_subc->matriz[i][j] += mat_suba->matriz[i][k] * mat_subb->matriz[k][j];
  		}
  	}
  }
	return 0;
}
