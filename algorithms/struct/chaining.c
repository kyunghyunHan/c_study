#include "chaining.h"

HashTable *cht_create_hash_table(int table_size)
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (ht == NULL)
        return NULL;

    ht->Table = (List *)malloc(sizeof(List) * table_size);
    if (ht->Table == NULL)
    {
        free(ht);
        return NULL;
    }

    memset(ht->Table, 0, sizeof(List) * table_size);

    ht->TableSize = table_size;

    return ht;
}

Node *cht_create_node(KeyType key, ValueType value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;

    new_node->Key = (char *)malloc(sizeof(char) * (strlen(key) + 1));
    if (new_node->Key == NULL)
    {
        free(new_node);
        return NULL;
    }

    strcpy(new_node->Key, key);

    new_node->Value = (char *)malloc(sizeof(char) * (strlen(value) + 1));
    if (new_node->Value == NULL)
    {
        free(new_node->Key);
        free(new_node);
        return NULL;
    }

    strcpy(new_node->Value, value);

    new_node->Next = NULL;

    return new_node;
}

void cht_destroy_node(Node *the_node)
{
    if (the_node == NULL)
        return;

    free(the_node->Key);
    free(the_node->Value);
    free(the_node);
}

void cht_set(HashTable *ht, KeyType key, ValueType value)
{
    int address = cht_hash(key, strlen(key), ht->TableSize);

    Node *new_node = cht_create_node(key, value);
    if (new_node == NULL)
        return;

    // 해당 주소가 비어 있는 경우
    if (ht->Table[address] == NULL)
    {
        ht->Table[address] = new_node;
    }
    // 충돌이 발생한 경우
    else
    {
        List list = ht->Table[address];

        new_node->Next = list;
        ht->Table[address] = new_node;

        printf("Collision occurred : Key(%s), Address(%d)\n",
               key, address);
    }
}

ValueType cht_get(HashTable *ht, KeyType key)
{
    int address = cht_hash(key, strlen(key), ht->TableSize);

    List the_list = ht->Table[address];

    while (the_list != NULL)
    {
        if (strcmp(the_list->Key, key) == 0)
        {
            return the_list->Value;
        }

        the_list = the_list->Next;
    }

    return NULL;
}

static void cht_destroy_list(List list)
{
    if (list == NULL)
        return;

    if (list->Next != NULL)
        cht_destroy_list(list->Next);

    cht_destroy_node(list);
}

void cht_destroy_hashtable(HashTable *ht)
{
    if (ht == NULL)
        return;

    for (int i = 0; i < ht->TableSize; i++)
    {
        List list = ht->Table[i];
        cht_destroy_list(list);
    }

    free(ht->Table);
    free(ht);
}

int cht_hash(KeyType key, int key_lenght, int table_size)
{
    int hash_value = 0;

    for (int i = 0; i < key_lenght; i++)
    {
        hash_value = (hash_value << 3) + key[i];
    }

    hash_value = hash_value % table_size;

    return hash_value;
}