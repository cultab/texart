#include "parse.hpp"

using std::cout;
using std::endl;

Parser::Parser()
{
    font.open("font.txt", std::ios::in);
}

void Parser::run()
{
    state s = parse_height();
    while (s != END) {
        switch(s) {
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
        default:
            std::cout << "?????" << std::endl;
            break;
        }
    }
    std::cout << "Parsing done!" << std::endl;
}

Parser::state Parser::parse_height()
{
    font >> cur_height;
    cout << "Read h:" << cur_height << endl;

    return RUNE;
}

Parser::state Parser::parse_rune()
{
    font >> cur_rune;
    cout << "Read r:" << cur_rune << endl;

    return WIDTH;
}

Parser::state Parser::parse_width()
{
    font >> cur_width;
    cout << "Read w:" << cur_width << endl;

    return LETTER;
}

Parser::state Parser::parse_letter()
{
    char c;
    std::string lines;

    font.get(); // discard newline
    for (int i=0; i<cur_height; i++) {
        //cout << "i:" <<  i << endl;
        for (int j=0; j<cur_width+1; j++) {
            c = font.get();

            switch(c) {
            case '\n':
                break;
            case '@':
                lines.append(1, '@');
                break;
            default:
                lines.append(1, c);
                break;
            }
            //cout << "j:" << j << endl;
            cout << "Read char: '" << (c != '\n' ? c : 'N' ) << "'" << endl;

        }
    }
    cout << "letter end" << endl;

    letters.insert(std::pair<char,Letter>(cur_rune, Letter(cur_width, cur_height, lines)));

    /* cout << "w and h:" << let.getWidth() << " " << let.getHeight() << endl; */

    /* if (let1.first != letters.end()) { */
    /*     cout << "1 w and h:" << let1.first->second.getWidth() << " " << let1.first->second.getHeight() << endl; */
    /* } else { */
    /*     cout << "end" << endl; */
    /* } */
    
    /* auto let2 = letters.find('a'); */
    /* if (let2 != letters.end()) { */
    /*     cout << "2 w and h:" << let2->second.getWidth() << " " << let2->second.getHeight() << endl; */
    /* } else { */
    /*     cout << "end" << endl; */
    /* } */
    /* if (let1.first == let2) { */
    /*     cout << "AAAAAAA" << endl; */
    /* } */

    c = font.peek();

    if (c == EOF) {
        return END;
    }
    return RUNE;
}
