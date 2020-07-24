#pragma once

#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

#define fren friend

class Letter {
    public:
        Letter(int width, int height, const std::string &in);
        const void writeLine(int index, std::ostream &out);
        fren std::ostream& operator<<(std::ostream &out, const Letter &let);

    private:
        // not sure if necessary, keeping track of in case
        int width; 
        int height;
        
        std::vector<std::string> lines;
};
