#include "hashtable.h"
#include <stdlib.h>
#include <string.h>


Hashtable ht_init(size_t size) {
    Hashtable ht;
    ht.arr = malloc(size * sizeof(Block*));
    ht.size = size;
    ht.count = 0;
    init_blocks(&ht, size);
    return ht;
}

void init_blocks(Hashtable* ht, size_t size) {
    for (int i=0;i<size;i++) {
        ht->arr[i]=NULL;
    }
}

int ht_hash(char* key) {
    int result=0;
    for (;*key != '\0';key++) {
        result+=*key;
    }
    return result;
}

void ht_insert(Hashtable* ht, char* key, char* value) {
    int hash = ht_hash(key) % ht->size;
    if (ht->arr[hash] == NULL) {
        ht->arr[hash] = init_block(key, value);
        ht->count++;
    } else {
        Block* block = ht->arr[hash];
        for (;;) {
            if (block->next == NULL) {
                block->next = init_block(key, value);
                ht->count++;
                break;
            }
            block = block->next; 
        }
    }
    if ((float)ht->count/ht->size >= 0.7) {
        ht->arr = realloc(ht->arr, (ht->size * 2) * sizeof(Block));
        init_blocks(ht + (ht->size / 2), ht->size / 2);
    }
}

Block* init_block(char *key, char *value) {
    Block *block = malloc(sizeof(Block));
    block->key = strdup(key);
    block->value = strdup(value);
    block->next = NULL;
    return block;
}

char* ht_select(Hashtable *ht, char *key) {
    int hash = ht_hash(key) % ht->size;
    if (ht->arr[hash] != NULL) {
        Block* block = ht->arr[hash];
        for (;;) {
            if (strcmp(block->key, key) == 0) {
                return block->value;
            } else if (block->next != NULL) {
                block = block->next; 
            } else {
                return '\0';
            }
        }
    } else {
        return '\0';
    }
}