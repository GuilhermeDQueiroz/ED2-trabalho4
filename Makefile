# Compiler
CC = g++

# Flags 
CC_FLAGS = -g -Iinclude -c

all: main

main: main.o review.o
		$(CC) -o bin/main.exe obj/main.o obj/Review.o

main.o: main.cpp include/Huffman.h
		$(CC) $(CC_FLAGS) main.cpp -o obj/main.o

review.o: src/Review.cpp include/Review.h
		$(CC) $(CC_FLAGS) src/Review.cpp -o obj/Review.o


execute: all
		./bin/main.exe