#include "matrix.h"

int main() {
    double aux[] = {3,-2,-2,4,0,8};
    unsigned int N = sizeof(aux)/sizeof(double);
    Matrix *A, *Ax, *Ay, *b; // A*x=b
    A = M_create(2,2);
    M_fill(A,aux,aux+4);
    M_print(A);
    b = M_create(2,1);
    M_fill(b,aux+4,aux+6);
    M_print(b);
    Ax = M_create(2,2);
    Ay = M_create(2,2);
    aux[0] = 0; aux[2] = 8;
    M_fill(Ax,aux,aux+4);
    aux[0] = 3; aux[2] = -2; aux[1] = 0; aux[3] = 8; 
    M_fill(Ay,aux,aux+4);
    M_print(Ax);M_print(Ay);
    printf("x = %lf; y = %lf\n",
        M_det(Ax)/M_det(A),
        M_det(Ay)/M_det(A)
    );
    return 0;
}