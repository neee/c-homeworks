#include <stdio.h>
#include <stdlib.h>

long data[] = {4, 8, 15, 16, 23, 42};
const size_t data_length = sizeof(data) / sizeof(long);

typedef struct {
    long first;
    long second;
} Pair;

void print_int(long n) {
    printf("%ld ", n);
    fflush(stdout);
}

long p(long n) {
    return n & 1;
}

Pair *add_element(long first, long second) {
    Pair *pair = malloc(sizeof(Pair));
    if (pair == NULL) {
        abort();
    }
    pair->first = first;
    pair->second = second;
    return pair;
}

void m(Pair *pair, void (*fn)(long)) {
    if (pair == NULL) {
        return;
    }
    fn(pair->first);
    m((Pair *) pair->second, fn);
}

Pair *f(Pair *pair, void *data_value, long (*pred)(long), Pair *acc) {
    if (pair == NULL) {
        return acc;
    }
    if (pred(pair->first)) {
        Pair *new_pair = add_element(pair->first, (long) acc);
        acc = new_pair;
    } else {
        acc = (Pair *) pair->second;
    }
    return f((Pair *) pair->second, data_value, pred, acc);
}

int main() {
    Pair *pair = NULL;
    for (size_t i = 0; i < data_length; i++) {
        pair = add_element(data[i], (long) pair);
    }

    m(pair, print_int);
    printf("\n");

    Pair *filtered_pair = f(pair, NULL, p, NULL);
    m(filtered_pair, print_int);
    printf("\n");

    return 0;
}
