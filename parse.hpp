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
            END
        };

        int  cur_height;
        int  cur_width;
        char cur_rune;
        std::ifstream font;

        Parser::state parse_height();
        Parser::state parse_rune();
        Parser::state parse_width();
        Parser::state parse_letter();

    public:
        std::map<char,Letter> letters;
        Parser();
        void run();


};
