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
        std::cout << "before current reading function" << std::endl;
        _currentReadingFunction = &LexerParser::_extractSingleCharKey;
        std::cout << "after current reading function" << std::endl;
        std::cout << "tokensString: " << tokensString << std::endl;
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
    if (*reader == '\0') return;
    std::cout << "reader: " << *reader << std::endl;
    //   -a10-t-l-m
    //    ^ - *reader == 'a' 
    currentKey = *reader;
    std::cout << "currentKey: " << currentKey << std::endl;
    //   -a10-t-l-m
    //    ^ push_back('a')
    _extractNum(++reader);
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
    }
    else
    {
        currentNum = 0;
    }
    
    std::cout << "currentNum: " << currentNum << std::endl;
    tasks.emplace(Task::keys[currentKey], currentNum);
    (this->*_currentReadingFunction)(reader);
}
