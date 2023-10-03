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

void jobs(){
                   // char *argv1[] = {"ps", "-u", NULL}; // Running processes
                // char *argv2[] = {"ps", "-A", NULL}; // Completed processes

                // cout << "Running Processes\n";
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
    int pipe_fd[2];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
    }

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
    }

    if (child_pid == 0) { // Child process
        // Close the read end of the pipe (we only need to write to it)
        close(pipe_fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the write end of the pipe (now stdout is redirected)
        close(pipe_fd[1]);

        // Execute the ps -u command using execve
        char* const ps_args[] = { (char*)"ps", (char*)"-u", NULL };
        execve("/bin/ps", ps_args, NULL);

        // execve will only return if there is an error
        perror("execve");
    } else { // Parent process
        // Close the write end of the pipe (we only need to read from it)
        close(pipe_fd[1]);

        // Read and print the output of ps -u from the pipe
        char buffer[1024];
        ssize_t bytes_read;

        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            // Null-terminate the buffer to treat it as a C string
            buffer[bytes_read] = '\0';

            // Check if the line contains " R " to identify running processes
            char* running_indicator = strstr(buffer, " R ");
            if (running_indicator != nullptr) {
                // If found, print the line (which includes the elapsed time for running processes)
                std::cout << buffer;
            }
        }

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Wait for the child process to complete
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "Child process exited with status " << WEXITSTATUS(status) << std::endl;
        }
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
void parseInput(){
    string cmd;
    cin>>cmd;
    stringstream ss(cmd);
    string s;
    vector<string> cmd_vec;

    while (getline(ss,s, ' ')){
        cmd_vec.push_back(s);
    }
    if (cmd.find('&')==string::npos && cmd.find('<')==string::npos && cmd.find('>')==string::npos){
        //split cmd by spaces
    }
};
void background(){

};
void inputFile(){

};
void outputFile(){

};