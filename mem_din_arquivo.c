#include <stdio.h>
#include <stdlib.h>

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

void salva_como_NetPPM(Pixel * pini, int larg_px, int alt_px) {
    /* 
    # NetPPM: https://en.wikipedia.org/wiki/Netpbm_format
    # The part above is the header
    # "P3" means this is a RGB color image in ASCII
    # "3 2" is the width and height of the image in pixels
    # "255" is the maximum value for each color
    # The part below is image data: RGB triplets
     */
    FILE * arquivo;
    int i, j;
    arquivo = fopen("Tons.ppm", "w");
    fprintf(arquivo, "P3\n%d %d\n255\n# Pixels:\n", larg_px, alt_px);
    for(i = 0; i < alt_px; i++) {
        for(j = 0; j < larg_px; j++) {
            fprintf(arquivo, "%d\t%d\t%d\t\t",
                pini[i].R, pini[i].G, pini[i].B);
        }    
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

int main() {
    unsigned int N;
    Pixel * pixels;
    printf("Quantos tons de cinza: ");
    scanf("%u", &N); getchar();
    pixels = gera_tons_de_cinza(N);
    mostra_tons_de_cinza(pixels, pixels + N);
    salva_como_NetPPM(pixels, 20, N);
    free(pixels);
    return 0;
}
