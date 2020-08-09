#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "letter.hpp"

class Parser {
    private:
        enum state {
            HEIGHT,
            RUNE,
            WIDTH,
            LETTER,
            END,
            STOP
        };

        int  cur_height;
        int  cur_width;
        char cur_rune;

        int cur_line;

        std::string cur_rune_name;
        std::ifstream font;

        Parser::state parse_height();
        Parser::state parse_rune();
        Parser::state parse_width();
        Parser::state parse_letter();

    public:
        std::map<std::string,Letter> letters;
        Parser();
        Parser(std::string fontfile);
        int run();
        int getHeight() { return cur_height; }
        std::map<std::string, Letter>& getLetters() { return letters; }


};
