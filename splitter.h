#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdarg.h>
#include <fcntl.h>

#define max_size 1000

char s[max_size];

char** str_split(char* a_str, const char a_delim, int* no_of_args);

