#pragma once
#ifndef LOGGER_H

#include <fstream>
#include <filesystem>
#include <string>
#include <cstdlib>

class Logger final
{
private:
	std::ofstream logfile;

public:
	Logger();
	~Logger();

public:
	void operator()(char* msg) { logfile << msg << '\n'; }
	void operator()(std::string msg) { operator()(msg.c_str()); }
};

#define LOGGER_H
#endif
