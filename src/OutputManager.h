#pragma once
#ifndef OUTPUT_MANAGER_H

#include <iostream>	// std::cout
#include <string>	// strings

class OutputManager final
{
private:
public:
	OutputManager() {};
	~OutputManager() {};

public:
	void operator()(const char* msg) { std::cout << msg << std::endl; }
	void operator()(std::string msg) { operator()(msg.c_str()); }
};

#define OUTPUT_MANAGER_H
#endif
