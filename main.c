/* Compile and run using:
gcc listprimes.c linkedlist.c main.c -o list-primes && list-primes 0 100

*/

#include <stdio.h>
#include <stdlib.h>
#include <linkedlist.h>
#include <listprimes.h>

typedef enum {FIRST_N_PRIMES, PRIMES_LTE_N} mode_type;
const int DEFAULT_MODE = FIRST_N_PRIMES; // by default, list first n primes
const int DEFAULT_N = 20; // by default, list first 20 primes

int main(int argc, char** argv) {
    // Read arguments / use defaults
    mode_type mode;
    int n;
    switch (argc) {
        case 1: // no args provided, use defaults
            mode = DEFAULT_MODE;
            n = DEFAULT_N;
            break;
        case 2: // 1 arg, use default mode and custom n
            mode = DEFAULT_MODE;
            n = atoi(argv[1]);
            break;
        case 3: // custom args, check validity
            mode = (mode_type) atoi(argv[1]);
            n = atoi(argv[2]);
            break;
        default: // error
            fprintf(stderr, "Error: Please enter valid arguments\n");
            return 1;
    }

    // Create appropriate list of primes
    elem* prime_list;
    switch (mode) {
        case FIRST_N_PRIMES:
            prime_list = first_n_primes(n);
            break;
        case PRIMES_LTE_N:
            prime_list = primes_lte_n(n);
            break;
        default:
            fprintf(stderr, "Error: Invalid mode type\n");
            return 2;
    }
    
    // Display list of primes and release memory
    display(prime_list);
    release(prime_list);

    return 0;
}
