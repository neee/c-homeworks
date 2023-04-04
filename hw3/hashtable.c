//
// Created by Sergey Serdyuk on 24.03.2023.
//

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <printf.h>
#include "hashtable.h"

#define INITIAL_TABLE_SIZE 2

static size_t hash_table_size = 0;
static size_t used_cells = 0;
static Entity **hash_table = NULL;

void expand_table(void);

void init_hash_table(int size) {
    hash_table_size = size;
    hash_table = (Entity **) calloc(sizeof(Entity *), hash_table_size);
}

unsigned int hash(unsigned char *key) {
    unsigned int hash_value = 0;
    for (size_t i = 0; i < strlen((char *) key); i++) {
        hash_value = key[i] + (hash_value << 5) - hash_value;
    }

    return hash_value % hash_table_size;
}

int put_to_hash_table(unsigned char *key, unsigned int value) {
    if (hash_table == NULL) {
        init_hash_table(INITIAL_TABLE_SIZE);
    }
    // Is need to expand table
    if ((100 / hash_table_size * used_cells) > 70) {
        expand_table();
    }
    size_t index = hash(key);
    for (size_t i = 0; i < hash_table_size; i++) {
        size_t attempt = (index + i) % hash_table_size;
        if (hash_table[attempt] == NULL) {
            Entity *new_entity = malloc(sizeof(Entity));
            new_entity->key = key;
            new_entity->value = value;
            hash_table[attempt] = new_entity;
            // Successful insertion
            used_cells++;
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

void expand_table(void) {
    size_t old_size = hash_table_size;
    Entity **old_table = hash_table;
    hash_table_size = old_size * 2;
    hash_table = (Entity **) calloc(sizeof(Entity *), hash_table_size);
    for (size_t i = 0; i < old_size; i++) {
        Entity *entity = old_table[i];
        if (entity != NULL) {
            size_t index = hash(entity->key);
            for (size_t n = 0; n < hash_table_size; n++) {
                size_t attempt = (index + n) % hash_table_size;
                if (hash_table[attempt] == NULL) {
                    hash_table[attempt] = entity;
                    break;
                }
            }
        }
    }
    printf("### DEBUG: Resize hash table (used %zu) from: %zu to %zu\n", used_cells, old_size, hash_table_size);
    free(old_table);
}

Entity *get_from_hash_table(unsigned char *key) {
    if (hash_table == NULL) {
        init_hash_table(INITIAL_TABLE_SIZE);
    }
    size_t index = hash(key);
    for (size_t i = 0; i < hash_table_size; i++) {
        size_t attempt = (index + i) % hash_table_size;
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
    for (size_t i = 0; i < hash_table_size; i++) {
        Entity *e = hash_table[i];
        if (e != NULL) {
            printf("%s - %d\n", e->key, e->value);
        }
    }
}

void free_hash_table(void) {
    for (size_t i = 0; i < hash_table_size; i++) {
        Entity *e = hash_table[i];
        if (e != NULL) {
            free(e);
        }
    }
    free(hash_table);
    printf("### DEBUG: Free mem hash table\n");
}
