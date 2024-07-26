#include "LexerParser.h"

// reads command arguments and defines job and given num
void LexerParser::operator()(int argc, char** argv)
{
    if (argc == 1)
    {
        throw std::runtime_error("Undefined task, keys are not given. Use \"TrainingCounter -h\" for help");
    }

    std::string arguments;
    arguments.reserve(UINT8_MAX);

    _collectArguments(arguments, argc, argv);
    _extractTokens(arguments);
}

const uint16_t LexerParser::getNum() noexcept
{
    uint16_t ret{ nums.at(0) };
    nums.pop_front();
    return ret;
}

void LexerParser::_collectArguments(std::string& strArgs, int argc, char** argv) noexcept
{
    for (int i{ 1 }; i < argc; ++i) strArgs += argv[i];
}

void LexerParser::_extractTokens(const std::string& tokensString)
{
    const char* reader = tokensString.c_str();

    if (*reader) _extractKey(reader);
    else throw std::runtime_error("Undefined task, keys are not given");
}

void LexerParser::_extractKey(const char* reader)
{
    //   -a10-t-l-m
    //   ^ - *reader == '-'
    if (!*reader)
    {
        return;
    }
    else if (*reader++ == '-')
    {
        //   -a10-t-l-m
        //    ^ - *reader == 'a' 
        if (*reader == 'a' || *reader == 's' || (*reader == 'l' && isdigit(*(reader + 1))))
        {
            _validateKey(*reader);

            keys.push_back(*reader);
            //   -a10-t-l-m
            //    ^ push_back('a')
            ++reader;
            //   -a10-t-l-m
            //     ^ - *reader == '1'
            _extractNum(reader);
        }
        //   -a10-t-l-m
        //        ^ - *reader == 't' 
        else if (*reader == 't' || *reader == 'm' || *reader == 'h' || *reader == 'v' || *reader == 'r' || (*reader == 'l' && !isdigit(*(reader + 1))))
        {
            _validateKey(*reader);

            keys.push_back(*reader);
            //   -a10-t-l-m
            //        ^ push_back('t')
            if (*reader == 'l') nums.push_back(0);

            ++reader;
            //   -a10-t-l-m
            //         ^ - *reader == '-'
            _extractKey(reader);
        }
    }
    else throw std::runtime_error(std::string("Unexpected token \"") + *reader + "\"");
}

void LexerParser::_extractNum(const char* reader)
{

    if (isdigit(*reader))
        //   -a10-t-l-m
        //     ^ *reader == 1
    {
        std::string buffer;

        while (isdigit(*reader))
        {
            buffer.push_back(*reader);
            //   -a10-t-l-m
            //     ^ push_back('1')
            ++reader;
        }
        nums.push_back(atoi(buffer.c_str()));

        _extractKey(reader);
    }
    else throw std::runtime_error(std::string("Unexpected token \"") + *reader + "\" token has to be a number");
}
