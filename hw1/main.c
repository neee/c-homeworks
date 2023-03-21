/**
 * Created by Sergey Serdyuk on 09.03.2023.
 */
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define LOCAL_FILE_SIGNATURE 0x04034b50

FILE *get_file(const char *file_path);

int main(int argc, char **argv) {
    char *file_path = argv[1];
    if (file_path == NULL && argc <= 1) {
        printf("Input file path as first argument (example: \"./main test.zip\")");
        exit(EXIT_FAILURE);
    }

    FILE *fp = get_file(file_path);
    bool is_zip_archive = false;

    while (true) {
        uint32_t current_signature = 0;
        // Break if EOF
        size_t read_status;
        while (true) {
            read_status = fread(&current_signature, sizeof(uint32_t), 1, fp);
            if (!read_status) {
                fclose(fp);
                if (!is_zip_archive) {
                    printf("File isn't zip archive\n");
                }
                printf("Done!");
                fclose(fp);
                exit(EXIT_SUCCESS);
            }
            if (LOCAL_FILE_SIGNATURE == current_signature) {
                if (!is_zip_archive) {
                    printf("File is zip archive\n");
                }
                is_zip_archive = true;
                printf("Current signature: %x\n", current_signature);
                break;
            }
        }

        // Get file length
        fseek(fp, 18, SEEK_CUR);
        uint32_t compressed_file_length = 0;
        fread(&compressed_file_length, sizeof(compressed_file_length), 1, fp);
        printf("Compressed file size: %u bytes\n", compressed_file_length);

        // Get file name length
        uint16_t filename_length = 0;
        fread(&filename_length, sizeof(uint16_t), 1, fp);
        printf("Filename length: %u\n", filename_length + 1);

        uint16_t extra_filed_length = 0;
        fread(&extra_filed_length, sizeof(uint16_t), 1, fp);
        printf("Extra field length: %u\n", extra_filed_length);

        // Get file name chars
        char *filename = calloc(filename_length + 1, sizeof(char));
        if (filename == 0) {
            printf("Out of memory, can't allocate memory for file size");
            exit(EXIT_SUCCESS);
        }

        fread(filename, sizeof(char), filename_length, fp);
        printf("Filename: %s\n", filename);
        printf("-----------\n");
        fseek(fp, extra_filed_length + compressed_file_length, SEEK_CUR);

        free(filename);
    }
}

FILE *get_file(const char *file_path) {
    printf("Input file: %s\n", file_path);
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("File not found");
        exit(EXIT_FAILURE);
    }
    return fp;
}
