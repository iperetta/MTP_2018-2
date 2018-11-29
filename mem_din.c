#include <stdio.h>
#include <stdlib.h>

/* Tons de cinza */

typedef unsigned char Byte;
typedef struct { Byte B, G, R; } Pixel;

Pixel * gera_tons_de_cinza(int N) {
    Pixel * pixels = (Pixel *) calloc(N,sizeof(Pixel));
    int i;
    for(i = 0; i < N; i++)
        pixels[i].R = pixels[i].B = pixels[i].G = (255*i)/(N-1);
    return pixels;
}

void mostra_tons_de_cinza(Pixel * p_ini, Pixel * p_fim) {
    if(p_ini < p_fim) {
        printf("R: %d, G: %d, B: %d\n", p_ini->R, p_ini->G, p_ini->B);
        mostra_tons_de_cinza(p_ini+1, p_fim);
    }
}

int main() {
    unsigned int N;
    Pixel * pixels;
    printf("Quantos tons de cinza: ");
    scanf("%u", &N); getchar();
    pixels = gera_tons_de_cinza(N);
    mostra_tons_de_cinza(pixels, pixels + N);
    free(pixels);
    return 0;
}
