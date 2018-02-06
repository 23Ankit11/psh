#include "history.h"

void update_history(char *s){

	
	char envhome[1000];
	strcpy(envhome, getenv("HOME"));
	FILE * fp;
	fp = fopen(strcat(envhome, "/history.txt"),"a+");
		if(fp!=NULL){
			fseek(fp,0,SEEK_SET);
			fprintf(fp, "%s\n", s);
		}
		else
			printf("%s\n","Something went wrong... Unable to access $HOME directory");

	fclose (fp);
}


void history(int line_num)
{
	line_num += 1;
	char envhome[1000];
	strcpy(envhome, getenv("HOME"));
	FILE * fp;
	fp = fopen(strcat(envhome, "/history.txt"),"r");

	int count=0;
	char c;
	for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') 
            count = count + 1;
	// printf("%d\n%d\n", count , line_num);
	
	if(line_num == 0 || line_num > count) line_num = count;
    
    int i = 0;
    fseek(fp,0,SEEK_SET);
    
    for (c = getc(fp); c != EOF; c = getc(fp))
        {
        
        if(i >= count - line_num + 1 )
        	printf("%c",c);
        if (c == '\n') 
            i++;
    }


	fclose (fp);
}

char *issue(int line_num)
{
	line_num += 1;
 	char envhome[1000];
	strcpy(envhome, getenv("HOME"));
	FILE * fp;
	fp = fopen(strcat(envhome, "/history.txt"),"r");
	
	char *line = malloc(sizeof(char)*1024);
	
	int count=0, j=0;
	char c;
	

	for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') 
            count = count + 1;
	

	
	
	if(line_num == 0 || line_num > count) line_num = count;
    
    int i = 0;
    fseek(fp,0,SEEK_SET);
    
    for (c = getc(fp); c != EOF; c = getc(fp))
     {  
     	 if( c!='\n'  && i == count - line_num + 1 )
    	{
    		line[j]=c; j++;
    	}

     	if (c == '\n') 
            i++;
        
       

        if(i == count - line_num + 2 )
        	break;
    }

	fclose (fp);
	// printf("%s", line);
	return line;
}

