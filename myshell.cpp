#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;



// int main() {

//     char* args[2];

//     string pwd = "pwd";

//     args [0] = (char*)pwd.c_str();
//     args [1] = NULL;

//     if(execvp (args[0], args) == -1) {
//         perror("execvp()\n");
//     }

//     return 0;
// }

static void execute(char* command) {


    pid_t pid = fork();

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

int main() {


    while(1) {
        cout << "m% ";
        
        

        getline(cin, line);

        for(int i = 0; i < line.length(); i++) {

        }

        // ss >> command;  //parse command
        // args[0] = (char*)command.c_str();

        // if(getline(cin, flag)) {
        //     for(int i = 1; i <= flag.length(); i++) {
        //         args[i] = (char*)
        //     }
        // }else {
        //     args[1] = NULL;
        // }
        



        if(command == "exit" || command == "myexit") {
            exit(EXIT_SUCCESS);
        }

        // 
        // if(flag != "\0") {
        //     args[1] = (char*)flag.c_str();
        //     args[2] = NULL;
        // }else {
        //     args[1] = NULL;
        // }

         execute(command);

    }

    return 0;
}

