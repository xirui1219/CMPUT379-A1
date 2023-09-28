#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
//#include "wait.h"
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    char *envp[] = {NULL};
    while (true)
    {
        string instruct;
        cin >> instruct;
        if (fork() == 0)
        { // fork so that it will loop
            if (instruct == "jobs")
            {
                char *argv1[] = {"ps", "-e", NULL}; // Running processes
                char *argv2[] = {"ps", "-A", NULL}; // Completed processes

                cout << "Running Processes\n";
                // int pipe_fd[2];
                // if (pipe(pipe_fd) == -1)
                // {
                //     perror("pipe");
                //     return 1;
                // }
                if (fork() == 0)
                {
                    // Child process for the first command
                    if (execve("/bin/ps", argv1, envp) == -1)
                    {
                        perror("execve");
                    }
                }
                else
                {
                    // Parent process
                    wait(nullptr); // Wait for the child process to finish
                    std::cout << "Completed Processes\n";
                    if (execve("/bin/ps", argv2, envp) == -1)
                    {
                        perror("execve");
                    }
                }
            }
            else if (instruct.find("kill") == 0)
            {
                int pid;
                cin >> pid;
                string pidStr = to_string(pid);
                char *argv1[] = {"kill", const_cast<char *>(pidStr.c_str()), NULL};

                if (execve("/bin/kill", argv1, envp) == -1)
                {
                    perror("execve");
                }
            }
            else if (instruct == "exit")
            {
                fflush(NULL);
                _exit(0);
            }
            else if (instruct == "sleep")
            {
                int sec;
                cin >> sec;
                sleep(sec);
            }
            else if (instruct == "resume")
            {
                int pid;
                cin >> pid;
                string pidStr = to_string(pid);
                char *argv1[] = {"kill", "-CONT", const_cast<char *>(pidStr.c_str()), NULL};

                if (execve("/bin/kill", argv1, envp) == -1)
                {
                    perror("execve");
                }
            }
            else if (instruct == "suspend")
            {
                int pid;
                cin >> pid;
                string pidStr = to_string(pid);
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
            }
            else if (instruct == "wait")
            {
                int pid;
                cin >> pid;
                int status;
                waitpid(pid, &status, 0);
            }
            else
            {
                // command input
                string cmd;
                cin>>cmd;

                if (cmd.find('&')==string::npos && cmd.find('<')==string::npos && cmd.find('>')==string::npos){
                    //split cmd by spaces
                }
            }
        }
        else
        {
            wait(nullptr);
        }
    }

    // jobs
    // kill <pid>
    // resume <pid>
    //  kill -CONT <pid>
    // sleep <int>
    // sleep
    // suspend <pid>
    //  kill -STOP
    // wait <pid>
    // pid_t wait? or some combination with suspend
    // else <cmd> <arg>* (numerous values of arg)
    // string parse of arg between <>
    //& - last argument, command needs to be executed in the background

    // pid_t wait(int *status)
    // waits until one of the children terminates
    // int open(const char *path, int oflags, mode_t mode);
    //  opens a file
    // int close(int fildes)
    // closes a file
    return 0;
}
