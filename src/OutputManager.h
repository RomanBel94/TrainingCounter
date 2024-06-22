#pragma once
#ifndef OUTPUT_MANAGER_H

#include <iostream>	// std::cout
#include <string>	// strings

class OutputManager final
{
private:
    std::string helpMessage = 
        "Usage:\n\n"
        "\ttc -a <num>\tAdd <num> workouts;\n"
        "\ttc -s <num>\tSet <num> workouts;\n"
        "\ttc -m\t\tMark completed workout;\n"
        "\ttc [-h]\t\tPrint help;\n"
        "\ttc -w\t\tShow remaining workouts.\n";
public:
	OutputManager() {};
	~OutputManager() {};

    void printHelp() { operator()(helpMessage); }
public:
	inline void operator()(const char* msg) const
		{ std::cout << msg << std::endl; }
	
	inline void operator()(std::string msg) const
		{ operator()(msg.c_str()); }
};

#define OUTPUT_MANAGER_H
#endif
