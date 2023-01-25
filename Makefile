all: maker

CC = gcc
override CFLAGS +=  -ggdb3 -Wall

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS) 

maker: $(OBJS)
	$(CC) $(CFLAGS) -o main $^ -lm

run:
	./inde

clean:
	@rm *.o main

val:
	@valgrind --leak-check=full ./main
	