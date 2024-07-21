#include "LexerParser.h"
#include <cctype>

// reads command arguments and defines job and given num
void LexerParser::operator()(int argc, char** argv) noexcept
{
    for (int i{ 1 }; i < argc; ++i)
    {
        if(isdigit(argv[i][0]))
            nums.push_back(atoi(argv[i]));
        else if (argv[i][0] == '-' && isalpha(argv[i][1]))
            for (char* key{argv[i] + 1}; *key; ++key)
            {
                if(isalpha(*key))
                    keys.push_back(*key);
                else if (isdigit(*key))
                    nums.push_back(atoi(key));
            }   
    }
}

const uint16_t LexerParser::getNum() noexcept
{
    auto ret{ *current_num > 0 ? *current_num : 0 };
    ++current_num;
    return ret;
}
