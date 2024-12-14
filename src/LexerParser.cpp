#include "LexerParser.h"

/*
    Reads "argv" parameter, extracts given keys and number arguments
    and places them in _keys and _nums collections

    @param1    argc parameter from main()
    @param2    argv parameter from main()
*/
void LexerParser::parseCommandLine(int argc, char** argv)
{
    if (argc == 1)
    {
        tasks.emplace(Task(Task::jobType::undefined));
        return;
    }

    std::string arguments;

    _collectArguments(arguments, argc, argv);
    _extractTokens(arguments);
}

/*
    Reads arguments from argv and places them in one buffer

    @param1    buffer for writing arguments
    @param2    argc parameter from main()
    @param3    argv parameter from main()
*/
void LexerParser::_collectArguments(std::string& strArgs, int argc, char** argv) noexcept
{
    for (int i{ 1 }; i < argc; ++i) strArgs += argv[i];
}

/*
    Entry point for parsing start

    @param1    buffer with all read arguments
*/
void LexerParser::_extractTokens(const std::string& tokensString)
{
    if (tokensString[0] == DIVIDER && tokensString[1] != DIVIDER)
    {
        _currentReadingFunction = &LexerParser::_extractSingleCharKey;
        (this->*_currentReadingFunction)(tokensString.c_str() + 1);
    }
    else throw std::runtime_error(fmt::format("Unexpected token {}", tokensString[0]));
}

/*
    Extracts key from given buffer string

    @param1    buffer string pointer
*/
void LexerParser::_extractSingleCharKey(const char* reader)
{
    //   -a10-t-l-m
    //   ^ - *reader == '-'
    if (!*reader && *(reader - 1) != DIVIDER)
    {
        return;
    }
    else if (*reader == DIVIDER || std::isalpha(*reader))
    {
        *reader == DIVIDER ? ++reader : reader;
        //   -a10-t-l-m
        //    ^ - *reader == 'a' 
        if (
            _numberIsRequired(*reader) ||
            _numberIsOptional(*reader) && isdigit(*(reader + 1))
            )
        {
            currentKey = *reader;
            //   -a10-t-l-m
            //    ^ push_back('a')
            ++reader;
            //   -a10-t-l-m
            //     ^ - *reader == '1'
            _extractNum(reader);
        }
        //   -a10-t-l-m
        //        ^ - *reader == 't' 
        else if (_numberIsNotRequired(*reader) || _numberIsOptional(*reader))
        {
            tasks.emplace(Task::keys[*reader]);
            //   -a10-t-l-m
            //        ^ push_back('t')
            ++reader;
            //   -a10-t-l-m
            //         ^ - *reader == '-'
            (this->*_currentReadingFunction)(reader);
        }
        else
        {
            throw std::runtime_error(fmt::format("Unexpected token {}", *reader));
        }
    }
    else
    {
        throw std::runtime_error(fmt::format("Unexpected token {}", *reader));
    }
}

/*
    Extracts number from given buffer string

    @param1    buffer string pointer
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
        currentNum = atoi(buffer.c_str());

        tasks.emplace(Task::keys[currentKey], currentNum);
        (this->*_currentReadingFunction)(reader);
    }
    else
    {
        throw std::runtime_error("Number is required");
    }
}
