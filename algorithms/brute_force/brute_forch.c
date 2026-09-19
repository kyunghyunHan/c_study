#include "brute_force.h"

int brute_force(char *text, int text_size, int start, char *pattern, int pattern_size)
{
    int i = 0;
    int j = 0;

    for (i = start; i <= text_size - pattern_size; i++)
    {
        for (j = 0; j < pattern_size; j++)
        {
            if (text[i + j] != pattern[j])
                break;
        }

        if (j >= pattern_size)
        {
            return i;
        }
    }
    return -1;
}