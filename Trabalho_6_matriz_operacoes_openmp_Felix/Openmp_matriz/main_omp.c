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
#include "matriz-operacoes-omp.h"

#define DIVISOR 20 //Numero de divisoes das matrizes na multiplicacao em blocos


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {
	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	int **mat_a = NULL;
	int **mat_b = NULL;
	int **mat_c = NULL;
	int **mat_comp = NULL;
	FILE *fmat_a, *fmat_b, *fmat_c, *fmatbloco_c, *fmatseqthreadomp_c, *fmatseqthreadompbloco_c;
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
	int **mat_c_openmp = NULL;
	int **mat_c_openmp_blc = NULL;
	//int n_tasks;
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

	// matriz_comp (comparaçao) = N (linha) x M(coluna)
	mat_comp = alocar_matriz(N, M);
	zerar_matriz(mat_comp, N, M);

	if ((mat_c == NULL) || (mat_b == NULL) || (mat_a == NULL)) {
		printf("ERROR: Out of memory\n");
	}
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  // Multiplicação IJK
	printf("\n ##### Multiplicação de Matrizes Sequencial(IKJ) #####\n");
	for (int i=0; i<10; i++){
		zerar_matriz(mat_c, N, M);
		start_time = wtime();
		multiplicarIKJ(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		for(int i = 0; i < N; i ++)
			for(int j = 0; j < M; j ++)
				mat_comp[i][j] = mat_c[i][j];
		printf("\tExecução %d\n", i+1);
		printf("\tRuntime: %f\n", end_time - start_time);
		sum_1+=end_time-start_time;
		printf("\tTotal Runtime: %f\n\n", sum_1);
		fmat_c= fopen("outIKJ.map-result","w");
		fileout_matriz(mat_c, N, M, fmat_c);
	}

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  // Multiplicação em Bloco v3
	printf(" ##### Multiplicação de Matrizes Sequencial em blocos #####\n");
	for (int i=0; i<10; i++){
		mat_bloco_final = alocar_matriz(N, M);
		zerar_matriz(mat_bloco_final, N, M);
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
		end_time = wtime();
		printf("\tExecução %d\n", i+1);
		printf("\tRuntime: %f\n", end_time - start_time);
		sum_2+=end_time-start_time;
		printf("\tTotal Runtime: %f\n\n", sum_2);
		fmatbloco_c = fopen("outBloco.map-result","w");
		fileout_matriz(mat_bloco_final, N, M, fmatbloco_c);
	}

// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

// Multiplicação openMP sequencial
	printf("\n #### Multiplicação Paralela de Matrizes sequencial openMP #####\n");
	for (int i=0; i<10; i++){
		mat_c_openmp = alocar_matriz(N, M);
		zerar_matriz(mat_c_openmp, N, M);
		start_time = wtime();
		mult_seq_openmp(mat_a, mat_b, mat_c_openmp, N, M, La, DIVISOR);
		end_time = wtime();

		printf("\tExecução %d\n", i+1);
		printf("\tRuntime: %f\n", end_time - start_time);
		sum_3+=end_time-start_time;
		printf("\tTotal Runtime: %f\n\n", sum_3);
		fmatseqthreadomp_c = fopen("outSeqOpenMPIJK.map-result","w");
		fileout_matriz(mat_c_openmp, N, M, fmatseqthreadomp_c);
	}

// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%

	// Multiplicação openMP em blocos
	printf("\n #### Multiplicação Paralela de Matrizes em blocos openMP #####\n");
	for (int i=0; i<10; i++){
		mat_c_openmp_blc = alocar_matriz(N, M);
		zerar_matriz(mat_c_openmp_blc, N, M);
		start_time = wtime();
		Vsubmat_aa = particionar_matriz (mat_a, N, La, 1, DIVISOR);
		Vsubmat_bb = particionar_matriz (mat_b, Lb, M, 0, DIVISOR);
		Vsubmat_cc = constroi_submatrizv2 (N, M, DIVISOR);
		for (int j=0; j<DIVISOR; j++){
			for (int z=0; z<DIVISOR; z++){
				mult_bloco_openmp(Vsubmat_aa[j], Vsubmat_bb[z], Vsubmat_cc[DIVISOR-1]);
			}
		}

		// for(int k=0; k<(DIVISOR-1); k=k+2){
		// 	somarIJ(Vsubmat_cc[k]->matriz,Vsubmat_cc[k+1]->matriz,mat_c_openmp_blc, N, La, M);
		// }
		end_time = wtime();
		mat_c_openmp_blc = Vsubmat_cc[DIVISOR-1]->matriz;
		printf("\tExecução %d\n", i+1);
		printf("\tRuntime: %f\n", end_time - start_time);
		sum_4+=end_time-start_time;
		printf("\tTotal Runtime: %f\n\n", sum_4);
		fmatseqthreadompbloco_c = fopen("outBlocoOpenMPIJK.map-result","w");
		fileout_matriz(mat_c_openmp_blc, N, M, fmatseqthreadompbloco_c);
	}

// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
	// Comparação das Matrizes
	printf("\nComparação matrizes sequencial e em blocos\n");
	comparar_matriz (mat_comp, mat_bloco_final, N, M);
	printf("Comparação matrizes sequencial e sequencial openMP:\n");
	comparar_matriz (mat_comp, mat_c_openmp, N, M);
	printf("Comparação matrizes sequencial e blocos openMP:\n");
	comparar_matriz (mat_comp, mat_c_openmp_blc, N, M);

	printf("\nResultados individuais encontram-se nos arquivos <out*.map-result>.\n");
	// Tempo medio
	printf("\nTempo médio multiplicacao sequencial=%f\n",(sum_1/10));
	printf("Tempo médio multiplicacao em blocos=%f\n",(sum_2/10));
	printf("Tempo médio multiplicacao sequencial openMP=%f\n",(sum_3/10));
	printf("Tempo médio multiplicacao em blocos openMP=%f\n",(sum_4/10));
	printf("\nSpeedup multiplicacao sequencial openMP=%f\n",(sum_1/sum_3));
	printf("Speedup multiplicacao em blocos openMP=%f\n",(sum_2/sum_4));



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
	liberar_matriz(mat_comp,N,M);
	liberar_matriz(mat_bloco_final,N,M);
	liberar_matriz(mat_c_openmp,N,M);
	liberar_matriz(mat_c_openmp_blc,N,M);

	fclose(fmat_a);
	fclose(fmat_b);
	fclose(fmat_c);
	fclose(fmatbloco_c);
	fclose(fmatseqthreadompbloco_c);
	fclose(fmatseqthreadomp_c);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	return 0;
}
