//
// Created by Sergey Serdyuk on 24.03.2023.
//

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <printf.h>
#include "hashtable.h"

#define TABLE_SIZE 1000

Entity *hash_table[TABLE_SIZE];

unsigned int hash(unsigned char *key) {
    unsigned int hash_value = 0;
    for (size_t i = 0; i < strlen((char *) key); i++) {
        hash_value = key[i] + (hash_value << 5) - hash_value;
    }

    return hash_value % TABLE_SIZE;
}

int put_to_hash_table(unsigned char *key, unsigned int value) {
    size_t index = hash(key);

    for (size_t i = 0; i < TABLE_SIZE; i++) {
        size_t attempt = (index + i) % TABLE_SIZE;
        if (hash_table[attempt] == NULL) {
            Entity *new_entity = malloc(sizeof(Entity));
            new_entity->key = key;
            new_entity->value = value;
            hash_table[attempt] = new_entity;
            // Successful insertion
            return 1;
        } else if (strcmp((char *) hash_table[attempt]->key, (char *) key) == 0) {
            // Key already exists in the table
            hash_table[attempt]->value = value;
            return 0;
        }
    }
    // Table is full
    return -1;
}

Entity *get_from_hash_table(unsigned char *key) {
    size_t index = hash(key);

    for (size_t i = 0; i < TABLE_SIZE; i++) {
        size_t attempt = (index + i) % TABLE_SIZE;
        if (hash_table[attempt] == NULL) {
            // Key not found in the table
            return NULL;
        } else if (strcmp((char *) hash_table[attempt]->key, (char *) key) == 0) {
            // Key found in the table
            return hash_table[attempt];
        }
    }
    // Key not found in the table
    return NULL;
}

void print_hash_table(void) {
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        Entity *e = hash_table[i];
        if (e != NULL) {
            printf("%s - %d\n", e->key, e->value);
        }
    }
}

void free_hash_table(void) {
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        Entity *e = hash_table[i];
        if (e != NULL) {
            free(e);
        }
    }
    free(*hash_table);
}
