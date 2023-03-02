#include <stdio.h>
#include <string.h>

int main(){
    char exitCmd[10];
    char exitStr[] = "exit";
    while(strcmp(exitStr, exitCmd) != 0){
        scanf("%[^\n]s", exitCmd);
        printf("%s", exitCmd);
    }
    
    return 0;
}