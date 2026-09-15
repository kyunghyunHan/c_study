#ifndef SIMPLE_HASHTABLE_H
#define SIMPLE_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef int ValueType;

typedef struct Node
{
    KeyType key;
    ValueType value;
} Node;

typedef struct HashTable
{
    int table_size;
    Node *table;
} HashTable;

HashTable *sht_create_hash_table(int table_size);
void sht_Set(HashTable *ht, KeyType key, ValueType value);
ValueType sht_Get(HashTable *ht, KeyType key);
void sht_destroy_hash_table(HashTable *ht);
int sht_hash(KeyType key, int table_size);

#endif