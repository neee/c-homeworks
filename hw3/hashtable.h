//
// Created by Sergey Serdyuk on 24.03.2023.
//
#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct {
    unsigned char *key;
    unsigned int value;
} Entity;

int put_to_hash_table(unsigned char *key, unsigned int value);

Entity *get_from_hash_table(unsigned char *key);

void print_hash_table(void);

void free_hash_table(void);

#endif
