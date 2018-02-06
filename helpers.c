#include "helpers.h"

void signal_handler(int sig){
	kill(child_id,SIGKILL);
}

void signal_handler_int(int sig){
	kill(child_id,SIGKILL);
}

int isNumericString(char *tmp){
	int isDigit = 1;
	int j=0;
	while(j<strlen(tmp) && isDigit == 1){
	  isDigit = (tmp[j] >= '0'  && tmp[j] <= '9');
	  j++;
	}

	return isDigit;
}

int numericString(char *tmp){
	int isDigit = 1;
	int j=0;
	int ans = 0;
	while(j<strlen(tmp) && isDigit == 1){
	  ans = ans * 10 + (tmp[j] - '0');
	  j++;
	}

	return ans;
}

void cd(char* s)
{	
	int status;
	if(!strcmp(s,"")){
		printf("%s\n",getenv("HOME") );
		status = chdir(getenv("HOME"));
	}
	else status = chdir(s);
	if(status == -1)
		printf("Error occured, ensure that directory name is correct. \n");
}

void ls(char *s)
{
	DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char buf[512];
    mydir = opendir(s);
    while((myfile = readdir(mydir)) != NULL)
    {
        if(myfile->d_name[0]=='.') continue;
        printf(" %s  ", myfile->d_name);
    }
    printf("\n");
    closedir(mydir);
}

int is_empty(const char *s) {
  while (*s != '\0') {
    if (!isspace((unsigned char)*s))
      return 0;
    s++;
  }
  return 1;
}

void help(){
	printf("ls           	\tlist all directory in the folder\n");
	printf("cd           	\tchange directory\n");
	printf("rm           	\tremove folder or files\n");
	printf("rmexcept     	\tremove all folder or files except specified.\n");
	printf("<program_name> m\tto run a program for max m seconds\n");
	printf("exit            \tto exit the terminal\n");
	printf("help            \tto print the help menu\n");
	printf("history n       \tto print the last n commands\n");
	printf("issue n         \tto rerun the last nth command\n");
}
