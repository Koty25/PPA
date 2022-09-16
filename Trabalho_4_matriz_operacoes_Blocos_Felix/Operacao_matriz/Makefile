# GNU Makefile

CC = gcc
CCFLAGS = -Wall -O3 #-llikwid #-funroll-all-loops
LDFLAGS =
TARGET = main_matriz gera_matriz2 help
EXE = ./gera_matriz2


all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_matriz: main_matriz.c matriz.o toolsv2.o matriz-operacoes.o
	$(CC) $(CCFLAGS) matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
	$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

help:
	$(EXE) 10 10 a
	$(EXE) 10 10 b
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main_matriz 10x10-mata.map 10x10-matb.map"

clean:
	rm -f *.o *~ $(TARGET) *.map *.map-result
