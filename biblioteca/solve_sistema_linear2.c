#include "matrix.h"

int main() {
    double aux[] = {3,-2,-2,4,0,8};
    unsigned int N = sizeof(aux)/sizeof(double);
    Matrix *A, *iA, *b, *x; // A*x=b
    A = M_create(2,2);
    M_fill(A,aux,aux+4);
    M_print(A);
    b = M_create(2,1);
    M_fill(b,aux+4,aux+6);
    M_print(b);
    M_inv(A, &iA);
    M_prod(iA, b, &x);
    printf("x = %lf; y = %lf\n", *M_at(x,0,0), *M_at(x,1,0));
    return 0;
}