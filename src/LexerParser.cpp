#include "LexerParser.h"

// reads command arguments and defines job and given num
void LexerParser::operator()(int argc, char** argv)
{
    if (argc > 1 && argv[1][0] == '-')  // process given key
        switch (tolower(argv[1][1]))
        {
        case 'a':
            todo = add; break;
        case 's':
            todo = set; break;
        case 'm':
            todo = mark; break;
        case 't':
            todo = show;
        };
    // read num if exists
    if (argc > 2 && isdigit(argv[2][0])) num = atoi(argv[2]);
}
