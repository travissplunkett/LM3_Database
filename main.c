// CS475W lab03_Process
// This lab is to create a child process which executes the command given by the user.
// Student name: 
// Date:

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE 80 /* The maximum length command */

void printArray(char *pointerToArray);

int main(void)
{

    char *args[MAX_LINE / 2 + 1];   /* command line arguments */
    char *cmd;
    int should_run = 1;             /* flag to determine when to exit program */
    char exit_str[] = "exit";

    /*
    int i = 0;
    while(ptr != NULL){
        args[i++] = ptr;

        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }*/
    
    

    
    while (should_run)
    {
        
        printf("CS475W>");
        char str[MAX_LINE/2 + 1];
        char delim[] = " ";
        scanf(" %[^\n]s", str);    

        char *ptr; 
        cmd = strtok(str, delim);
        ptr = strtok(NULL, delim);
        int i = 0;
        
        while(ptr != NULL){
            args[i++] = ptr;

            //printf("'%s'\n", ptr);
            ptr = strtok(NULL, delim);
        }
        printf("%s", cmd);

        if(strcmp(str, exit_str) == 0){
            should_run = 0;
        }

        fflush(stdin);

        
        //* After reading user input, the steps are:
        //* (1) fork a child process using fork
         //call fork() from parent process

        int pid;
        pid = fork();
        if(pid == 0){
            printf("Child process");
            execvp(cmd, args);            
            //_exit(0);
        } else if (pid == -1){
            printf("Issues with fork");
            //_exit(1);
        } else {
            printf("Parent process");
        }   


    

        //* (2) the child process will invoke execvp()
        //* (3) if command included &, parent will invoke wait()
        
    }
    
    return 0;
}
