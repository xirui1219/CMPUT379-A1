CC = g++
CFLAGS = -Wall -std=c++11
SOURCES_MAIN = main.cpp commands.cpp
SOURCES_SLEEPER = sleeper.cpp
EXECUTABLE_MAIN = my_program
EXECUTABLE_SLEEPER = sleeper_program

all: $(EXECUTABLE_MAIN) $(EXECUTABLE_SLEEPER)

$(EXECUTABLE_MAIN): $(SOURCES_MAIN)
	$(CC) $(CFLAGS) $^ -o $@

$(EXECUTABLE_SLEEPER): $(SOURCES_SLEEPER)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(EXECUTABLE_MAIN) $(EXECUTABLE_SLEEPER)
