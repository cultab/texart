#include "letter.hpp"
#include <ostream>
#include <sstream>
#include <stdexcept>

Letter::Letter(int width, int height, const std::string &in): width(width), height(height)
{
    for(int i = 0; i < height; i++){
        std::string substr = in.substr(i * width, width);
        /* std::cerr << "from " << start << " to "  << end << std::endl; */
        /* std::cerr << "content: |" << substr << "|" << std::endl; */
        lines.push_back(substr);
    }
}

std::string Letter::operator[](int index)
{
    if (index < 0 || index > height) {
        throw std::out_of_range("Letter index out of range");
    }
    return lines[index];
}

std::ostream& operator<<(std::ostream &out, const Letter &let)
{
    // fucking word salad, even java is better
    // TODO: use auto ???
    for(auto iter = let.lines.begin(); iter != let.lines.end(); iter++) {
        out << *iter << std::endl;
    }
    return out;
}
