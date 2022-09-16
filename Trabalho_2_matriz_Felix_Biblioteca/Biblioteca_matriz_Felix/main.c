#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	int **mat_a = NULL;
	int **mat_b = NULL;
	FILE *fmat_a;
	FILE *fmat_b;
	int nr_line;
	int *vet_line = NULL;
	int N, M;
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	if (argc != 3){
		printf ("ERRO: Numero de parametros %s <matriz_a> <matriz_b>\n", argv[0]);
		exit (1);
	}

  // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	fmat_a = fopen(argv[1],"r");
	fmat_b = fopen(argv[2],"w");
        if ( fmat_a == NULL ) {
		printf("Error: Na abertura dos arquivos.");
		exit(1);
        }

  // matriz_a N (linha) x La (coluna)
	extrai_parametros_matriz(fmat_a, &N, &M, &vet_line, &nr_line);
	mat_a = alocar_matriz(N, M);
	if (mat_a == NULL) {
		printf("ERROR: Out of memory\n");
	}
	filein_matriz (mat_a, N, M, fmat_a, vet_line, nr_line);
	printf("\t\t**** mat_a lida LinhaxColuna(%d,%d) **** \n", N, M);
	imprimir_matriz(mat_a, N, M);

	zerar_matriz(mat_a, N, M);
	printf("\t\t**** mat_a c/ Zeros LinhaxColuna(%d,%d) **** \n", N, M);
 imprimir_matriz(mat_a, N, M);


  // matriz_a N (linha) x La (coluna)
	mat_b = alocar_matriz(N, M);
	if (mat_b == NULL) {
		printf("ERROR: Out of memory\n");
	}

	gerar_matriz(mat_b, N, M, 0);
	fileout_matriz(mat_b, N, M, fmat_b);
	printf("\t\t**** mat_b gerada c/ Zeros LinhaxColuna(%d,%d) **** \n", N, M);
	imprimir_matriz(mat_b, N, M);

	printf("\t\t**** Comparar mat_a / mat_b LinhaxColuna(%d,%d) **** \n", N, M);
	comparar_matriz (mat_a, mat_b, N, M);

	filein_matriz (mat_a, N, M, fmat_a, vet_line, nr_line);
	printf("\t\t**** Loaded mat_a LinhaxColuna(%d,%d) **** \n", N, M);
	imprimir_matriz(mat_a, N, M);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	comparar_matriz (mat_a, mat_b, N, M);
	printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");

	liberar_matriz(mat_a,N,M);
	liberar_matriz(mat_b,N,M);

	fclose(fmat_a);
	fclose(fmat_b);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	return 0;
}
