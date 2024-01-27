/* Contains code to create a linked list of prime numbers. */

elem* first_n_primes(int n);
    // Return a pointer to the first element in a linked list of the first n
    // primes

elem* primes_lte_n(int n);
    // Return a pointer to the first element in a linked list of all primes
    // less than or equal to `n`

int is_prime(int x, elem* first_prime);
    // Check if x is prime, given a linked list of prime numbers (assumed
    // valid)
