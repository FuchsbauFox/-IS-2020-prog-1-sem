#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union BitMapFileHeader {
    char buffer[14];

    struct {
        unsigned char bfType[2]; // Символы BM (2 байта)
        unsigned int bfSize; // Размер файла (4 байта)
        unsigned short bfReserved1; // 0 (2 байта)
        unsigned short bfReserved2; // 0 (2 байта)
        unsigned int bfOffBits; // Местанахождение данных растрового массива (4 байта)
    } data;
} FILEHEADER;

typedef union BitMapInfoHeader {
    char buffer[40];

    struct {
        unsigned int biSize; // Длинна этого заголовка (4 байта)
        unsigned int biWidth; // Ширина изображения (4 байта)
        unsigned int biHeight; // Высота изображения (4 байта)
        unsigned short biPlanes; // Число цветовых плоскостей (2 байта)
        unsigned short biBitCount; // Бит/пиксель (2 байта)
        unsigned int biCompression; // Метод сжатия (4 байта)
        unsigned int biSizeImage; // Количество байт в поле данных
        unsigned int biXPelsPerMeter; // горизонтальное разрешение, точек на дюйм
        unsigned int biYPelsPerMeter; // вертикальное разрешение, точек на дюйм
        unsigned int biClrUsed; // Количество используемых цветов
        unsigned int biClrImportant; // Количество существенных цветов.
    } data;
} INFOHEADER;

typedef union RGBclr {
    char buffer[3];

    struct {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
    } data;
} RGB;

RGB** LoadRGB(FILE* F, INFOHEADER infoHeader) {
    RGB **pixels = (RGB**) malloc(infoHeader.data.biHeight * sizeof(RGB*));
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        pixels[i] = (RGB*) malloc(infoHeader.data.biWidth * sizeof(RGB));
    }
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        for (int j = 0; j < infoHeader.data.biWidth; j++) {
            fread(pixels[i][j].buffer, sizeof(char), 3, F);
        }
    }
    return pixels;
}

void CreateBMP(FILE* F, FILEHEADER fileHeader, INFOHEADER infoHeader, RGB **pixels) {
    fwrite(&fileHeader.buffer, sizeof(char), 14, F);
    fwrite(&infoHeader.buffer, sizeof(char), 40, F);
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        for (int j = 0; j < infoHeader.data.biWidth; j++) {
            fwrite(&pixels[i][j].buffer, sizeof(char), 3, F);
        }
    }
}

unsigned int Check_black(RGB pixel) {
    return (pixel.data.red == 0 && pixel.data.green == 0 && pixel.data.blue == 0) ? 1 : 0;
}

unsigned int ComparisonBMP (INFOHEADER infoHeader, RGB** word1, RGB** word2) {
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        for (int j = 0; j < infoHeader.data.biWidth; j++) {
            if (Check_black(word1[i][j]) != Check_black(word2[i][j]))
                return 0;
        }
    }
    return 1;
}

RGB** CopyRGB (INFOHEADER infoHeader, RGB** in, RGB** out) {
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        for (int j = 0; j < infoHeader.data.biWidth; j++) {
            out[i][j].data = in[i][j].data;
        }
    }
    return out;
}

unsigned int CountLivePixels (INFOHEADER infoHeader, RGB** word) {
    unsigned int count = 0;
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        for (int j = 0; j < infoHeader.data.biWidth; j++) {
            if (Check_black(word[i][j]))
                count++;
        }
    }
    return count;
}

unsigned int CountLiveNeighbors (INFOHEADER infoHeader, RGB** word, unsigned int x, unsigned int y) {
    unsigned int count = 0;
    int up = x - 1, down = x + 1, right = y + 1, left = y - 1;
    if (x == 0)
        up = infoHeader.data.biHeight - 1;
    if (x == infoHeader.data.biHeight - 1)
        down = 0;
    if (y == 0)
        left = infoHeader.data.biWidth - 1;
    if (y == infoHeader.data.biWidth - 1)
        right = 0;
    if (Check_black(word[down][y])) count++;
    if (Check_black(word[x][right])) count++;
    if (Check_black(word[up][y])) count++;
    if (Check_black(word[x][left])) count++;
    if (Check_black(word[up][right])) count++;
    if (Check_black(word[down][right])) count++;
    if (Check_black(word[up][left])) count++;
    if (Check_black(word[down][left])) count++;
    return count;
}

