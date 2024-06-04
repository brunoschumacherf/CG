#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição da estrutura para armazenar as cores RGB de um pixel
typedef struct {
    unsigned char vermelho, verde, azul;
} Pixel;

// Definição da estrutura da imagem, contendo as dimensões e os dados dos pixels
typedef struct {
    int largura, altura;
    Pixel *dados;
} Imagem;

// Função para ler uma imagem no formato PPM do tipo P3 de um arquivo
Imagem* lerPPM(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); // Abrindo o arquivo em modo leitura
    if (!arquivo) { // Verifica se o arquivo foi aberto corretamente
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char tipo[3];
    fscanf(arquivo, "%s", tipo); // Lê o tipo do arquivo PPM (deve ser P3)
    if (tipo[0] != 'P' || tipo[1] != '3') { // Verifica se o tipo é P3
        fprintf(stderr, "Formato de arquivo PPM não suportado (deve ser P3)\n");
        fclose(arquivo);
        exit(1);
    }

    int largura, altura, maxval;
    fscanf(arquivo, "%d %d %d", &largura, &altura, &maxval); // Lê as dimensões e o valor máximo de cor

    Imagem *img = malloc(sizeof(Imagem)); // Aloca memória para a estrutura da imagem
    img->largura = largura; // Define a largura da imagem
    img->altura = altura; // Define a altura da imagem
    img->dados = malloc(largura * altura * sizeof(Pixel)); // Aloca memória para os dados dos pixels

    for (int i = 0; i < largura * altura; i++) { // Lê os dados dos pixels
        fscanf(arquivo, "%hhu %hhu %hhu", &img->dados[i].vermelho, &img->dados[i].verde, &img->dados[i].azul);
    }

    fclose(arquivo); // Fecha o arquivo
    return img; // Retorna a imagem carregada
}

// Função para escrever uma imagem no formato PPM P3 em um arquivo
void escreverPPM(const char *nomeArquivo, Imagem *img) {
    FILE *arquivo = fopen(nomeArquivo, "w"); // Abre o arquivo para escrita
    if (!arquivo) { // Verifica se o arquivo foi aberto corretamente
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "P3\n%d %d\n255\n", img->largura, img->altura); // Escreve o cabeçalho do arquivo PPM
    for (int i = 0; i < img->largura * img->altura; i++) { // Escreve os dados dos pixels
        fprintf(arquivo, "%d %d %d ", img->dados[i].vermelho, img->dados[i].verde, img->dados[i].azul);
        if ((i + 1) % img->largura == 0) fprintf(arquivo, "\n");
    }

    fclose(arquivo); // Fecha o arquivo
}

// Função para redimensionar uma imagem usando a interpolação de 1-vizinhança
Imagem* redimensionar1Vizinhanca(Imagem *orig, int novaLargura, int novaAltura) {
    Imagem *novaImg = malloc(sizeof(Imagem)); // Aloca memória para a nova imagem
    novaImg->largura = novaLargura; // Define a nova largura
    novaImg->altura = novaAltura; // Define a nova altura
    novaImg->dados = malloc(novaLargura * novaAltura * sizeof(Pixel)); // Aloca memória para os novos dados dos pixels

    double x_ratio = orig->largura / (double) novaLargura; // Calcula a relação de aspecto horizontal
    double y_ratio = orig->altura / (double) novaAltura; // Calcula a relação de aspecto vertical

    for (int i = 0; i < novaAltura; i++) {
        for (int j = 0; j < novaLargura; j++) {
            int px = floor(j * x_ratio); // Calcula a posição horizontal do pixel original
            int py = floor(i * y_ratio); // Calcula a posição vertical do pixel original
            novaImg->dados[i * novaLargura + j] = orig->dados[py * orig->largura + px]; // Atribui o pixel mais próximo
        }
    }

    return novaImg; // Retorna a imagem redimensionada
}

// Função para redimensionar uma imagem usando a interpolação de 4-vizinhança
Imagem* redimensionar4Vizinhanca(Imagem *orig, int novaLargura, int novaAltura) {
    Imagem *novaImg = malloc(sizeof(Imagem)); // Aloca memória para a nova imagem
    novaImg->largura = novaLargura; // Define a nova largura
    novaImg->altura = novaAltura; // Define a nova altura
    novaImg->dados = malloc(novaLargura * novaAltura * sizeof(Pixel)); // Aloca memória para os novos dados dos pixels

    double x_ratio = orig->largura / (double) novaLargura; // Calcula a relação de aspecto horizontal
    double y_ratio = orig->altura / (double) novaAltura; // Calcula a relação de aspecto vertical

    for (int i = 0; i < novaAltura; i++) {
        for (int j = 0; j < novaLargura; j++) {
            double px = j * x_ratio; // Calcula a posição horizontal proporcional
            double py = i * y_ratio; // Calcula a posição vertical proporcional
            int x1 = (int)px; // Coordenada x do pixel mais próximo à esquerda
            int y1 = (int)py; // Coordenada y do pixel mais próximo acima
            int x2 = x1 + 1 < orig->largura ? x1 + 1 : x1; // Coordenada x do pixel mais próximo à direita
            int y2 = y1 + 1 < orig->altura ? y1 + 1 : y1; // Coordenada y do pixel mais próximo abaixo

            // Obtém os quatro pixels mais próximos
            Pixel p1 = orig->dados[y1 * orig->largura + x1];
            Pixel p2 = orig->dados[y1 * orig->largura + x2];
            Pixel p3 = orig->dados[y2 * orig->largura + x1];
            Pixel p4 = orig->dados[y2 * orig->largura + x2];

            // Calcula a média dos quatro pixels para obter o pixel interpolado
            novaImg->dados[i * novaLargura + j].vermelho = (p1.vermelho + p2.vermelho + p3.vermelho + p4.vermelho) / 4;
            novaImg->dados[i * novaLargura + j].verde = (p1.verde + p2.verde + p3.verde + p4.verde) / 4;
            novaImg->dados[i * novaLargura + j].azul = (p1.azul + p2.azul + p3.azul + p4.azul) / 4;
        }
    }

    return novaImg; // Retorna a imagem redimensionada
}

int main() {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo PPM: ");
    scanf("%99s", nomeArquivo);

    Imagem *imagemOriginal = lerPPM(nomeArquivo);

    int novaLargura, novaAltura;
    printf("Digite a nova largura e altura: ");
    scanf("%d %d", &novaLargura, &novaAltura);

    Imagem *imagemRedimensionada1 = redimensionar1Vizinhanca(imagemOriginal, novaLargura, novaAltura);
    Imagem *imagemRedimensionada4 = redimensionar4Vizinhanca(imagemOriginal, novaLargura, novaAltura);

    escreverPPM("saida_1_vizinhanca.ppm", imagemRedimensionada1);
    escreverPPM("saida_4_vizinhanca.ppm", imagemRedimensionada4);

    free(imagemOriginal->dados);
    free(imagemOriginal);
    free(imagemRedimensionada1->dados);
    free(imagemRedimensionada1);
    free(imagemRedimensionada4->dados);
    free(imagemRedimensionada4);
    return 0;
}
