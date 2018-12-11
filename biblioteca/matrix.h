#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECK(x,y,z)                   \
    if(!(x)) { fprintf(stderr, y); }   \
    else z

typedef
    struct {
        unsigned int R, C;
        double * elements; // ROW-FIRST
    }
Matrix;

Matrix * M_create(unsigned int R, unsigned int C) {
    Matrix * A = (Matrix *) malloc(sizeof(Matrix));
    A->R = R; A->C = C;
    A->elements = (double *) calloc(R*C, sizeof(double));
    return A;
}

void M_free(Matrix * A) {
    free(A->elements);
    free(A);
}

double * M_at(Matrix * A, unsigned int i, unsigned int j) {
    return A->elements + (i*A->C + j);
}

void M_fill(Matrix * A, double * dini, double * dend) {
    unsigned int i, j;
    for(i = 0; i < A->R; i++)
        for(j = 0; j < A->C; j++)
            if(dini + i*A->C + j < dend)
                *M_at(A, i, j) = dini[i*A->C + j];
}

void M_print(Matrix * A) {
    unsigned int i, j;
    for(i = 0; i < A->R; i++) {
        for(j = 0; j < A->C; j++)
            printf("%lf ", *M_at(A,i,j));
        printf("\n");
    }
}

int M_add(Matrix * A, Matrix * B, Matrix ** Result) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A e B são matrizes (argumentos), Result é a resposta
     */
    int i, j;
    if(A->R == B->R && A->C == B->C) {
        *Result = M_create(A->R, A->C);
        for(i = 0; i < A->R; i++) 
            for(j = 0; j < A->C; j++)
                *M_at(*Result,i,j) = *M_at(A,i,j) + *M_at(B,i,j);
        return 1;
    } else return 0;
}

int M_timesK(Matrix * A, double k, Matrix ** Result) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A é matriz e k é constante (argumentos), Result é a resposta
     */
    int i, j;
    *Result = M_create(A->R, A->C);
    for(i = 0; i < A->R; i++) 
        for(j = 0; j < A->C; j++)
            *M_at(*Result,i,j) = *M_at(A,i,j) * k;
    return 1;
}

int M_prod(Matrix * A, Matrix * B, Matrix ** Result) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A e B são matrizes (argumentos), Result é a resposta
     */
    int i, j, k;
    double acc;
    if(A->C == B->R) {
        *Result = M_create(A->R, B->C);
        for(i = 0; i < A->R; i++) {
            for(j = 0; j < B->C; j++) {
                acc = 0.0;
                for(k = 0; k < A->C; k++)
                    acc += *M_at(A,i,k) * *M_at(B,k,j);
                *M_at(*Result,i,j) = acc;
            }
        }
        return 1;
    } else return 0;
}

int M_transpose(Matrix * A, Matrix ** At) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A é matriz (argumentos), At é a resposta
     */
    int i, j;
    *At = M_create(A->C, A->R);
    for(i = 0; i < A->R; i++) 
        for(j = 0; j < A->C; j++)
            *M_at(*At,j,i) = *M_at(A,i,j);
    return 1;
}

int M_submatrix(Matrix * A, int row, int column, Matrix ** S) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A é matriz, row e column posição (argumentos), S é a resposta
     */
    int i, j, p, q;
    if(row < A->R && column < A->C && (A->R != 1 || A->C != 1)) {
        *S = M_create(A->R-1, A->C-1);
        p = 0;
        for(i = 0; i < A->R; i++) {
            if(i != row) {
                q = 0;
                for(j = 0; j < A->C; j++) {
                    if(j != column) {            
                        *M_at(*S,p,q) = *M_at(A,i,j);
                        q++;
                    }
                }
                p++;
            }
        }
        return 1;
    } else return 0;
}

double M_det(Matrix * A);

double M_minor(Matrix * A, int i, int j) {
    double minor = NAN;
    Matrix * S;
    if(!(M_submatrix(A, i, j, &S)))
        fprintf(stderr, "Não existe submatriz!\n");
    else {
        minor = M_det(S);
        M_free(S);
    }
    return minor;
}

double M_cofactor(Matrix * A, int i, int j) {
	return (((i+j)%2) ? -1.0 : 1.0)*M_minor(A,i,j);
}

double M_det(Matrix * A) {
    int i, j = 0;
    double acc = 0.0;
    if(A->R == A->C) { 
        if(A->R == 1)
            return *M_at(A,0,0);
        if(A->R == 2)
            return *M_at(A,0,0) * *M_at(A,1,1) - 
                (*M_at(A,0,1) * *M_at(A,1,0));
        for(i = 0; i < A->R; i++)
            acc += *M_at(A,i,j) * M_cofactor(A,i,j);
        return acc;
    }
    return NAN;
}

int M_comatrix(Matrix * A, Matrix ** CoA) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A é matriz (argumentos), CoA é a resposta
     */
    int i, j;
    *CoA = M_create(A->R, A->C);
    for(i = 0; i < A->R; i++) 
        for(j = 0; j < A->C; j++) 
            *M_at(*CoA,i,j) = M_cofactor(A,i,j);
    return 1;
}

int M_adjoint(Matrix * A, Matrix ** adjA) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A é matriz (argumentos), adjA é a resposta
     */
    int i, j;
    Matrix * aux;
    M_comatrix(A, &aux);
    M_transpose(aux, adjA);
    M_free(aux);
    return 1;
}

int M_inv(Matrix * A, Matrix ** iA) {
    /* Retorna 0 se erro, ou 1 se correto 
     * A é matriz, row e column posição (argumentos), S é a resposta
     */
    Matrix * aux;
    double det = M_det(A);
    if(A->R == A->C && !isinf(1.0/det)) {
        M_adjoint(A, &aux);
        M_timesK(aux, 1.0/det, iA);
        M_free(aux);
        return 1;
    } else return 0;
}

#endif