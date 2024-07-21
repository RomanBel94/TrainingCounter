#include "LexerParser.h"

// reads command arguments and defines job and given num
void LexerParser::operator()(int argc, char** argv) noexcept
{
    if (argc > 1 && argv[1][0] == '-')  // process given key
       for (char* i{ argv[1] }; *i; ++i )
           if(isalpha(*i))
               keys.push_back(*i);

    // read num if exists
    if (argc > 2)
        for (int i{ 1 }; i < argc; ++i)
            if(isdigit(argv[i][0]))
                nums.push_back(atoi(argv[i]));
}

const uint16_t LexerParser::getNum() noexcept
{
    auto ret{ *current_num > 0 ? *current_num : 0 };
    ++current_num;
    return ret;
}
