#pragma once
#ifndef LOGGER_H

#include <fstream>	// ofstream
#include <filesystem>	// exists(), create_directory()
#include <string>	// strings
#include <cstdlib>	// getenv()
#include <exception>	// runtime_error()
#include <ctime>	// asctime()
#include <iostream> // cout

class OutputManager final
{
private:
	std::ofstream logfile;

	const std::string home{ getenv("HOME") };
	const std::string dir{ home + "/.TrainingCounter/" };
	const std::string file{ dir + "log.txt" };

private:
	std::string _datetime();

public:
	OutputManager();
	~OutputManager();

public:
	inline void operator()(const char* msg) noexcept
		{ logfile << _datetime() << '\t' << msg << '\n';
          std::cout << msg << std::endl; }

	inline void operator()(std::string msg) noexcept
		{ operator()(msg.c_str()); }
};

#define LOGGER_H
#endif
