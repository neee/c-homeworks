#include <stdio.h>
#include <ctype.h>
#include <printf.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define WORD_BUFFER_SIZE 100

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("File path wasn't added to program arguments, example: 'examples/test.txt'");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Error: failed to open file\n");
        exit(EXIT_FAILURE);
    }

    unsigned char bytes[4];
    int num_bytes = 0;
    int ch;
    unsigned char *word_buffer = calloc(WORD_BUFFER_SIZE, sizeof(char));
    int word_length = 0;
    while ((ch = fgetc(file)) != EOF) {
        char byte = (char) ch;
        if (isspace(byte) || ispunct(byte) || byte == '\n') {
            if (word_buffer[0] == 0) {
                continue;
            }
            word_buffer[word_length + 1] = '\0';
            Entity *entity = get_from_hash_table(word_buffer);
            // Need copy string to another addr
            unsigned char *word = (unsigned char *) strdup((char *) word_buffer);
            if (entity) {
                put_to_hash_table(word, entity->value + 1);
            } else {
                put_to_hash_table(word, 1);
            }
            word_length = 0;
            memset(word_buffer, 0, WORD_BUFFER_SIZE);
            continue;
        }

        if (num_bytes == 0) {
            // Start of a new character
            if ((byte & 0x80) == 0) {
                // Single-byte character
                unsigned int codepoint = (unsigned char) byte;
                if (isalpha((char) codepoint)) {
                    codepoint = tolower((char) codepoint);
                }
                word_buffer[word_length] = codepoint;
                word_length++;
            } else if ((byte & 0xE0) == 0xC0) {
                // Two-byte character
                bytes[0] = byte;
                num_bytes = 1;
            } else if ((byte & 0xF0) == 0xE0) {
                // Three-byte character
                bytes[0] = byte;
                num_bytes = 2;
            } else if ((byte & 0xF8) == 0xF0) {
                // Four-byte character
                bytes[0] = byte;
                num_bytes = 3;
            } else {
                // Invalid UTF-8 sequence
                num_bytes = 0;
            }
        } else {
            // Continuation byte
            if ((byte & 0xC0) == 0x80) {
                bytes[num_bytes] = byte;
                num_bytes--;
                if (num_bytes == 0) {
                    // Lowing case Russian symbols
                    if (bytes[0] == 0xD0 && bytes[1] < 0xB0) {
                        if (bytes[1] < 0xA0) {
                            bytes[1] = bytes[1] + 0x20;
                        } else {
                            bytes[0] = bytes[0] + 0x1;
                            bytes[1] = bytes[1] - 0x20;
                        }
                    }
                    word_buffer[word_length] = bytes[0];
                    word_length++;
                    word_buffer[word_length] = bytes[1];
                    word_length++;
                }
            } else {
                // Invalid UTF-8 sequence
                num_bytes = 0;
            }
        }
    }
    print_hash_table();
    fclose(file);

    exit(EXIT_SUCCESS);
}
