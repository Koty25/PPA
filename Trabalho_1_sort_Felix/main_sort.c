#include <stdio.h>
#include <stdlib.h>

// Bibliotecas pessoais
#include "vector.h"
#include "toolsvector.h"
#include "sort.h"

int main(int argc, char** argv) {
  int nlinhas;
  int *vet = NULL;
  FILE *fvet;
  double start_time, end_time;

  if (argc != 2){
    printf ("ERRO: Numero de parametros %s <filename>", argv[0]);
    exit (1);
  }

  //nlinhas =  atoi(argv[1]);
  fvet = fopen(argv[1],"r");
  if (fvet == NULL) {
    printf("Error: Na abertura dos arquivos.");
    exit(1);
  }

  nlinhas = extrai_nroLine(fvet);
  vet = alocar_vetor(nlinhas);
  filein_vetor (vet, nlinhas, fvet);
  printf("\t\t**** PRINT vetor lido N(%d) **** \n", nlinhas);
  imprimir_vetor(vet, nlinhas);


  int vet_merge[nlinhas], vet_bubble[nlinhas], cont;

  for(cont=0; cont<nlinhas; cont++)
    {
        vet_merge[cont] = vet[cont];
        vet_bubble[cont] = vet[cont];
    }

  start_time = wtime();
  quick_sort(vet, 0, nlinhas - 1);
  end_time = wtime();

  printf("\t\t**** PRINT vetor Ordenado (Quick Sort) N(%d) **** \n", nlinhas);
  imprimir_vetor(vet, nlinhas);

  printf("\tRuntime: %f\n", end_time - start_time);

  start_time = wtime();
  bubble_sort(vet_bubble, nlinhas);
  end_time = wtime();

  printf("\t\t**** PRINT vetor Ordenado (Bubble Sort) N(%d) **** \n", nlinhas);
  imprimir_vetor(vet_bubble, nlinhas);

  printf("\tRuntime: %f\n", end_time - start_time);

  start_time = wtime();
  merge_sort(vet_merge, 0, nlinhas - 1);
  end_time = wtime();

  printf("\t\t**** PRINT vetor Ordenado (Merge Sort) N(%d) **** \n", nlinhas);
  imprimir_vetor(vet_merge, nlinhas);

  printf("\tRuntime: %f\n", end_time - start_time);



  liberar_vetor (vet);
  fclose (fvet);
  return 0;
}
