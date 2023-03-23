//
// Created by Sergey Serdyuk on 23.03.2023.
//

#include <stdio.h>

void convert_from_iso88595_to_utf8(FILE *input_file, FILE *output_file) {
    unsigned char iso_8859_5_byte;
    unsigned char utf8_bytes[2];

    while (fread(&iso_8859_5_byte, 1, 1, input_file) > 0) {
        if (iso_8859_5_byte >= 128 && iso_8859_5_byte < 224) {
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = iso_8859_5_byte - 0x20;
            fwrite(utf8_bytes, 1, 2, output_file);
        } else if (iso_8859_5_byte >= 224) {
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = iso_8859_5_byte - 0x60;
            fwrite(utf8_bytes, 1, 2, output_file);
        } else {
            fwrite(&iso_8859_5_byte, 1, 1, output_file);
        }
    }
}
