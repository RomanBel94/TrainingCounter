#pragma once
#ifndef SAVE_H

#include <fstream>	// ifstream, ofstream
#include <filesystem>	// exists(), create_directory()
#include <cstdlib>	// getenv()
#include <string>	// strings

class Save 
{
using string = std::string;

private:
#ifdef _WIN32
    // cache directory for windows
    const string systemDrive{ getenv("WINDIR") };
    const string cacheDir{ systemDrive + "\\..\\ProgramData\\TrainingCounter\\" };
#else
    // cache directory for linux
    const string home{ getenv("HOME") };
    const string cacheDir{ home + "/.TrainingCounter/" };
#endif // _WIN32

    // savefile name
    string filename{ cacheDir + "save" };
public:
    Save();
    virtual ~Save() {}

    void write(const uint32_t trainings);
    const uint32_t read() const;
};

#define SAVE_H
#endif
