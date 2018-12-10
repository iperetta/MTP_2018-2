#include <stdio.h>
#include "matrix.h"

int main() {
    double aux[] = {4,-5,3,4,5,6,-3,-1,2,2,-4,8};
    unsigned int N = sizeof(aux)/sizeof(double);
    Matrix *A, *B, *C;
    A = M_create(3,2);
    M_fill(A, aux, aux + N);
    printf("A:\n"); M_print(A);
    B = M_create(3,2);
    M_fill(B, aux+6, aux + N);
    printf("B:\n"); M_print(B); 
    if(!(M_add(A, B, &C))) fprintf(stderr, "Não são da mesma ordem!\n");
    else {  printf("C:\n"); M_print(C); M_free(C); }
    M_free(B);
    B = M_create(2,3);
    M_fill(B, aux+6, aux + N);
    printf("B:\n"); M_print(B); 
    if(!(M_timesK(A, -0.5, &C))) fprintf(stderr, "Não tem esse erro!\n");
    else {  printf("C:\n"); M_print(C); M_free(C); }
    if(!(M_prod(A, B, &C))) fprintf(stderr, "Matrizes de ordem errada!\n");
    else {  printf("C:\n"); M_print(C); M_free(C); }
    if(!(M_transpose(A, &C))) fprintf(stderr, "Não tem esse erro!\n");
    else {  printf("At:\n"); M_print(C); M_free(C); }
    if(!(M_submatrix(A, 1, 0, &C))) fprintf(stderr, "Não tem submatriz\n");
    else {  printf("A_1,0:\n"); M_print(C); M_free(C); }
    M_free(B);
    B = M_create(3,3);
    M_fill(B, aux+2, aux + N);
    printf("B:\n"); M_print(B); 
    printf("Determinante de B = %lf\n", M_det(B));
    M_free(A);    M_free(B);    
    return 0;
}
