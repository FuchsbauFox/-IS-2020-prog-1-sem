#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Data {
    unsigned create:1;
    unsigned extract:1;
    unsigned list:1;
    char* archiveName;
} DATA;

typedef struct Input_Files{
    char** files;
    unsigned amountFiles;
    int* sizeFiles;
} INPUTFILE;

int main(int argc, char**argv) {
    char buffer[100];
    int counter = 0;
    int amount;
    char ** filenames, char_buf;
    int * fileSize;
    FILE *bufferFile, *archiveFile;

    if (argc == 1) {
        puts("Options aren't detecting.");
        return 0;
    }
    DATA data;
    INPUTFILE inputfile;
    data.extract = 0;
    data.create = 0;
    data.list = 0;
    while (--argc > 0) {
        argv++;
        if (strcmp(*argv, "--file") == 0) {
            if (argc != 1)
                data.archiveName = *++argv;
            else {
                puts("Error: incorrect data entry");
                return 0;
            }
            argc--;
        } else if (strcmp(*argv, "--create") == 0)
            data.create = 1;
        else if (strcmp(*argv, "--extract") == 0)
            data.extract = 1;
        else if (strcmp(*argv, "--list") == 0)
            data.list = 1;
        else {
            inputfile.amountFiles = argc;
            inputfile.files = argv;
            argc = 0;
        }
    }

    if (data.list + data.create + data.extract != 1) {
        puts("Error: incorrect data entry");
        return 0;
    }

    if (data.create && inputfile.amountFiles == 0) {
        puts("Error: file not found");
        return 0;
    }

    // create
    if (data.create) {
        FILE *file;
        inputfile.sizeFiles = malloc(inputfile.amountFiles * sizeof(int));
        for (int i = 0; i < inputfile.amountFiles; ++i) {
            inputfile.sizeFiles[i] = 0;
        }
        for (int i = 0; i < inputfile.amountFiles; i++) {

            file = fopen(inputfile.files[i], "rb");

            if (file == NULL) {
                printf("Error: File \"%s\" can't be open.", inputfile.files[i]);
                return 0;
            }

            while (fread(buffer, 1, 1, file) != 0) {
                inputfile.sizeFiles[i] += 1;
            }
            fclose(file);
        }
        FILE *fout;
        strcpy(buffer, data.archiveName);
        strcat(buffer, ".arc");
        fout = fopen(buffer, "wb");
        sprintf(buffer, "%i:", inputfile.amountFiles);
        fwrite(buffer, sizeof(char), strlen(buffer), fout);
        for (int i = 0; i < inputfile.amountFiles; ++i) {
            fwrite(inputfile.files[i], sizeof(char), strlen(inputfile.files[i]), fout);
            fprintf(fout, ":%i:", inputfile.sizeFiles[i]);
        }

        for (int i = 0; i < inputfile.amountFiles; i++) {

            file = fopen(inputfile.files[i], "rb");

            if (file == NULL) {
                printf("Error: File \"%s\" can't be open.", inputfile.files[i]);
                return 0;
            }

            while (fread(buffer, 1, 1, file) != 0) {
                fwrite(buffer, sizeof(char), 1, fout);
            }
            fclose(file);
        }
    }

    // extract
    if (data.extract) {
        archiveFile = fopen(data.archiveName, "rb");
        fscanf(archiveFile, "%i:", &amount);
        filenames = malloc(sizeof(char*) * amount);
        fileSize = malloc(sizeof(int) * amount);
        for (int i = 0; i < amount; ++i) {
            filenames[i] = malloc(sizeof(char) * 100);
            while((char_buf = getc(archiveFile)) != ':'){
                filenames[i][counter] = char_buf;
                counter++;
            }
            filenames[i][counter] = '\0';
            counter = 0;
            fscanf(archiveFile, "%i:", fileSize + i);
        }
        for (int i = 0; i < amount; ++i) {
            bufferFile = fopen(filenames[i], "wb");
            for (int j = 0; j < fileSize[i]; ++j) {
                fread(&char_buf, 1, 1, archiveFile);
                fwrite(&char_buf, 1, 1, bufferFile);
            }
            fclose(bufferFile);
        }
    }

    //list
    if (data.list){
        archiveFile = fopen(data.archiveName, "rb");
        fscanf(archiveFile, "%i:", &amount);
        filenames = malloc(sizeof(char*) * amount);
        for (int i = 0; i < amount; ++i) {
            filenames[i] = malloc(sizeof(char) * 100);
            while((char_buf = getc(archiveFile)) != ':'){
                filenames[i][counter] = char_buf;
                counter++;
            }
            filenames[i][counter] = '\0';
            counter = 0;
            fscanf(archiveFile, "%i:", buffer);
        }
        printf("==========\n");
        for (int i = 0; i < amount; ++i) {
            printf("%s\n", filenames[i]);
        }
        printf("==========\n");
    }
    return 0;
}