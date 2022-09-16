#include "matriz-operacoes-threads.h"
#include "matriz-operacoes.h"


int multiplicar_openmp(int **mat_a, int **mat_b, int **mat_c, int N, int M, int La, int Lb) {

	int i,j,k, nthreads;
	int ch;

	if ((mat_a==NULL) || (mat_b==NULL) || (mat_c==NULL)){
                printf("\nERRO: Matriz não alocada!!\n");
                exit(1);
        } else {
		if (La!=Lb) {
			printf("\n Impossível multiplicar: Colunas de A diferente Linhas de B!\n");
                        return 1;
                } else {
			nthreads = 8;
			ch = N/nthreads;
			#pragma omp parallel for private(i, j, k) shared(mat_a, mat_b, mat_c, N, M, La) schedule(dynamic,ch)
		       	for(i=0;i<N;i++){
                       		for(j=0;j<M;j++){
                                       	for(k=0;k<La;k++){
                                               	mat_c[i][k]+= mat_a[i][j]*mat_b[j][k];
					}
				}
			}
                }
         }
return 0;
}

int multiplicar_openmp_bloco(matriz_bloco_t *mat_subaa, matriz_bloco_t *mat_subbb, matriz_bloco_t *mat_subcc) {

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

void *mult_thread (void *arg) {
  param_t *p = (param_t *) arg;
  int passo, ini, fin, N, M, L;

  N = p->N;
  M = p->M;
  L = p->L;
  passo = N/p->ntasks;
  ini = p->tid*passo;
  fin = (p->tid+1)*passo;

  for(int i=ini; i < fin; i++){
    for(int j=0; j< M; j++){
      for(int k=0; k< L; k++){
        p->matrizc[i][k]+= p->matriza[i][j]*p->matrizb[j][k];
      }
    }
  }

  return NULL;
}

int multiplicar_bloco_pthread (matriz_bloco_t *mat_suba, matriz_bloco_t *mat_subb, matriz_bloco_t *mat_subc, int nro_threads) {

  int Lin_inicio_a, Lin_fim_a, Col_inicio_a, Col_fim_a, Lin_inicio_b, Lin_fim_b, Col_inicio_b, Col_fim_b, final;
  pthread_t *threads;
  param_bloco *args;

        threads = (pthread_t *)malloc(nro_threads * sizeof(pthread_t));
        args = (param_bloco*) malloc(nro_threads * sizeof(param_bloco));

        Lin_inicio_a = mat_suba->bloco->lin_inicio;
        Lin_fim_a = mat_suba->bloco->lin_fim;

        Col_inicio_a = mat_suba->bloco->col_inicio;
        Col_fim_a = mat_suba->bloco->col_fim;

        Lin_inicio_b = mat_subb->bloco->lin_inicio;
        Lin_fim_b = mat_subb->bloco->lin_fim;

        Col_inicio_b = mat_subb->bloco->col_inicio;
        Col_fim_b = mat_subb->bloco->col_fim;

	int passo = (Lin_fim_a-Lin_inicio_a)/nro_threads;

	for(int r=0; r<nro_threads;r++){

		if(r==nro_threads-1){
			final = (Lin_fim_a-Lin_inicio_a);}
		else {	final = (r+1) * passo;}

		args[r].inicio = r * passo;
		args[r].final = final;
		args[r].mat_suba = mat_suba->matriz;
		args[r].Col_inicio_a = Col_inicio_a;
		args[r].Col_fim_a = Col_fim_a;
		args[r].mat_subb = mat_subb->matriz;
		args[r].Lin_inicio_b = Lin_inicio_b;
		args[r].Lin_fim_b = Lin_fim_b;
		args[r].Col_inicio_b = Col_inicio_b;
		args[r].Col_fim_b = Col_fim_b;
		args[r].mat_subc = mat_subc->matriz;
		pthread_create(&threads[r], NULL, multiplicar_bb, (void *)(args+r));

	}

                for (int r = 0; r < nro_threads; r++){
                        pthread_join(threads[r], NULL);
                }
return 0;
}

void *multiplicar_bb (void *args) {

	int i,j,k;

	param_bloco *p = (param_bloco *) args;

	if ((p->mat_suba==NULL) || (p->mat_subb==NULL) || (p->mat_subc==NULL)){
		printf("\nERRO: Matriz não alocada!!\n");
		exit(1);
	} else {
		if ((p->Col_fim_a)-(p->Col_inicio_a)!=(p->Lin_fim_b)-(p->Lin_inicio_b)) {
			printf("\n Impossível multiplicar: Colunas de A diferente Linhas de B!\n");
			exit(1);
		} else {
			for(i=p->inicio;i < p->final;i++){
				for(j=p->Col_inicio_b;j < p->Col_fim_b;j++){
					for(k=p->Col_inicio_a;k < p->Col_fim_a;k++){
						printf("valor mat_subc[0][0]%d\n", p->mat_subc[0][0]);
						p->mat_subc[i][j]+= p->mat_suba[i][k]*p->mat_subb[k][j];
					}
				}
			}
		}
	}
return NULL;
}
