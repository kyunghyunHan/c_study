#include "simple_hash_table.h"

int main(void)
{
    HashTable *ht = sht_create_hash_table(193);

    sht_set(ht, 418, 32114);
    sht_set(ht, 9, 514);
    sht_set(ht, 27, 8917);
    sht_set(ht, 1031, 286);

    printf("Key : %d , value : %d\n", 418, sht_get(ht, 418));
    printf("Key : %d , value : %d\n", 9, sht_get(ht, 9));
    printf("Key : %d , value : %d\n", 27, sht_get(ht, 27));
    printf("Key : %d , value : %d\n", 1031, sht_get(ht, 1031));

    sht_destroy_hash_table(ht);
    return 0;
}