#pragma once
#ifndef PARSER_H

class Parser final
{
private:
	enum job {none=0, add, set, get};
public:
	Parser() {};
	~Parser() {};

	job operator()(char* argv, int& num);
};

#define PARSER_H
#endif
