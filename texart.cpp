
#include "letter.hpp"


int main(int argc, char** argv)
{

    const int height = 5;
    Letter a = Letter(3, height, " # # ##### ## #");
    Letter b = Letter(3, height, "## # ### # ### ");
    Letter c = Letter(3, height, "####  #  #  ###");
    Letter d = Letter(3, height, "## # ## ## ### ");
    Letter e = Letter(3, height, "####  ## #  ###");
    Letter f = Letter(3, height, "####  ## #  #  ");
    Letter g = Letter(3, height, "               ");
    Letter h = Letter(3, height, "               ");
    Letter j = Letter(3, height, "               ");
    Letter k = Letter(3, height, "               ");
    Letter l = Letter(3, height, "               ");
    Letter m = Letter(3, height, "               ");
    Letter n = Letter(3, height, "               ");
    Letter o = Letter(3, height, "               ");
    Letter p = Letter(3, height, "               ");
    Letter q = Letter(3, height, "               ");
    Letter r = Letter(3, height, "               ");
    Letter s = Letter(3, height, "               ");
    Letter t = Letter(3, height, "               ");
    Letter u = Letter(3, height, "               ");
    Letter v = Letter(3, height, "               ");
    Letter w = Letter(3, height, "               ");
    Letter x = Letter(3, height, "               ");
    Letter y = Letter(3, height, "               ");
    Letter z = Letter(3, height, "               ");
    Letter let_spc = Letter(1, height, "     ");
    Letter space = Letter(3, height, "               ");
    //std::cout << a;

    for(int i=0; i<5; i++) {
        d.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        e.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        a.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        d.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        space.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        b.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        e.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        e.writeLine(i, std::cout);
        let_spc.writeLine(i, std::cout);
        f.writeLine(i, std::cout);
        std::cout << std::endl;

    }



    return 0;
}
