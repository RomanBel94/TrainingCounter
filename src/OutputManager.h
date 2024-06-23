#pragma once
#ifndef OUTPUT_MANAGER_H

#include <iostream>	// std::cout
#include <string>	// strings

class OutputManager final
{
public:
	OutputManager() {};
	~OutputManager() {};

public:
	inline void operator()(const char* msg) const
		{ std::cout << msg << std::endl; }
	
	inline void operator()(std::string msg) const
		{ operator()(msg.c_str()); }
};

#define OUTPUT_MANAGER_H
#endif
