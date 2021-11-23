TARGET:=texart

CC := clang++
CXXFLAGS='-D_GLIBCXX_USE_CXX11_ABI=0'
CFLAGS = --std=c++11 -Wall -Wpedantic

PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man
RESOURCES = $(PREFIX)/share

SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

letter.o: letter.hpp
parse.o: parse.hpp letter.hpp
texart.o: parse.hpp letter.hpp

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

debug: CFLAGS += -g -DDEBUG -Og
debug: $(TARGET)

$(TARGET): CFLAGS += -O3
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

install: $(TARGET)
	mkdir -vp        $(PREFIX)/bin/
	cp -vf $(TARGET) $(PREFIX)/bin/
	chmod 755        $(PREFIX)/bin/$(TARGET)
	mkdir -vp   $(RESOURCES)/$(TARGET)
	cp -v *.txr $(RESOURCES)/$(TARGET)
	chmod 644   $(RESOURCES)/$(TARGET)/*.txr
	#mkdir -p $(MANPREFIX)/man1
	#chmod 644 $(MANPREFIX)/man1/st.1

uninstall:
	rm -vf $(PREFIX)/bin/$(TARGET)
	rm -vf $(RESOURCES)/$(TARGET)/*.txr
	#rm -vf $(MANPREFIX)/man1/texart.1

test: $(TARGET)
	./$(TARGET) asdf

run: $(TARGET)
	./texart

.PHONY: all debug clean install uninstall test run
