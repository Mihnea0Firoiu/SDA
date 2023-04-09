CC = gcc
CFLAGS = -g -Wall -pedantic-errors

.phony: clean run

build: tema2.o task_1.o task_2.o task_3.o tree.o
	$(CC) $(CFLAGS) *.o -o tema2

tema2.o: tema2.c
	$(CC) $(CFLAGS) -c tema2.c -o tema2.o

task_1.o: task_1.c
	$(CC) $(CFLAGS) -c task_1.c -o task_1.o

task_2.o: task_2.c
	$(CC) $(CFLAGS) -c task_2.c -o task_2.o

task_3.o: task_3.c
	$(CC) $(CFLAGS) -c task_3.c -o task_3.o

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c -o tree.o

clean:
	rm -f tema2 *.o

run: tema2
	./tema2

archive:
	zip tema2.zip *.c *.h tema2 README.md Makefile
