#include "LexerParser.h"


void LexerParser::operator()(int argc, char** argv)
{
    if (argc > 1) {     // check count of args
        if (argv[1][0] == '-') {    // process given key
            switch (argv[1][1]) {
            case 'a':
                todo = add; break;
            case 's':
                todo = set; break;
            //case 'h':
            //    todo = help; break;
            case 'm':
                todo = mark;
            default:
                todo = help;
            }
        }
        else todo = help;
    }

    if (argc > 2 && isdigit(argv[2][0])) num = atoi(argv[2]);
}
