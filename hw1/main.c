//
// Created by Sergey Serdyuk on 09.03.2023.
//
#include <stdio.h>
#include <stdlib.h>

#define ZIP_SIGNATURE 0x4034b50

int main() {
    char file_path[] = "../a1.zip";  //argv[1];
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("File not found");
        exit(EXIT_FAILURE);
    }

    uint32_t *buffer = calloc(1, sizeof(uint32_t));
    if (buffer == 0) {
        exit(EXIT_SUCCESS);
    }

    fread(buffer, sizeof(uint32_t), 1, fp);
    printf("Current file signature: %x\n", *buffer);
    if (ZIP_SIGNATURE != *buffer) {
        printf("File isn't zip archive\n");
        fclose(fp);
        exit(EXIT_SUCCESS);
    }

    printf("File is zip archive\n");

    fseek(fp, 26, SEEK_SET);
    buffer = realloc(buffer, sizeof(uint16_t));
    fread(buffer, sizeof(uint16_t), 1, fp);
    printf("-- %x\n", *buffer);

    fclose(fp);
    exit(EXIT_SUCCESS);
}
