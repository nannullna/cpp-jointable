#include "jointable.h"
#include <vector>
#include <thread>
#include <omp.h>

void jointable_ref(const long long* const tableA, const long long* const tableB,
                   std::vector<long long>* const solution, const int R, const int S) {
  
  for (long long i = 0; i < R; i++)
    for (long long j = 0; j < S; j++)
      if (tableA[i] == tableB[j]) {
        solution->push_back(tableA[i]);
        break;
      }

      
}

void jointable_optimized(const long long* const tableA, const long long* const tableB,
                         std::vector<long long>* const solution, const int R,
                         const int S) {

    int NT = 16;

    std::vector<long long> A[NT];
    std::vector<long long> B[NT];



    #pragma omp parallel num_threads(NT)
    {
        int hash;
        #pragma omp for
        for (long long i = 0; i < R; i++) {
            hash = tableA[i] % NT;
            A[hash].push_back(A[i]);
        }

        #pragma omp for
        for (long long j = 0; j < S; j++) {
            hash = tableB[j] % NT;
            B[hash].push_back(B[j]);
        }


    }
}
