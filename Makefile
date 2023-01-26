all: maker_index

CC = gcc
override CFLAGS +=  -ggdb3 -Wall

SRCS = $(wildcard docword/*.c)
OBJS = $(SRCS:.c=.o)

libdocword.a: $(SRCS) $(OBJS)
	gcc -c docword/documentos.c -o docword/documentos.o $(CFLAGS)
	gcc -c docword/palavras.c -o docword/palavras.o $(CFLAGS)
	gcc -c docword/hash.c -o docword/hash.o $(CFLAGS)
	ar -crs libdocword.a docword/documentos.o docword/palavras.o docword/hash.o

maker_index: libdocword.a indexbuilder.c
	$(CC) -o indexbuild indexbuilder.c -I docword -L . -ldocword $(CFLAGS) -lm

run:
	./inde

clean:
	@rm docword/*.o indexbuild *.a 

val:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.txt ./main datasets/tiny/train.txt out.bin
	