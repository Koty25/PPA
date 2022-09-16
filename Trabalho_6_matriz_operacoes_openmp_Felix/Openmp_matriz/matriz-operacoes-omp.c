#include "matriz-operacoes-omp.h"
#include "matriz-operacoes.h"


int mult_seq_openmp(int **mat_a, int **mat_b, int **mat_c, int N, int M, int La, int divisor) {

	int i,j,k, passo;// nthreads;
	passo = N/divisor;

	if ((mat_a==NULL) || (mat_b==NULL) || (mat_c==NULL)){
		printf("\nERRO: Matriz não alocada!!\n");
		exit(1);
	}
	//nthreads = 8;
	#pragma omp parallel for private(i, j, k) shared(mat_a, mat_b, mat_c, N, M, La) schedule(dynamic,passo)
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
  			for(k=0;k<La;k++){
					mat_c[i][k]+= mat_a[i][j]*mat_b[j][k];
				}
			}
		}

return 0;
}

// int mult_bloco_openmp (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc) {
//   if(!mat_suba || !mat_subb || !mat_subc){
// 		printf("ERROR: Out of memory 11\n");
// 		return 1;
// 	}
// 	int ma_lin_ini = mat_suba->bloco->lin_inicio;
// 	int ma_lin_fim = mat_suba->bloco->lin_fim;
// 	int ma_col_ini = mat_suba->bloco->col_inicio;
// 	int ma_col_fim = mat_suba->bloco->col_fim;
// 	int mb_col_ini = mat_subb->bloco->col_inicio;
// 	int mb_col_fim = mat_subb->bloco->col_fim;
//
//   for(int i = ma_lin_ini; i < ma_lin_fim; i++){
//   	for(int k = ma_col_ini; k < ma_col_fim; k++){
//   		for(int j = mb_col_ini; j < mb_col_fim; j++){
//   			mat_subc->matriz[i][j] += mat_suba->matriz[i][k] * mat_subb->matriz[k][j];
//   		}
//   	}
//   }
// 	return 0;
// }

int mult_bloco_openmp(matriz_bloco_t *mat_subaa, matriz_bloco_t *mat_subbb, matriz_bloco_t *mat_subcc) {

  if(!mat_subaa || !mat_subbb || !mat_subcc){
		printf("ERROR: Out of memory 11\n");
		return 1;
	}
	int i,j,k;//,passo=5/divisor;
	//#pragma omp parallel for private(i, j, k) shared(mat_a->matriz, mat_b->matriz, mat_c->matriz, N, M, La) schedule(dynamic,ch)
	//for (int j=0; j<DIVISOR; j++){
		//for (int z=0; z<DIVISOR; z++){

			int ma_lin_ini = mat_subaa->bloco->lin_inicio;
			int ma_lin_fim = mat_subaa->bloco->lin_fim;
			int ma_col_ini = mat_subaa->bloco->col_inicio;
			int ma_col_fim = mat_subaa->bloco->col_fim;
			int mb_col_ini = mat_subbb->bloco->col_inicio;
			int mb_col_fim = mat_subbb->bloco->col_fim;
			//printf("%d\n", mat_subaa->matriz[20][20]);
			int iter=0;
			iter++;
			//printf("%d\n", iter);

		#pragma omp parallel for private(i, j, k) shared(mat_subaa, mat_subbb, mat_subcc, ma_lin_ini, ma_lin_fim, ma_col_ini, ma_col_fim, mb_col_ini, mb_col_fim)// schedule(dynamic, passo)
			for(i = ma_lin_ini; i < ma_lin_fim; i++){
				for(k = ma_col_ini; k < ma_col_fim; k++){
					for(j = mb_col_ini; j < mb_col_fim; j++){
						mat_subcc->matriz[i][j] += mat_subaa->matriz[i][k] * mat_subbb->matriz[k][j];
					}
				}
			}
		//}
	//}
	//printf("%d\n", mat_subcc->matriz[0][0]);

	return 0;
}
