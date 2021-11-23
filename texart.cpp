#include "letter.hpp"
#include "parse.hpp"

#include <any>
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

// helper function to hash strings  TODO: check for collisions
constexpr unsigned int hash(const char *s, int off = 0) { return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off]; }

int main(int argc, char **argv)
{
    std::string input;
    std::string fontfile;

    bool next_is_arg = false;

    for (int i = 1; i < argc; i++) {
        if (!next_is_arg) {
            switch (hash(argv[i])) {
            case hash("-f"):
            case hash("--font"):
                if (i + i <= argc) {
#ifdef DEBUG
                    cerr << "reading font from: " << fontfile << endl;
#endif
                    next_is_arg = true;
                    fontfile = argv[i + 1];
                    break;
                } else {
                    cerr << argv[0] << ": -f and --font need to be followed by a FONTFILE." << endl << endl;
                } // fallthrough  TODO: this is a hack, use a helpstring
            case hash("-h"):
            case hash("--help"):
                cerr << argv[0] << " [flags] input_text" << endl
                     << "[flags]: " << endl
                     << "-h, --help          Print this message and exit." << endl
                     << "-f FONTFILE, --font FONTFILE" << endl
                     << "                    Use FONTFILE as the fontfile." << endl
                     << "-v                  Ignored." << endl;
                exit(0);
            case hash("-v"):
                break;
            default:
#ifdef DEBUG
                cerr << "reading input " << argv[i] << endl;
#endif
                input.append(argv[i]);
                if (i != argc) {
                    input.append(" ");
                }
                break;
            }
        } else {
            next_is_arg = false;
#ifdef DEBUG
            cerr << "skipping " << argv[i] << endl;
#endif
        }
    }

    // init parser
    Parser prsr;

    if (!fontfile.empty()) {
        prsr = Parser(fontfile);
    }

    // parsing failed, exit
    if (prsr.run() != 0) {
        std::exit(1);
    }

    // get letter map out of parser
    auto letter_map = prsr.getLetters();

    // find separator letter
    Letter separator_let = letter_map.find("separator")->second;

    std::vector<Letter> letter_vec;

    // exit early if not input text is given
    if (input.empty()) {
        exit(0);
    }

    // fill letter vector with appropriate letters
    for (char ch : input) {
        auto let_iter = letter_map.end();

        switch (ch) {
        case ' ':
            let_iter = letter_map.find("space");
            break;
        default:
            let_iter = letter_map.find(std::string(1, std::tolower(ch)));
            break;
        }
        if (let_iter == letter_map.end()) {
            cerr << "Letter for character '" << ch << "' not found!" << endl;
        } else {
            letter_vec.push_back(let_iter->second);
        }
    }

    int height = prsr.getHeight();

    // print
    for (int line = 0; line < height; line++) {
        for (auto letter : letter_vec) {
            cout << letter[line];
            cout << separator_let[line];
        }
        cout << endl;
    }

    return 0;
}
