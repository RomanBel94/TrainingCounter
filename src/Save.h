#pragma once
#ifndef SAVE_H

#include <fstream>
#include <filesystem>

class Save final
{
private:
	std::string savefilePath;
public:
	Save(std::string savefile) : savefilePath(savefile) {};
	~Save() {};

	void writeSavefile(int num);
	int readSavefile();
};

#define SAVE_H
#endif
