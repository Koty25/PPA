
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#define N1 10
#define M1 10


int main(int argc, char *argv[]) {

	int **mat_a = NULL;
	mat_a = alocar_matriz(N1, M1);
	imprimir_matriz(mat_a, N1, M1);
	zerar_matriz(mat_a, N1, M1);
	imprimir_matriz(mat_a, N1, M1);
	gerar_matriz(mat_a, N1, M1, -9999);
	imprimir_matriz(mat_a, N1, M1);
	liberar_matriz(mat_a, N1, M1);

return 0;

}
