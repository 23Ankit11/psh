#include "splitter.h"

char** str_split(char* a_str, const char a_delim, int* no_of_args)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    int total_count = 0;
    while(*tmp == ' ') tmp++;
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            total_count++;
            last_comma = tmp;
            while(*tmp && a_delim == *tmp)
                tmp++, last_comma = tmp, total_count++;
        }
        else
            tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
     *no_of_args = count;
    count++;

   

    result = malloc(sizeof(char*) * (count+1));

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    *(result + *no_of_args) = NULL;
    return result;
}
