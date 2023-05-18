/* FIROIU Mihnea-Ioan 313CD */

#ifndef HEAP_H
#define HEAP_H

typedef struct heap_content{
	int data; // Item priority
	int prior; // Item d
}HContent;

typedef struct heap{
	long capacity; // capacity
	long size; // number of elements
	HContent *elem; // array of elements
} Heap;

Heap* make_queue(int);
void sift_up(Heap *, int);
void sift_down(Heap *, int);
void insert_heap(Heap *, HContent);
void remove_min(Heap *);
HContent get_min(Heap *);
void free_queue(Heap *);

#endif
