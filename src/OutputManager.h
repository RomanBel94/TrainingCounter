#pragma once
#ifndef LOGGER_H

#include <fstream>	// ofstream
#include <filesystem>	// exists(), create_directory()
#include <string>	// strings
#include <cstdlib>	// getenv()
#include <ctime>	// asctime()
#include <iostream> // cout

class OutputManager final
{
private:
	std::ofstream logfile;    // log file
#ifdef _WIN32
    // cache directory for windows
	const std::string dir{ "C:\\ProgramData\\TrainingCounter\\" };
#else
    // cache directory for linux
	const std::string home{ getenv("HOME") };
	const std::string dir{ home + "/.TrainingCounter/" };
#endif // _WIN32
	const std::string file{ dir + "log.txt" };   // log file path

private:
	const std::string _datetime();    // returns current date and time

public:
	enum color { black = 0, red, green, yellow, blue, magenta, cyan, white };

public:
	OutputManager();
	~OutputManager();

public:
	inline void operator()(const char* msg) noexcept   // write message in file and console
		{ logfile << _datetime() << '\t' << msg << '\n';
          std::cout << msg << std::endl; }

	inline void operator()(const std::string& msg) noexcept
		{ operator()(msg.c_str()); }

    inline void operator()(const std::string&& msg) noexcept
        { operator()(msg.c_str()); }

	inline void resetColor() noexcept { setColor(white); }
	void setColor(const color color) noexcept;
};

#define LOGGER_H
#endif
