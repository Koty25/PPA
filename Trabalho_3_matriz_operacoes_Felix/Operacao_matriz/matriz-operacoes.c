	#include "matriz-operacoes.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% MATRIZ %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somarIJ (int **mat_a, int **mat_b, int **mat_c, int N, int M) {
	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			mat_c[i][j]= mat_a[i][j] + mat_b[i][j];
  return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int somarJI (int **mat_a, int **mat_b, int **mat_c, int N, int M) {
	for (int j=0; j < M; j++)
		for (int i=0; i < N; i++)
			mat_c[i][j]= mat_a[i][j] + mat_b[i][j];
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
int multiplicarJKI (int **mat_a, int **mat_b, int **mat_c, int N, int L, int M) {
	for(int j = 0; j < M; j ++)
		for(int k = 0; k < L; k ++)
			for(int i = 0; i < N; i ++)
				mat_c[i][j] += mat_a[i][k] * mat_b[k][j];
  return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//int multiplicar_submatriz (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc) {
//  #TODO
//	return 0;
//}
