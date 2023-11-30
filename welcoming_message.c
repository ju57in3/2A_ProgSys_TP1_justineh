//
// Created by justhaza21 on 30/11/23.
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void WelcomeMessage(){
    const void *message= "Welcome in ENSEA tiny Shell.\nType 'exit' to quit.\n";

    //Display of a welcome message
    ssize_t bytwrite = write(STDOUT_FILENO, message, strlen(message));
}

void Prompt(){
    const void *prompt="enseash %";

    //Display of a simple prompt
    ssize_t bytwrite = write(STDOUT_FILENO, prompt, strlen(prompt));
}

int main(){
    WelcomeMessage();
    Prompt();
}