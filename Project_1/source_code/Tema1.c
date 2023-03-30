/*FIROIU Mihnea-Ioan 313CD*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_command 20

typedef char T;
#include "DoublyLinkedListWSentinel.h"
#include "Queue.h"
#include "Stack.h"

int main() {
    FILE *input = fopen("tema1.in", "r");
    FILE *output = fopen("tema1.out", "w");
    char command[MAX_command];

    // Declare the data structures that are used.
    TList list = initList();
    TQueue queue_update = NULL;
    TStack undo = NULL, redo = NULL;
    
    int number = 0;
    fscanf(input, "%d", &number);
    for (int i = 0; i < number; i++) {
        fscanf(input, "%s", command);
        char character = '\0';

        // UPDATE operations that are followed by a char.
        if (strcmp(command, "WRITE") == 0
         || strcmp(command, "INSERT_RIGHT") == 0 
         || strcmp(command, "INSERT_LEFT") == 0
         || strcmp(command, "MOVE_RIGHT_CHAR") == 0
         || strcmp(command, "MOVE_LEFT_CHAR") == 0) {
            if(queue_update == NULL) {
                queue_update = initQueue(command);
            } else {
                queue_update = enqueue(queue_update, command);
            }
            fscanf(input, " %c", &character);
            queue_update->tail->character = character;
        
        // UPDATE operations that are NOT followed by a char.
        } else if (strcmp(command, "MOVE_LEFT") == 0 
         || strcmp(command, "MOVE_RIGHT") == 0) {
            if(queue_update == NULL) {
                queue_update = initQueue(command);
            } else {
                queue_update = enqueue(queue_update, command);
            }
        
        // QUERY operations.
        } else if (strcmp(command, "SHOW") == 0) {
            Node_d *head = list->sentinel->next;
            while (head != NULL) {
                if (head == list->finger) {
                    fprintf(output, "|%c|", head->value);
                } else {
                    fprintf(output, "%c", head->value);
                }
                head = head->next;
            }
            fprintf(output, "\n");
        } else if (strcmp(command, "SHOW_CURRENT") == 0) {
            fprintf(output, "%c\n", list->finger->value);

        // UNDO / REDO operations.
        } else if (strcmp(command, "UNDO") == 0) {
            redo = push(redo, list->finger);
            list->finger = undo->prev_finger;
            undo = pop(undo);
        } else if (strcmp(command, "REDO") == 0) {
            undo = push(undo, list->finger);
            list->finger = redo->prev_finger;
            redo = pop(redo);

        // EXECUTE operation.
        } else if (strcmp(command, "EXECUTE") == 0) {
            if (strcmp("MOVE_LEFT", queue_update->head->data) == 0) {
                if (list->finger->prev != list->sentinel) {
                    undo = push(undo, list->finger);
                }
                moveLeft(list);
                queue_update = dequeue(queue_update);
            } else if (strcmp("MOVE_RIGHT", queue_update->head->data) == 0) {
                undo = push(undo, list->finger);
                moveRight(list);
                queue_update = dequeue(queue_update);
            } else if (strcmp("MOVE_LEFT_CHAR", queue_update->head->data) == 0) {
                undo = freeStack(undo);
                redo = freeStack(redo);
                moveLeftChar(list, queue_update->head->character, output);
                queue_update = dequeue(queue_update);
            } else if (strcmp("MOVE_RIGHT_CHAR", queue_update->head->data) == 0) {
                undo = freeStack(undo);
                redo = freeStack(redo);
                moveRightChar(list, queue_update->head->character);
                queue_update = dequeue(queue_update);
            } else if (strcmp("WRITE", queue_update->head->data) == 0) {
                undo = freeStack(undo);
                redo = freeStack(redo);
                write(list, queue_update->head->character);
                queue_update = dequeue(queue_update);
            } else if (strcmp("INSERT_LEFT", queue_update->head->data) == 0) {
                undo = freeStack(undo);
                redo = freeStack(redo);
                insertLeft(list, queue_update->head->character, output);
                queue_update = dequeue(queue_update);
            } else if (strcmp("INSERT_RIGHT", queue_update->head->data) == 0) {
                undo = freeStack(undo);
                redo = freeStack(redo);
                insertRight(list, queue_update->head->character);
                queue_update = dequeue(queue_update); 
            } 
        }
    }
    list = freeList(list); // Free list.
    if (queue_update != NULL) {
        queue_update = freeQueue(queue_update); // Free operation queue.
    }
    if (undo != NULL) {
        undo = freeStack(undo); // Free undo stack.
    }
    if (redo != NULL) {
        redo = freeStack(redo); // Free redo stack.
    }
    fclose(input); // Close input file.
    fclose(output); // Close output file.
    return 0;
}
