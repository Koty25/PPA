# GNU Makefile

CC = gcc
CCFLAGS = -Wall -g -fopenmp -O3 #-llikwid #-funroll-all-loops
LDFLAGS =
TARGET = main_omp gera_matriz2 help #main_matriz
EXE = ./gera_matriz2


# Dimensões da matriz
DIMENSÃO_X = 1000
DIMENSÃO_Y = 1000

all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_omp: main_omp.c matriz.o toolsv2.o matriz-operacoes.o matriz-operacoes-omp.o
	$(CC) $(CCFLAGS) matriz-operacoes-omp.o matriz-operacoes.o matriz.o toolsv2.o main_omp.c  -o $@ $(LDFLAGS)

# main_matriz: main_matriz.c matriz.o toolsv2.o matriz-operacoes.o
# 	$(CC) $(CCFLAGS) matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
	$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

run:
	@./main_omp $(DIMENSÃO_X)x$(DIMENSÃO_Y)-mat.map $(DIMENSÃO_X)x$(DIMENSÃO_Y)-mat.map

matriz:
	@$(EXE) $(DIMENSÃO_X) $(DIMENSÃO_Y)

help:
	$(EXE) $(DIMENSÃO_X) $(DIMENSÃO_Y)
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main_omp 1000x1000-mat.map 1000x1000-mat.map"

clean:
	rm -f *.o *~ $(TARGET) *.map *.map-result
