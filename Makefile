all: maker_main

CC = gcc
override CFLAGS += -g -Wall

SRCS = $(wildcard docword/*.c)
OBJS = $(SRCS:.c=.o)

libdocword.a: $(SRCS) $(OBJS)
	@gcc -c docword/documentos.c -o docword/documentos.o $(CFLAGS)
	@gcc -c docword/palavras.c -o docword/palavras.o $(CFLAGS)
	@gcc -c docword/organiza_arq.c -o docword/organiza_arq.o $(CFLAGS)
	@gcc -c docword/ordenador.c -o docword/ordenador.o $(CFLAGS)
	@ar -crs libdocword.a docword/documentos.o docword/palavras.o docword/organiza_arq.o docword/ordenador.o

maker_index: libdocword.a indexbuilder.c
	$(CC) -o indexbuild indexbuilder.c -I docword -L . -ldocword $(CFLAGS) -lm

maker_main: libdocword.a main.c
	$(CC) -o main main.c -I docword -L . -ldocword $(CFLAGS) -lm

maker_experiment: libdocword.a experiment.c
	$(CC) -o experimento experiment.c -I docword -L . -ldocword $(CFLAGS) -lm

run_index:
	./indexbuild

run:
	./main

run_experiment:
	./experimento

clean:
	@rm docword/*.o indexbuild main experimento *.a 

val_index:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ./indexbuild datasets/small/train.txt out.bin

val:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ./main out.bin 10

val_experiment:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ./experimento
	