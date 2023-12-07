//
// Created by justhaza21 on 07/12/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

const void *bye = "Bye bye...\n";

int Command(char *command){
    pid_t pid = fork();                                  //fork a new process
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(pid == 0){                                 //child process
        execlp(command, command, (char *)NULL);
        perror("execlp");                             //if execlp fails
        exit(EXIT_FAILURE);
    } else {                                            //parent process
        int status;
        wait(&status);            //wait for the child to finish
        return(status);
    }
    return 0;
}

void WelcomeMessage(){
    const void *message= "Welcome in ENSEA tiny Shell.\nType 'exit' to quit.\n";

    //Display of a welcome message
    write(STDOUT_FILENO, message, strlen(message));
}

void Prompt(int status){
    const void *prompt="enseash % ";
    //Display of a simple prompt
    write(STDOUT_FILENO, prompt, strlen(prompt));
    if(WIFEXITED(status)){
        write(STDOUT_FILENO,"exit", 4);
        char buf[10];
        sprintf(buf, "%d", WEXITSTATUS(status));
        write(STDOUT_FILENO, buf, 1);
    } else if(WIFSIGNALED(status)){
        write(STDOUT_FILENO,"sign", 4);
        char buf[10];
        sprintf(buf, "%d", WTERMSIG(status));
        write(STDOUT_FILENO, buf, 1);
    }

}

int main(){
    WelcomeMessage();
    Prompt(0);
    while(1){
        char userInput[1024];
        int byteread;

        //remove new line character from user input


        //read user input
        if((byteread = read(STDIN_FILENO,userInput, 1024))==0){
            //handle ctrl+d or end of file
            write(STDOUT_FILENO,bye, strlen(bye));
            exit(EXIT_SUCCESS);
        }
        userInput[byteread - 1] ='\0';
        //write(STDOUT_FILENO, userInput, strlen(userInput));

        if((strcmp(userInput, "exit") == 0)){              //check if the user wants to exit
            //handle ctrl+d or end of file
            write(STDOUT_FILENO,bye, strlen(bye));
            exit(EXIT_SUCCESS);
        }

        //execute the entered command
        int status = Command(userInput);

        Prompt(status);
    }
}
