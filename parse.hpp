#pragma once

#include "letter.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

class Parser
{
  private:
    enum state { HEIGHT, RUNE, WIDTH, LETTER, END, STOP };

    int cur_height;
    int cur_width;

    int cur_line;

    std::string cur_rune_name;
    std::string fontfile;
    std::ifstream font;
    std::map<std::string, Letter> letters;

    Parser::state parse_height();
    Parser::state parse_rune();
    Parser::state parse_width();
    Parser::state parse_letter();

  public:
    Parser();
    Parser(std::string fontfile);
    void open_font();
    int run();
    int getHeight() { return cur_height; }
    std::map<std::string, Letter> &getLetters() { return letters; }
};
