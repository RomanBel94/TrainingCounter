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

    Save(const Save&) = delete;
    Save(Save&&) = delete;
    Save& operator=(const Save&) = delete;
    Save& operator=(Save&&) = delete;

#ifdef _WIN32
    // cache directory for windows
    inline static const string m_systemDrive{ getenv("WINDIR") };
    inline static const string m_cacheDir{ systemDrive + "\\..\\ProgramData\\TrainingCounter\\" };
#else
    // cache directory for linux
    inline static const string m_home{ getenv("HOME") };
    inline static const string m_cacheDir{ m_home + "/.TrainingCounter/" };
#endif // _WIN32

    // savefile name
    inline static const string filename{ m_cacheDir + "save" };
public:
    Save();
    virtual ~Save() {}

    void write(const uint32_t trainings) const;
    const uint32_t read() const;
};

#define SAVE_H
#endif
