#This is Example Makefile

list-primes: listprimes.o linkedlist.o main.o
	gcc listprimes.o linkedlist.o main.o -o list-primes

listprimes.o: listprimes.c includes/listprimes.h
	gcc -c listprimes.c -I ./includes

linkedlist.o: linkedlist.c includes/linkedlist.h
	gcc -c linkedlist.c -I ./includes

main.o: main.c includes/listprimes.h includes/linkedlist.h
	gcc -c main.c -I ./includes

clean:
	rm -f *.o
	rm -f list-primes
