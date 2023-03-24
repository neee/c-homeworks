//
// Created by Sergey Serdyuk on 23.03.2023.
//

#include <stdio.h>

void convert_char_from_koi8_to_utf8(unsigned char input, unsigned char utf8_bytes[]) {
    switch (input) {
        case 0xE1:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x90;
            break;
        case 0xE2:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x91;
            break;
        case 0xF7:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x92;
            break;
        case 0xE7:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x93;
            break;
        case 0xE4:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x94;
            break;
        case 0xE5:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x95;
            break;
        case 0xF6:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x96;
            break;
        case 0xFA:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x97;
            break;
        case 0xE9:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x98;
            break;
        case 0xEA:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x99;
            break;
        case 0xEB:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x9A;
            break;
        case 0xEC:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x9B;
            break;
        case 0xED:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x9C;
            break;
        case 0xEE:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x9D;
            break;
        case 0xEF:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x9E;
            break;
        case 0xF0:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x9F;
            break;
        case 0xF2:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA0;
            break;
        case 0xF3:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA1;
            break;
        case 0xF4:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA2;
            break;
        case 0xF5:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA3;
            break;
        case 0xE6:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA4;
            break;
        case 0xE8:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA5;
            break;
        case 0xE3:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA6;
            break;
        case 0xFE:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA7;
            break;
        case 0xFB:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA8;
            break;
        case 0xFD:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xA9;
            break;
        case 0xFF:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xAA;
            break;
        case 0xF9:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xAB;
            break;
        case 0xF8:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xAC;
            break;
        case 0xFC:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xAD;
            break;
        case 0xE0:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xAE;
            break;
        case 0xF1:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xAF;
            break;
            // Lower case
        case 0xC1:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB0;
            break;
        case 0xC2:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB1;
            break;
        case 0xD7:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB2;
            break;
        case 0xC7:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB3;
            break;
        case 0xC4:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB4;
            break;
        case 0xC5:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB5;
            break;
        case 0xD6:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB6;
            break;
        case 0xDA:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB7;
            break;
        case 0xC9:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB8;
            break;
        case 0xCA:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xB9;
            break;
        case 0xCB:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xBA;
            break;
        case 0xCC:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xBB;
            break;
        case 0xCD:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xBC;
            break;
        case 0xCE:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xBD;
            break;
        case 0xCF:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xBE;
            break;
        case 0xD0:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0xBF;
            break;
        case 0xD2:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x80;
            break;
        case 0xD3:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x81;
            break;
        case 0xD4:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x82;
            break;
        case 0xD5:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x83;
            break;
        case 0xC6:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x84;
            break;
        case 0xC8:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x85;
            break;
        case 0xC3:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x86;
            break;
        case 0xDE:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x87;
            break;
        case 0xDB:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x88;
            break;
        case 0xDD:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x89;
            break;
        case 0xDF:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x8A;
            break;
        case 0xD9:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x8B;
            break;
        case 0xD8:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x8C;
            break;
        case 0xDC:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x8D;
            break;
        case 0xC0:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x8E;
            break;
        case 0xD1:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x8F;
            break;
        case 0xB3:
            utf8_bytes[0] = 0xD0;
            utf8_bytes[1] = 0x81;
            break;
        case 0xA3:
            utf8_bytes[0] = 0xD1;
            utf8_bytes[1] = 0x91;
            break;
        default:
            utf8_bytes[0] = 0x0;
            utf8_bytes[1] = 0x0;
            break;
    }
}

void convert_from_koi8r_to_utf8(FILE *input_file, FILE *output_file) {
    unsigned char koi8ru_byte;
    unsigned char utf8_bytes[2];

    while (fread(&koi8ru_byte, 1, 1, input_file) > 0) {
        if (koi8ru_byte < 0x80) {
            fwrite(&koi8ru_byte, sizeof(char), 1, output_file);
        } else {
            convert_char_from_koi8_to_utf8(koi8ru_byte, utf8_bytes);
            fwrite(utf8_bytes, sizeof(char), 2, output_file);
        }
    }
}
