//
// Created by Sergey Serdyuk on 23.03.2023.
//

#include <stdio.h>

void convert_from_cp1251_to_utf8(FILE *input_file, FILE *output_file) {
    unsigned char cp1251_byte;
    unsigned char utf8_bytes[2];

    while (fread(&cp1251_byte, 1, 1, input_file) > 0) {
        if (cp1251_byte >= 0xC0 && cp1251_byte < 0xF0) {
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = cp1251_byte - 0x30;
            fwrite(utf8_bytes, 1, 2, output_file);
        } else if (cp1251_byte >= 0xF0) {
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = cp1251_byte - 0x70;
            fwrite(utf8_bytes, 1, 2, output_file);
        } else {
            fwrite(&cp1251_byte, 1, 1, output_file);
        }
    }
}
