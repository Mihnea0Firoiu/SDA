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
    int parent = (idx - 1) / 2;
	HContent tmp = h->elem[parent];
	while (tmp.prior > h->elem[idx].prior && idx != 0) {
		HContent aux = tmp;
		h->elem[(idx - 1) / 2] = h->elem[idx];
		h->elem[idx] = aux;

		idx = (idx - 1) / 2;
		tmp = h->elem[(idx - 1) / 2];
	}
}

void sift_down(Heap *h, int idx) {
	if (h->size <= 1) {
		return;
	}
	HContent tmp;
	int idx_child;
	if (h->elem[2 * idx + 1].prior < h->elem[idx].prior) {
		tmp = h->elem[2 * idx + 1];
		idx_child = 2 * idx + 1;
	} else {
		tmp = h->elem[2 * idx + 2];
		idx_child = 2 * idx + 2;
	}
	while (tmp.prior < h->elem[idx].prior && idx_child < h->size) {
		HContent aux = tmp;
		h->elem[idx_child] = h->elem[idx];
		h->elem[idx] = aux;

		idx = idx_child;

		if (h->elem[2 * idx + 1].prior < h->elem[idx].prior) {
			tmp = h->elem[2 * idx + 1];
			idx_child = 2 * idx + 1;
		} else {
			tmp = h->elem[2 * idx + 2];
			idx_child = 2 * idx + 2;
		}
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
	for (int i = 0; i < h->size - 1; i++) {
		h->elem[i] = h->elem[i + 1];
	}
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