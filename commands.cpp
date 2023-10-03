#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

void inputFile(char* args[], int arrySize);

void jobs(){
                   // char *argv1[] = {"ps", "-u", NULL}; // Running processes
                // char *argv2[] = {"ps", "-A", NULL}; // Completed processes

                printf("Running Processes\n");
                // int pipe_fd[2];
                // if (pipe(pipe_fd) == -1)
                // {
                //     perror("pipe");
                //     return 1;
                // }
                // if (fork() == 0)
                // {
                //     // Child process for the first command
                //     if (execve("/bin/ps", argv1, envp) == -1)
                //     {
                //         perror("execve");
                //     }
                // }
                // else
                // {
                //     // Parent process
                //     wait(nullptr); // Wait for the child process to finish
                //     std::cout << "Completed Processes\n";
                //     if (execve("/bin/ps", argv2, envp) == -1)
                //     {
                //         perror("execve");
                //     }
                // }
            FILE* pipe = popen("ps -u | grep -v 'T' | grep -v 'Z'", "r");
            if (!pipe) {
                perror("popen");
            }

            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                // Process and print each line of the output
                std::cout << buffer;
            }

            int status = pclose(pipe);
            if (status == -1) {
                perror("pclose");
            } else {
                std::cout << "Command exited with status " << status << std::endl;
            }
    
};
void kill(){
    int pid;
    cin >> pid;
    char *envp[] = {NULL};
    string pidStr = to_string(pid);
    char *argv1[] = {"kill", const_cast<char *>(pidStr.c_str()), NULL};

    if (execve("/bin/kill", argv1, envp) == -1)
    {
        perror("execve");
    }
};
void sleep(){
    int sec;
    cin >> sec;
    sleep(sec);
};
void exit(){
    fflush(NULL);
    _exit(0);
};
void resume(){
    int pid;
    cin >> pid;
    string pidStr = to_string(pid);
    char *envp[] = {NULL};
    char *argv1[] = {"kill", "-CONT", const_cast<char *>(pidStr.c_str()), NULL};

    if (execve("/bin/kill", argv1, envp) == -1)
    {
        perror("execve");
    }
};
void suspend(){
    int pid;
    cin >> pid;
    string pidStr = to_string(pid);
    char *envp[] = {NULL};
    char *argv1[] = {"kill", "-STOP", const_cast<char *>(pidStr.c_str()), NULL};

    if (fork() == 0)
    {
        if (execve("/bin/kill", argv1, envp) == -1)
        {
            perror("execve");
        }
    }
    else
    {
        wait(nullptr);
    }
};
void wait(){
    int pid;
    cin >> pid;
    int status;
    waitpid(pid, &status, 0);
            
};

void parseInput(string instruct){
    const int maxCommandLength = 1024;
    char command[instruct.length()];
    strcpy(command, instruct.c_str());

    // Tokenize the input into command and arguments
    char* args[maxCommandLength];
    char *inputToken = strchr(command, '<');
    char* token = strtok(command, " ");
    int argCount = 0;

    while (token != nullptr && argCount < maxCommandLength) {
        args[argCount] = token;
        token = strtok(nullptr, " ");
        argCount++;
    }

    args[argCount] = nullptr;

    if (inputToken != nullptr){
        
        inputFile(args, argCount);
    }
    // Execute the command
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
    }

    if (child_pid == 0) { // Child process
        execvp(args[0], args);

        // execvp will only return if there is an error
        perror("execvp");
    } else { // Parent process
        // Wait for the child process to complete
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "Child process exited with status " << WEXITSTATUS(status) << std::endl;
        }
    }
};
void background(){

};
void inputFile(char* args[], int arrySize){
    const char * filename = args[1]+1;
    int fd = open(filename, O_RDONLY);
    char buffer[1024]; // Buffer to read lines
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        // Process and print each line
        for (ssize_t i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0'; // Replace newline with null terminator
                std::cout << buffer << std::endl;
                // Reset the buffer for the next line
                buffer[0] = '\0';
            }
        }
    }
};
void outputFile(){

};