PREFIX=/usr/local
MANPREFIX=$(PREFIX)/share/man
RESOURCES=$(PREFIX)/share

CC=g++
CFLAGS= --std=c++11 -Wall -Wpedantic

SRC= texart.cpp letter.cpp parse.cpp
OBJ= $(SRC:.cpp=.o)

all: texart

.cpp.o:
	$(CC) $(CFLAGS) $(SRC) -c $<

letter.o: letter.hpp
parse.o: parse.hpp
texart.o: letter.hpp parse.hpp

debug:
	make _debug -B
_debug: CFLAGS += -g -DDEBUG -Og
_debug: texart

texart: CFLAGS += -O3
texart: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o texart

clean:
	rm -f texart $(OBJ)

install: texart
	mkdir -p $(PREFIX)/bin
	cp -f texart $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/texart
	#mkdir -p $(MANPREFIX)/man1
	#chmod 644 $(MANPREFIX)/man1/st.1
	mkdir -p $(RESOURCES)/texart
	cp *.txr $(RESOURCES)/texart
	chmod 644 $(RESOURCES)/texart/*.txr

uninstall:
	rm $(PREFIX)/bin/texart
	#rm -r $(MANPREFIX)/man1/texart.1
	rm -f $(RESOURCES)/texart/*.txr

test: texart
	./texart asdf

run: texart
	./texart

.PHONY: all _debug debug clean install uninstall test run
