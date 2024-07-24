#include "LexerParser.h"

int main()
{

    constexpr int argc = 5;
    const char* argv[] {
        "path/to/program",
        "-a10",
        "-t" ,
        "-l",
        "-m"
    };

    LexerParser parser;
    parser(argc, argv); 

    return 0;
}
