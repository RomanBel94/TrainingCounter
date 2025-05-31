#pragma once
#ifndef SAVE_H

#include <cstdlib>    // getenv()
#include <filesystem> // exists(), create_directory()
#include <fstream>    // ifstream, ofstream
#include <string>     // strings

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
    inline static const std::string cacheDir{fmt::format(
        "{}\\..\\ProgramData\\TrainingCounter\\", getenv("WINDIR"))};
#else
    // cache directory for linux
    inline static const std::string cacheDir{
        fmt::format("{}/.TrainingCounter/", getenv("HOME"))};
#endif // _WIN32

    // savefile name
    inline static const std::string filename{fmt::format("{}save", cacheDir)};

public:
    Save();
    ~Save() = default;

    static void write(const uint32_t trainings) noexcept;
    static const uint32_t read() noexcept;

    static void removeSavefile();
    static const auto& getCacheDir() noexcept { return cacheDir; }
};

#define SAVE_H
#endif
