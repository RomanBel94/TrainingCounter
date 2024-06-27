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
	const std::string dir{ "C:\\ProgramData\\TrainingCounter\\" };
#else
	const std::string home{ getenv("HOME") };
	const std::string dir{ home + "/.TrainingCounter/" };
#endif // _WIN32
	std::string file{ dir + "save" };
public:
	Save();
	~Save() {};

	void write(const uint8_t trainings);
	const uint8_t read() const;
};

#define SAVE_H
#endif
