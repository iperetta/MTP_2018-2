#include <stdio.h>
#include "matriz.h"

int main() {
    int i, j;
    Matriz A;
    criar(3, 2, &A);
    for(i = 0; i < A.m; i++)
        for(j = 0; j < A.n; j++)
            *at(&A, i, j) = i*A.n+j;
    printM(&A);
    destroi(&A);
    return 0;
}
