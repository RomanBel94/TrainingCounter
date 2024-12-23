#pragma once
#ifndef SAVE_H

#include <fstream>	// ifstream, ofstream
#include <filesystem>	// exists(), create_directory()
#include <cstdlib>	// getenv()
#include <string>	// strings

#include "../external/fmt/include/fmt/core.h"

class Save final
{
private:

    Save(const Save&) = delete;
    Save(Save&&) = delete;
    Save& operator=(const Save&) = delete;
    Save& operator=(Save&&) = delete;

#ifdef _WIN32
    // cache directory for windows
    inline static const std::string cacheDir{ fmt::format("{}\\..\\ProgramData\\TrainingCounter\\", getenv("WINDIR")) };
#else
    // cache directory for linux
    inline static const std::string cacheDir{ fmt::format("{}/.TrainingCounter/", getenv("HOME")) };
#endif // _WIN32

    // savefile name
    inline static const std::string filename{ fmt::format("{}save", cacheDir) };
public:
    Save();
    ~Save() = default;

    void write(uint32_t trainings) const noexcept;
    const uint32_t read() const noexcept;

    void removeSavefile() const;
    const auto& getCacheDir() const noexcept { return cacheDir; }
};

#define SAVE_H
#endif
