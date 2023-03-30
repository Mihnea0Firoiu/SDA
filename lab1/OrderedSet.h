#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

long binary_search_v2 (OrderedSet* Set, T x) {
  int left = 0, right = Set->size - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if(Set->elements[mid] == x) {
      return -1;
    } else if(Set->elements[mid] < x) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return left; 
}

int contains(OrderedSet* set, const T element) {
  // TODO : Cerința 2
  int left = 0, right = set->size - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if(set->elements[mid] == element) {
      return 1;
    } else if(set->elements[mid] < element) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void add(OrderedSet* set, const T newElement) {
  if(set->capacity == set->size) {
    set->capacity = 2 * set->capacity;
    T* aux = realloc(set->elements, set->capacity * sizeof(T));
    if(aux != NULL) {
      set->elements = aux;
    } else {
      printf("Could not allocate aux\n");
      exit(1);
    }
  }
  int pos = binary_search_v2(set, newElement);
  if(pos != -1) {
    for (int i = set->size - 1; i >= pos; i--) {
      set->elements[i + 1] = set->elements[i];
    }
    set->size = set->size + 1;
    set->elements[pos] = newElement;
  }
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
  long size_T = s1->size + s2->size;
  OrderedSet *newset = createOrderedSet(size_T);
  int cap = 0;
  int i = 0, j = 0;
  while (i < s1->size && j < s2->size) {
    if(s1->elements[i] == s2->elements[j]) {
      newset->elements[cap++] = s1->elements[i];
      i++;
      j++;
    } else if (s1->elements[i] < s2->elements[j]) {
      newset->elements[cap++] = s1->elements[i];
      i++;
    } else {
      newset->elements[cap++] = s2->elements[i];
      j++;
    }
  }
  for(int k = i; k < s1->size; k++) {
    newset->elements[cap++] = s1->elements[k];
  }
  for(int k = j; k < s2->size; k++) {
    newset->elements[cap++] = s2->elements[k];
  }
  newset->size = size_T;
  return newset;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  // TODO : Cerința 3
  long size_T = s1->size + s2->size;
  OrderedSet *newset = createOrderedSet(size_T);
  int cap = 0;
  int i = 0, j = 0;
  while (i < s1->size && j < s2->size) {
    if(s1->elements[i] == s2->elements[j]) {
      newset->elements[cap++] = s1->elements[i];
      i++;
      j++;
    } else if (s1->elements[i] < s2->elements[j]) {
      i++;
    } else {
      j++;
    }
  }
  newset->size = size_T;
  return newset;
}


// -----------------------------------------------------------------------------

#endif
