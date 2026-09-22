#include "simple_hash_table.h"

int main(void)
{
    HashTable *ht = sht_create_hash_table(193);

    sht_Set(ht, 418, 32114);
    sht_Set(ht, 9, 514);
    sht_Set(ht, 27, 8917);
    sht_Set(ht, 1031, 286);

    printf("Key : %d , value : %d\n", 418, sht_Get(ht, 418));
    printf("Key : %d , value : %d\n", 9, sht_Get(ht, 9));
    printf("Key : %d , value : %d\n", 27, sht_Get(ht, 27));
    printf("Key : %d , value : %d\n", 1031, sht_Get(ht, 1031));

    sht_destroy_hash_table(ht);
    return 0;
}