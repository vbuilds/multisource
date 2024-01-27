/* Contains code to create and manipulate a linked list of `int`s */

typedef struct elem {
    int val;
    struct elem* next;
} elem;

elem* create(int val, elem* prev_elem);
    // Add a new elem number to the linked list

void display(elem* first_elem);
    // Print out the current list of elems

void release(elem* first_elem);
    // Release the memory used by the linked list

int check_membership(int val, elem* first_elem);
    // Check linked list for presence of `val`
