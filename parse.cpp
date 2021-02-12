#include "parse.hpp"

#define DEFAULT_FONTFILE "line.txr"

static const bool DEBUG = false;

using std::cerr;
using std::cout;
using std::endl;

Parser::Parser(): cur_line(1) { font.open(DEFAULT_FONTFILE, std::ios::in); }

Parser::Parser(std::string fontfile): cur_line(1) { font.open(fontfile, std::ios::in); }

int Parser::run()
{
    state s = parse_height();

    while ( s != END && s != STOP ) {
        switch ( s ) {
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
            cerr << "?????" << endl;
            break;
        }
    }

    if ( s == END ) {
        if ( DEBUG )
            cout << "Parsing Completed Succesfully!" << endl << "probably.." << endl;
        return 0;
    } else {
        if ( DEBUG )
            cout << "Parsing FAILED!!!" << endl;
        return 1;
    }
}

Parser::state Parser::parse_height()
{
    font >> cur_height;
    if ( DEBUG )
        cout << "Font height:" << cur_height << endl;

    cur_line++;
    return RUNE;
}

Parser::state Parser::parse_rune()
{
    font >> cur_rune_name;

    if ( DEBUG )
        cout << "Parsing letter:" << cur_rune_name << endl;

    return WIDTH;
}

Parser::state Parser::parse_width()
{
    font >> cur_width;
    if ( DEBUG )
        cout << "Current letter width:" << cur_width << endl;

    cur_line++;
    return LETTER;
}

Parser::state Parser::parse_letter()
{
    char        c;
    std::string lines;

    font.get(); // discard newline

    int  h       = 0; // height
    int  w       = 0; // width
    bool reset_w = false; // reset width ?

    while ( h < cur_height * (cur_width + 1) ) {
        c = font.get();

        if ( DEBUG )
            cout << "Read char: '" << (c != '\n' ? c : 'N') << "'" << endl;

        switch ( c ) {
        case '\n':
            if ( w < cur_width ) {
                cerr << "Line " << cur_line << ": Expected more characters! (Did you forget to pad with spaces?)" << endl;
                return STOP;
            } else if ( w != cur_width ) {
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
    
        if ( reset_w ) {
            w = 0;
            reset_w = false;
        } else {
            w++;
        }
    }

    if ( DEBUG )
        cout << "Parsed letter: " << cur_rune_name << endl;

    letters.insert(std::pair<std::string, Letter>(cur_rune_name, Letter(cur_width, cur_height, lines)));

    c = font.peek();

    if ( c == EOF ) {
        return END;
    }

    return RUNE;
}
