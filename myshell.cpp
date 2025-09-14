#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

//function to fork process and run command
static void execute(char* args[]) {

    if(!args || !args[0]) { //check if cmd was entered
        return;
    }

    //check if user exits
    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "myexit") == 0) {
        exit(EXIT_SUCCESS);
    }

    //fork process
    pid_t pid = fork();
    if(pid == -1) {
        perror("fork()\n");
        return;
    }

    //create child process to execute command
    if(pid == 0) {
        if(execvp(args[0], args) == -1) {   //execution
            perror("execvp()\n");
            exit(EXIT_FAILURE);
        }
    }else {     //wait for process to finish before returning
        int status = 0;
        if(waitpid(pid, &status, 0) == -1) {
            perror("waitpid()");
        }
    }
}

//function to count the number of arguments user entered 
//including multiple flags
//returns count
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

        if(!getline(cin, line)) {   //get whole command
            cout << endl;
            break;
        }

        if(line.empty()) {
            continue;
        }

        int arg_counter = count_args(line);

        if(arg_counter == 0) {
            continue;
        }
    
        stringstream ss(line);
        string command;
        char* args[256];

        //parse command line into args[] 
        //includes flags
        int i = 0;
        for(; i < arg_counter; i++) {
            ss >> command;
            args[i] = strdup(command.c_str());
        }
        args[i] = NULL;   //add null terminator to command

        execute(args);  //call to run command

        //free allocated memory
        for(int j = 0; j < arg_counter; j++) {
            free(args[j]);
        }

    }

    return 0;
}

