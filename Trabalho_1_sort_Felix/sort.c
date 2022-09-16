#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define n_ele(x)  (sizeof(x) / sizeof((x)[0]))

int particiona(int *vetor, int ini, int fin){
	int esq, dir, pivo, aux;
	esq = ini;
	dir = fin;
	pivo = vetor[ini];
	while(esq < dir){
		while(vetor[esq] <= pivo)
			esq++;
		while(vetor[dir] > pivo)
			dir--;
		if(esq<dir){
			aux = vetor[esq];
			vetor[esq] = vetor[dir];
			vetor[dir] = aux;
		}
	}
	vetor[ini] = vetor[dir];
	vetor[dir] = pivo;
	return dir;
}


void quick_sort(int *vetor, int ini, int fin) {
	int pivo;
	if(fin > ini){
		pivo = particiona(vetor, ini, fin);
		quick_sort(vetor, ini, pivo-1);
		quick_sort(vetor, pivo+1, fin);
	}
   // Desenvolva o código do Quicksort
}





void bubble_sort(int *vetor, int tam_vetor) {
	int i, conta, aux, fin = tam_vetor;
	do{
		conta = 0;
		for(i = 0; i < fin-1; i++){
			if(vetor[i] > vetor[i+1]){
			aux = vetor[i];
			vetor[i] = vetor[i+1];
			vetor[i+1] = aux;
			conta++;
			}
		}
		fin--;
	}
	while(conta != 0);

}


void merge(int *vetor, int ini, int mid, int fin){
	int *temp, p1, p2, tamanho, i, j, k;
	int fin1 = 0, fin2 = 0;
	tamanho = fin - ini+1;
	p1 = ini;
	p2 = mid+1;
	temp = (int *) malloc(tamanho*sizeof(int));
	if(temp != NULL){
		for(i=0; i<tamanho; i++){
			if(!fin1 && !fin2){
				if(vetor[p1] < vetor[p2])
					temp[i] = vetor[p1++];
				else
					temp[i] = vetor[p2++];
				if (p1 > mid)
					fin1=1;
				if(p2 > fin)
					fin2=1;
			}
			else{
				if(!fin1)
					temp[i] = vetor[p1++];
				else
					temp[i] = vetor[p2++];
			}
		}
		for (j=0, k=ini; j<tamanho; j++, k++)
			vetor[k] = temp[j];
	}
	free(temp);
}

void merge_sort(int *vetor, int ini, int fin) {
	int mid;
	if(ini < fin){
		mid = floor((ini+fin)/2);
		merge_sort(vetor, ini, mid);
		merge_sort(vetor, mid+1, fin);
		merge(vetor,ini,mid,fin);
	}
}
