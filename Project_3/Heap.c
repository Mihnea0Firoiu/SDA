/* FIROIU Mihnea-Ioan 313CD */

#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

void make_queue(Heap **heap, int capacity) {
	*heap = malloc(sizeof(Heap));
	(*heap)->capacity = capacity;
	(*heap)->size = 0;
	(*heap)->elem = malloc(sizeof(HContent) * capacity);
}

int is_in_heap(Heap *heap, int value) {
	for (int i = 0; i < heap->size; i++) {
		if (heap->elem[i].data == value) {
			return 1;
		}
	}
	return 0;
}

void sift_up(Heap *h, int idx) {
	if (idx == 0) {
		return ;
	}
	while (h->elem[(idx - 1) / 2].prior > h->elem[idx].prior && idx != 0) {
		HContent aux = h->elem[(idx - 1) / 2];
		h->elem[(idx - 1) / 2] = h->elem[idx];
		h->elem[idx] = aux;

		idx = (idx - 1) / 2;
	}
}

void sift_down(Heap *heap, int idx) {
	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < heap->size && heap->elem[left].prior < heap->elem[smallest].prior) {
		smallest = left;
	}

	if (right < heap->size && heap->elem[right].prior < heap->elem[smallest].prior) {
		smallest = right;
	}

	if (smallest != idx) {
		HContent tmp = heap->elem[idx];
		heap->elem[idx] = heap->elem[smallest];
		heap->elem[smallest] = tmp;
		sift_down(heap, smallest);
	}
}

void insert_heap(Heap *h, HContent x) {
	if (h->size >= h->capacity) {
		h->capacity = h->capacity * 2;
		h->elem = realloc(h->elem, h->capacity * sizeof(HContent));
	}
	h->elem[h->size] = x;
	sift_up(h, h->size);
	h->size++;
}

void remove_min(Heap *h) {
	h->elem[0] = h->elem[h->size - 1];
	sift_down(h, 0);
	h->size--;
}

HContent get_min(Heap *h) {
	return h->elem[0];
}

void free_queue(Heap *h) {
	if (h != NULL) {
		free(h->elem);
		free(h);
	}
}