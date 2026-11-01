#include "simple_hash_table.h"

HashTable *sht_create_hash_table(int table_size)
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    (*ht).table = (Node *)malloc(sizeof(Node) * table_size);
    (*ht).table_size = table_size;
    return ht;
}
void sht_set(HashTable *ht, KeyType key, ValueType value)
{
    int address = sht_hash(key, (*ht).table_size);
    (*ht).table[address].key = key;
    (*ht).table[address].value = value;
}
ValueType sht_get(HashTable *ht, KeyType key)
{
    int address = sht_hash(key, (*ht).table_size);
    return (*ht).table[address].value;
}

void sht_destroy_hash_table(HashTable *ht)
{
    free((*ht).table);
    free(ht);
}
int sht_hash(KeyType key, int table_size)
{
    return key % table_size;
}


