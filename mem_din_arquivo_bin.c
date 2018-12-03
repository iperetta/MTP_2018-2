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

void grava_bin(Pixel * pini, int N) {
    FILE * arquivo;
    arquivo = fopen("Tons.bin", "wb");
    fwrite(pini, N, sizeof(Pixel), arquivo);
    fclose(arquivo);
}

Pixel * le_bin(char * nome_arquivo, unsigned int * pN) {
    Pixel * pixels = (Pixel *) malloc(sizeof(Pixel));
    unsigned int N = 0;
    FILE * arquivo;
    arquivo = fopen(nome_arquivo, "rb");
    while(1) {
        fread(pixels, 1, sizeof(Pixel), arquivo);
        if(feof(arquivo)) break;
        N++;
    }
    rewind(arquivo);
    pixels = (Pixel *) realloc(pixels, N*sizeof(Pixel));
    fread(pixels, N, sizeof(Pixel), arquivo);
    fclose(arquivo);
    *pN = N;
    return pixels;
}

int main() {
    unsigned int N, opc;
    Pixel * pixels;
    char fn[] = "Tons.bin";
    printf("1 - Ler arquivo; 2 - Gravar arquivo: ");
    scanf("%u", &opc); getchar();
    if(opc == 1) {
        pixels = le_bin(fn, &N);
    } else {
        printf("Quantos tons de cinza: ");
        scanf("%u", &N); getchar();
        pixels = gera_tons_de_cinza(N);
        grava_bin(pixels, N);
    }
    mostra_tons_de_cinza(pixels, pixels + N);
    salva_como_NetPPM(pixels, 20, N);
    free(pixels);
    return 0;
}
