/**
 * Created by Sergey Serdyuk on 09.03.2023.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LOCAL_FILE_SIGNATURE 0x04034b50

FILE *get_file(const char *file_path);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Input file path as first argument (example: \"./main test.zip\")");
        exit(EXIT_FAILURE);
    }

    char *file_path = argv[1];
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
                exit(EXIT_SUCCESS);
            }
            if (LOCAL_FILE_SIGNATURE == current_signature) {
                if (!is_zip_archive) {
                    printf("File is zip archive\n");
                }
                is_zip_archive = true;
                break;
            } else {
                // Shift 3 byte back
                fseek(fp, -3, SEEK_CUR);
            }
        }

        // Get file length
        fseek(fp, 18, SEEK_CUR);
        uint32_t compressed_file_length = 0;
        fread(&compressed_file_length, sizeof(compressed_file_length), 1, fp);

        // Get file name length
        uint16_t filename_length = 0;
        fread(&filename_length, sizeof(uint16_t), 1, fp);

        uint16_t extra_filed_length = 0;
        fread(&extra_filed_length, sizeof(uint16_t), 1, fp);

        // Get file name chars
        unsigned char filename[filename_length + 1];
        memset(&filename, 0, filename_length + 1);

        fread(filename, sizeof(char), filename_length, fp);
        if (filename[filename_length - 1] == '/') {
            printf("Dir: %s\n", filename);
        } else {
            printf("%s\n", filename);
        }

        fseek(fp, extra_filed_length, SEEK_CUR);
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
