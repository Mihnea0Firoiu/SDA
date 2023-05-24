/* FIROIU Mihnea-Ioan 313CD */

#ifndef HEAP_H
#define HEAP_H

typedef struct heap_content{
	int data; // value of the node
	float prior; // priority
}HContent;

typedef struct heap{
	long capacity; // capacity
	long size; // number of elements
	HContent *elem; // array of elements
} Heap;

void make_queue(Heap **, int);
int is_in_heap(Heap*, int);
void sift_up(Heap *, int);
void sift_down(Heap *, int);
void insert_heap(Heap *, HContent);
void remove_min(Heap *);
HContent get_min(Heap *);
void free_queue(Heap *);

#endif
