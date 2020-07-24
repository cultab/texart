CC=g++
CFLAGS= --std=c++11 -Wall -Wpedantic

sources= texart.cpp letter.cpp
headers= letter.hpp

make:
	${CC} ${CFLAGS} ${sources} -o texart

run: make
	./texart
