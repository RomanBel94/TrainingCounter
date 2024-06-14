#pragma once
#ifndef SAVE_H

#include <fstream>	// ifstream, ofstream
#include <filesystem>	// exists(), create_directory()
#include <cstdlib>	// getenv()

class Save final
{
private:
	/*
	TODO: create constructor that initializes directory, i have to refactor this class!!!!!


	*/
public:
	Save() {};
	~Save() {};

	void write(uint8_t trainings);
	uint8_t read();
};

#define SAVE_H
#endif
