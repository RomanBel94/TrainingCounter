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
	const std::string dir{ "C:\\ProgramData\\TrainingCounter\\" };
#else
    // cache directory for linux
	const std::string home{ getenv("HOME") };
	const std::string dir{ home + "/.TrainingCounter/" };
#endif // _WIN32
	std::string filename{ dir + "save" };    // save file name
public:
	Save();

	void write(const uint8_t trainings);    // write save file
	const uint8_t read() const;             // read save file
};

#define SAVE_H
#endif
