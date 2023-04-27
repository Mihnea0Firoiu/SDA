CC = gcc
CFLAGS = -g -Wall -pedantic-errors

.phony: clean run

build: quadtree.o task_1.o task_2.o task_3.o tree.o func.o Queue.o
	$(CC) $(CFLAGS) *.o -o quadtree

tema2.o: quadtree.c
	$(CC) $(CFLAGS) -c quadtree.c -o quadtree.o

task_1.o: task_1.c
	$(CC) $(CFLAGS) -c task_1.c -o task_1.o

task_2.o: task_2.c
	$(CC) $(CFLAGS) -c task_2.c -o task_2.o

task_3.o: task_3.c
	$(CC) $(CFLAGS) -c task_3.c -o task_3.o

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c -o tree.o

func.o: func.c
	$(CC) $(CFLAGS) -c func.c -o func.o

Queue.o: Queue.c
	$(CC) $(CFLAGS) -c Queue.c -o Queue.o

clean:
	rm -f quadtree *.o

run: quadtree
	./quadtree

archive:
	zip quadtree.zip *.c *.h README.md Makefile
