#include <iostream>

#include "letter.hpp"
#include "parse.hpp"


int main(int argc, char** argv)
{

    /* const int height = 5; */
    /* Letter a = Letter(3, height, " # # ##### ## #"); */
    /* Letter b = Letter(3, height, "## # ### # ### "); */
    /* Letter c = Letter(3, height, "####  #  #  ###"); */
    /* Letter d = Letter(3, height, "## # ## ## ### "); */
    /* Letter e = Letter(3, height, "####  ## #  ###"); */
    /* Letter f = Letter(3, height, "####  ## #  #  "); */
    /* Letter g = Letter(4, height, "#####   # ###  #####"); */
    /* Letter h = Letter(3, height, "# ## ##### ## #"); */
    /* Letter i = Letter(3, height, "### #  #  # ###"); */
    /* Letter j = Letter(3, height, "  #  #  ## ####"); */
    /* Letter k = Letter(4, height, "# ### # ##  # # # ##"); */
    /* Letter l = Letter(3, height, "#  #  #  #  ###"); */
    /* Letter m = Letter(6, height, "##  ### ## ##    ##    ##    #"); */
    /* Letter n = Letter(6, height, "##   ## #  ##  # ##   ###    #"); */
    /* Letter o = Letter(3, height, "#### ## ## ####"); */
    /* Letter p = Letter(3, height, "#### #####  #  "); */
    /* Letter q = Letter(4, height, "### # # # # # # ## #"); */
    /* Letter r = Letter(3, height, "## # ### # ## #"); */
    /* Letter s = Letter(3, height, "####  ###  ####"); */
    /* Letter t = Letter(3, height, "### #  #  #  # "); */
    /* Letter u = Letter(3, height, "# ## ## ## ####"); */
    /* Letter v = Letter(3, height, "# ## ## ## # # "); */
    /* Letter w = Letter(3, height, "               "); */
    /* Letter x = Letter(3, height, "               "); */
    /* Letter y = Letter(3, height, "               "); */
    /* Letter z = Letter(3, height, "               "); */
    /* Letter let_spc = Letter(1, height, "     "); */
    /* Letter space = Letter(3, height, "               "); */

    Parser prsr = Parser();

    prsr.run();

    auto let1 = prsr.letters.find('d');
    auto let2 = prsr.letters.find('e');
    auto let3 = prsr.letters.find('a');
    for(int line=0; line<5; line++) {
        std::cout << let1->second[line];
        std::cout << let2->second[line];
        std::cout << let3->second[line];
        std::cout << std::endl;
    }



    return 0;
}
