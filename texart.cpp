#include <iostream>
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

    prsr.run();

    auto letter_map =  prsr.getLetters();
    std::vector<Letter> letter_vec;

    for (char ch : input) {
        if (ch == ' ') {
            ch = '@'; // hack for getting spaces
        }
        auto let_iter = letter_map.find(ch);
        if (let_iter == letter_map.end()) {
            cerr << "Letter for character '" << ch << "' not found!" << endl;
        } else {
            letter_vec.push_back(let_iter->second);
        }
    }


    int height = prsr.getHeight();

    for(int line=0; line<height; line++) {
        for (auto letter : letter_vec) {
            cout << letter[line];
            cout << ' ';

        }
        cout << endl;
    }



    return 0;
}
