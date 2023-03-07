// CS475W lab03_Process
// This lab is to create a child process which executes the command given by the user.
// Student name: Minh Nguyen
// Date: 03/06/2023

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */

void printArray(char *pointerToArray);

int main(void)
{

    char *args[MAX_LINE / 2 + 1];   /* command line arguments */
    char *cmd;
    int should_run = 1;             /* flag to determine when to exit program */
    char exit_str[] = "exit";
    char ampersand[] = "&";

    while (should_run)
    {
        int has_ampersand = 0;
        printf("CS475W>");
        char str[MAX_LINE/2 + 1];
        char delim[] = " ";
        scanf(" %[^\n]s", str);    
        // scanf reads the command the user enters
        char *ptr; 
        //parse the string with strtok, specifying the delimiter 
        cmd = strtok(str, delim);
        args[0] = cmd;
        ptr = strtok(NULL, delim);
        // insert each part of the command into the array of strings
        int i = 1;
        while(ptr != NULL){
            args[i++] = ptr;
            ptr = strtok(NULL, delim);
        }

        if(strcmp(str, exit_str) == 0){
            should_run = 0;
        }

        fflush(stdout);
        // if the command contains &, change it to NULL in the array and set ampersand flag to 1
        if(strcmp(args[i-1], ampersand) == 0){
            args[i-1] = NULL;
            has_ampersand = 1;
        }
        
        //* After reading user input, the steps are:
        //* (1) fork a child process using fork
         //call fork() from parent process

        int pid;
        pid = fork(); // fork a child to handle the command
        if(pid == 0){
            execvp(cmd, args);   

        } else if (pid == -1){
            printf("Issues with fork");

        } else {
            if(has_ampersand == 1){ // if ampersand flag is set, then the parent will wait for the child to finish
                int returnStatus;    
                waitpid(pid, &returnStatus, 0);  // Parent process waits here for child to terminate.

                if (returnStatus == 0)  // Verify child process terminated without error.  
                {
                    printf("The child process terminated normally\n");    
                    printf("Ampersand detected\n");

                }

                if (returnStatus == 1)      
                {
                    printf("The child process terminated with an error!.");    
                }
            }
        }   
    }
    
    return 0;
}
