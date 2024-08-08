#pragma once
#ifndef SAVE_H

#include <fstream>	// ifstream, ofstream
#include <filesystem>	// exists(), create_directory()
#include <cstdlib>	// getenv()
#include <string>	// strings

class Save final
{
private:
#ifdef _WIN32
    // cache directory for windows
	const std::string _systemDrive{ getenv("WINDIR") };
	const std::string _cacheDir{ _systemDrive + "\\..\\ProgramData\\TrainingCounter\\" };
#else
    // cache directory for linux
	const std::string _home{ getenv("HOME") };
	const std::string _cacheDir{ _home + "/.TrainingCounter/" };
#endif // _WIN32

	// savefile name
	std::string _filename{ _cacheDir + "save" };
public:
	Save();

	void write(const uint16_t trainings);
	const uint16_t read() const;
};

#define SAVE_H
#endif
