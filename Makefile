# -*- MakeFile -*-

CC = g++
CC_TAGS = -g -Wall

all:
	$(CC) $(CC_TAGS) src/*.cpp -I. -Iinclude -lSDL2main -lSDL2 -o build/SignalSim
	./build/SignalSim