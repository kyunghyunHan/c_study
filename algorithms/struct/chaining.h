#ifndef CHAINING_H
#define CHAINING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *KeyType;
typedef char *ValueType;

typedef struct Node
{
    KeyType Key;
    ValueType Value;

    struct Node *Next;
} Node;

typedef Node *List;

typedef struct HashTable
{
    int TableSize;
    List *Table;
} HashTable;

HashTable *cht_create_hash_table(int table_size);
void cht_destroy_hashtable(HashTable *ht);

Node *cht_create_node(KeyType key, ValueType value);
void cht_destroy_node(Node *the_node);

void cht_set(HashTable *ht, KeyType key, ValueType value);
ValueType cht_get(HashTable *ht, KeyType key);
int cht_hash(KeyType key, int key_lenght, int table_size);

#endif