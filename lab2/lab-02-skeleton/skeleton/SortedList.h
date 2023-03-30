#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
    IMPORTANT!

    As we stick to pure C, we cannot use templates. We will just asume
    some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct node {
    T value;
    struct node* next;
} TNode, *TSortedList;

// TODO : Cerința 1 & Cerința 2

TSortedList create(T value) {
    // TODO (se va completa la Cerința 2)
    TSortedList list = malloc (sizeof(TNode));
    list->next = NULL;
    list->value = value;
    return list;
}

int isEmpty(TSortedList list) {
    if (list == NULL) {
        return 1;
    }
    return 0;
}

int contains(TSortedList list, T value) {
    TSortedList head = list;
    while(head != NULL) {
        if (head->value == value) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

TSortedList insert(TSortedList list, T value) {
    if (isEmpty(list) == 1) {
        list = create(value);
    } else if (list->value >= value){
        TSortedList head = create(value);
        head->next = list;
        list = head;
    } else {
        int ok = 0;
        TSortedList head = list;
        while (head->next != NULL) {
            TSortedList ptr_n = head->next;
            if (ptr_n->value >= value) {
                TSortedList ptr = create(value);
                ptr->next = head->next;
                head->next = ptr;
                ok = 1;
                break;
            }
            head = head->next;
        }
        if (ok == 0) {
            head->next = create(value);
        }
    }
    return list;
}

TSortedList deleteOnce(TSortedList list, T value) {
    TSortedList head = list;
    TSortedList l = head->next;
    if (head == NULL) {
        return list;
    }
    if (head->value == value) {
        return head->next;
    }
    while (l != NULL) {
        if (l->value == value) {
            head->next = l->next;
            free(l);
            return list;
        }
        head = l;
        l = l->next;
    }
    return list;
}

long length(TSortedList list) {
    if (list != NULL) {
        return 1 + length(list->next);
    }
    return 0;
}

T getNth(TSortedList list, int n) {
    TSortedList head = list;
    int counter = 0;
    while (head != NULL) {
        counter++;
        if (counter == n) {
            return head->value;
        }
        head = head->next;
    }
}

TSortedList freeTSortedList(TSortedList list) {
    while(list != NULL) {
        TSortedList back = list;
        list = list->next;
        free(back);
    }
    return list;
}

#endif
