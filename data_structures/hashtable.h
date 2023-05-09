#include <stdbool.h>
#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct block{
    char *key;
    char *value;
    struct block* next;
} Block;


typedef struct {
    Block **arr;
    int size;
    int count;
} Hashtable;

Hashtable ht_init(size_t);

Block* init_block(char*, char*);
void init_blocks(Hashtable*, size_t);
void ht_insert(Hashtable*, char*, char*);
int hash(char*);
char* ht_select(Hashtable*, char*);

#endif