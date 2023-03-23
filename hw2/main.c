#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encoding/koi8r.h"
#include "encoding/cp1251.h"
#include "encoding/iso88595.h"

#define OUTPUT_FILENAME_SIZE 100

typedef enum {
    CP_1251,
    KOI8_R,
    ISO_8859_5,
} Encoding;

Encoding parseEncodingEnum(char *value);

int main(int agrc, char **argv) {
    printf("File converter\n");
    if (agrc < 3) {
        printf("Not enough input values, example: input_file_name.txt cp1251");
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen(argv[1], "rb");
    if (input_file == 0) {
        printf("Input file \"%s\" not found", argv[1]);
        exit(EXIT_FAILURE);
    }
    Encoding encoding = parseEncodingEnum(argv[2]);
    char output_file_name[OUTPUT_FILENAME_SIZE] = "output_";
    strcat(output_file_name, argv[2]);
    strcat(output_file_name, ".txt");
    FILE *output_file = fopen(output_file_name, "wb");

    printf("Conversion from %s to utf-8 encoding stating...\n", argv[2]);
    switch (encoding) {
        case CP_1251:
            convert_from_cp1251_to_utf8(input_file, output_file);
            break;
        case KOI8_R:
            convert_from_koi8r_to_utf8(input_file, output_file);
            break;
        case ISO_8859_5:
            convert_from_iso88595_to_utf8(input_file, output_file);
            break;
    }
    printf("Output file: %s\n", output_file_name);
    printf("Conversion from %s to utf-8 encoding done!\n", argv[2]);

    fclose(input_file);
    fclose(output_file);

    exit(EXIT_SUCCESS);
}

Encoding parseEncodingEnum(char *value) {
    if (strcmp(value, "cp1251") == 0) {
        return CP_1251;
    } else if (strcmp(value, "koi8r") == 0) {
        return KOI8_R;
    } else if (strcmp(value, "iso88595") == 0) {
        return ISO_8859_5;
    }
    return -1;
}
