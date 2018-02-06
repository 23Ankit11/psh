#ifndef CD_IMPL
#define CD_IMPL

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
#include "splitter.h"
#include "history.h"
#include "helpers.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
	
int main()
{
	
	char input[max_size];
	char **input_parsed;
	int no_of_args;
	int flag_issue =0;

	
 
	while(1)
	{
	
		//initallise the terminal for new command
		char cwd[1024];
		getcwd(cwd,sizeof(cwd));

		// taking input saving it in history
		//parsing the input to get program_name and arguments
		if(flag_issue==0)		
		{	
			printf("%s%s$>%s ",ANSI_COLOR_YELLOW, cwd, ANSI_COLOR_RESET);
			gets(input);
			update_history(input);

		}

		strcat(input, " ");
		// printf("%s ", input);
		if(is_empty(input))
			continue;
		input_parsed = str_split(input, ' ', &no_of_args);
	
		// int i=0;
		// for(i=0;i<no_of_args;i++){printf("%s\n",input_parsed[i] );}

		// exit()
		if(!strcmp(input_parsed[0], "exit"))
			break;
		
		//cd dir_name
		else if(!strcmp(input_parsed[0], "cd")){
			if(no_of_args==1){
				cd("");
			}else
				cd(input_parsed[1]);
		}

		//ls
		else if(!strcmp(input_parsed[0], "ls"))
		{
			if(no_of_args==1)
				ls(cwd);
			else if (input_parsed[1][0] == '-')
			{
				int pid= fork();
        		int status;
        		if(pid==0)
        			execvp("/bin/ls",&input_parsed[0]);
        		else
        		{
        			wait(&status);
        			if(status==-1) printf("Error executing rmexcept\n");
        		}
			}
			else
				ls(input_parsed[1]);
		}

		else if(!strcmp(input_parsed[0], "help")){
			help();
		}

		// history n 
		else if(!strcmp(input_parsed[0], "history"))
		{
			if(no_of_args==1)
				history(-1);			
			else 
				history(numericString(input_parsed[1]));
		}

		// issue n
		else if(!strcmp(input_parsed[0], "issue"))
		{
			if(no_of_args==1)
				printf("%s\n","Second argument not passed");			
			else {
				flag_issue = 1;
				// printf("asd%sasd\n",input );
				strcpy(input ,issue(numericString(input_parsed[1])));
				// printf("asd%sasd\n",input );

			}
			
			continue;
		}

		// rm -rf filename
		else if(!strcmp(input_parsed[0], "rm"))
		{
			int status;
			int pid = fork();
			if(pid == 0)
					execvp("rm",&input_parsed[0]);
			else
			{
				wait(&status);
				if(status == -1)
					printf("\nError occured while executing %s\n", input_parsed[0]);				
			}
		}

		//rmexcept 	
		else if(!strcmp(input_parsed[0], "rmexcept"))
		{

			DIR *mydir;
		    struct dirent *myfile;
		    struct stat mystat;
		    char buf[512];
		    mydir = opendir(cwd);
			int i=1;
			char* c = ".tmp";
	    	struct stat st = {0};
		    if (stat(c, &st) == -1) 
    			mkdir(c, 0700);
	    	

	    	for(i=1;i<no_of_args;i++)
        	{
        		int pid= fork();
        		int status;
        		char *temp[6]= {"/bin/cp","--parents","-r", input_parsed[i], ".tmp", NULL};
        		if(pid==0)
        			execvp("/bin/cp",temp);
        		else
        		{
        			wait(&status);
        			if(status==-1) printf("Error executing rmexcept\n");
        		}
        	}
		
		    while((myfile = readdir(mydir)) != NULL)
		    {
		        if(myfile->d_name[0]=='.') continue;
		        int flag=0;
				for(i=1;i<no_of_args;i++)
				{

		        if(!strcmp(myfile->d_name,".tmp"))
		        	{
		        		flag = 1;break;
		        	}
		        }
		        
		        if(flag==0)
		        	{
		        		printf("Deleting  %s ...\n",myfile->d_name);
		        		char *temp[4]= {"/bin/rm","-rf",myfile->d_name,NULL};
		        		int pid= fork();
		        		int status;
		        		if(pid==0)
		        			execvp("/bin/rm",temp);
		        		else
		        		{
		        			wait(&status);
		        			if(status==-1) printf("Error executing rmexcept\n");
		        		}
		        	}
		    	
		    }
		    
		    closedir(mydir);
		    mydir = opendir(".tmp");
			cd(".tmp");

			while((myfile = readdir(mydir)) != NULL)
		    {
		        if(myfile->d_name[0]=='.') continue;
		        char *temp[6]= {"/bin/cp","--parents","-r", myfile->d_name, "./../", NULL};
        		int pid= fork();
		        int status;
        		if(pid==0)
        			execvp("/bin/cp",temp);
        		else
        		{
        			wait(&status);
        			if(status==-1) printf("Error executing rmexcept\n");
        		}
		    }
		    closedir(mydir);
			cd("./../");
	    	char *temp[4]= {"/bin/rm","-rf",".tmp",NULL};
    		int pid= fork();
    		int status;
    		if(pid==0)
    			execvp("/bin/rm",temp);
    		else
    		{
    			wait(&status);
    			if(status==-1) printf("Error executing rmexcept\n");
    		}
		        	
		}
		
		//<programname>	n or <programname>	argument
		else {
				int status;
				
				// check run time spectified or not 
				if(no_of_args>1 && isNumericString(input_parsed[1]))
					{	signal(SIGALRM,signal_handler);
						alarm(numericString(input_parsed[1]));
						 
					}
					

				//check redirection specified or not
				int i=1;
				int fin=-1;
				int fout=-1;
				int dfin = dup(STDIN_FILENO), dout =dup(STDOUT_FILENO);

				for(i=1;i<no_of_args;i++){
					if(!strcmp(input_parsed[i],"<"))
						{fin = open(input_parsed[i+1], O_RDONLY);i++;}
					if(!strcmp(input_parsed[i],">"))
						{fout = creat(input_parsed[i+1], 0644);i++;}


				}

				if(fin!=-1){
					dup2(fin, STDIN_FILENO);
        			close(fin);
        		}

        		if (fout!=-1)
				{
					dup2(fout, STDOUT_FILENO);
					close(fout);
				}


				int pid = fork();
				child_id = pid;
				if(pid == 0)
				{
						execvp(input_parsed[0],&input_parsed[0]);

				}
				else
				{
					wait(&status);
					if(status == -1)
						printf("\nError occured while executing %s\n", input_parsed[0]);				
					
					dup2(dfin, STDIN_FILENO );
					close(dfin);
					dup2(dout, STDOUT_FILENO);
					close(dout);

				}
			}
	
		flag_issue =0;
	}
   	
	return 0;
}

#endif
