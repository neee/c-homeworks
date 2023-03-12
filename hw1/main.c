/**
 * Created by Sergey Serdyuk on 09.03.2023.
 */
#include <stdio.h>
#include <stdlib.h>

#define ZIP_SIGNATURE 0x4034b50

int main() {
    char file_path[] = "../a1.zip";  // Will move to argv;
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("File not found");
        exit(EXIT_FAILURE);
    }

    /**
     * Я каждый раз делаю calloc но может на стеке правильней выделять под такие быстроживущие перменные память, хорошо бы прояснить что лушче и в какой момент
     * еще не ясно если делать на стеке перменную то fread ее не примит в качестве аргумента так как ему надо указатель передавать
     */
    uint32_t *current_file_signature = calloc(1, sizeof(uint32_t));
    if (current_file_signature == 0) {
        printf("Out of memory, can't allocate memory for current file signature");
        exit(EXIT_SUCCESS);
    }

    fread(current_file_signature, sizeof(uint32_t), 1, fp);
    printf("Current file signature: %x\n", *current_file_signature);
    if (ZIP_SIGNATURE != *current_file_signature) {
        printf("File isn't zip archive\n");
        fclose(fp);
        exit(EXIT_SUCCESS);
    }
    free(current_file_signature);

    printf("File is zip archive\n");

    // Get file length
    fseek(fp, 14, SEEK_CUR);
    uint32_t *compressed_file_length = calloc(1, sizeof(compressed_file_length));
    fread(compressed_file_length, sizeof(compressed_file_length), 1, fp);
    printf("Compressed file size: %u bytes\n", *compressed_file_length);

    // Get file name length
    uint16_t *filename_length = calloc(1, sizeof(uint16_t));
    fread(filename_length, sizeof(uint16_t), 1, fp);
    printf("Filename length: %u\n", *filename_length);

    uint16_t *extra_filed_length = calloc(1, sizeof(uint16_t));
    fread(extra_filed_length, sizeof(uint16_t), 1, fp);
    printf("Extra field length: %u\n", *extra_filed_length);

    // Get file name chars
    char *filename1 = calloc(*filename_length, sizeof(char));
    if (filename1 == 0) {
        printf("Out of memory, can't allocate memory for file size");
        exit(EXIT_SUCCESS);
    }

    fread(filename1, sizeof(char), *filename_length, fp);
    /**
     * Вопрос:
     * Возможно как-то упросить вывод строки (не использвоать цикл)
     */
    printf("Filename: ");
    for (int i = 0; i < *filename_length; ++i) {
        printf("%c", filename1[i]);
    }
    printf("\n");
    printf("-----------\n");

    /**
     * Вопрос:
     * я взял размер файла после имени файла и сделал fseek, то есть пропустил байты сжатого файла, после этого идет дескриптор размером 4+4+4 = 12 byte
     * то есть строка printf("New file signature: %x\n", *buffer3); должна вывести "New file signature: 4034b50" - начало нового заголовка, но выводит a666572
     * пытался в файле найти эти адерса, пока не вышло.
     * Думаю что-то упускаю со смещением или формат zip архива не правильно понял, я потом все это в цикл заверну чтоб не разбирать файлы последовательно,
     * но для начала надо чтобы 2й файл тоже показал свою сигнатуру.
     * Вообщем нужна помощь понять почему смещение не верное.
     */

    fseek(fp, *extra_filed_length + *compressed_file_length, SEEK_CUR);

    uint32_t *buffer3 = calloc(1, sizeof(uint32_t));
    fread(buffer3, sizeof(uint32_t), 1, fp);
    printf("New file signature: %x\n", *buffer3);

    fclose(fp);
    exit(EXIT_SUCCESS);
}
