#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "toolsv2.h"
#include "matriz.h"
#include "matriz-operacoes.h"
#include "matriz-operacoes-threads.h"

#define DIVISOR 10 //Numero de divisoes das matrizes na multiplicacao em blocos


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {
	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	int **mat_a = NULL;
	int **mat_b = NULL;
	int **mat_c = NULL;
	FILE *fmat_a, *fmat_b, *fmat_c, *fmatbloco_c, *fmatseqthread_c, *fmatblcthread_c;
	int nr_line;
	int *vet_line = NULL;
	int N = 0, M = 0, La, Lb;
	float sum_1=0, sum_2=0, sum_3=0, sum_4=0;
	double start_time, end_time;

	matriz_bloco_t **Vsubmat_a = NULL;
	matriz_bloco_t **Vsubmat_b = NULL;
	matriz_bloco_t **Vsubmat_c = NULL;
	matriz_bloco_t **Vsubmat_aa = NULL;
	matriz_bloco_t **Vsubmat_bb = NULL;
	matriz_bloco_t **Vsubmat_cc = NULL;
	int **mat_bloco_final = NULL;
	int **mat_seqC = NULL;
	int **mat_seqBlC = NULL;
	int n_tasks;
	param_t *args;
	pthread_t *threads;
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}

  // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	fmat_a = fopen(argv[1],"r");
	fmat_b = fopen(argv[2],"r");
  if ((fmat_a == NULL) || (fmat_b == NULL)) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
  }

  // matriz_a N (linha) x La (coluna)
	extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
	mat_a = alocar_matriz(N, La);
	filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

	// matriz_b Lb (linha) x M (coluna)
	extrai_parametros_matriz(fmat_b, &Lb, &M, &vet_line, &nr_line);
	mat_b = alocar_matriz(Lb, M);
	filein_matriz (mat_b, Lb, M, fmat_b, vet_line, nr_line);

	// matriz_c (resultante) = N (linha) x M(coluna)
	mat_c = alocar_matriz(N, M);
	zerar_matriz(mat_c, N, M);

	if ((mat_c == NULL) || (mat_b == NULL) || (mat_a == NULL)) {
		printf("ERROR: Out of memory\n");
	}
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  // Multiplicação IKJ
	for (int i=0; i<10; i++){
		zerar_matriz(mat_c, N, M);
		start_time = wtime();
		multiplicarIKJ(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (IKJ) #####\n");
		printf("\tRuntime: %f\n", end_time - start_time);
		sum_1+=end_time-start_time;
		printf("\tTotal Runtime (i=%d): %f\n", i+1, sum_1);
		fmat_c= fopen("outIKJ.map-result","w");
		fileout_matriz(mat_c, N, M, fmat_c);
	}

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  // Multiplicação em Bloco v3
	for (int i=0; i<10; i++){
		mat_bloco_final = alocar_matriz(N, M);
		zerar_matriz(mat_bloco_final, N, M);
		printf(" ##### Multiplicação de Matrizes (blocov2) #####\n");
		start_time = wtime();
		Vsubmat_a = particionar_matriz (mat_a, N, La, 1, DIVISOR);
		Vsubmat_b = particionar_matriz (mat_b, Lb, M, 0, DIVISOR);
		Vsubmat_c = constroi_submatrizv2 (N, M, DIVISOR);
		zerar_matriz(mat_bloco_final, N, M);
		for (int j=0; j<DIVISOR; j++){
			for (int z=0; z<DIVISOR; z++){
				multiplicar_submatriz (Vsubmat_a[j], Vsubmat_b[z], Vsubmat_c[j]);
			}
		}
		for(int k=0; k<(DIVISOR-1); k=k+2){
			somarIJ(Vsubmat_c[k]->matriz,Vsubmat_c[k+1]->matriz,mat_bloco_final, N, La, M);
		}
		//somarIJ(Vsubmat_c[2]->matriz,Vsubmat_c[3]->matriz,mat_bloco_final, N, La, M);
		end_time = wtime();

		printf("\tRuntime: %f\n\n", end_time - start_time);
		sum_2+=end_time-start_time;
		printf("\tTotal Runtime (i=%d): %f\n", 1, sum_2);
		fmatbloco_c = fopen("outBloco.map-result","w");
		fileout_matriz(mat_bloco_final, N, M, fmatbloco_c);
	}

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

// Multiplicação MultiThread
	mat_seqC = alocar_matriz(N, M);
	for (int i=0; i<10; i++){
		printf(" ##### Multiplicação de Matrizes (MultiThreadSeq) #####\n");
		zerar_matriz(mat_seqC, N, M);
		n_tasks=20;
		threads = (pthread_t *) malloc(n_tasks * sizeof(pthread_t));
		args = (param_t *) malloc(n_tasks * sizeof(param_t));

		start_time = wtime();
		for (int i=0; i<n_tasks; i++){
			args[i].tid = i;
      args[i].ntasks = n_tasks;
			args[i].matriza = mat_a;
			args[i].matrizb = mat_b;
			args[i].matrizc = mat_seqC;
			args[i].N = N;
			args[i].M = M;
			args[i].L = La;
			pthread_create(&threads[i], NULL, mult_thread, (void *) (args+i));
		}
		for (int i = 0; i < n_tasks; i++){
			pthread_join(threads[i], NULL);
		}
		end_time = wtime();

		printf("\tRuntime: %f\n\n", end_time - start_time);
		sum_3+=end_time-start_time;
		printf("\tTotal Runtime (i=%d): %f\n", i+1, sum_3);
		fmatseqthread_c = fopen("outSeqThreadIKJ.map-result","w");
		fileout_matriz(mat_seqC, N, M, fmatseqthread_c);
	}

	free(threads);


// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

// Multiplicação MultiThreads em Bloco
	mat_seqBlC = alocar_matriz(N, M);
	for(int i=0; i<10; i++){
		printf(" ##### Multiplicação de Matrizes (MultiThreadBlocos) #####\n");
		start_time = wtime();
		Vsubmat_aa = particionar_matriz (mat_a, N, La, 1, DIVISOR);
		Vsubmat_bb = particionar_matriz (mat_b, Lb, M, 0, DIVISOR);
		Vsubmat_cc = constroi_submatrizv2 (N, M, DIVISOR);
		//printf("%d\n", Vsubmat_a[1]->matriz[101][0]);
		zerar_matriz(mat_seqBlC, N, M);
		n_tasks=DIVISOR;
		threads = (pthread_t *) malloc(n_tasks * sizeof(pthread_t));
		args = (param_t *) malloc(n_tasks * sizeof(param_t));
		printf("%d\n", n_tasks);
		for (int i=0; i<n_tasks; i++){
			args[i].tid = i;
			args[i].ntasks = n_tasks;
			args[i].submatriza = Vsubmat_aa;
			args[i].submatrizb = Vsubmat_bb;
			args[i].submatrizc = Vsubmat_cc;
			args[i].matrizsoma= mat_seqBlC;
			args[i].divisor = DIVISOR;
			args[i].N = N;
			args[i].M = M;
			args[i].L = La;
			pthread_create(&threads[i], NULL, mult_thread_bloco, (void *) (args+i));
		}


		for (int i = 0; i < n_tasks; i++){
			pthread_join(threads[i], NULL);
		}
		mat_seqBlC=args->submatrizc[0]->matriz;
		//for (int n=0; n<n_tasks; n++){
			for(int k=0; k<((n_tasks)-1); k++){
				for (int i=0; i < N; i++){
					for (int j=0; j < M; j++){
						mat_seqBlC[i][j]+= args->submatrizc[k]->matriz[i][j] + args->submatrizc[k]->matriz[i][j];
					}
				}
			}
		//}
		// for (int i=0; i<n_tasks; i++){
		// 	for(int k=0; k<((n_tasks)-1); k=k+2){
		// 		somarIJ(args[i].submatrizc[k]->matriz,args[i].submatrizc[k+1]->matriz,args[i].matrizsoma, args[i].linha, args[i].colunas, args[i].coluna);
		// 	}
		// }
		end_time = wtime();

		printf("\tRuntime: %f\n\n", end_time - start_time);
		sum_4+=end_time-start_time;
		printf("\tTotal Runtime (i=%d): %f\n", i+1, sum_4);
		fmatblcthread_c = fopen("outBlcThreadIKJ.map-result","w");
		fileout_matriz(mat_seqBlC, N, M, fmatblcthread_c);
	}


// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%



	comparar_matriz (mat_c, mat_bloco_final, N, M);
	comparar_matriz (mat_c, mat_seqC, N, M);
	comparar_matriz (mat_bloco_final, mat_seqBlC, N, M);
	printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");
	// Tempo medio
	printf("Tempo médio multiplicacao sequencial=%f\n",(sum_1/10));
	printf("Tempo médio multiplicacao em blocos=%f\n",(sum_2/10));
	printf("Tempo médio multiplicacao sequencial multithread=%f\n",(sum_3/10));
	printf("Tempo médio multiplicacao em blocos multithread=%f\n",(sum_4/10));
	printf("Speedup multiplicacao sequencial multithread=%f\n",(sum_1/sum_3));
	printf("Speedup multiplicacao em blocos multithread=%f\n",(sum_2/sum_4));

  // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// LIBERAR MEMÓRIA
	Vsubmat_a = liberar_submatriz (Vsubmat_a, DIVISOR);
	Vsubmat_b = liberar_submatriz (Vsubmat_b, DIVISOR);
	Vsubmat_c = liberar_submatriz (Vsubmat_c, DIVISOR);
	Vsubmat_aa = liberar_submatriz (Vsubmat_aa, DIVISOR);
	Vsubmat_bb = liberar_submatriz (Vsubmat_bb, DIVISOR);
	Vsubmat_cc = liberar_submatriz (Vsubmat_cc, DIVISOR);

	liberar_matriz(mat_a,N,La);
	liberar_matriz(mat_b,Lb,M);
	liberar_matriz(mat_c,N,M);
	liberar_matriz(mat_bloco_final,N,M);
	liberar_matriz(mat_seqC,N,M);
	liberar_matriz(mat_seqBlC,N,M);

	fclose(fmat_a);
	fclose(fmat_b);
	fclose(fmat_c);
	fclose(fmatbloco_c);
	fclose(fmatseqthread_c);
	fclose(fmatblcthread_c);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	return 0;
}
