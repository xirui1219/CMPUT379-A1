CC = g++
C_FLAGS = -std=c++11 -Wall -g

main: main.cpp
	$(CC) $(C_FLAGS) -c main.cpp -o main.o
	$(CC) -o main main.o

sleep: sleeper.cpp
	$(CC) $(C_FLAGS) -c sleeper.cpp -o sleeper.o
	$(CC) -o sleeper sleeper.o
clean: 
	rm -f main main.o sleeper.o sleeper
