#pragma once
#ifndef LOGGER_H

#include <fstream>	// ofstream
#include <filesystem>	// exists(), create_directory()
#include <string>	// msg
#include <cstdlib>	// getenv()
#include <exception>	// runtime_error()
#include <ctime>	// asctime()

class Logger final
{
private:
	std::ofstream logfile;

private:
	char* _datetime();

public:
	Logger();
	~Logger();

public:
	void operator()(const char* msg)
		{ logfile << _datetime() << msg << '\n'; }
	void operator()(std::string msg) { operator()(msg.c_str()); }
};

#define LOGGER_H
#endif
