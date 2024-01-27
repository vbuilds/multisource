/* Contains code to create and manipulate a linked list of `int`s */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

elem* create(int val, elem* prev_elem) {
    // Add a new elem number to the linked list
    elem* new_elem = malloc(sizeof(elem));
    new_elem->val = val;
    new_elem->next = NULL;
    if (prev_elem != NULL) prev_elem->next = new_elem;
    return new_elem;
}

void display(elem* first_elem) {
    // Print out the current list of elems
    elem* cur_elem = first_elem;
    int i = 1;
    while (cur_elem != NULL) {
        printf("(%i) %i\n", i, cur_elem->val);
        cur_elem = cur_elem->next;
        i++;
    }
}

void release(elem* first_elem) {
    // Release the memory used by the linked list
    elem *cur_elem = first_elem, *next_elem;
    while (cur_elem != NULL) {
        next_elem = cur_elem->next; // Store pointer to next elem
        free(cur_elem); // release memory for the current elem
        cur_elem = next_elem; // next iteration, free the next elem
    }
}

int check_membership(int val, elem* first_elem) {
    // Check linked list for presence of `val`
    int found_val = 0;
    elem* cur_elem = first_elem;
    while (cur_elem != NULL) {
        if (val == cur_elem->val) {
            found_val = 1;
            break;
        } else {
            cur_elem = cur_elem->next;
        }
    }
    return found_val;
}
