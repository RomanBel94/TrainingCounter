#pragma once
#ifndef LEXERPARSER_H

#include <stdint.h>
#include <forward_list>
#include <string>

class LexerParser final
{
public:
	enum job {usage=0, add, set, get, mark};

private:
    job todo{ usage };
    uint8_t num{ 0 };

    class Token
    {
    public:
        enum tokType { undefined=0, job, num };

    private:
        std::string content;
        tokType type;

    public:
        Token(std::string& content, tokType type) : content(content), type(type) {};
        std::string& getContent() { return content; }
        tokType getType() { return type; }
    };
    
    std::forward_list<Token> tokens;

public:
	LexerParser() {};
	~LexerParser() {};

	void operator()(int argc, char** argv);
    job getJob() { return todo; }
    uint8_t getNum(){ return num; }
};

#define LEXERPARSER_H
#endif
