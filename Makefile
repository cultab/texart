PREFIX=/usr/local
MANPREFIX=$(PREFIX)/share/man
RESOURCES=$(PREFIX)/share

CC=g++
CFLAGS= --std=c++11 -Wall -Wpedantic

sources= texart.cpp letter.cpp parse.cpp
headers= letter.hpp parse.hpp

compile:
	${CC} ${CFLAGS} ${sources} -o texart

install: compile
	mkdir -p $(PREFIX)/bin
	cp -f texart $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/texart
	#mkdir -p $(MANPREFIX)/man1
	#chmod 644 $(MANPREFIX)/man1/st.1
	mkdir -p $(RESOURCES)/texart
	cp *.txr $(RESOURCES)/texart
	chmod 644 $(RESOURCES)/texart/*.txr

uninstall:
	rm -r $(PREFIX)/bin/texart
	#rm -r $(MANPREFIX)/man1/texart.1

test: make
	./texart asdf

run: make
	./texart
