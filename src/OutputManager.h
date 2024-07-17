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

public:
	enum color { black = 0, red, green, yellow, blue, magenta, cyan, white };

private:
	const std::string _datetime();    // returns current date and time
	void _setColor(const color color = white) noexcept;

public:
	OutputManager();
	~OutputManager();

public:
	// write message in file and console
	void operator()(const char* msg, color color = white, bool log = true) noexcept;

	inline void operator()(const std::string& msg, color color = white, bool log = true) noexcept
		{ operator()(msg.c_str(), color, log); }

    inline void operator()(const std::string&& msg, color color = white, bool log = true) noexcept
        { operator()(msg.c_str(), color, log); }

	// removes log file
	bool removeLogfile();

	// shows log file
	void showLog() noexcept;
};

#define LOGGER_H
#endif
