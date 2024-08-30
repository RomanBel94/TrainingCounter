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
	const std::string _home{ getenv("HOME") };
	const std::string _cacheDir{ _home + "/.TrainingCounter/" };
#endif // _WIN32
	const std::string _logFileName{ _cacheDir + "log.txt" };   // log file path

private:
	const std::string _datetime() const noexcept;    // returns current date and time

public:
	OutputManager();
	~OutputManager();
	
	/*
		Writes message in logfile and console

		@param message
		@param need to write log
	*/
	template <class T>
	void operator()(T msg, bool log = true) noexcept
	{
		if (log && logfile.is_open())
		{
			logfile << _datetime() << '\t' << msg << '\n';
		}
		std::cout << msg << std::endl;
	}

	void removeLogfile();
	void showLog(size_t lines_num = 0);
};

#define LOGGER_H
#endif
