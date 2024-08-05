#pragma once
#ifndef LOGGER_H

#include <fstream>	// ofstream
#include <filesystem>	// exists(), create_directory()
#include <string>	// strings
#include <cstdlib>	// getenv()
#include <ctime>	// asctime()
#include <iostream> // cout
#include <deque>    // deque

class OutputManager final
{
private:
	std::ofstream logfile;    // log file
#ifdef _WIN32
    // cache directory for windows
	const std::string _systemDrive{ getenv("WINDIR") };
	const std::string _cacheDir{ _systemDrive + "\\..\\ProgramData\\TrainingCounter\\" };
#else
    // cache directory for linux
	const std::string home{ getenv("HOME") };
	const std::string dir{ home + "/.TrainingCounter/" };
#endif // _WIN32
	const std::string _logFileName{ _cacheDir + "log.txt" };   // log file path

public:
	enum color { black = 0, red, green, yellow, blue, magenta, cyan, white };
    enum messageType { message, error };

private:
	const std::string _datetime() const noexcept;    // returns current date and time
	void _setColor(const color color = white) const noexcept;

public:
	OutputManager();
	~OutputManager();
	
	void operator()(messageType type, const char* msg, color color = white, bool log = true) noexcept;

	/*
	Writes message in logfile and console

	@param message type
	@param message
	@param message color
	@param need to write log
	*/
	inline void operator()(messageType type, const std::string& msg, color color = white, bool log = true) noexcept
		{ operator()(type, msg.c_str(), color, log); }

	/*
	Writes message in logfile and console

	@param message type
	@param message
	@param message color
	@param need to write log
	*/
    inline void operator()(messageType type, const std::string&& msg, color color = white, bool log = true) noexcept
        { operator()(type, msg.c_str(), color, log); }

	void removeLogfile();
	void showLog(int lines_num = 0);
};

#define LOGGER_H
#endif
