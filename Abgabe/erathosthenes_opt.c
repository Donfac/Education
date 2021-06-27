// 
// Algorithmus zur Implementierung des Siebs von Erastothenes
// 
// Copyright (c) 2021 Angela Pohl
//


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>

#include <omp.h>

// datatype needed to store upper limit of search space
// windows
//typedef __int32 LimitSize; 
//typedef __int64 LimitSize; 
// unix
//typedef int32_t LimitSize;
typedef int64_t LimitSize;


#define MAX_NUMBER 100000000  // upper limit of search space


double eratosthenes_naiv(LimitSize limit);
double eratosthenes_opt(LimitSize limit);


int main (void){

    LimitSize limit = MAX_NUMBER;

    double t_naiv = eratosthenes_naiv(limit);
    double t_opt = eratosthenes_opt(limit);

    printf("\nExecution times:\n");
    printf("Naiv:\t\tt_naiv: %.8f\n", t_naiv);
    printf("Opt:\t\tt_opt: %.8f\n", t_opt);    
    printf("\n");
            
    return 0;
}

// *
// * Basic Algorithm
// *
double eratosthenes_naiv(LimitSize limit){

    // allocate buffer for results
    char* primes = (char*) malloc((limit+1) * sizeof(char));
    if (primes == NULL){
        printf("Memory allocation for results failed!\n Exit...\n");
        return -1;
    }

    // start time measurement    
    double t_start = omp_get_wtime();
    
    LimitSize limit_sqrt = (LimitSize) ceil(sqrt((double) limit));

    // init all entries in result buffer
    // start at value 2
    for (LimitSize i = 2; i <= limit; i++){
        primes[i] = 1;
    }
    
    // now, walk through results, start at i = 2
    for (LimitSize i = 2; i < limit_sqrt; i++){
        // check if entry is still marked as prime
        if (primes[i] == 1){
            // reset entries of all multiples
            // start at i*i
            for (LimitSize j = i; i*j <= limit; j++){
                primes[i*j] = 0;
            }
        }
    }

    // count number of found primes
    LimitSize num_of_primes = 0;
    for (LimitSize k = 0; k <= limit; k++){
        if (primes[k] == 1){
            num_of_primes++;            
        }
    }

    double t_end = omp_get_wtime();
    
    printf("\nNaiv:\t\tFound %ld prime numbers!\n", num_of_primes);
    
    free(primes);
    
    return (t_end - t_start);
}


// *
// * Algorithm that only tests odd numbers
// *
double eratosthenes_opt(LimitSize limit){

    // allocate buffer for results    
    char* primes = (char*) malloc((limit+1) * sizeof(char));
    if (primes == NULL){
        printf("Memory allocation for results failed!\n Exit...\n");
        return -1;
    }

    // start time measurement    
    double t_start = omp_get_wtime();
    
    // **
    // YOUR SOLUTION HERE
    // **
    LimitSize limit_sqrt = (LimitSize)sqrt((double)limit);
    primes[2] = 1;
    for (LimitSize i = 3; i <= limit; i = i + 2) {
        if ((i % 2) != 0) {
            primes[i] = 1;
        }
        else {
            primes[i] = 0;
        }
    }

    for (LimitSize i = 3; i < limit_sqrt; i = i + 2) {
        
        if (primes[i] == 1) {
            // reset entries of all multiples
            // start at i*i
            for (LimitSize j = i; i * j <= limit; j = j + 2) {
                primes[i * j] = 0;
            }
        }
    }

    // count number of found primes
    LimitSize num_of_primes = 1;
    for (LimitSize k = 3; k <= limit; k = k + 2) {
        if (primes[k] == 1) {
            num_of_primes++;
        }
    }

    double t_end = omp_get_wtime();
    
    printf("\nOdd:\t\tFound %ld prime numbers!\n", num_of_primes);
    
    free(primes);
    
    return (double) (t_end - t_start);
}