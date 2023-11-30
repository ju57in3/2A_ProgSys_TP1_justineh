//
// Created by justhaza21 on 30/11/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void Command(char *command){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        execlp(command, command, (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);
    }
}

void WelcomeMessage(){
    const void *message= "Welcome in ENSEA tiny Shell.\nType 'exit' to quit.\n";

    //Display of a welcome message
    ssize_t bytesWrite = write(STDOUT_FILENO, message, strlen(message));
}

void Prompt(){
    const void *prompt="enseash %";

    //Display of a simple prompt
    ssize_t bytesWrite = write(STDOUT_FILENO, prompt, strlen(prompt));
}

int main2(){
    WelcomeMessage();
    while(1){
        Prompt();
        ssize_t bytesRead = read(STDIN_FILENO,);
        Command();
    }
}