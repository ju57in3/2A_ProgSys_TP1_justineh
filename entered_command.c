//
// Created by justhaza21 on 30/11/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <sys/types.h>

const void *bye = "Goodbye!\n";

void Command(char *command){
    pid_t pid = fork();                                  //fork a new process
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(pid == 0){                                 //child process
        execlp(command, command, (char *)NULL);
        perror("execlp");                             //if execlp fails
        exit(EXIT_FAILURE);
    } else {                                             //parent process
        waitpid(pid, NULL, 0);            //wait for the child to finish
    }
}

void WelcomeMessage(){
    const void *message= "Welcome in ENSEA tiny Shell.\nType 'exit' to quit.\n";

    //Display of a welcome message
    write(STDOUT_FILENO, message, strlen(message));
}

void Prompt(){
    const void *prompt="enseash % ";

    //Display of a simple prompt
    write(STDOUT_FILENO, prompt, strlen(prompt));
}

int main(){
    WelcomeMessage();
    while(1){
        Prompt();
        char userInput[1024];
        fgets(userInput,1024,stdin);

        //remove new line character from user input
        userInput[strcspn(userInput,"\n")]='\0';

        //check if the user wants to exit
        if(strcmp(userInput,"exit")==0){
            write(STDOUT_FILENO,bye,strlen(bye));
        }

        //execute the entered command
        Command(userInput);
    }
}
