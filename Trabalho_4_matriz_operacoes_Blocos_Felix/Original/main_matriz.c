#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include "matriz-operacoes.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	int **mat_a = NULL;
	int **mat_b = NULL;
	int **mat_c = NULL;
//	int **mat_c1 = NULL;
	//int **mat_c2 = NULL;
	//int **mat_final = NULL;
	FILE *fmat_a, *fmat_b, *fmat_c;//, *fmatbloco_c;
	int nr_line;
	int *vet_line = NULL;
	int N, M, La, Lb;
	double start_time, end_time;
	// matriz_bloco_t **vet_submat_a = NULL;
	// matriz_bloco_t **vet_submat_b = NULL;
	// matriz_bloco_t **vet_submat_c1 = NULL;
	// matriz_bloco_t **vet_submat_c2 = NULL;
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



	printf("\t\t**** Loaded mat_a NxL(%d,%d) **** \n", N, La);
	imprimir_matriz(mat_a, N, La);
	printf("\t\t**** Loaded mat_b LxM(%d,%d) **** \n", Lb, M);
	imprimir_matriz(mat_b, Lb, N);
	printf("\t\t**** Loaded mat_c NxM(%d,%d) **** \n", N, M);
	imprimir_matriz(mat_c, N, M);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// Restricao da operacao de soma de matrizes
	// Numero de linha de matriz_a deve ser o mesmo de colunas da matriz_b
	if (N == Lb && La == M){



	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// somarIJ
	int **mat_somaIJ = alocar_matriz(N, M);
	zerar_matriz(mat_somaIJ, N, M);
	if (mat_somaIJ == NULL) {
		printf("ERROR: Out of memory\n");
	}

	start_time = wtime();
	somarIJ(mat_a,mat_b,mat_somaIJ, N, M);
	end_time = wtime();
	printf("\n ##### somarIJ de Matrizes (IJ) #####\n");
	printf("\tRuntime: %f\n", end_time - start_time);
	fmat_c= fopen("somarIJ.map-result","w");
	fileout_matriz(mat_somaIJ, N, M, fmat_c);


	// somarJI
	int **mat_somaJI = alocar_matriz(Lb, M);
	zerar_matriz(mat_somaJI, N, M);
	if (mat_somaJI == NULL) {
		printf("ERROR: Out of memory\n");
	}

	start_time = wtime();
	somarJI(mat_a,mat_b,mat_somaJI, Lb, M);
	end_time = wtime();
	printf("\n ##### somarJI de Matrizes (JI) #####\n");
	printf("\tRuntime: %f\n", end_time - start_time);
	fmat_c= fopen("somarJI.map-result","w");
	fileout_matriz(mat_somaJI, N, M, fmat_c);

	comparar_matriz (mat_somaIJ, mat_somaJI, N, M);

	liberar_matriz(mat_somaIJ,N,M);
	liberar_matriz(mat_somaJI,N,M);
	}
	else {
		printf ("ERROR: matriz a vs matriz b incompativeis para a Soma.\n");
		printf ("Construa duas matrizes com as mesmas dimensoes para efetuar a Soma\n");
	}

	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%


	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  //Multiplicação IJK
	if (La != Lb) {
		printf ("ERROR: matriz a vs matriz b incompativeis para a Multiplicação.\n");
		printf ("Construa duas matrizes com o mesmo tamanho na coluna da matriz A e na linha da matriz B para efetuar a Multiplicação\n");
		exit(1);
	}
		zerar_matriz(mat_c, N, M);
		if (mat_c == NULL) {
			printf("ERROR: Out of memory\n");
		}
		start_time = wtime();
		multiplicarIJK(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (IJK) #####\n");
		printf("\tRuntime: %f\n", end_time - start_time);
		fmat_c= fopen("outIJK.map-result","w");
		printf("\n **** Matriz C	 resultante! **** \n");
		imprimir_matriz(mat_c, N, M);
		fileout_matriz(mat_c, N, M, fmat_c);


	//Multiplicação IKJ
		zerar_matriz(mat_c, N, M);
		if (mat_c == NULL) {
			printf("ERROR: Out of memory\n");
		}
		start_time = wtime();
		multiplicarIKJ(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (IKJ) #####\n");
		printf("\tRuntime: %f\n", end_time - start_time);
		fmat_c= fopen("outIKJ.map-result","w");
		printf("\n **** Matriz C	 resultante! **** \n");
		imprimir_matriz(mat_c, N, M);
		fileout_matriz(mat_c, N, M, fmat_c);


	//Multiplicação KIJ
		zerar_matriz(mat_c, N, M);
			if (mat_c == NULL) {
				printf("ERROR: Out of memory\n");
			}
			start_time = wtime();
			multiplicarKIJ(mat_a,mat_b,mat_c, N, La, M);
			end_time = wtime();
			printf("\n ##### Multiplicação de Matrizes (KIJ) #####\n");
			printf("\tRuntime: %f\n", end_time - start_time);
			fmat_c= fopen("outKIJ.map-result","w");
			printf("\n **** Matriz C	 resultante! **** \n");
			imprimir_matriz(mat_c, N, M);
			fileout_matriz(mat_c, N, M, fmat_c);


	//Multiplicação KJI
		zerar_matriz(mat_c, N, M);
		if (mat_c == NULL) {
			printf("ERROR: Out of memory\n");
		}
		start_time = wtime();
		multiplicarKJI(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (KJI) #####\n");
		printf("\tRuntime: %f\n", end_time - start_time);
		fmat_c= fopen("outKJI.map-result","w");
		printf("\n **** Matriz C	 resultante! **** \n");
		imprimir_matriz(mat_c, N, M);
		fileout_matriz(mat_c, N, M, fmat_c);


	//Multiplicação JIK
		zerar_matriz(mat_c, N, M);
		if (mat_c == NULL) {
			printf("ERROR: Out of memory\n");
		}
		start_time = wtime();
		multiplicarJIK(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (JIK) #####\n");
		printf("\tRuntime: %f\n", end_time - start_time);
		fmat_c= fopen("outJIK.map-result","w");
		printf("\n **** Matriz C	 resultante! **** \n");
		imprimir_matriz(mat_c, N, M);
		fileout_matriz(mat_c, N, M, fmat_c);


	//Multiplicação JKI
		zerar_matriz(mat_c, N, M);
		if (mat_c == NULL) {
			printf("ERROR: Out of memory\n");
		}
		start_time = wtime();
		multiplicarJKI(mat_a,mat_b,mat_c, N, La, M);
		end_time = wtime();
		printf("\n ##### Multiplicação de Matrizes (JKI) #####\n");
		printf("\tRuntime: %f\n", end_time - start_time);
		fmat_c= fopen("outJKI.map-result","w");
		printf("\n **** Matriz C	 resultante! **** \n");
		imprimir_matriz(mat_c, N, M);
		fileout_matriz(mat_c, N, M, fmat_c);

	//%%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%


	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
  // Multiplicação em Bloco
 // printf(" ##### Multiplicação de Matrizes (bloco) #####\n");
	// start_time = wtime();

	// printf("\n\n**** Matriz A (%p) completa ****\n",mat_a);
	// imprimir_matriz(mat_a, N, La);
	// vet_submat_a = particionar_matriz (mat_a, N, La, 1);
	// imprimir_bloco (vet_submat_a[0]);
	// imprimir_submatriz (vet_submat_a[0]);
	// imprimir_submatriz (vet_submat_a[1]);

	// printf("\n\n**** Matriz B (%p) completa ****\n",mat_b);
	// imprimir_matriz(mat_b, Lb, M);
	// vet_submat_b = particionar_matriz (mat_b, Lb, M, 0);
	// imprimir_bloco (vet_submat_b[0]);
	// imprimir_submatriz (vet_submat_b[0]);
	// imprimir_submatriz (vet_submat_b[1]);

	// mat_c1 = alocar_matriz(N, M);
	// zerar_matriz(mat_c1, N, M);
	// vet_submat_c1 = constroi_submatriz (mat_c1, N, M, 1);

	// mat_c2 = alocar_matriz(N, M);
	// zerar_matriz(mat_c2, N, M);
	// vet_submat_c2 = constroi_submatriz (mat_c2, N, M, 1);

	// mat_final = alocar_matriz(N, M);
	// zerar_matriz(mat_final, N, M);

	// multiplicar_submatriz (vet_submat_a[0], vet_submat_b[0], vet_submat_c1[0]);
	// imprimir_matriz(mat_c1, N, M);
	// multiplicar_submatriz (vet_submat_a[1], vet_submat_b[1], vet_submat_c2[0]);
	// imprimir_matriz(mat_c2, N, M);
	// somarIJ(mat_c1,mat_c2,mat_final, N, N, N);
	// end_time = wtime();

	// printf("\tRuntime: %f\n\n", end_time - start_time);
	// fmatbloco_c = fopen("outBloco.map-result","w");
	// fileout_matriz(mat_final, N, M, fmatbloco_c);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%


	comparar_matriz (mat_a, mat_b, N, M);
	comparar_matriz (mat_a, mat_a, N, M);
	printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");

  // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// LIBERAR MEMÓRIA
	// vet_submat_a = liberar_submatriz (vet_submat_a);
	// vet_submat_b = liberar_submatriz (vet_submat_b);
	// vet_submat_c1= liberar_submatriz (vet_submat_c1);
	// vet_submat_c2= liberar_submatriz (vet_submat_c2);

	liberar_matriz(mat_a,N,La);
	liberar_matriz(mat_b,Lb,M);
	liberar_matriz(mat_c,N,M);

	fclose(fmat_a);
	fclose(fmat_b);
	fclose(fmat_c);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	return 0;
}
