#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;


static void execute(char* args[]) {
    pid_t pid = fork();

    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "myexit") == 0) {
        exit(EXIT_SUCCESS);
    }

    if(pid == 0) {
        if(execvp(args[0], args) == -1) {
            perror("execvp()\n");
            exit(EXIT_FAILURE);
        }
    }else if (pid < 0){
        perror("fork()\n");
    }

    wait(NULL);
}

int count_args(const string& str) {
    if(str.empty()) {
        return 0;
    }

    stringstream ss(str);
    string command;
    int arg_counter = 0;

    while(ss >> command) {
        arg_counter++;
    }

    return arg_counter;
}

int main() {


    while(1) {
        cout << "m% ";
        string line;
        string command;
        char* args[256];
        
        getline(cin, line);
        int arg_counter = count_args(line);
        stringstream ss(line);
        

        int i;
        for(i = 0; i < arg_counter; i++) {
            ss >> command;
            args[i] = (char*)command.c_str();
        }

        args[i+1] = NULL;
        execute(args);

    }

    return 0;
}

