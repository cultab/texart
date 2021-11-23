#include "parse.hpp"

#include <exception>
#include <fstream>
#include <new>
#include <ostream>
#include <stdexcept>
#include <string>

static const std::string DEFAULT_FONT_LOCATION = "/usr/local/share/texart/";
static const std::string DEFAULT_FONTFILE = "line_smol.txr";

using std::cerr;
// using std::cout;
using std::endl;

Parser::Parser() : cur_line(1), fontfile(DEFAULT_FONTFILE)
{
    try {
        open_font();
    } catch (std::runtime_error &re) {
        cerr << re.what() << endl;
        exit(2);
    }
}

Parser::Parser(std::string file) : cur_line(1), fontfile(file)
{
    try {
        open_font();
    } catch (std::runtime_error &re) {
        cerr << re.what() << endl;
        exit(2);
    }
}

void Parser::open_font()
{
    font.open(fontfile);

    if (!font.is_open()) {
        font.open(DEFAULT_FONT_LOCATION + fontfile);
    }

    if (!font.is_open()) {
        throw std::runtime_error("Fontfile \"" + fontfile + "\" could not be opened.");
    }
}

int Parser::run()
{
    state s = parse_height();

    while (s != END && s != STOP) {
        switch (s) {
        case HEIGHT:
            s = parse_height();
            break;
        case RUNE:
            s = parse_rune();
            break;
        case WIDTH:
            s = parse_width();
            break;
        case LETTER:
            s = parse_letter();
            break;
        case END:
            break;
        case STOP:
            break;
        default:
            cerr << "????? How ?????" << endl;
            break;
        }
    }

    if (s == END) {
#ifdef DEBUG
        cerr << "Parsing Completed Succesfully!"
             << "probably.." << endl;
#endif
        return 0;
    } else {
        cerr << "Parsing fontfile: \"" << fontfile << "\" failed."
             << endl; // we want to know this even when not debugging
        return 1;
    }
}

Parser::state Parser::parse_height()
{
    font >> cur_height;
#ifdef DEBUG
    cerr << "Font height:" << cur_height << endl;
#endif
    if (cur_height == 0) {
        cerr << "Line " << cur_line << ": font height can not be 0." << endl;
        return STOP;
    } else if (cur_height < 0) {
        cerr << "Line " << cur_line << ": font height can not negative (" << cur_height << ")." << endl;
        return STOP;
    }

    cur_line++;
    return RUNE;
}

Parser::state Parser::parse_rune()
{
    font >> cur_rune_name;

#ifdef DEBUG
    cerr << "Parsing letter:" << cur_rune_name << endl;
#endif

    return WIDTH;
}

Parser::state Parser::parse_width()
{
    font >> cur_width;
#ifdef DEBUG
    cerr << "Current letter width:" << cur_width << endl;
#endif

    cur_line++;
    return LETTER;
}

Parser::state Parser::parse_letter()
{
    char c;
    std::string lines;

    font.get(); // discard newline

    int h = 0;            // height
    int w = 0;            // width
    bool reset_w = false; // reset width ?

    while (h < cur_height * (cur_width + 1)) {
        c = font.get();

#ifdef DEBUG
        cerr << "Read char: '" << (c != '\n' ? std::string(1, c) : "\\n") << "'" << endl;
#endif

        switch (c) {
        case '\n':
            if (w < cur_width) {
                cerr << "Line " << cur_line << ": Expected more characters! (Did you forget to pad with spaces?)"
                     << endl;
                return STOP;
            } else if (w != cur_width) {
                cerr << "Line " << cur_line << ": Too many characters! (Did you forget to trim extra spaces?)" << endl;
                return STOP;
            }
            cur_line++;
            reset_w = true;
            break;
        default:
            lines.append(1, c);
            break;
        }

        h++;

        if (reset_w) {
            w = 0;
            reset_w = false;
        } else {
            w++;
        }
    }

#ifdef DEBUG
    cerr << "Parsed letter: " << cur_rune_name << endl;
#endif

    letters.insert(std::pair<std::string, Letter>(cur_rune_name, Letter(cur_width, cur_height, lines)));

    c = font.peek();

    if (c == EOF) {
        return END;
    }

    return RUNE;
}
