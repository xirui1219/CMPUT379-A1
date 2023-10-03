#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "commands.h"
using namespace std;

int main()
{
    char *envp[] = {NULL};
    while (true)
    {
        string instruct;
        cin >> instruct;
        if (fork()==0){

            if (instruct == "jobs")
            {
                jobs();
            }
            else if (instruct.find("kill") == 0)
            {
                kill();
            }
            else if (instruct == "exit")
            {
                exit();
            }
            else if (instruct == "sleep")
            {
                sleep();
            }
            else if (instruct == "resume")
            {
               resume();
            }
            else if (instruct == "suspend")
            {
                suspend();
            }
            else if (instruct == "wait")
            {
                wait();
            }
            else{
                // command input
               parseInput();
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
