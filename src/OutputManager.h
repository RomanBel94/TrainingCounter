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
#ifdef _WIN32
	const std::string dir{ "C:\\ProgramData\\TrainingCounter\\" };
#else
	const std::string home{ getenv("HOME") };
	const std::string dir{ home + "/.TrainingCounter/" };
#endif // _WIN32
	const std::string file{ dir + "log.txt" };

private:
	const std::string _datetime();

public:
	OutputManager();
	~OutputManager();

public:
	inline void operator()(const char* msg) noexcept
		{ logfile << _datetime() << '\t' << msg << '\n';
          std::cout << msg << std::endl; }

	inline void operator()(const std::string& msg) noexcept
		{ operator()(msg.c_str()); }

    inline void operator()(const std::string&& msg) noexcept
        { operator()(msg.c_str()); }
};

#define LOGGER_H
#endif
