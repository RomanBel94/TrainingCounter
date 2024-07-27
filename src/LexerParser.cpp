#include "LexerParser.h"

/*
    Reads "argv" parameter, extracts given keys and number arguments
    and places them in _keys and _nums collections

    @ param1    argc parameter from main()
    @ param2    argv parameter from main()
*/
void LexerParser::operator()(int argc, char** argv)
{
    if (argc == 1)
    {
        throw std::runtime_error(_undefinedTaskErrorMessage);
    }

    std::string arguments;
    arguments.reserve(UINT8_MAX);

    _collectArguments(arguments, argc, argv);
    _extractTokens(arguments);
}

/*
    Returns first number from _nums collection

    @ return    uint16_t <number given for key>
*/
const uint16_t LexerParser::getNum() noexcept
{
    uint16_t ret{ _nums.at(0) };
    _nums.pop_front();
    return ret;
}

/*
    Reads arguments from argv and places them in one buffer

    @ param1    buffer for writing arguments
    @ param2    argc parameter from main()
    @ param3    argv parameter from main()
*/
void LexerParser::_collectArguments(std::string& strArgs, int argc, char** argv) noexcept
{
    for (int i{ 1 }; i < argc; ++i) strArgs += argv[i];
}

/*
    Entry point for parsing start

    @ param1    buffer with all read arguments
*/
void LexerParser::_extractTokens(const std::string& tokensString)
{
    _extractKey(tokensString.c_str());
}

/*
    Extracts key from given buffer string

    @ param1    buffer string pointer
*/
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
        if (
            *reader == 'a' || 
            *reader == 's' || 
            (*reader == 'l' && isdigit(*(reader + 1)))
            )
        {
            _validateKey(*reader);

            _keys.push_back(*reader);
            //   -a10-t-l-m
            //    ^ push_back('a')
            ++reader;
            //   -a10-t-l-m
            //     ^ - *reader == '1'
            _extractNum(reader);
        }
        //   -a10-t-l-m
        //        ^ - *reader == 't' 
        else if (
                 *reader == 't' || 
                 *reader == 'h' || 
                 *reader == 'm' || 
                 *reader == 'v' || 
                 *reader == 'r' || 
                 (*reader == 'l' && !isdigit(*(reader + 1)))
                 )
        {
            _validateKey(*reader);

            _keys.push_back(*reader);
            //   -a10-t-l-m
            //        ^ push_back('t')
            if (*reader == 'l') _nums.push_back(0);

            ++reader;
            //   -a10-t-l-m
            //         ^ - *reader == '-'
            _extractKey(reader);
        }
    }
    else
    {
        _unexpectedTokenErrorMessage += *(reader - 1);
        throw std::runtime_error(_unexpectedTokenErrorMessage);
    }
}

/*
    Extracts number from given buffer string

    @ param1    buffer string pointer
*/
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
            //   -a10-t-l-m             |   -a10-t-l-m
            //     ^ push_back('1')     |      ^ push_back('0')
            ++reader;
            //   -a10-t-l-m             |   -a10-t-l-m
            //      ^ - reader          |       ^ - reader
        }
        _nums.push_back(atoi(buffer.c_str()));

        _extractKey(reader);
    }
    else
    {
        *reader == '\0' ?
            _unexpectedTokenErrorMessage += "\\0" :
            _unexpectedTokenErrorMessage += *reader;

        throw std::runtime_error(_unexpectedTokenErrorMessage);
    }
}