RGB PixelDies (RGB pixel) {
    pixel.data.red = 255;
    pixel.data.green = 255;
    pixel.data.blue = 255;
    return pixel;
}

RGB PixelLives (RGB pixel) {
    pixel.data.red = 0;
    pixel.data.green = 0;
    pixel.data.blue = 0;
    return pixel;
}

RGB** GenerationNewWord (INFOHEADER infoHeader, RGB** word, RGB** new_word) {
    unsigned int live_nb;
    for (int i = 0; i < infoHeader.data.biHeight; i++) {
        for (int j = 0; j < infoHeader.data.biWidth; j++) {
            live_nb = CountLiveNeighbors(infoHeader, word, i, j);
            if (Check_black(word[i][j])) {
                if (live_nb < 2 || live_nb > 3)
                    new_word[i][j] = PixelDies(new_word[i][j]);
                else
                    new_word[i][j] = PixelLives(new_word[i][j]);
            }
            else {
                if (live_nb == 3)
                    new_word[i][j] = PixelLives(new_word[i][j]);
                else
                    new_word[i][j] = PixelDies(new_word[i][j]);
            }
        }
    }
    return new_word;
}

unsigned int SizeInt (int x) {
    int i;
    for (i = 0; x != 0; i++, x = x/10) {}
    return i;
}

int main(int argc, char* argv[]) {
    char *fileName;
    char *directory;
    int max_iter = -1, dump_freq = 1;
    if (argc % 2 == 0 || argc == 1) {
        printf("%s", "Error: incorrect data entry\n");
        return 0;
    }
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--input") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            fileName = argv[i + 1];
        }
        if (strcmp(argv[i], "--output") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            directory = argv[i + 1];
        }
        if (strcmp(argv[i], "--max_iter") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            sscanf_s(argv[i + 1], "%d", &max_iter);
        }
        if (strcmp(argv[i], "--dump_freq") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            sscanf_s(argv[i + 1], "%d", &dump_freq);
        }
    }
    FILE *fin = fopen(fileName, "r");

    if (fin == NULL) {
        printf("Error: file not found\n");
        return 0;
    }
    fseek(fin, 0, SEEK_SET);
    FILEHEADER header;
    fread(header.buffer, sizeof(char), 14, fin);
    INFOHEADER info;
    fread(info.buffer, sizeof(char), 40, fin);
    RGB **prev_word = LoadRGB(fin, info);
    fclose(fin);
    RGB **new_word = (RGB **) malloc(info.data.biHeight * sizeof(RGB *));
    for (int i = 0; i < info.data.biHeight; i++) {
        new_word[i] = (RGB *) malloc(info.data.biWidth * sizeof(RGB));
    }
    new_word = CopyRGB(info, prev_word, new_word);
    unsigned int live_pixels;

    int k;
    for (k = 0; k != max_iter; k++) {
        new_word = GenerationNewWord(info, prev_word, new_word);
        live_pixels = CountLivePixels(info, new_word);
        if (k % dump_freq == 0) {
            char *directoryFileName = calloc(2 * strlen(directory) + SizeInt(k) + 5, sizeof(char));
            sprintf(directoryFileName, "%s/%s%d.bmp", directory, directory, k);
            FILE *fout = fopen(directoryFileName, "w");
            CreateBMP(fout, header, info, new_word);
            fclose(fout);
        }
        if (live_pixels == 0 || ComparisonBMP(info, prev_word, new_word)) {
            break;
        }
        prev_word = CopyRGB(info, new_word, prev_word);
    }
    char *directoryFileName = calloc(2 * strlen(directory) + SizeInt(k) + 5, sizeof(char));
    sprintf(directoryFileName, "%s/%s%d.bmp", directory, directory, k);
    FILE *fout = fopen(directoryFileName, "w");
    CreateBMP(fout, header, info, new_word);
    fclose(fout);
    return 0;
}