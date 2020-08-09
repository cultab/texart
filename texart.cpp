#include "letter.hpp"
#include "parse.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    std::string input;
    std::string fontfile;
    Parser prsr;

    bool skip = false;
    
    // copy input and check for fontfile flag
    for ( int i = 1; i < argc; i++ ) {
        if ( std::strcmp(argv[i], "-f") == 0 ) {
            //cout << "Fontfile flag?" << argv[i] << endl;
            fontfile = argv[i + 1];
            skip = true;
        } else {
            if (!skip) {
            input.append(argv[i]);
            input.append(" ");
            }
            skip = false;
        }
    }

    // init parser
    if ( fontfile.empty() ) {
        prsr = Parser();
    } else {
        prsr = Parser(fontfile);
    }

    if ( prsr.run() != 0 ) {
        std::exit(1);
    }

    // get letter map out of parser
    auto letter_map = prsr.getLetters();

    // find separator letter
    Letter separator_let = letter_map.find("separator")->second;

    std::vector<Letter> letter_vec;

    // fill letter vector with appropriate letters
    for ( char ch : input ) {
        auto let_iter = letter_map.end();

        switch ( ch ) {
        case ' ':
            let_iter = letter_map.find("space");
            break;
        default:
            let_iter = letter_map.find(std::string(1, std::tolower(ch)));
            break;
        }
        if ( let_iter == letter_map.end() ) {
            cerr << "Letter for character '" << ch << "' not found!" << endl;
        } else {
            letter_vec.push_back(let_iter->second);
        }
    }

    int height = prsr.getHeight();

    // print
    for ( int line = 0; line < height; line++ ) {
        for ( auto letter : letter_vec ) {
            cout << letter[line];
            cout << separator_let[line];
        }
        cout << endl;
    }

    return 0;
}
