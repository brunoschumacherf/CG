#include <stdio.h>
#include <stdlib.h>

FILE *fpin1, *fpin2, *fpout;
int **image1R, **image1G, **image1B, **image2R, **image2G, **image2B;
int **resultR, **resultG, **resultB;
int ncol, nlin, quant_nivel_cinza;

void abrir_arquivos(int argc, char *argv[]);
void ler_cabecalho(FILE *fp, int *ncol, int *nlin, int *quant_nivel_cinza);
void ler_imagem(FILE *fp, int **imagemR, int **imagemG, int **imagemB);
void gravar_imagem(FILE *fp, int **imagemR, int **imagemG, int **imagemB);
void fechar_arquivos(void);
void subtrair_imagens(void);

void abrir_arquivos(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Modo correto de uso: <prog> <imagemIn1> <imagemIn2> <imagemOut>\n");
        exit(1);
    }

    if ((fpin1 = fopen(argv[1], "r")) == NULL || (fpin2 = fopen(argv[2], "r")) == NULL) {
        printf("Nao foi possivel abrir arquivo de imagem\n");
        exit(1);
    }

    if ((fpout = fopen(argv[3], "w")) == NULL) {
        printf("Nao foi possivel abrir arquivo de saida\n");
        exit(1);
    }
}

void ler_cabecalho(FILE *fp, int *ncol, int *nlin, int *quant_nivel_cinza) {
    char controle[4];
    fscanf(fp, "%s\n", controle);
    fscanf(fp, "%d %d\n", ncol, nlin);
    fscanf(fp, "%d\n", quant_nivel_cinza);
}

void ler_imagem(FILE *fp, int **imagemR, int **imagemG, int **imagemB) {
    int lin, col;
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fscanf(fp, "%d ", &imagemR[lin][col]);
            fscanf(fp, "%d ", &imagemG[lin][col]);
            fscanf(fp, "%d ", &imagemB[lin][col]);
        }
    }
}

void gravar_imagem(FILE *fp, int **imagemR, int **imagemG, int **imagemB) {
    int lin, col;
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", ncol, nlin);
    fprintf(fp, "%d\n", quant_nivel_cinza);
    for (lin = 0; lin < nlin; lin++) {
        for (col = 0; col < ncol; col++) {
            fprintf(fp, "%d ", imagemR[lin][col]);
            fprintf(fp, "%d ", imagemG[lin][col]);
            fprintf(fp, "%d ", imagemB[lin][col]);
        }
        fprintf(fp, "\n");
    }
}

void fechar_arquivos(void) {
    fclose(fpin1);
    fclose(fpin2);
    fclose(fpout);
}

void subtrair_imagens(void) {
    int lin, col;
    resultR = (int **)malloc(nlin * sizeof(int *));
    resultG = (int **)malloc(nlin * sizeof(int *));
    resultB = (int **)malloc(nlin * sizeof(int *));

    for (lin = 0; lin < nlin; lin++) {
        resultR[lin] = (int *)malloc(ncol * sizeof(int));
        resultG[lin] = (int *)malloc(ncol * sizeof(int));
        resultB[lin] = (int *)malloc(ncol * sizeof(int));

        for (col = 0; col < ncol; col++) {
            resultR[lin][col] = (image2R[lin][col] - image1R[lin][col] + 255) / 2;
            resultG[lin][col] = (image2G[lin][col] - image1G[lin][col] + 255) / 2;
            resultB[lin][col] = (image2B[lin][col] - image1B[lin][col] + 255) / 2;

            // Garante que os valores estejam no intervalo de 0 a 255
            resultR[lin][col] = (resultR[lin][col] < 0) ? 0 : resultR[lin][col];
            resultR[lin][col] = (resultR[lin][col] > 255) ? 255 : resultR[lin][col];

            resultG[lin][col] = (resultG[lin][col] < 0) ? 0 : resultG[lin][col];
            resultG[lin][col] = (resultG[lin][col] > 255) ? 255 : resultG[lin][col];

            resultB[lin][col] = (resultB[lin][col] < 0) ? 0 : resultB[lin][col];
            resultB[lin][col] = (resultB[lin][col] > 255) ? 255 : resultB[lin][col];
        }
    }
}

int main(int argc, char *argv[]) {
    abrir_arquivos(argc, argv);
    
    // Ler cabeçalho e dimensões da primeira imagem
    ler_cabecalho(fpin1, &ncol, &nlin, &quant_nivel_cinza);
    image1R = (int **)malloc(nlin * sizeof(int *));
    image1G = (int **)malloc(nlin * sizeof(int *));
    image1B = (int **)malloc(nlin * sizeof(int *));
    ler_imagem(fpin1, image1R, image1G, image1B);

    // Ler cabeçalho e dimensões da segunda imagem
    ler_cabecalho(fpin2, &ncol, &nlin, &quant_nivel_cinza);
    image2R = (int **)malloc(nlin * sizeof(int *));
    image2G = (int **)malloc(nlin * sizeof(int *));
    image2B = (int **)malloc(nlin * sizeof(int *));
    ler_imagem(fpin2, image2R, image2G, image2B);

    // Fechar arquivo da primeira imagem
    fclose(fpin1);

    // Subtrair imagens para detectar movimento
    subtrair_imagens();

    // Gravar imagem de resultado
    gravar_imagem(fpout, resultR, resultG, resultB);

    // Liberar memória alocada dinamicamente
    for (int i = 0; i < nlin; i++) {
        free(image1R[i]);
        free(image1G[i]);
        free(image1B[i]);
        free(image2R[i]);
        free(image2G[i]);
        free(image2B[i]);
        free(resultR[i]);
        free(resultG[i]);
        free(resultB[i]);
    }
    free(image1R);
    free(image1G);
    free(image1B);
    free(image2R);
    free(image2G);
    free(image2B);
    free(resultR);
    free(resultG);
    free(resultB);

    // Fechar arquivos
    fechar_arquivos();

    return 0;
}
