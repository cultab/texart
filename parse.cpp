#include "parse.hpp"

using std::cerr;
using std::cout;
using std::endl;

Parser::Parser() { font.open("bfont.txt", std::ios::in); }

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
        cout << "Parsing Completed Succesfully!" << endl << "probably.." << endl;
        return 0;
    } else {
        cout << "Parsing FAILED!!!" << endl;
        return 1;
    }
}

Parser::state Parser::parse_height()
{
    font >> cur_height;
    cout << "Font height:" << cur_height << endl;

    return RUNE;
}

Parser::state Parser::parse_rune()
{
    font >> cur_rune_name;

    cout << "Parsing letter:" << cur_rune_name << endl;

    return WIDTH;
}

Parser::state Parser::parse_width()
{
    font >> cur_width;
    cout << "Current letter width:" << cur_width << endl;

    return LETTER;
}

Parser::state Parser::parse_letter()
{
    char        c;
    std::string lines;

    font.get(); // discard newline
    for ( int i = 0; i < cur_height; i++ ) {
        // cout << "i:" <<  i << endl;
        for ( int j = 0; j < cur_width + 1; j++ ) {
            c = font.get();

            switch ( c ) {
            case '\n':
                if ( j != cur_width ) {
                    cerr << "Expected more characters on line! (Did you forget to pad with spaces?)" << endl;
                    return STOP;
                }
                break;
            default:
                lines.append(1, c);
                break;
            }
            // cout << "j:" << j << endl;
            cout << "Read char: '" << (c != '\n' ? c : 'N') << "'" << endl;
        }
    }
    cout << "Parsed letter: " << cur_rune_name << endl;

    letters.insert(std::pair<std::string, Letter>(cur_rune_name, Letter(cur_width, cur_height, lines)));

    c = font.peek();

    if ( c == EOF ) {
        return END;
    }
    return RUNE;
}
