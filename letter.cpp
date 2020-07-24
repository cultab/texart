#include "letter.hpp"

Letter::Letter(int width, int height, const std::string &in): width(width), height(height)
{
    int start, len;
    for(int i = 0; i < height; i++){
        start = i * width;
        len = width;
        std::string substr = in.substr(start, len);
        /* std::cerr << "from " << start << " to "  << end << std::endl; */
        /* std::cerr << "content: |" << substr << "|" << std::endl; */
        lines.push_back(substr);
    }
}

const void Letter::writeLine(int index, std::ostream &out)
{
    out << lines[index];
}

std::ostream& operator<<(std::ostream &out, const Letter &let)
{
    // fucking word salad, even java is better
    // TODO: use auto ???
    std::vector<std::string>::const_iterator iter;
    for(iter = let.lines.begin(); iter != let.lines.end(); iter++) {
        out << *iter << std::endl;
    }
    return out;
}
