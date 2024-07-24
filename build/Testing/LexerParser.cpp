#include "LexerParser.h"

// reads command arguments and defines job and given num
void LexerParser::operator()(int argc, const char** argv) 
{
    if (argc == 1)
    {
        throw std::runtime_error("Undefined task, keys are not given");
    }

    std::string arguments;

    for(int i{ 1 }; i < argc; ++i)
    {
        arguments += argv[i];
    }
    /* DEBUG INFO */    std::cout << arguments << std::endl;
}

const uint16_t LexerParser::getNum() noexcept
{
    return 0;
}
