#pragma once
#ifndef SAVE_H

#include <fstream>	// ifstream, ofstream
#include <filesystem>	// exists(), create_directory()
#include <cstdlib>	// getenv()
#include <string>	// strings

class Save final
{
private:
	std::string home{ getenv("HOME") };
	std::string dir{ home + "/.tc/" };
	std::string file{ dir + "save.sav" };
public:
	Save();
	~Save() {};

	void write(uint8_t trainings);
	uint8_t read() const;
};

#define SAVE_H
#endif
