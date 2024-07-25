#include "LexerParser.h"

// reads command arguments and defines job and given num
void LexerParser::operator()(int argc, const char** argv) 
{
    if (argc == 1)
    {
        throw std::runtime_error("Undefined task, keys are not given");
    }

    std::string arguments;

    _readArguments(arguments, int argc, const char argv**)
    
    /* DEBUG INFO */    std::cout << arguments << std::endl;
}

const uint16_t LexerParser::getNum() noexcept
{
    return 0;
}

void LexerParser::_readArguments(std::string& strArgs, int argc, const char argv**)
{
    for (int i{ 1 }; i < argc; ++i)
    {
        strArgs += argv[i];
    }
}
