#include "toolsv2.h"
#include <time.h>
#include <sys/time.h>

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FERRAMENTAS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
double wtime() {
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec + (double) t.tv_usec / 1000000;
}

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  char **split(const char *str, char sep, int nro_line) {
  	int conta_palavras;
  	unsigned int start = 0, stop;
  	char **retStr;



  	retStr = (char **) malloc (nro_line*sizeof(char *));
  	conta_palavras = 0;

  	for (stop = 0; str[stop]; stop++) {


  		if (str[stop] == sep) {

  			if ( conta_palavras < nro_line ) {

  				retStr[conta_palavras] = (char *) malloc (((stop - start)+1)*sizeof(char));
  				if (retStr == NULL)
  				    printf("ERROR: Out of memory\n");
  				strncpy (retStr[conta_palavras], str + start, stop - start);
  				memcpy (retStr[conta_palavras], str + start, stop - start);
  				retStr[conta_palavras][(stop-start)] = '\0';

  				conta_palavras++;
  				start = stop + 1;
  			} else {
  				printf("Error: Ultrapassou o número máximo de palavras (%d)\n",conta_palavras);
  				exit (0);
  			}
  		}
  	}


  	if (retStr == NULL)
  	    printf("ERROR: Out of memory\n");
  	strncpy (retStr[conta_palavras], str + start, stop - start);

  	return (retStr);
  }

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int fileout_matriz (int **matriz, int linha, int coluna, FILE *infile){
	fprintf(infile,"#Linha#Coluna#\n");
	fprintf(infile,"%d#%d#\n", linha, coluna);
	for (int i=0; i < linha; i++) {
		for (int j=0; j < coluna; j++){
			fprintf(infile,"%d,", matriz[i][j]);
		}
		fprintf(infile,"\n");
	}
	return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int extrai_parametros_matriz ( FILE *const fin, int* linha,
	int *coluna, int **vet_line, int *nr_line ) {
		char *getLine = NULL;
		char **strSplit = NULL;

		*nr_line = 1;
		*vet_line = (int *) malloc ((*nr_line+2)*sizeof(int));

		*nr_line = conta_line_file (fin, 2, *nr_line, *vet_line);
		free (*vet_line);
		*vet_line = (int *) malloc ((*nr_line+2)*sizeof(int));

		*nr_line = contabiliza_file (fin, *vet_line);
		getLine = get_line_file (fin, 2, *nr_line, *vet_line);
		strSplit = split(getLine, '#', *nr_line);
		*linha = atoi(strSplit[0]);
		*coluna = atoi(strSplit[1]);
		return 0;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int contabiliza_file( FILE *const fin, int* line_length ) {
	int c, count, line = 0, vet_ind = 0;

	count = 0;
	line = 0;
	fseek( fin, 0, SEEK_SET );
	for( ;; ) {
		c = fgetc( fin );

		if ( c == '\n' ) {

			line_length[vet_ind] = count;
			vet_ind++;
			count = 0;
			line++;

		}
		if( c == EOF )
		break;
		++count;
	}
	return line;
}


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int conta_line_file ( FILE *const fin, int get_line, int nro_line, int *vet_line ) {
	char *getLine = NULL;
	char **strSplit = NULL;
	int c, count;

	fseek( fin, 15, SEEK_SET );
	count = 0;
	getLine = (char *) malloc (10*sizeof(char));
	for( ;; ) {
		c = fgetc( fin );

		getLine[count] = c;
		if ( c == '\n' ) {
			getLine[count] = '\x0';

			break;
		}
		count++;
	}


	strSplit = split(getLine, '#', count);

	return atoi(strSplit[0]);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int nr_line_file ( FILE *const fin, int *vet_line ) {
	int nr_line;

	nr_line = 1;
	vet_line = (int *) malloc ((nr_line+2)*sizeof(int));
	nr_line = conta_line_file (fin, 2, nr_line, vet_line);
	free (vet_line);
	vet_line = (int *) malloc ((nr_line+2)*sizeof(int));
	return nr_line;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
char *get_line_file ( FILE *const fin, int get_line, int nro_line, int *vet_line ) {
	int c, count, vet_ind = 0, posicao = 0;
	char *retStr = NULL;


	count = 0;
	for (int i=0; i < (get_line-1); i++) {

		posicao += vet_line[i];
	}

	fseek( fin, posicao+1, SEEK_SET );

	retStr = (char *) malloc (vet_line[get_line-1] * sizeof(char));


	for( ;; ) {
		c = fgetc( fin );

		retStr[count] = c;
		if ( c == '\n' ) {
			retStr[count] = '\x0';

			count = -1;
			vet_ind++;

			return (retStr);
		}
	 	if( c == EOF )
	 		break;
	 	++count;
	}
	return NULL;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int filein_matriz (int **matriz, int linha, int coluna, FILE *file, int *vet_ind, int nr_line){
	char *getLine = NULL;
	char **strSplit= NULL;


	if (linha != (nr_line -2)) {
		printf("ERRO: Numero de linha da matriz nao esta correta!\n");
		exit (1);
	}

	for (int i=0; i < linha; i++) {

		getLine = get_line_file (file, i+3, nr_line, vet_ind);

		strSplit = split(getLine, ',', vet_ind[i+2]);

		for (int j=0; j < coluna; j++){
			
			matriz[i][j] = atoi(strSplit[j]);
		}
	}
	return 0;
}
