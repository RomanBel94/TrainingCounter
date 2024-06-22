#include "LexerParser.h"


void LexerParser::operator()(int argc, char** argv)
{
    if (argc > 1) {     // check count of args
        switch (argv[1][0]) {
        case '-':                    // process given key
            switch (argv[1][1]) {
            case 'a':
                todo = add; break;
            case 's':
                todo = set; break;
            case 'm':
                todo = mark; break;
            default:
                todo = help;
            }; break;
        default:
            todo = help;
        }
    }

    if (argc > 2 && isdigit(argv[2][0])) num = atoi(argv[2]);
}
