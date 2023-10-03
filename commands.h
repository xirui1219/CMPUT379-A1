#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>

using namespace std;

void jobs();
void kill();
void exit();
void sleep();
void resume();
void suspend();
void wait();
void parseInput(string instruct);
void inputFile(char* args[], int arrySize);
#endif
