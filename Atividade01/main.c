#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

typedef struct
{
    int width;
    int height;
    unsigned char *data; // Array de bytes para armazenar os pixels (R, G, B)
} ImagePPM;

// Função para ler uma imagem PPM
ImagePPM readPPM(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    ImagePPM image;
    char type[3];

    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fscanf(file, "%s\n", type);
    if (type[0] != 'P' || type[1] != '6')
    {
        fprintf(stderr, "Formato de arquivo PPM inválido\n");
        exit(1);
    }

    // Ignorar comentários
    char comment = getc(file);
    while (comment == '#')
    {
        while (getc(file) != '\n')
            ;
        comment = getc(file);
    }
    ungetc(comment, file);

    // Ler largura, altura e valor máximo de pixel
    fscanf(file, "%d %d\n", &image.width, &image.height);
    int maxval;
    fscanf(file, "%d\n", &maxval);

    // Alocar memória para os pixels
    image.data = (unsigned char *)malloc(image.width * image.height * 3 * sizeof(unsigned char));
    fread(image.data, sizeof(unsigned char), image.width * image.height * 3, file);

    fclose(file);
    return image;
}

// Função para salvar uma imagem PPM
void writePPM(const char *filename, const ImagePPM *image)
{
    FILE *file = fopen(filename, "wb");

    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(file, "P6\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "255\n");
    fwrite(image->data, sizeof(unsigned char), image->width * image->height * 3, file);

    fclose(file);
}

// Função para converter uma imagem PPM para JPEG
void ppmToJpeg(const char *ppmFilename, const char *jpegFilename, int quality)
{
    ImagePPM ppmImage = readPPM(ppmFilename);

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    FILE *jpegFile = fopen(jpegFilename, "wb");
    if (!jpegFile)
    {
        perror("Erro ao criar o arquivo JPEG");
        exit(1);
    }

    jpeg_stdio_dest(&cinfo, jpegFile);

    cinfo.image_width = ppmImage.width;
    cinfo.image_height = ppmImage.height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride = ppmImage.width * 3;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &ppmImage.data[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(jpegFile);

    jpeg_destroy_compress(&cinfo);
    free(ppmImage.data);
}

// Função para subtrair duas imagens PPM com normalização
ImagePPM subtractImages(const ImagePPM *image1, const ImagePPM *image2)
{
    if (image1->width != image2->width || image1->height != image2->height)
    {
        fprintf(stderr, "As imagens têm dimensões diferentes\n");
        exit(1);
    }

    ImagePPM result;
    result.width = image1->width;
    result.height = image1->height;
    result.data = (unsigned char *)malloc(result.width * result.height * 3 * sizeof(unsigned char));

    for (int i = 0; i < result.width * result.height * 3; i++)
    {
        int pixel_value = (int)image1->data[i] - (int)image2->data[i];

        // Normalização para o intervalo [0, 255]
        if (pixel_value < 0)
        {
            result.data[i] = 0;
        }
        else if (pixel_value > 255)
        {
            result.data[i] = 255;
        }
        else
        {
            result.data[i] = (unsigned char)pixel_value;
        }
    }

    return result;
}

// Função para segmentar o objeto na imagem resultante (binarização)
ImagePPM segmentObject(const ImagePPM *resultImage)
{
    ImagePPM segmented;
    segmented.width = resultImage->width;
    segmented.height = resultImage->height;
    segmented.data = (unsigned char *)malloc(segmented.width * segmented.height * 3 * sizeof(unsigned char));

    // Limiar para binarização (ajuste conforme necessário)
    int threshold = 50; // Limiar de 50 (pode ajustar conforme necessário)

    // Binarização da imagem resultante
    for (int i = 0; i < segmented.width * segmented.height * 3; i += 3)
    {
        // Calcular a média dos valores RGB do pixel
        int pixel_value = (resultImage->data[i] + resultImage->data[i + 1] + resultImage->data[i + 2]) / 3;

        // Binarizar o pixel com base no limiar
        if (pixel_value > threshold)
        {
            segmented.data[i] = 255;     // R
            segmented.data[i + 1] = 255; // G
            segmented.data[i + 2] = 255; // B
        }
        else
        {
            segmented.data[i] = 0;     // R
            segmented.data[i + 1] = 0; // G
            segmented.data[i + 2] = 0; // B
        }
    }

    return segmented;
}

int main()
{
    const char *inputFilename1 = "img2.ppm";
    const char *inputFilename2 = "img1.ppm";
    const char *outputFilename = "resultado.ppm";
    const char *segmentedFilename = "objeto_segmentado.ppm";
    const char *outputJpegFilename = "resultado.jpg";
    const char *segmentedJpegFilename = "objeto_segmentado.jpg";
    int jpegQuality = 90; // Qualidade JPEG (0 a 100)

    // Ler as duas imagens de entrada
    ImagePPM image1 = readPPM(inputFilename1);
    ImagePPM image2 = readPPM(inputFilename2);

    // Subtrair as imagens com normalização
    ImagePPM subtracted = subtractImages(&image1, &image2);

    // Salvar a imagem resultante da subtração em formato PPM
    writePPM(outputFilename, &subtracted);

    // Segmentar o objeto na imagem resultante
    ImagePPM segmented = segmentObject(&subtracted);

    // Salvar a imagem segmentada (objeto binarizado) em formato PPM
    writePPM(segmentedFilename, &segmented);

    // Converter e salvar a imagem resultante em formato JPEG
    ppmToJpeg(outputFilename, outputJpegFilename, jpegQuality);

    // Converter e salvar a imagem segmentada em formato JPEG
    ppmToJpeg(segmentedFilename, segmentedJpegFilename, jpegQuality);

    // Liberar memória alocada
    free(image1.data);
    free(image2.data);
    free(subtracted.data);
    free(segmented.data);

    printf("Subtração das imagens concluída. Imagem resultante salva em '%s' e '%s'\n", outputFilename, outputJpegFilename);
    printf("Objeto segmentado salvo em '%s' e '%s'\n", segmentedFilename, segmentedJpegFilename);

    return 0;
}
