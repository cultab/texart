#include <cctype>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "letter.hpp"
#include "parse.hpp"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char** argv)
{
    std::string input;

    for (int i=1; i<argc; i++) {
        input.append(argv[i]);
        input.append(" ");
    }

    Parser prsr = Parser();

    if ( prsr.run() != 0 ) {
        std::exit(1);
    }

    auto letter_map =  prsr.getLetters();

    Letter separator_let = letter_map.find("separator")->second;

    std::vector<Letter> letter_vec;

    for (char ch : input) {
        auto let_iter = letter_map.end();

        switch( ch ) {
            case ' ':
                let_iter = letter_map.find("space");
                break;
            default:
                let_iter = letter_map.find(std::string(1,std::tolower(ch)));
                break;
        }
        if ( let_iter == letter_map.end() ) {
            cerr << "Letter for character '" << ch << "' not found!" << endl;
        } else {
            letter_vec.push_back(let_iter->second);
        }
    }

    int height = prsr.getHeight();

    for ( int line=0; line<height; line++ ) {
        for (auto letter : letter_vec) {
            cout << letter[line];
            cout << separator_let[line];
        }
        cout << endl;
    }



    return 0;
}
