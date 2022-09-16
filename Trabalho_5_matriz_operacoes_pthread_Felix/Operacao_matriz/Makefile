# GNU Makefile

CC = gcc
CCFLAGS = -Wall -g -O3 #-llikwid #-funroll-all-loops
LDFLAGS = -pthread
TARGET = main_thread gera_matriz2 help #main_matriz
EXE = ./gera_matriz2


all: $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

main_thread: main_thread.c matriz.o toolsv2.o matriz-operacoes.o matriz-operacoes-threads.o
	$(CC) $(CCFLAGS) matriz-operacoes-threads.o matriz-operacoes.o matriz.o toolsv2.o main_thread.c  -o $@ $(LDFLAGS)

# main_matriz: main_matriz.c matriz.o toolsv2.o matriz-operacoes.o
# 	$(CC) $(CCFLAGS) matriz-operacoes.o matriz.o toolsv2.o main_matriz.c -o $@ $(LDFLAGS)

gera_matriz2: matriz.o toolsv2.o gera_matriz2.c
	$(CC) $(CCFLAGS) matriz.o toolsv2.o gera_matriz2.c -o $@ $(LDFLAGS)

help:
	$(EXE) 100 100 a
	$(EXE) 100 100 b
	@echo
	@echo
	@echo "####### Exemplo de Execução #######"
	@echo "./main_thread 100x100-mata.map 100x100-matb.map"

clean:
	rm -f *.o *~ $(TARGET) *.map *.map-result
