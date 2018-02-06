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

int child_id;

void signal_handler(int sig);

void signal_handler_int(int sig);

int isNumericString(char *tmp);

int numericString(char *tmp);

void cd(char* s);

void ls(char *s);

int is_empty(const char *s);

void helper();
