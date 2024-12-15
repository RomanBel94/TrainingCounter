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
        tasks.emplace(currentKey);
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
        _currentArgumentReadingFunction = &LexerParser::_extractSingleCharKey;
        (this->*_currentArgumentReadingFunction)(tokensString.c_str());
    }
    else if (tokensString[0] == DIVIDER && tokensString[1] == DIVIDER)
    {
        _currentArgumentReadingFunction = &LexerParser::_extractMultiCharKey;
        (this->*_currentArgumentReadingFunction)(tokensString.c_str() + 2);
    }
    else 
    {
        throw std::runtime_error(fmt::format("Unexpected token {}", tokensString[0]));
    }

}

/*
    Extracts key from given buffer string

    @param1    buffer string pointer
*/
void LexerParser::_extractSingleCharKey(const char* reader)
{
    if (*reader == '\0') return;
    if (*reader == DIVIDER)
    {
        if (*(reader + 1) == DIVIDER)
        {
            _currentArgumentReadingFunction = &LexerParser::_extractMultiCharKey;
            (this->*_currentArgumentReadingFunction)(reader + 2);
            return;
        }
        else
        {
            ++reader;
        }
    }
    if (_isAllowedSingleKey(*reader))
        currentKey = *reader;
    else
        throw std::runtime_error(fmt::format("Token {} is not allowed", *reader));
    _extractNum(++reader);
}

void LexerParser::_extractMultiCharKey(const char* reader)
{
    currentKey = "";

    while (std::isalpha(*reader) || *reader == '_')
    {
        currentKey += *reader;
        ++reader;
    }
    _currentArgumentReadingFunction = &LexerParser::_extractSingleCharKey;
    _extractNum(reader);
}

/*
    Extracts number from given buffer string

    @param1    buffer string pointer
*/
void LexerParser::_extractNum(const char* reader)
{
    if (currentKey.size() == 1 && _numberIsRequired(currentKey[0]) && !std::isdigit(*reader))
        throw std::runtime_error(fmt::format("Number is required for key {}", currentKey));

    if (isdigit(*reader))
    {
        std::string buffer;
        while (isdigit(*reader))
        {
            buffer.push_back(*reader);
            ++reader;
        }
        currentNum = atoi(buffer.c_str());
    }
    else
    {
        currentNum = 0;
    }

    tasks.emplace(currentKey, currentNum);
    (this->*_currentArgumentReadingFunction)(reader);
}
