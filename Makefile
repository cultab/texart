CC=g++
CFLAGS= --std=c++11 -Wall -Wpedantic

sources= texart.cpp letter.cpp parse.cpp
headers= letter.hpp parse.hpp

make:
	${CC} ${CFLAGS} ${sources} -o texart

run: make
	./texart

test: make
	./texart asdf
