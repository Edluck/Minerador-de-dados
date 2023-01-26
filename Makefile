all: maker_index

CC = gcc
override CFLAGS += -g -Wall

SRCS = $(wildcard docword/*.c)
OBJS = $(SRCS:.c=.o)

libdocword.a: $(SRCS) $(OBJS)
	@gcc -c docword/documentos.c -o docword/documentos.o $(CFLAGS)
	@gcc -c docword/palavras.c -o docword/palavras.o $(CFLAGS)
	@gcc -c docword/hash.c -o docword/hash.o $(CFLAGS)
	@ar -crs libdocword.a docword/documentos.o docword/palavras.o docword/hash.o

maker_index: libdocword.a indexbuilder.c
	$(CC) -o indexbuild indexbuilder.c -I docword -L . -ldocword $(CFLAGS) -lm

maker_main: libdocword.a main.c
	$(CC) -o main main.c -I docword -L . -ldocword $(CFLAGS) -lm

maker_experiment: libdocword.a experiment.c
	$(CC) -o experimento experiment.c -I docword -L . -ldocword $(CFLAGS) -lm

run:
	./inde

clean:
	@rm docword/*.o indexbuild *.a 

val:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ./indexbuild datasets/tiny/train.txt out.bin
	