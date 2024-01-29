/* Contains code to create a linked list of prime numbers. */
/* Update from linux user */

#include <stdlib.h>
#include <math.h>
#include <linkedlist.h>
#include <listprimes.h>

elem* first_n_primes(int n) {
    // Return a pointer to the first element in a linked list of the first n
    // primes

    elem *first_prime = create(2, NULL), *cur_prime = first_prime;
    int cur_val = 3, list_len = 1;
    
    // Iterate until list of primes is desired length
    while (list_len < n) {
        if (is_prime(cur_val, first_prime)) { // cur_val is prime
            cur_prime = create(cur_val, cur_prime); // add to linked list
            list_len ++;
            // printf("(%i) %i\n", list_len, cur_val);
        }
        cur_val += 2;
    }
    return first_prime;
}

elem* primes_lte_n(int n) {
    // Return a pointer to the first element in a linked list of all primes
    // less than or equal to `n`
    elem *first_prime = create(2, NULL), *cur_prime = first_prime;
    int cur_val = 3, list_len = 1;
    
    // Iterate until all primes less than n have been considered
    while (cur_val <= n) {
        if (is_prime(cur_val, first_prime)) { // cur_val is prime
            cur_prime = create(cur_val, cur_prime); // add to linked list
            list_len ++;
            // printf("(%i) %i\n", list_len, cur_val);
        }
        cur_val += 2;
    }
    return first_prime;
}

int is_prime(int x, elem* first_prime) {
    // Check if x is prime, given a linked list of prime numbers (assumed
    // valid)
    elem* cur_prime = first_prime;
    double sqrtx = sqrt(x);
    // Iterate through each element of the linked list
    while (cur_prime != NULL) {
        if (x % cur_prime->val == 0) return 0;
        else if (cur_prime->val > sqrtx) return 1;
        else cur_prime = cur_prime->next;
    }
    return 1;
}
